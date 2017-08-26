#include "clientsocket.h"
#include <QDebug>
#include <QThread>

//设置房间udp端口号
int ClientSocket::port = 8000;

ClientSocket::ClientSocket(QTcpSocket* socket,QObject *parent)
    : QObject(parent),socket(socket)
{
    connect(socket,SIGNAL(readyRead()),this,SLOT(onReadyRead()));
}

//设置udp端口号
void ClientSocket::setPort(int port)
{
    this->port = port;
}

//获取udp端口号
int ClientSocket::getPort() const
{
    return port;
}

//tcp读取数据包
void ClientSocket::onReadyRead()
{
    package pack;
    memset(&pack,0,sizeof(pack));
    socket->read((char*)&pack,sizeof(pack));
    switch(pack.type)
    {
    case ENROLL_MESSAGE://注册
        qDebug() << "enroll choose";
        enrollUser(pack);
        break;
    case LOGIN_MESSAGE://登录
        qDebug() << "login choose";
        loginUser(pack);
        break;
    case EXIT_MESSAGE://退出
        qDebug() << "exit choose";
        exitUser(pack);
        break;
    case ROOM_CREAT://创建房间
        qDebug() << "room create";
        roomCreatUser(pack);
        break;
    case ROOM_REFRESH://房间列表刷新
        qDebug() << "room refresh";
        roomRefreshUser(pack);
        break;
    case ENTER_ROOM://进入房间
        qDebug() << "enter room";
        enterRoomUser(pack);
        break;
    case PERSON_REFRESH://刷新房间成员
        qDebug() << "person refresh";
        personRefresh(pack);
        break;
    case SEND_MESSAGE://发送消息
        qDebug() << "send message";
        sendMessage(pack);
        break;
    case EXIT_ROOM://退出房间
        qDebug() << "send message";
        sendExitRoom(pack);
        exitRoom(pack);
        break;
    case SEND_BS://发送弹幕
        qDebug() << "send bs";
        sendBs(pack);
        break;
    default:
        qDebug() << "unkown choose";
        break;
    }
}

//注册用户
void ClientSocket::enrollUser(package pack)
{
    QString name = QString::fromLocal8Bit(pack.name);
    QString  password = QString::fromLocal8Bit(pack.password);
    User user(name,password);

    qDebug() << name;
    qDebug() << password;
    UserDao ud;
    if(ud.insertUser(user) == 0)
    {
        pack.type = ENROLL_FAILED;
        strcpy(pack.message,"用户名已被注册，注册失败!!!");
        qDebug() <<  "ENROLL_FAILED";
    }
    else
    {
        pack.type = ENROLL_SUCCESS;
        strcpy(pack.message,"注册成功!!!");
        qDebug() <<  "ENROLL_SUCCESS";
    }
    emit sigWrite(socket,(char*)&pack,sizeof(pack));
}

//用户登录
void ClientSocket::loginUser(package pack)
{
    QString name = QString::fromLocal8Bit(pack.name);
    QString  password = QString::fromLocal8Bit(pack.password);
    User user(name,password);
    UserDao ud;
    if(ud.searchUser(user) == 0)
    {
        pack.type = LOGIN_FAILED;
        strcpy(pack.message,"登录失败!!!");
        qDebug() <<  "LOGIN_FAILED";
    }
    else
    {
        pack.type = LOGIN_SUCCESS;
        strcpy(pack.message,"登录成功!!!");
        qDebug() <<  "LOGIN_SUCCESS";
    }

    emit sigWrite(socket,(char*)&pack,sizeof(pack));
}

//用户退出
void ClientSocket::exitUser(package pack)
{
    QString name = QString::fromLocal8Bit(pack.name);
    QString  password = QString::fromLocal8Bit(pack.password);
    User user(name,password);
    UserDao ud;
    if(ud.exitUserDao(user) == 0)
    {
        pack.type = EXIT_FAIL;
        strcpy(pack.message,"退出异常!!!");
        qDebug() <<  "LOGIN_FAILED";
    }
    else
    {
        pack.type = EXIT_SUCC;
        strcpy(pack.message,"成功退出!!!");
        qDebug() <<  "LOGIN_FAILED";
    }

    emit sigWrite(socket,(char*)&pack,sizeof(pack));
}

