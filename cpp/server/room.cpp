#include "room.h"

Room::Room(const QString& name,QTcpSocket *socket)
    :name(name),socket(socket)
{
    vector<Person> vect;
}

void Room::setVector(Person& person)
{
    vect.push_back(person);
}

QString Room::getName()const
{
    return name;
}

vector<Person> Room::getVector() const
{
    return vect;
}

QTcpSocket* Room::getSocket() const
{
    return socket;
}
