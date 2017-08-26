#ifndef ROOM_H
#define ROOM_H

#include "person.h"
#include <vector>
#include <QTcpSocket>

using namespace std;

class Room
{
public:
    Room(const QString& name, QTcpSocket* socket);
    void setVector(Person& person);
    QString getName()const;
    vector<Person> getVector() const;
    QTcpSocket* getSocket() const;
private:
    QString name;
    QTcpSocket* socket;
    vector<Person> vect;
};

#endif // ROOM_H
