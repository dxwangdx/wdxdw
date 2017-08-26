/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>
#include "sclicklabel.h"

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QWidget *gridLayoutWidget;
    QGridLayout *gridLayout;
    SClickLabel *lb_enroll;
    SClickLabel *lb_password_getback;
    QLineEdit *le_password;
    QLineEdit *le_name;
    QLabel *lb_password;
    QLabel *lb_name;
    QPushButton *btn_login;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(553, 325);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        gridLayoutWidget = new QWidget(centralWidget);
        gridLayoutWidget->setObjectName(QStringLiteral("gridLayoutWidget"));
        gridLayoutWidget->setGeometry(QRect(100, 50, 351, 101));
        gridLayout = new QGridLayout(gridLayoutWidget);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        lb_enroll = new SClickLabel(gridLayoutWidget);
        lb_enroll->setObjectName(QStringLiteral("lb_enroll"));
        QFont font;
        font.setUnderline(true);
        lb_enroll->setFont(font);

        gridLayout->addWidget(lb_enroll, 0, 2, 1, 1);

        lb_password_getback = new SClickLabel(gridLayoutWidget);
        lb_password_getback->setObjectName(QStringLiteral("lb_password_getback"));
        lb_password_getback->setFont(font);

        gridLayout->addWidget(lb_password_getback, 1, 2, 1, 1);

        le_password = new QLineEdit(gridLayoutWidget);
        le_password->setObjectName(QStringLiteral("le_password"));
        le_password->setEchoMode(QLineEdit::Password);

        gridLayout->addWidget(le_password, 1, 1, 1, 1);

        le_name = new QLineEdit(gridLayoutWidget);
        le_name->setObjectName(QStringLiteral("le_name"));

        gridLayout->addWidget(le_name, 0, 1, 1, 1);

        lb_password = new QLabel(gridLayoutWidget);
        lb_password->setObjectName(QStringLiteral("lb_password"));

        gridLayout->addWidget(lb_password, 1, 0, 1, 1);

        lb_name = new QLabel(gridLayoutWidget);
        lb_name->setObjectName(QStringLiteral("lb_name"));

        gridLayout->addWidget(lb_name, 0, 0, 1, 1);

        btn_login = new QPushButton(centralWidget);
        btn_login->setObjectName(QStringLiteral("btn_login"));
        btn_login->setGeometry(QRect(100, 150, 351, 24));
        QFont font1;
        font1.setPointSize(12);
        font1.setBold(true);
        font1.setWeight(75);
        btn_login->setFont(font1);
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 553, 23));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0));
        lb_enroll->setText(QApplication::translate("MainWindow", "\346\263\250\345\206\214\350\264\246\345\217\267", 0));
        lb_password_getback->setText(QApplication::translate("MainWindow", "\346\211\276\345\233\236\345\257\206\347\240\201", 0));
        lb_password->setText(QApplication::translate("MainWindow", "<html><head/><body><p align=\"right\"><span style=\" font-size:12pt; font-weight:600;\">\345\257\206 \347\240\201</span></p></body></html>", 0));
        lb_name->setText(QApplication::translate("MainWindow", "<html><head/><body><p align=\"right\"><span style=\" font-size:12pt; font-weight:600;\">\347\224\250\346\210\267\345\220\215</span></p></body></html>", 0));
        btn_login->setText(QApplication::translate("MainWindow", "\347\231\273    \345\275\225", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
