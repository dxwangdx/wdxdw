#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QHostAddress>

//主界面构造函数
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle(tr("直播平台"));
    socket  = new QTcpSocket(this);//tcp套接字
    connect(socket,SIGNAL(error(QAbstractSocket::SocketError)),this,SLOT(onError(QAbstractSocket::SocketError)));//套接字错误
    socket->connectToHost(QHostAddress::LocalHost,8888);//tcp连接地址及端口

    enrollWindow = new EnrollWindow(socket,this);
    roomWindow = new RoomWindow(socket,this);
    myRoomWindow = new MyRoomWindow(socket,this);
    connect(ui->lb_enroll,SIGNAL(clicked()),this,SLOT(onEnrollWindow()));
    connect(ui->lb_password_getback,SIGNAL(clicked()),this,SLOT(onPwdGetBack()));

    connect(socket,SIGNAL(readyRead()),this,SLOT(onReadyRead()));//tcp数据读取

}

//主界面析构函数
MainWindow::~MainWindow()
{
    delete ui;
    delete enrollWindow;
    delete roomWindow;
    delete socket;
}

//改写关闭事件
void MainWindow::closeEvent(QCloseEvent *event)
{
    QMainWindow::closeEvent(event);
    exit(0);
}

//错误处理槽函数
void MainWindow::onError(QAbstractSocket::SocketError socketError)
{
    Q_UNUSED(socketError);
    QString str = socket->errorString();
    QMessageBox::warning(this,"warning",str);
}

//注册 界面跳转
void MainWindow::onEnrollWindow()
{

    this->hide();
    enrollWindow->show();
}

//修改密码 消息提示
void MainWindow::onPwdGetBack()
{
     QMessageBox::information(this,"information","该功能暂未开通！！！");
}

//登录函数
void MainWindow::on_btn_login_clicked()
{
    package pack;
    memset(&pack,0,sizeof(package));
    pack.type = LOGIN_MESSAGE;

    QString name = ui->le_name->text();
    if(name.isEmpty())
    {
        QMessageBox::warning(this,"warning","用户名不能为空！！！");
        return;
    }
    const char *nameP = name.toLocal8Bit().data();
    strncpy(pack.name,nameP,20);


    roomWindow->setName(nameP);
    roomWindow->setWindowTitle(tr(nameP));
    myRoomWindow->setName(nameP);
    myRoomWindow->statusBar()->showMessage(nameP);

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

//tcp协议读取函数
void MainWindow::onReadyRead()
{
    package pack;
    memset(&pack,0,sizeof(package));
    socket->read((char*)&pack,sizeof(pack));
    QApplication::setQuitOnLastWindowClosed(false);
    switch(pack.type)
    {
    case ENROLL_FAILED://注册失败
        qDebug() << "ENROLL_FAILED";
        QMessageBox::information(this,"information",pack.message);
        break;
    case ENROLL_SUCCESS://注册成功
        qDebug() << "ENROLL_SUCCESS";
        QMessageBox::information(this,"information",pack.message);
        break;
    case LOGIN_FAILED://登录失败
        qDebug() << "LOGIN_FAILED";
        QMessageBox::information(this,"information",pack.message);
        break;
    case LOGIN_SUCCESS://登录成功
        qDebug() << "LOGIN_SUCCESS";
        this->hide();
        roomWindow->show();
//        QMessageBox::information(this,"information",pack.message);
        break;
    case EXIT_FAIL://退出失败
        qDebug() << "EXIT_FAILED";
        QMessageBox::information(this,"information",pack.message);
        break;
    case EXIT_SUCC://退出成功
        qDebug() << "EXIT_SUCCESS";
        QMessageBox::information(this,"information",pack.message);
        this->show();
        break;
    case ROOM_SUCCESS://创建房间成功
        qDebug() << "ROOM_SUCCESS";
        roomWindow->hide();
        myRoomWindow->setWindowTitle(tr(pack.name));
        myRoomWindow->setRoomName(pack.name);
        myRoomWindow->setPort(pack.port);
        myRoomWindow->openCamera();
        myRoomWindow->show();
        break;
    case ROOM_FAILED://创建房间失败
        qDebug() << "ROOM_FAILED";
        QMessageBox::information(this,"information",pack.message);
        break;
    case ROOM_REFRESH://刷新房间
        qDebug() << "ROOM_REFRESH";
        roomWindow->refreshRoomList(pack);
        break;
    case ENTER_SUCCESS://进入房间成功
        qDebug() << "ENTER_SUCCESS";
        roomWindow->hide();
        myRoomWindow->setWindowTitle(tr(pack.roomName));
        myRoomWindow->setRoomName(pack.roomName);
        myRoomWindow->setPort(pack.port);
        myRoomWindow->openCamera();
        myRoomWindow->show();
        break;
    case ENTER_FAILED://进入房间失败
        qDebug() << "ENTER_FAILED";
        QMessageBox::information(this,"information",pack.message);
        break;
    case PERSON_REFRESH://房间成员刷新
        qDebug() << "PERSON_REFRESH";
        myRoomWindow->refreshPersonList(pack);
        break;
    case SEND_MESSAGE://发送消息
        qDebug() << "SEND_MESSAGE";
        myRoomWindow->reveiceMessage(pack);
        break;
    case EXIT_ROOM://退出房间
        qDebug() << "EXIT_ROOM";
        roomWindow->show();
        QMessageBox::information(this,"information",pack.message);
        break;
    case SEND_BS://发送弹幕
        qDebug() << "SEND_BS";
        myRoomWindow->textScroll(pack);
        break;
    default:
        qDebug() << "unkown type";
        break;
    }
}
