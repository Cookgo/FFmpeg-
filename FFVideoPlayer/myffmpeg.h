#ifndef MYFFMPEG_H
#define MYFFMPEG_H

#include <QMutex>

extern "C"
{
#include <libavformat/avformat.h>
#include<libswscale/swscale.h>
#include <libswresample/swresample.h>
}

class MyFFmpeg
{
public:
    static MyFFmpeg *GetObj()
    {
        static MyFFmpeg ff;
        return &ff;
    }

    virtual ~MyFFmpeg();

    int OpenVideo(const char *path);
    int DecodeFrame(const AVPacket *pkt); //返回 pts
    AVPacket ReadFrame();
    bool YuvToRGB(char *out, int outweight, int outheight);
    int ToPCM(char *out);

    void CloseForeVideo();

    //pos 0~~1
    bool Seek(float pos);

    int GetPts(const AVPacket *pkt);

public:
    bool m_isPlay;
    AVFrame *m_yuv = NULL; //视频帧数据
    AVFrame *m_pcm = NULL;
    SwsContext *m_cCtx = NULL; //转换器

    int m_sampleRate = 48000;
    int m_sampleSize = 16;
    int m_channel = 2;

    int m_videoStream = 0;
    int m_audioStream = 1;

    int m_pts; //当前视频播放进度
    int m_totalMs;

protected:
    MyFFmpeg();

    AVFormatContext* m_afc = NULL;

    QMutex mtx;
    SwrContext *m_aCtx = NULL; //音频
};
#endif // MYFFMPEG_H
