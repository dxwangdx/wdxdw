#ifndef PERSON_H
#define PERSON_H

#include <QTcpSocket>

//房间成员类
class Person
{
public:
    Person(const QString& name,QTcpSocket* socket);
    ~Person();
    void setName(const QString& name);//设置成员名
    void setRoomName(const QString& roomName);//设置房间名
    void setPort(int port);//设置udp端口
    QString getName()const;//获取成员名
    QString getRoomName()const;//获取房间名
    QTcpSocket* getSocket() const;//获取tcp套接字
    int getPort() const;//获取udp端口
private:
    QString name;
    QString roomName;
    QTcpSocket* socket;
    int port;
};

#endif // PERSON_H
