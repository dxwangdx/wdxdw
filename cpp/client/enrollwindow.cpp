#include "enrollwindow.h"
#include "ui_enrollwindow.h"

EnrollWindow::EnrollWindow(QTcpSocket* socket,QWidget *parent) :
    QMainWindow(parent),socket(socket),
    ui(new Ui::EnrollWindow)
{
    ui->setupUi(this);
}

EnrollWindow::~EnrollWindow()
{
    delete ui;
}

//关闭事件
void EnrollWindow::closeEvent(QCloseEvent *event)
{
    Q_UNUSED(event);
    QWidget *parent = this->parentWidget();
    if(0!=parent){
        parent->show();
    }
}

//注册返回
void EnrollWindow::on_btn_return_clicked()
{
    QWidget *parent = this->parentWidget();
    if(0!=parent){
        parent->show();
        this->close();
    }
}

//注册确定
void EnrollWindow::on_btn_ensure_clicked()
{
    package pack;
    memset(&pack,0,sizeof(package));
    pack.type = ENROLL_MESSAGE;

    QString name = ui->le_name->text();
    if(name.isEmpty())
    {
        QMessageBox::warning(this,"warning","用户名不能为空！！！");
        return;
    }
    const char *nameP = name.toLocal8Bit().data();
    strncpy(pack.name,nameP,20);

    QString password = ui->le_password->text();
    if(password.isEmpty())
    {
        QMessageBox::warning(this,"warning","密码不能为空！！！");
        return;
    }
    const char *passwordP = password.toLocal8Bit().data();
    strncpy(pack.password,passwordP,20);

    ui->le_name->setFocus();
    ui->le_name->clear();
    ui->le_password->clear();

    socket->write((char*)&pack,sizeof(pack));
}

