#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "clientsocket.h"
#include <QThread>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle(tr("直播平台服务器"));
    server = new QTcpServer(this);
    connect(server,SIGNAL(newConnection()),this,SLOT(onNewConnect()));
    if(server->isListening())
    {
        ui->tb_show->append("already listening......");
    }
    else
    {
        if(server->listen(QHostAddress::LocalHost ,8888))
        {
            ui->tb_show->append("listening success......");
        }
        else
        {
            ui->tb_show->append("listening failed......");
        }
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

//关闭事件
void MainWindow::closeEvent(QCloseEvent *event)
{
    DbCreator* dbclose = DbCreator::getInstance();
    dbclose->creatConnect();
    QSqlQuery query;
    query.exec("update tb_user set status = 0");
    dbclose->destoryConnect();
    QMainWindow::closeEvent(event);
    exit(0);
}

//获取新的tcp连接
void MainWindow::onNewConnect()
{
    ui->tb_show->append("new connection......");
    QTcpSocket* client = server->nextPendingConnection();
    ClientSocket* cs = new ClientSocket(client);
    QThread* thread = new QThread(this);

    connect(cs,SIGNAL(sigWrite(QTcpSocket*,const char*,int)),this,SLOT(onSigWrite(QTcpSocket*,const char*,int)));
    connect(client,SIGNAL(disconnected()),cs,SLOT(deleteLater()));
    connect(client,SIGNAL(disconnected()),thread,SLOT(quit()));

    cs->moveToThread(thread);
    thread->start();
}

//tcp写入数据包
void MainWindow::onSigWrite(QTcpSocket* socket,const char* str, int len)
{
    socket->write((char*)str,len);
}
