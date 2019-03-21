#include "myffmpeg.h"

static double r2d(AVRational r)
{
    return r.num == 0 || r.den == 0 ? 0. : (double)r.num / (double)r.den;
}

MyFFmpeg::MyFFmpeg()
{
    //ffmpeg编程的第一句
    av_register_all();

    m_isPlay = false;
}


MyFFmpeg::~MyFFmpeg()
{
}

int MyFFmpeg::OpenVideo(const char *path)
{
    CloseForeVideo();

    mtx.lock();
    int nRet = avformat_open_input(&m_afc, path, 0, 0);
    if (nRet != 0)
    {
        mtx.unlock();
        char buf[1024] = { 0 };
        av_strerror(nRet, buf, sizeof(buf));
        return 0;
    }

    m_totalMs = (m_afc->duration / AV_TIME_BASE) * 1000;  //视频的时间，结果是多少豪秒

    //打开解码器
    for (int i = 0; i < m_afc->nb_streams; i++)  //nb_streams打开的视频文件中流的数量，一般nb_streams = 2，音频流和视频流
    {
        AVCodecContext *acc = m_afc->streams[i]->codec; //分别获取音频流和视频流的解码器

        if (acc->codec_type == AVMEDIA_TYPE_VIDEO)   //如果是视频
        {
            m_videoStream = i;
            AVCodec *codec = avcodec_find_decoder(acc->codec_id);   // 解码器

            //"没有该类型的解码器"
            if (!codec)
            {
                mtx.unlock();
                qDebug("没有该类型的解码器");
                return 0;
            }

            //解码器打开失败
            int err = avcodec_open2(acc, codec, NULL);

            if (err != 0)
            {
                //解码器打开失败
                mtx.unlock();
                char buf[1024] = { 0 };
                av_strerror(err, buf, sizeof(buf));
                 qDebug("解码器打开失败");
                return 0;
            }
        }
        else if (acc->codec_type == AVMEDIA_TYPE_AUDIO)
        {
            m_audioStream = i;
            AVCodec *codec = avcodec_find_decoder(acc->codec_id);
            int aRet = avcodec_open2(acc, codec, NULL);
            if (aRet < 0)
            {
                mtx.unlock();
                return 0;
            }

            //设置音频参数
            this->m_sampleRate = acc->sample_rate; //采样频率
            this->m_channel = acc->channels;       //通道数
            switch (acc->sample_fmt)
            {
            case AV_SAMPLE_FMT_S16:
                this->m_sampleSize = 16;
                break;
            case AV_SAMPLE_FMT_S32:
                this->m_sampleSize = 32;
                break;
            default:
                break;
            }
        }
    }
    mtx.unlock();

    return m_totalMs;
}

void MyFFmpeg::CloseForeVideo()
{
    mtx.lock();
    if (m_afc)
    {
        avformat_close_input(&m_afc);
    }

    if (m_yuv)
    {
        av_frame_free(&m_yuv);
    }

    if (m_cCtx)
    {
        sws_freeContext(m_cCtx);
        m_cCtx = NULL;
    }

    if (m_aCtx)
    {
        swr_free(&m_aCtx);
    }

    mtx.unlock();
}

int MyFFmpeg::DecodeFrame(const AVPacket *pkt)
{
    mtx.lock();
    if (!m_afc)
    {
        mtx.unlock();
        return 0;
    }

    if (m_yuv == NULL)
    {
        m_yuv = av_frame_alloc();
    }

    if (m_pcm == NULL)
    {
        m_pcm = av_frame_alloc();
    }

    AVFrame *frame = m_yuv;  //解码后m_yuv会改变
    if (pkt->stream_index == m_audioStream)
    {
        frame = m_pcm;
    }

    //根据索引 stream_index 来判断是音频还是视频
    int re = avcodec_send_packet(m_afc->streams[pkt->stream_index]->codec, pkt);
    if (re != 0)
    {
        mtx.unlock();
        return 0;
    }

    re = avcodec_receive_frame(m_afc->streams[pkt->stream_index]->codec, frame);
    if (re != 0)
    {
        //失败
        mtx.unlock();
        return 0;
    }
    mtx.unlock();

    int p = (frame->pts * r2d(m_afc->streams[pkt->stream_index]->time_base)) * 1000; //毫秒数
    if (pkt->stream_index == m_audioStream)
    {
        this->m_pts = p;
    }

    return m_pts;
}

