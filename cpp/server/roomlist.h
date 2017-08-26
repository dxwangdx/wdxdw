#ifndef ROOMLIST_H
#define ROOMLIST_H

#include "person.h"
#include <vector>

using namespace std;

class RoomList
{
public:
    static RoomList* getInstance();//获取指针 单例模式
    void setVectorPerson(Person& person);//房间成员vector容器加入成员
    void setVectorRoom(const QString& roomName);//房间vector容器加入房间
    vector<Person> getVectorPerson() const;//获取房间成员vector容器
    vector<QString> getVectorRoom() const;//获取房间vector容器
    void eraseVectorRoom(QString roomName);//删除房间vector成员
    void eraseVectorAllPerson(QString roomName);//循环删除房间成员vector容器成员
    void eraseVectorPerson(QString personName, QString roomName);//删除房间成员vector容器成员
private:
    static RoomList* instance;
    RoomList();
    static vector<Person> vectPerson;//房间成员容器
    static vector<QString> vectRoom;//房间容器
};

#endif // ROOMLIST_H
