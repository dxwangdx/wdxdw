#include "roomwindow.h"
#include "ui_roomwindow.h"

RoomWindow::RoomWindow(QTcpSocket* socket,QWidget *parent) :
    QMainWindow(parent),socket(socket),
    ui(new Ui::RoomWindow)
{
    ui->setupUi(this);
}

RoomWindow::~RoomWindow()
{
    delete ui;
}

//关闭事件
void RoomWindow::closeEvent(QCloseEvent *event)
{
    Q_UNUSED(event);
    package pack;
    memset(&pack,0,sizeof(package));
    pack.type = EXIT_MESSAGE;
    strcpy(pack.name,getName());
    socket->write((char*)&pack,sizeof(pack));
    QWidget *parent = this->parentWidget();
    if(0!=parent){
        parent->show();
    }
}

//退出按钮
void RoomWindow::on_btn_exit_clicked()
{
        this->close();
}

//设置用户名
void RoomWindow::setName(const char* name)
{
    strncpy(this->name,name,20);
}

//获取用户名
const char* RoomWindow::getName() const
{
    return name;
}

//创建房间按钮
void RoomWindow::on_btn_room_clicked()
{
    package pack;
    memset(&pack,0,sizeof(package));
    pack.type = ROOM_CREAT;
    strcpy(pack.name,getName());
    socket->write((char*)&pack,sizeof(pack));
}

//刷新房间按钮
void RoomWindow::on_btn_refresh_clicked()
{
    package pack;
    memset(&pack,0,sizeof(package));
    pack.type = ROOM_REFRESH;
    strcpy(pack.name,getName());
    socket->write((char*)&pack,sizeof(pack));
}

//接收房间列表
void RoomWindow::refreshRoomList(package pack)
{
    if(strcmp(pack.message,"refresh") == 0)
    {
        ui->lw_room->clear();
    }
    else
    {
        QString str = QString::fromLocal8Bit(pack.name);
        ui->lw_room->addItem(str);
    }
}

//双击进入房间
void RoomWindow::on_lw_room_doubleClicked(const QModelIndex &index)
{
    Q_UNUSED(index);
    package pack;
    memset(&pack,0,sizeof(package));
    pack.type = ENTER_ROOM;
    QListWidgetItem* listWidget = ui->lw_room->currentItem();
    QString roomName = listWidget->text();
    const char *nameP = roomName.toLocal8Bit().data();
    strncpy(pack.roomName,nameP,20);
    strcpy(pack.name,this->getName());
    socket->write((char*)&pack,sizeof(pack));
}
