#ifndef CLIENTSOCKET_H
#define CLIENTSOCKET_H

#include <QObject>
#include <QTcpSocket>
#include "package.h"
#include "userdao.h"
#include "user.h"
#include "roomlist.h"

class ClientSocket : public QObject
{
    Q_OBJECT
public:
    explicit ClientSocket(QTcpSocket* socket,QObject *parent = 0);
    void enrollUser(package pack);//用户注册
    void loginUser(package pack);//用户登录
    void exitUser(package pack);//用户退出
    void roomCreatUser(package pack);//创建房间
    void roomRefreshUser(package pack);//房间刷新
    void enterRoomUser(package pack);//进入房间
    void personRefresh(package pack);//房间成员刷新
    void sendMessage(package pack);//发送信息
    void sendExitRoom(package pack);//发送退出房间消息
    void exitRoom(package pack);//退出房间
    void setPort(int port);//设置端口
    int getPort() const;//获取端口
    void sendBs(package pack);//发送弹幕
private:
    QTcpSocket* socket;
    static int port;
signals:
    void sigWrite(QTcpSocket *socket,const char* str, int len);//向主线程发送要写入的数据包
public slots:
    void onReadyRead();//tcp读取数据包
};

#endif // CLIENTSOCKET_H
