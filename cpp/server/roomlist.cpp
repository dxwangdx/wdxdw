#include "roomlist.h"

RoomList* RoomList::instance = 0;
vector<Person> RoomList::vectPerson;
vector<QString> RoomList::vectRoom;

RoomList::RoomList()
{

}

RoomList* RoomList::getInstance()
{
    if(0 == instance)
    {
        instance = new RoomList();
    }
    return instance;
}

//用户容器添加用户
void RoomList::setVectorPerson(Person &person)
{
    vectPerson.push_back(person);
}

//房间容器添加房间
void RoomList::setVectorRoom(const QString& roomName)
{
    vectRoom.push_back(roomName);
}

//获取用户容器
vector<Person> RoomList::getVectorPerson() const
{
    return vectPerson;
}

//获取房间容器
vector<QString> RoomList::getVectorRoom() const
{
    return vectRoom;
}

//移除房间容器中的成员
void RoomList::eraseVectorRoom(QString roomName)
{
    vector<QString>::iterator itRoom;
    for(itRoom = vectRoom.begin(); itRoom != vectRoom.end();)
    {
        if(roomName == *itRoom)
        {
            vectRoom.erase(itRoom);
        }
        else
        {
            itRoom++;
        }
    }
}

//移除房间成员容器中的是roomName房间的成员
void RoomList::eraseVectorAllPerson(QString roomName)
{
    vector<Person>::iterator itPerson;
    vector<QString>::iterator itRoom;
    for(itPerson = vectPerson.begin(); itPerson != vectPerson.end();)
    {
        if(roomName == itPerson->getRoomName())
        {
            vectPerson.erase(itPerson);
        }
        else
        {
            itPerson++;
        }
    }
    for(itRoom = vectRoom.begin(); itRoom != vectRoom.end();)
    {
        if(roomName == *itRoom)
        {
            vectRoom.erase(itRoom);
        }
        else
        {
            itRoom++;
        }
    }
}

//移除房间成员容器中的成员
void RoomList::eraseVectorPerson(QString personName, QString roomName)
{
    vector<Person>::iterator itPerson;
    for(itPerson = vectPerson.begin(); itPerson != vectPerson.end();)
    {
        if(roomName == itPerson->getRoomName() && personName == itPerson->getName())
        {
            vectPerson.erase(itPerson);
        }
        else
        {
            itPerson++;
        }
    }
}
