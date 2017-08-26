/********************************************************************************
** Form generated from reading UI file 'roomwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ROOMWINDOW_H
#define UI_ROOMWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_RoomWindow
{
public:
    QWidget *centralwidget;
    QWidget *horizontalLayoutWidget;
    QHBoxLayout *horizontalLayout;
    QLabel *lb_room;
    QPushButton *btn_refresh;
    QPushButton *btn_room;
    QPushButton *btn_exit;
    QListWidget *lw_room;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *RoomWindow)
    {
        if (RoomWindow->objectName().isEmpty())
            RoomWindow->setObjectName(QStringLiteral("RoomWindow"));
        RoomWindow->resize(451, 337);
        centralwidget = new QWidget(RoomWindow);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        horizontalLayoutWidget = new QWidget(centralwidget);
        horizontalLayoutWidget->setObjectName(QStringLiteral("horizontalLayoutWidget"));
        horizontalLayoutWidget->setGeometry(QRect(40, 20, 371, 41));
        horizontalLayout = new QHBoxLayout(horizontalLayoutWidget);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        lb_room = new QLabel(horizontalLayoutWidget);
        lb_room->setObjectName(QStringLiteral("lb_room"));
        QFont font;
        font.setPointSize(12);
        font.setBold(true);
        font.setWeight(75);
        lb_room->setFont(font);

        horizontalLayout->addWidget(lb_room);

        btn_refresh = new QPushButton(horizontalLayoutWidget);
        btn_refresh->setObjectName(QStringLiteral("btn_refresh"));
        QFont font1;
        font1.setBold(true);
        font1.setWeight(75);
        btn_refresh->setFont(font1);

        horizontalLayout->addWidget(btn_refresh);

        btn_room = new QPushButton(horizontalLayoutWidget);
        btn_room->setObjectName(QStringLiteral("btn_room"));
        btn_room->setFont(font1);

        horizontalLayout->addWidget(btn_room);

        btn_exit = new QPushButton(horizontalLayoutWidget);
        btn_exit->setObjectName(QStringLiteral("btn_exit"));
        QFont font2;
        font2.setBold(true);
        font2.setUnderline(false);
        font2.setWeight(75);
        btn_exit->setFont(font2);

        horizontalLayout->addWidget(btn_exit);

        lw_room = new QListWidget(centralwidget);
        lw_room->setObjectName(QStringLiteral("lw_room"));
        lw_room->setGeometry(QRect(40, 60, 371, 241));
        RoomWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(RoomWindow);
        menubar->setObjectName(QStringLiteral("menubar"));
        menubar->setGeometry(QRect(0, 0, 451, 23));
        RoomWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(RoomWindow);
        statusbar->setObjectName(QStringLiteral("statusbar"));
        RoomWindow->setStatusBar(statusbar);

        retranslateUi(RoomWindow);

        QMetaObject::connectSlotsByName(RoomWindow);
    } // setupUi

    void retranslateUi(QMainWindow *RoomWindow)
    {
        RoomWindow->setWindowTitle(QApplication::translate("RoomWindow", "MainWindow", 0));
        lb_room->setText(QApplication::translate("RoomWindow", "<html><head/><body><p align=\"center\">\346\210\277\351\227\264\345\210\227\350\241\250</p></body></html>", 0));
        btn_refresh->setText(QApplication::translate("RoomWindow", "\345\210\267  \346\226\260", 0));
        btn_room->setText(QApplication::translate("RoomWindow", "\345\210\233\345\273\272\346\210\221\347\232\204\346\210\277\351\227\264", 0));
        btn_exit->setText(QApplication::translate("RoomWindow", "\351\200\200  \345\207\272", 0));
    } // retranslateUi

};

namespace Ui {
    class RoomWindow: public Ui_RoomWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ROOMWINDOW_H
