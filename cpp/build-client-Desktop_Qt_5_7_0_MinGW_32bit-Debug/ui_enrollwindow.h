/********************************************************************************
** Form generated from reading UI file 'enrollwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ENROLLWINDOW_H
#define UI_ENROLLWINDOW_H

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
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_EnrollWindow
{
public:
    QWidget *centralwidget;
    QWidget *gridLayoutWidget;
    QGridLayout *gridLayout;
    QLineEdit *le_password;
    QLabel *lb_name;
    QLineEdit *le_name;
    QLabel *lb_password;
    QPushButton *btn_ensure;
    QPushButton *btn_return;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *EnrollWindow)
    {
        if (EnrollWindow->objectName().isEmpty())
            EnrollWindow->setObjectName(QStringLiteral("EnrollWindow"));
        EnrollWindow->resize(490, 316);
        centralwidget = new QWidget(EnrollWindow);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        gridLayoutWidget = new QWidget(centralwidget);
        gridLayoutWidget->setObjectName(QStringLiteral("gridLayoutWidget"));
        gridLayoutWidget->setGeometry(QRect(100, 80, 281, 81));
        gridLayout = new QGridLayout(gridLayoutWidget);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        le_password = new QLineEdit(gridLayoutWidget);
        le_password->setObjectName(QStringLiteral("le_password"));
        le_password->setEchoMode(QLineEdit::Password);

        gridLayout->addWidget(le_password, 1, 1, 1, 1);

        lb_name = new QLabel(gridLayoutWidget);
        lb_name->setObjectName(QStringLiteral("lb_name"));

        gridLayout->addWidget(lb_name, 0, 0, 1, 1);

        le_name = new QLineEdit(gridLayoutWidget);
        le_name->setObjectName(QStringLiteral("le_name"));

        gridLayout->addWidget(le_name, 0, 1, 1, 1);

        lb_password = new QLabel(gridLayoutWidget);
        lb_password->setObjectName(QStringLiteral("lb_password"));

        gridLayout->addWidget(lb_password, 1, 0, 1, 1);

        btn_ensure = new QPushButton(centralwidget);
        btn_ensure->setObjectName(QStringLiteral("btn_ensure"));
        btn_ensure->setGeometry(QRect(260, 160, 78, 24));
        QFont font;
        font.setPointSize(12);
        font.setBold(true);
        font.setWeight(75);
        btn_ensure->setFont(font);
        btn_return = new QPushButton(centralwidget);
        btn_return->setObjectName(QStringLiteral("btn_return"));
        btn_return->setGeometry(QRect(140, 160, 78, 24));
        btn_return->setFont(font);
        EnrollWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(EnrollWindow);
        menubar->setObjectName(QStringLiteral("menubar"));
        menubar->setGeometry(QRect(0, 0, 490, 23));
        EnrollWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(EnrollWindow);
        statusbar->setObjectName(QStringLiteral("statusbar"));
        EnrollWindow->setStatusBar(statusbar);

        retranslateUi(EnrollWindow);

        QMetaObject::connectSlotsByName(EnrollWindow);
    } // setupUi

    void retranslateUi(QMainWindow *EnrollWindow)
    {
        EnrollWindow->setWindowTitle(QApplication::translate("EnrollWindow", "MainWindow", 0));
        lb_name->setText(QApplication::translate("EnrollWindow", "<html><head/><body><p align=\"right\"><span style=\" font-size:12pt; font-weight:600;\">\347\224\250 \346\210\267 \345\220\215</span></p></body></html>", 0));
        lb_password->setText(QApplication::translate("EnrollWindow", "<html><head/><body><p align=\"right\"><span style=\" font-size:12pt; font-weight:600;\">\345\257\206  \347\240\201</span></p></body></html>", 0));
        btn_ensure->setText(QApplication::translate("EnrollWindow", "\347\241\256 \345\256\232", 0));
        btn_return->setText(QApplication::translate("EnrollWindow", "\350\277\224 \345\233\236", 0));
    } // retranslateUi

};

namespace Ui {
    class EnrollWindow: public Ui_EnrollWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ENROLLWINDOW_H
