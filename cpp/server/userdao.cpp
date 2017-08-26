#include "userdao.h"

UserDao::UserDao()
{

}

//向数据库中添加用户
bool UserDao::insertUser(const User& user)
{
    DbCreator* dbinsert = DbCreator::getInstance();
    dbinsert->creatConnect();
    QSqlQuery query;
    QString tb_user = QString("create table if not exists tb_user("
                              "id integer PRIMARY KEY autoincrement,"
                              "name varchar(20) not null,"
                              "password varchar(20) not null,"
                              "status integer not null)");
    bool ret = query.exec(tb_user);
    if(0 == ret)
    {
        qDebug() << query.lastError().text();
    }
    query.prepare("select name from tb_user where name = :name");
    query.bindValue(":name",user.getName());
    bool retv = query.exec();
    if(0 == retv)
    {
        qDebug() << query.lastError().text();
    }
    while(query.next())
    {
        dbinsert->destoryConnect();
        return false;//查找到重名的 则返回false
    }
    query.prepare("insert into tb_user(name,password,status)values(:name,:password,0)");
    query.bindValue(":name",user.getName());
    query.bindValue(":password",user.getPassword());
    bool retval = query.exec();
    if(0 == retval)
    {
        qDebug() << query.lastError().text();
    }
    dbinsert->destoryConnect();
    return true;//插入数据成功 则返回true
}

//在数据库中查找用户
bool UserDao::searchUser(const User& user)
{

    DbCreator* dbsearch = DbCreator::getInstance();
    dbsearch->creatConnect();
    QSqlQuery query;

    query.prepare("select *from tb_user where name=:name and password=:password");
    query.bindValue(":name",user.getName());
    query.bindValue(":password",user.getPassword());
    bool retval = query.exec();
    if(0 == retval)
    {
        qDebug() << query.lastError().text();
    }
    while(query.next())
    {
        int status = query.value(3).toInt();
        if(0 == status){
            query.prepare("update tb_user set status = 1 where name=:name");
            query.bindValue(":name",user.getName());
            if(0 == query.exec())
            {
                break;//状态位修改失败 则跳出循环
            }
            dbsearch->destoryConnect();
            return true;//登录成功
        }
    }
    dbsearch->destoryConnect();
    return false;//登录失败
}

//用户退出 修改数据库中用户对应的状态位
bool UserDao::exitUserDao(const User& user)
{

    DbCreator* dbexit = DbCreator::getInstance();
    dbexit->creatConnect();
    QSqlQuery query;

    query.prepare("select *from tb_user where name=:name");
    query.bindValue(":name",user.getName());
    bool retval = query.exec();
    if(0 == retval)
    {
        qDebug() << query.lastError().text();
    }
    while(query.next())
    {
        int status = query.value(3).toInt();
        if(1 == status){
            query.prepare("update tb_user set status = 0 where name=:name");
            query.bindValue(":name",user.getName());
            if(0 == query.exec())
            {
                return false;//状态位修改失败 则跳出循环 退出异常
            }
            dbexit->destoryConnect();
            return true;//成功退出
        }
    }
    dbexit->destoryConnect();
    return true;//未查找到
}
