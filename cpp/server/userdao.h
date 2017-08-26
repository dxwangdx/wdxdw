#ifndef USERDAO_H
#define USERDAO_H

#include "user.h"
#include "dbcreator.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>

//用户注册登录数据库操作类
class UserDao
{
public:
    UserDao();
    bool insertUser(const User& user);//加入用户
    bool searchUser(const User& user);//查找用户
    bool exitUserDao(const User& user);//用户退出
};

#endif // USERDAO_H
