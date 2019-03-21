#include "videoviewwidget.h"
#include "myffmpeg.h"
#include "playthread.h"
#include <QPainter>
#include <iostream>
#include <list>

using namespace std;

VideoViewWidget::VideoViewWidget(QWidget *parent)
    : QOpenGLWidget(parent)
{
    startTimer(10); //刷新视频
    PlayThread::GetObj()->start();
}

VideoViewWidget::~VideoViewWidget()
{

}

void VideoViewWidget::paintEvent(QPaintEvent *e)
{
    static QImage *image = NULL;

    static int w = 0; //记录之前的窗口大小
    static int h = 0;
    if (w != width() || h != height())
    {
        //如果窗口大小发生变化，删除内存
        if (image)
        {
            delete image->bits();  //删除QImage的内部空间
            delete image;
            image = NULL;
        }
    }

    if (image == NULL)
    {
        uchar *buf = new uchar[width() * height() * 4];
        image = new QImage(buf, width(), height(), QImage::Format_ARGB32);
    }

    MyFFmpeg::GetObj()->YuvToRGB((char *)(image->bits()), width(), height());

    QPainter painter;
    painter.begin(this);
    painter.drawImage(QPoint(0, 0), *image);
    painter.end();
}

void VideoViewWidget::timerEvent(QTimerEvent *e)
{
    this->update();
}
