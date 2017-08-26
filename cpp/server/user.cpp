#include "user.h"

User::User(const QString& name, const QString& password, const int &id)
    :name(name), password(password),id(id)
{

}

//获取id
int User::getId()const
{
    return id;
}

//获取用户名
QString User::getName()const
{
    return name;
}

//获取密码
QString User::getPassword()const
{
    return password;
}
