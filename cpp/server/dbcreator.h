#ifndef DBCREATOR_H
#define DBCREATOR_H

#include <QSqlDatabase>

class DbCreator
{
public:
    static DbCreator *getInstance();//获取数据库指针 单例模式
    void creatConnect();//创建并打开数据库
    void destoryConnect();//断开并移除数据库
private:
    static DbCreator* instance;
    DbCreator();
    QSqlDatabase db;
};

#endif // DBCREATOR_H