//房间创建
void ClientSocket::roomCreatUser(package pack)
{
    QString personName = QString::fromLocal8Bit(pack.name);
    Person person(personName,socket);
    person.setRoomName(personName);

    RoomList* roomList = RoomList::getInstance();
    vector<Person> vectPerson = roomList->getVectorPerson();
    vector<Person>::iterator itPerson;
    for(itPerson = vectPerson.begin(); itPerson != vectPerson.end(); itPerson++)
    {
        if(personName == itPerson->getName())
        {
            pack.type = ROOM_FAILED;
            strcpy(pack.message,"已经进入房间，不能创建房间！！！");
            emit sigWrite(socket,(char*)&pack,sizeof(pack));
            return;
        }
    }

    int port = this->getPort() + 1;
    this->setPort(port);

    person.setPort(port);
    roomList->setVectorPerson(person);
    roomList->setVectorRoom(personName);
    pack.type = ROOM_SUCCESS;
    pack.port = port;
    emit sigWrite(socket,(char*)&pack,sizeof(pack));
}

//房间列表刷新
void ClientSocket::roomRefreshUser(package pack)
{
    strcpy(pack.message,"refresh");
    emit sigWrite(socket,(char*)&pack,sizeof(pack));
    QThread::usleep(1000);
    memset(&pack.message,'\0',sizeof(pack.message));

    RoomList* roomList = RoomList::getInstance();
    vector<QString> vectRoom = roomList->getVectorRoom();
    vector<QString>::iterator itRoom;
    for(itRoom = vectRoom.begin(); itRoom != vectRoom.end(); itRoom++ )
    {
        const char *nameP = (*itRoom).toLocal8Bit().data();
        strncpy(pack.name,nameP,20);
        emit sigWrite(socket,(char*)&pack,sizeof(pack));
        QThread::usleep(1000);
    }
}

//进入房间
void ClientSocket::enterRoomUser(package pack)
{
    QString roomName = QString::fromLocal8Bit(pack.roomName);
    QString personName = QString::fromLocal8Bit(pack.name);
    Person person(personName,socket);
    person.setRoomName(roomName);

    RoomList* roomList = RoomList::getInstance();
    vector<Person> vectPerson = roomList->getVectorPerson();
    vector<Person>::iterator itPerson;
    for(itPerson = vectPerson.begin(); itPerson != vectPerson.end(); itPerson++ )
    {
        if(personName == itPerson->getName())
        {
            pack.type = ENTER_FAILED;
            strcpy(pack.message,"已经进入房间，不能重复进入！！！");
            emit sigWrite(socket,(char*)&pack,sizeof(pack));
            return;
        }
    }

    for(itPerson = vectPerson.begin(); itPerson != vectPerson.end(); itPerson++ )
    {
        if(roomName == itPerson->getRoomName())
        {
            person.setPort(itPerson->getPort());
            pack.port = itPerson->getPort();
        }
    }

    roomList->setVectorPerson(person);
    pack.type = ENTER_SUCCESS;
    strcpy(pack.message,"进入房间成功！！！");
    emit sigWrite(socket,(char*)&pack,sizeof(pack));
    QThread::usleep(1000);

    //给同组发送进入房间消息
    pack.type = SEND_MESSAGE;
    strcpy(pack.message,pack.name);
    strcat(pack.message," Already Enter Room!!!");
    strcpy(pack.name,"system");
    for(itPerson = vectPerson.begin(); itPerson != vectPerson.end(); itPerson++ )
    {
        if(roomName == itPerson->getRoomName())
        {
            emit sigWrite(itPerson->getSocket(),(char*)&pack,sizeof(pack));
            QThread::usleep(1000);
        }
    }
}

