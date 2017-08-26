#ifndef USER_H
#define USER_H

#include <QString>

//用户注册登录类
class User
{
public:
    User( const QString& name,const QString& password,const int& id = 0);
    int getId()const;
    QString getName()const;
    QString getPassword()const;
private:
    QString name;
    QString password;
    int id;
};

#endif // USER_H
