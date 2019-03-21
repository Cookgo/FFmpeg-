#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "ui_mainwindow.h"
#include <QMouseEvent>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

    public:
        MainWindow(QWidget *parent = Q_NULLPTR);

        void timerEvent(QTimerEvent *e);
        void mousePressEvent(QMouseEvent *e); //重写该函数

    public slots:
        void slotOpenFile();
        void slotPlay();

        void sliderPressed();
        void sliderReleased();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