//刷新房间成员
void ClientSocket::personRefresh(package pack)
{
    QString roomName = QString::fromLocal8Bit(pack.name);

    strcpy(pack.message,"refresh");
    emit sigWrite(socket,(char*)&pack,sizeof(pack));
    QThread::usleep(1000);
    memset(&pack.message,'\0',sizeof(pack.message));

    RoomList* roomList = RoomList::getInstance();
    vector<Person> vectPerson = roomList->getVectorPerson();
    vector<Person>::iterator itPerson;
    for(itPerson = vectPerson.begin(); itPerson != vectPerson.end(); itPerson++ )
    {
        if(roomName == itPerson->getRoomName())
        {
            const char *nameP = itPerson->getName().toLocal8Bit().data();
            strncpy(pack.name,nameP,20);
            emit sigWrite(socket,(char*)&pack,sizeof(pack));
            QThread::usleep(1000);
        }
    }
}

//发送消息
void ClientSocket::sendMessage(package pack)
{
    QString roomName = QString::fromLocal8Bit(pack.roomName);

    RoomList* roomList = RoomList::getInstance();
    vector<Person> vectPerson = roomList->getVectorPerson();
    vector<Person>::iterator itPerson;
    for(itPerson = vectPerson.begin(); itPerson != vectPerson.end(); itPerson++ )
    {
        if(roomName == itPerson->getRoomName())
        {
            emit sigWrite(itPerson->getSocket(),(char*)&pack,sizeof(pack));
            QThread::usleep(1000);
        }
    }
}

//发送弹幕信息
void ClientSocket::sendBs(package pack)
{
    QString roomName = QString::fromLocal8Bit(pack.roomName);

    RoomList* roomList = RoomList::getInstance();
    vector<Person> vectPerson = roomList->getVectorPerson();
    vector<Person>::iterator itPerson;
    for(itPerson = vectPerson.begin(); itPerson != vectPerson.end(); itPerson++ )
    {
        if(roomName == itPerson->getRoomName())
        {
            pack.type = SEND_BS;
            emit sigWrite(itPerson->getSocket(),(char*)&pack,sizeof(pack));
            QThread::usleep(1000);
        }
    }
}

//退出房间前 发送消息
void ClientSocket::sendExitRoom(package pack)
{
    QString roomName = QString::fromLocal8Bit(pack.roomName);
    QString personName = QString::fromLocal8Bit(pack.name);

    RoomList* roomList = RoomList::getInstance();
    vector<Person> vectPerson = roomList->getVectorPerson();
    vector<QString> vectRoom = roomList->getVectorRoom();
    vector<Person>::iterator itPerson;
    vector<QString>::iterator itRoom;
    for(itRoom = vectRoom.begin(); itRoom != vectRoom.end(); itRoom++)
    {
        if(personName == *itRoom)
        {
            for(itPerson = vectPerson.begin(); itPerson != vectPerson.end(); itPerson++)
            {
                if(roomName == itPerson->getRoomName())
                {
                    strcpy(pack.message,"房间已解散！！！");
                    emit sigWrite(itPerson->getSocket(),(char*)&pack,sizeof(pack));
                    QThread::usleep(1000);
                }
            }
        }
        else
        {
            for(itPerson = vectPerson.begin(); itPerson != vectPerson.end(); itPerson++)
            {
                if(personName == itPerson->getName())
                {
                    strcpy(pack.message,"成功退出房间！！！");
                    emit sigWrite(itPerson->getSocket(),(char*)&pack,sizeof(pack));
                    QThread::usleep(1000);
                }
            }
            //给同组发送退出消息
            pack.type = SEND_MESSAGE;
            strcpy(pack.message,pack.name);
            strcat(pack.message," Already Exit Room!!!");
            strcpy(pack.name,"system");
            for(itPerson = vectPerson.begin(); itPerson != vectPerson.end(); itPerson++ )
            {
                if(roomName == itPerson->getRoomName())
                {
                    emit sigWrite(itPerson->getSocket(),(char*)&pack,sizeof(pack));
                    QThread::usleep(1000);
                }
            }
        }
    }
}

//退出房间
void ClientSocket::exitRoom(package pack)
{
    QString roomName = QString::fromLocal8Bit(pack.roomName);
    QString personName = QString::fromLocal8Bit(pack.name);
    RoomList* roomList = RoomList::getInstance();
    if(roomName == personName)
    {
        roomList->eraseVectorRoom(roomName);
        roomList->eraseVectorAllPerson(roomName);
        QThread::usleep(1000);
    }
    else
    {
        roomList->eraseVectorPerson(personName, roomName);
        QThread::usleep(1000);
    }
}
