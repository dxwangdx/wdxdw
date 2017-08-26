#include "dbcreator.h"

DbCreator* DbCreator::instance = 0;

DbCreator::DbCreator()
{
    db = QSqlDatabase::addDatabase("QSQLITE");
}

DbCreator* DbCreator::getInstance()
{
    if(0 == instance)
    {
        instance = new DbCreator();
    }
    return instance;
}

//创建数据库并打开
void DbCreator::creatConnect()
{
    db.setDatabaseName("user.db");
    db.open();
}

//关闭数据库并移除
void DbCreator::destoryConnect()
{
    db.close();
    db.removeDatabase("user.db");
}