AVPacket MyFFmpeg::ReadFrame()
{
    AVPacket pkt;
    memset(&pkt, 0, sizeof(AVPacket));

    mtx.lock();
    if (!m_afc)
    {
        mtx.unlock();
        return pkt;
    }

    int err = av_read_frame(m_afc, &pkt);
    if (err != 0)
    {
        //失败
    }
    mtx.unlock();

    return  pkt;
}

bool MyFFmpeg::YuvToRGB(char *out, int outweight, int outheight)
{
    mtx.lock();
    if (!m_afc || !m_yuv) //像素转换的前提是视频已经打开
    {
        mtx.unlock();
        return false;
    }

    AVCodecContext *videoCtx = m_afc->streams[this->m_videoStream]->codec;
    m_cCtx = sws_getCachedContext(m_cCtx, videoCtx->width, videoCtx->height,
        videoCtx->pix_fmt,  //像素点的格式
        outweight, outheight,  //目标宽度与高度
        AV_PIX_FMT_BGRA,  //输出的格式
        SWS_BICUBIC,  //算法标记
        NULL, NULL, NULL
        );

    if (m_cCtx)
    {
        //sws_getCachedContext 成功"
    }
    else
    {
        mtx.unlock();
        //"sws_getCachedContext 失败"
        return false;
    }

    uint8_t *data[AV_NUM_DATA_POINTERS] = { 0 };

    data[0] = (uint8_t *)out;  //指针传值，形参的值会被改变，out的值一直在变，所以QImage每次的画面都不一样，画面就这样显示出来了，这应该是整个开发过程最难的点
    int linesize[AV_NUM_DATA_POINTERS] = { 0 };
    linesize[0] = outweight * 4;  //每一行转码的宽度

    //返回转码后的高度
    int h = sws_scale(m_cCtx, m_yuv->data, m_yuv->linesize, 0, videoCtx->height,
        data,
        linesize
        );
//    return true;
    mtx.unlock();


}

int MyFFmpeg::ToPCM(char *out)
{
    mtx.lock();
    if (!m_afc || !m_pcm || !out)
    {
        mtx.unlock();
        return 0;
    }

    AVCodecContext *ctx = m_afc->streams[m_audioStream]->codec;
    if (m_aCtx == NULL)
    {
        m_aCtx = swr_alloc();
        swr_alloc_set_opts(m_aCtx, ctx->channel_layout,
            AV_SAMPLE_FMT_S16,
            ctx->sample_rate,
            ctx->channels,
            ctx->sample_fmt,
            ctx->sample_rate,
            0, 0);

        swr_init(m_aCtx);
    }

    uint8_t *data[1];
    data[0] = (uint8_t *)out;
    int len = swr_convert(m_aCtx, data, 10000, (const uint8_t **)m_pcm->data, m_pcm->nb_samples);
    if (len <= 0)
    {
        mtx.unlock();
        return 0;
    }

    int outsize = av_samples_get_buffer_size(NULL, ctx->channels, m_pcm->nb_samples, AV_SAMPLE_FMT_S16, 0);
    mtx.unlock();

    return outsize;
}

bool MyFFmpeg::Seek(float pos)
{
    mtx.lock();

    if (!m_afc)
    {
        mtx.unlock();
        return false;
    }

    int64_t stamp = 0;
    stamp = pos * m_afc->streams[m_videoStream]->duration;
    int re = av_seek_frame(m_afc, m_videoStream, stamp, AVSEEK_FLAG_BACKWARD | AVSEEK_FLAG_FRAME); //向后|关键帧

    //清除之前的解码缓冲
    avcodec_flush_buffers(m_afc->streams[m_videoStream]->codec);
    mtx.unlock();
    if (re >= 0)
    {
        return true;
    }
    //关键帧，P帧， B帧
   else return false;
}

int MyFFmpeg::GetPts(const AVPacket *pkt)
{
    mtx.lock();
    if (!m_afc)
    {
        mtx.unlock();
        return -1;
    }
    int pts = (pkt->pts * r2d(m_afc->streams[pkt->stream_index]->time_base)) * 1000; //毫秒数
    mtx.unlock();
    return pts;
}

