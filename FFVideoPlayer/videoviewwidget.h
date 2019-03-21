#ifndef VIDEOVIEWWIDGET_H
#define VIDEOVIEWWIDGET_H

#include <QOpenGLWidget>

class VideoViewWidget : public QOpenGLWidget
{
    Q_OBJECT

public:
    VideoViewWidget(QWidget *parent);
    ~VideoViewWidget();

    void paintEvent(QPaintEvent *e);
    void timerEvent(QTimerEvent *e);
};

#endif // VIDEOVIEWWIDGET_H
