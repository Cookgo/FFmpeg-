/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.12.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>
#include <videoviewwidget.h>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QGridLayout *gridLayout_3;
    QGridLayout *gridLayout_2;
    QSpacerItem *horizontalSpacer;
    QGridLayout *gridLayout;
    VideoViewWidget *openGLWidget;
    QLineEdit *lineEdit_VideoName;
    QSlider *timeSlider;
    QPushButton *btn_OpenVideo;
    QLabel *label;
    QLabel *curTime;
    QLabel *totalTime;
    QSpacerItem *horizontalSpacer_2;
    QPushButton *btn_Play;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(595, 445);
        MainWindow->setAutoFillBackground(false);
        MainWindow->setAnimated(true);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        gridLayout_3 = new QGridLayout(centralWidget);
        gridLayout_3->setSpacing(6);
        gridLayout_3->setContentsMargins(11, 11, 11, 11);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        gridLayout_2 = new QGridLayout();
        gridLayout_2->setSpacing(0);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        horizontalSpacer = new QSpacerItem(50, 20, QSizePolicy::Minimum, QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer, 1, 2, 1, 1);

        gridLayout = new QGridLayout();
        gridLayout->setSpacing(0);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        openGLWidget = new VideoViewWidget(centralWidget);
        openGLWidget->setObjectName(QString::fromUtf8("openGLWidget"));
        QSizePolicy sizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(openGLWidget->sizePolicy().hasHeightForWidth());
        openGLWidget->setSizePolicy(sizePolicy);
        openGLWidget->setMinimumSize(QSize(420, 180));

        gridLayout->addWidget(openGLWidget, 1, 0, 1, 4);

        lineEdit_VideoName = new QLineEdit(centralWidget);
        lineEdit_VideoName->setObjectName(QString::fromUtf8("lineEdit_VideoName"));
        QSizePolicy sizePolicy1(QSizePolicy::Minimum, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(lineEdit_VideoName->sizePolicy().hasHeightForWidth());
        lineEdit_VideoName->setSizePolicy(sizePolicy1);
        lineEdit_VideoName->setMinimumSize(QSize(300, 0));

        gridLayout->addWidget(lineEdit_VideoName, 0, 1, 1, 2);

        timeSlider = new QSlider(centralWidget);
        timeSlider->setObjectName(QString::fromUtf8("timeSlider"));
        sizePolicy1.setHeightForWidth(timeSlider->sizePolicy().hasHeightForWidth());
        timeSlider->setSizePolicy(sizePolicy1);
        timeSlider->setMinimumSize(QSize(420, 0));
        timeSlider->setOrientation(Qt::Horizontal);

        gridLayout->addWidget(timeSlider, 2, 0, 1, 4);

        btn_OpenVideo = new QPushButton(centralWidget);
        btn_OpenVideo->setObjectName(QString::fromUtf8("btn_OpenVideo"));
        QSizePolicy sizePolicy2(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(btn_OpenVideo->sizePolicy().hasHeightForWidth());
        btn_OpenVideo->setSizePolicy(sizePolicy2);
        btn_OpenVideo->setMinimumSize(QSize(50, 0));

        gridLayout->addWidget(btn_OpenVideo, 0, 3, 1, 1);

        label = new QLabel(centralWidget);
        label->setObjectName(QString::fromUtf8("label"));
        sizePolicy2.setHeightForWidth(label->sizePolicy().hasHeightForWidth());
        label->setSizePolicy(sizePolicy2);

        gridLayout->addWidget(label, 0, 0, 1, 1);


        gridLayout_2->addLayout(gridLayout, 0, 0, 1, 5);

        curTime = new QLabel(centralWidget);
        curTime->setObjectName(QString::fromUtf8("curTime"));
        sizePolicy2.setHeightForWidth(curTime->sizePolicy().hasHeightForWidth());
        curTime->setSizePolicy(sizePolicy2);
        curTime->setMinimumSize(QSize(60, 20));

        gridLayout_2->addWidget(curTime, 1, 0, 1, 1);

        totalTime = new QLabel(centralWidget);
        totalTime->setObjectName(QString::fromUtf8("totalTime"));
        sizePolicy2.setHeightForWidth(totalTime->sizePolicy().hasHeightForWidth());
        totalTime->setSizePolicy(sizePolicy2);
        totalTime->setMinimumSize(QSize(60, 20));

        gridLayout_2->addWidget(totalTime, 1, 1, 1, 1);

        horizontalSpacer_2 = new QSpacerItem(170, 20, QSizePolicy::Minimum, QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer_2, 1, 4, 1, 1);

        btn_Play = new QPushButton(centralWidget);
        btn_Play->setObjectName(QString::fromUtf8("btn_Play"));
        sizePolicy2.setHeightForWidth(btn_Play->sizePolicy().hasHeightForWidth());
        btn_Play->setSizePolicy(sizePolicy2);
        btn_Play->setMinimumSize(QSize(80, 20));

        gridLayout_2->addWidget(btn_Play, 1, 3, 1, 1);


        gridLayout_3->addLayout(gridLayout_2, 0, 0, 1, 1);

        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 595, 23));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        MainWindow->setStatusBar(statusBar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", nullptr));
        btn_OpenVideo->setText(QApplication::translate("MainWindow", "\346\211\223\345\274\200\350\247\206\351\242\221", nullptr));
        label->setText(QApplication::translate("MainWindow", "\346\234\254\345\234\260\350\247\206\351\242\221", nullptr));
        curTime->setText(QApplication::translate("MainWindow", "\350\277\233\345\272\246", nullptr));
        totalTime->setText(QApplication::translate("MainWindow", "\346\200\273\346\227\266\351\225\277", nullptr));
        btn_Play->setText(QApplication::translate("MainWindow", "\346\222\255\346\224\276", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
