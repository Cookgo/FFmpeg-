#include "myaudio.h"
MyAudio::MyAudio()
{
}


MyAudio::~MyAudio()
{
}

void MyAudio::Stop()
{
    mutex.lock();
    if (output)
    {
        output->stop();
        delete output;
        output = NULL;
        io = NULL;
    }

    mutex.unlock();
}

bool MyAudio::Start()
{
    Stop();
    mutex.lock();
    QAudioFormat fmt; //Qt音频的格式
    fmt.setSampleRate(this->sampleRate); //1秒采集48000个声音
    fmt.setSampleSize(this->sampleSize); //16位
    fmt.setChannelCount(this->channel);  //声道2双声道
    fmt.setCodec("audio/pcm");           //音频的格式
    fmt.setByteOrder(QAudioFormat::LittleEndian); //次序
    fmt.setSampleType(QAudioFormat::UnSignedInt); //样本的类别

    output = new QAudioOutput(fmt);
    io = output->start();
    mutex.unlock();
    return true;
}

void MyAudio::Play(bool isPlay)
{
    mutex.lock();
    if (!output)
    {
        mutex.unlock();
        return;
    }

    if (isPlay)
    {
        output->resume();
    }
    else
    {
        output->suspend();
    }

    mutex.unlock();
}

//输入输出设备播放声音
bool MyAudio::Write(const char *data, int datasize)
{
    if (!data || datasize <= 0)
        return false;
    mutex.lock();
    if (io)
    {
        mutex.unlock();
        io->write(data, datasize); //输入输出设备播放声音,将数据从零终止的8位字符字符串写入设备。
        return true;
    }

    mutex.unlock();
}

int MyAudio::GetFree()
{
    mutex.lock();
    if (!output)
    {
        mutex.unlock();
        return 0;
    }

    int free = output->bytesFree();
    mutex.unlock();

    return free;
}
