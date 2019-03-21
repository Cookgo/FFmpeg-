#include "mainwindow.h"
#include <QFileDialog>
#include <QMessageBox>
#include <iostream>
#include <list>
#include "myffmpeg.h"
#include "myaudio.h"

using namespace std;

//全局静态变量只在该cpp文件中有效
static bool isPressSlider = false;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    ui->setupUi(this);
    startTimer(40);
    ui->curTime->setText("00:00:00");
    ui->totalTime->setText("00:00:00");

    connect(ui->btn_OpenVideo, SIGNAL(clicked()), this, SLOT(slotOpenFile()));
    connect(ui->btn_Play, SIGNAL(clicked()), this, SLOT(slotPlay()));
    connect(ui->timeSlider, SIGNAL(sliderPressed()), this, SLOT(sliderPressed()));
    connect(ui->timeSlider, SIGNAL(sliderReleased()), this, SLOT(sliderReleased()));
}

void MainWindow::slotOpenFile()
{
    QString fname = QFileDialog::getOpenFileName(this, QString::fromLocal8Bit("打开视频文件"));
    if (fname.isEmpty())
    {
        return;
    }

    ui->lineEdit_VideoName->setText(fname);

    int totalMs = MyFFmpeg::GetObj()->OpenVideo(fname.toLocal8Bit());

    MyAudio::GetObj()->sampleRate = MyFFmpeg::GetObj()->m_sampleRate;
    MyAudio::GetObj()->channel = MyFFmpeg::GetObj()->m_channel;
    MyAudio::GetObj()->sampleSize = 16;

    MyAudio::GetObj()->Start();  //播放音频

    char buf[1024] = { 0 };
    int min = (totalMs / 1000) / 60;
    int sec = (totalMs / 1000) % 60;
    sprintf(buf, "%03d:%02d", min, sec);
    this->ui->totalTime->setText(buf);

    MyFFmpeg::GetObj()->m_isPlay = true;
    ui->btn_Play->setText(QString::fromLocal8Bit("暂停"));
}

void MainWindow::slotPlay()
{
    if (ui->btn_Play->text() == QString::fromLocal8Bit("暂停"))
    {
        MyFFmpeg::GetObj()->m_isPlay = false; //线程阻塞，视频暂停
        ui->btn_Play->setText(QString::fromLocal8Bit("播放"));
    }
    else
    {
        MyFFmpeg::GetObj()->m_isPlay = true;  //线程运行，视频播放
        ui->btn_Play->setText(QString::fromLocal8Bit("暂停"));
    }
}

void MainWindow::timerEvent(QTimerEvent *e)
{
    int min = (MyFFmpeg::GetObj()->m_pts / 1000) / 60;
    int sec = (MyFFmpeg::GetObj()->m_pts / 1000) % 60;
    char buf[1024] = { 0 };
    sprintf(buf, "%03d:%02d", min, sec);
    ui->curTime->setText(buf);  //当前播放时间

    if (MyFFmpeg::GetObj()->m_totalMs > 0)
    {
        float rate = MyFFmpeg::GetObj()->m_pts / (float(MyFFmpeg::GetObj()->m_totalMs));
        //只有按下了，才才显示进度条
        if (!isPressSlider)
        {
            this->ui->timeSlider->setValue(rate * 100); //进度条
        }
    }
}

void MainWindow::sliderPressed()
{
    isPressSlider = true;
}

void MainWindow::sliderReleased()
{
    isPressSlider = false;
    float pos = 0;
    pos = this->ui->timeSlider->value() / (float)(ui->timeSlider->maximum() + 1); //从0开始的，不能让分母为0
    MyFFmpeg::GetObj()->Seek(pos);
}

void MainWindow::mousePressEvent(QMouseEvent *e)
{
    int value = ((float)(e->pos().x()) / (float)(this->width())) * (ui->timeSlider->maximum() + 1);
    ui->timeSlider->setValue(value);
}
