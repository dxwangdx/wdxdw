#include "person.h"

Person::Person(const QString& name, QTcpSocket *socket)
    :name(name),socket(socket)
{

}

Person::~Person()
{

}

//设置用户名
void Person::setName(const QString& name)
{
    this->name = name;
}

//设置房间名
void Person::setRoomName(const QString& roomName)
{
    this->roomName = roomName;
}

//设置udp端口号
void Person::setPort(int port)
{
    this->port = port;
}

//获取用户名
QString Person::getName()const
{
    return name;
}

//获取房间名
QString Person::getRoomName()const
{
    return roomName;
}

//获取tcp套接字
QTcpSocket* Person::getSocket() const
{
    return socket;
}

//获取udp端口号
int Person::getPort() const
{
    return port;
}
