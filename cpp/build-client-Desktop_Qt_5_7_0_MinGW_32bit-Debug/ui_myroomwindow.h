/********************************************************************************
** Form generated from reading UI file 'myroomwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MYROOMWINDOW_H
#define UI_MYROOMWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MyRoomWindow
{
public:
    QWidget *centralwidget;
    QTextEdit *te_member;
    QTextEdit *te_record;
    QLabel *lb_member;
    QLabel *lb_video;
    QLabel *lb_record;
    QLineEdit *le_message;
    QPushButton *btn_send;
    QPushButton *btn_refresh;
    QPushButton *btn_camera_open;
    QPushButton *btn_camera_close;
    QPushButton *btn_bs_send;
    QLabel *lb_audio;
    QLabel *lb_camera;
    QLabel *textscroll;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MyRoomWindow)
    {
        if (MyRoomWindow->objectName().isEmpty())
            MyRoomWindow->setObjectName(QStringLiteral("MyRoomWindow"));
        MyRoomWindow->resize(582, 350);
        centralwidget = new QWidget(MyRoomWindow);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        te_member = new QTextEdit(centralwidget);
        te_member->setObjectName(QStringLiteral("te_member"));
        te_member->setGeometry(QRect(330, 40, 221, 131));
        te_record = new QTextEdit(centralwidget);
        te_record->setObjectName(QStringLiteral("te_record"));
        te_record->setGeometry(QRect(30, 180, 521, 81));
        lb_member = new QLabel(centralwidget);
        lb_member->setObjectName(QStringLiteral("lb_member"));
        lb_member->setGeometry(QRect(340, 10, 121, 21));
        QFont font;
        font.setPointSize(12);
        font.setBold(true);
        font.setWeight(75);
        lb_member->setFont(font);
        lb_video = new QLabel(centralwidget);
        lb_video->setObjectName(QStringLiteral("lb_video"));
        lb_video->setGeometry(QRect(30, 20, 231, 121));
        lb_record = new QLabel(centralwidget);
        lb_record->setObjectName(QStringLiteral("lb_record"));
        lb_record->setGeometry(QRect(33, 160, 81, 20));
        le_message = new QLineEdit(centralwidget);
        le_message->setObjectName(QStringLiteral("le_message"));
        le_message->setGeometry(QRect(30, 270, 421, 21));
        btn_send = new QPushButton(centralwidget);
        btn_send->setObjectName(QStringLiteral("btn_send"));
        btn_send->setGeometry(QRect(470, 270, 75, 23));
        btn_send->setFont(font);
        btn_refresh = new QPushButton(centralwidget);
        btn_refresh->setObjectName(QStringLiteral("btn_refresh"));
        btn_refresh->setGeometry(QRect(470, 10, 75, 23));
        btn_refresh->setFont(font);
        btn_camera_open = new QPushButton(centralwidget);
        btn_camera_open->setObjectName(QStringLiteral("btn_camera_open"));
        btn_camera_open->setGeometry(QRect(280, 30, 41, 23));
        QFont font1;
        font1.setBold(true);
        font1.setWeight(75);
        btn_camera_open->setFont(font1);
        btn_camera_close = new QPushButton(centralwidget);
        btn_camera_close->setObjectName(QStringLiteral("btn_camera_close"));
        btn_camera_close->setGeometry(QRect(280, 60, 41, 23));
        btn_camera_close->setFont(font1);
        btn_bs_send = new QPushButton(centralwidget);
        btn_bs_send->setObjectName(QStringLiteral("btn_bs_send"));
        btn_bs_send->setGeometry(QRect(280, 140, 41, 23));
        btn_bs_send->setFont(font1);
        lb_audio = new QLabel(centralwidget);
        lb_audio->setObjectName(QStringLiteral("lb_audio"));
        lb_audio->setGeometry(QRect(280, 120, 41, 21));
        lb_camera = new QLabel(centralwidget);
        lb_camera->setObjectName(QStringLiteral("lb_camera"));
        lb_camera->setGeometry(QRect(280, 10, 41, 21));
        QFont font2;
        font2.setBold(true);
        font2.setWeight(75);
        font2.setKerning(true);
        lb_camera->setFont(font2);
        textscroll = new QLabel(centralwidget);
        textscroll->setObjectName(QStringLiteral("textscroll"));
        textscroll->setGeometry(QRect(30, 20, 231, 121));
        MyRoomWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MyRoomWindow);
        menubar->setObjectName(QStringLiteral("menubar"));
        menubar->setGeometry(QRect(0, 0, 582, 23));
        MyRoomWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MyRoomWindow);
        statusbar->setObjectName(QStringLiteral("statusbar"));
        MyRoomWindow->setStatusBar(statusbar);

        retranslateUi(MyRoomWindow);

        QMetaObject::connectSlotsByName(MyRoomWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MyRoomWindow)
    {
        MyRoomWindow->setWindowTitle(QApplication::translate("MyRoomWindow", "MainWindow", 0));
        lb_member->setText(QApplication::translate("MyRoomWindow", "<html><head/><body><p align=\"center\">\350\201\212\345\244\251\345\256\244\346\210\220\345\221\230\345\210\227\350\241\250</p></body></html>", 0));
        lb_video->setText(QString());
        lb_record->setText(QApplication::translate("MyRoomWindow", "<html><head/><body><p align=\"center\"><span style=\" font-size:12pt; font-weight:600;\">\350\201\212\345\244\251\350\256\260\345\275\225</span></p></body></html>", 0));
        btn_send->setText(QApplication::translate("MyRoomWindow", "\345\217\221 \351\200\201", 0));
        btn_refresh->setText(QApplication::translate("MyRoomWindow", "\345\210\267 \346\226\260", 0));
        btn_camera_open->setText(QApplication::translate("MyRoomWindow", "\345\274\200", 0));
        btn_camera_close->setText(QApplication::translate("MyRoomWindow", "\345\205\263", 0));
        btn_bs_send->setText(QApplication::translate("MyRoomWindow", "\345\217\221\351\200\201", 0));
        lb_audio->setText(QApplication::translate("MyRoomWindow", "<html><head/><body><p align=\"center\"><span style=\" font-weight:600;\">\345\274\271\345\271\225</span></p></body></html>", 0));
        lb_camera->setText(QApplication::translate("MyRoomWindow", "<html><head/><body><p align=\"center\">\346\221\204\345\203\217\345\244\264</p></body></html>", 0));
        textscroll->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class MyRoomWindow: public Ui_MyRoomWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MYROOMWINDOW_H
