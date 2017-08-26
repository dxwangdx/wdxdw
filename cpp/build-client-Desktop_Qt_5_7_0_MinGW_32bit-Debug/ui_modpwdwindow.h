/********************************************************************************
** Form generated from reading UI file 'modpwdwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MODPWDWINDOW_H
#define UI_MODPWDWINDOW_H

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

class Ui_ModPwdWindow
{
public:
    QWidget *centralwidget;
    QPushButton *btn_cancel;
    QWidget *gridLayoutWidget;
    QGridLayout *gridLayout;
    QLabel *lb_password_confirm;
    QLabel *lb_password;
    QLabel *lb_password_protect;
    QLineEdit *le_password;
    QLineEdit *le_name;
    QLineEdit *le_password_confirm;
    QLabel *lb_name;
    QLineEdit *le_code_identify;
    QPushButton *btn_ensure;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *ModPwdWindow)
    {
        if (ModPwdWindow->objectName().isEmpty())
            ModPwdWindow->setObjectName(QStringLiteral("ModPwdWindow"));
        ModPwdWindow->resize(518, 323);
        centralwidget = new QWidget(ModPwdWindow);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        btn_cancel = new QPushButton(centralwidget);
        btn_cancel->setObjectName(QStringLiteral("btn_cancel"));
        btn_cancel->setGeometry(QRect(150, 200, 78, 24));
        QFont font;
        font.setPointSize(12);
        font.setBold(true);
        font.setWeight(75);
        btn_cancel->setFont(font);
        gridLayoutWidget = new QWidget(centralwidget);
        gridLayoutWidget->setObjectName(QStringLiteral("gridLayoutWidget"));
        gridLayoutWidget->setGeometry(QRect(110, 60, 281, 142));
        gridLayout = new QGridLayout(gridLayoutWidget);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        lb_password_confirm = new QLabel(gridLayoutWidget);
        lb_password_confirm->setObjectName(QStringLiteral("lb_password_confirm"));

        gridLayout->addWidget(lb_password_confirm, 3, 0, 1, 1);

        lb_password = new QLabel(gridLayoutWidget);
        lb_password->setObjectName(QStringLiteral("lb_password"));

        gridLayout->addWidget(lb_password, 2, 0, 1, 1);

        lb_password_protect = new QLabel(gridLayoutWidget);
        lb_password_protect->setObjectName(QStringLiteral("lb_password_protect"));

        gridLayout->addWidget(lb_password_protect, 1, 0, 1, 1);

        le_password = new QLineEdit(gridLayoutWidget);
        le_password->setObjectName(QStringLiteral("le_password"));

        gridLayout->addWidget(le_password, 1, 1, 1, 1);

        le_name = new QLineEdit(gridLayoutWidget);
        le_name->setObjectName(QStringLiteral("le_name"));

        gridLayout->addWidget(le_name, 0, 1, 1, 1);

        le_password_confirm = new QLineEdit(gridLayoutWidget);
        le_password_confirm->setObjectName(QStringLiteral("le_password_confirm"));

        gridLayout->addWidget(le_password_confirm, 2, 1, 1, 1);

        lb_name = new QLabel(gridLayoutWidget);
        lb_name->setObjectName(QStringLiteral("lb_name"));

        gridLayout->addWidget(lb_name, 0, 0, 1, 1);

        le_code_identify = new QLineEdit(gridLayoutWidget);
        le_code_identify->setObjectName(QStringLiteral("le_code_identify"));

        gridLayout->addWidget(le_code_identify, 3, 1, 1, 1);

        btn_ensure = new QPushButton(centralwidget);
        btn_ensure->setObjectName(QStringLiteral("btn_ensure"));
        btn_ensure->setGeometry(QRect(270, 200, 78, 24));
        btn_ensure->setFont(font);
        ModPwdWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(ModPwdWindow);
        menubar->setObjectName(QStringLiteral("menubar"));
        menubar->setGeometry(QRect(0, 0, 518, 23));
        ModPwdWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(ModPwdWindow);
        statusbar->setObjectName(QStringLiteral("statusbar"));
        ModPwdWindow->setStatusBar(statusbar);

        retranslateUi(ModPwdWindow);

        QMetaObject::connectSlotsByName(ModPwdWindow);
    } // setupUi

    void retranslateUi(QMainWindow *ModPwdWindow)
    {
        ModPwdWindow->setWindowTitle(QApplication::translate("ModPwdWindow", "MainWindow", 0));
        btn_cancel->setText(QApplication::translate("ModPwdWindow", "\345\217\226 \346\266\210", 0));
        lb_password_confirm->setText(QApplication::translate("ModPwdWindow", "<html><head/><body><p align=\"right\"><span style=\" font-size:12pt; font-weight:600;\">\347\241\256\350\256\244\345\257\206\347\240\201</span></p></body></html>", 0));
        lb_password->setText(QApplication::translate("ModPwdWindow", "<html><head/><body><p align=\"right\"><span style=\" font-size:12pt; font-weight:600;\">\346\226\260 \345\257\206 \347\240\201</span></p></body></html>", 0));
        lb_password_protect->setText(QApplication::translate("ModPwdWindow", "<html><head/><body><p align=\"right\"><span style=\" font-size:12pt; font-weight:600;\">\345\257\206   \344\277\235</span></p></body></html>", 0));
        lb_name->setText(QApplication::translate("ModPwdWindow", "<html><head/><body><p align=\"right\"><span style=\" font-size:12pt; font-weight:600;\">\347\224\250 \346\210\267 \345\220\215</span></p></body></html>", 0));
        btn_ensure->setText(QApplication::translate("ModPwdWindow", "\347\241\256 \345\256\232", 0));
    } // retranslateUi

};

namespace Ui {
    class ModPwdWindow: public Ui_ModPwdWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MODPWDWINDOW_H
