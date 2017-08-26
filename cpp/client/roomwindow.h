#ifndef ROOMWINDOW_H
#define ROOMWINDOW_H

#include <QMainWindow>
#include <QTcpSocket>
#include "package.h"
#include <string.h>
#include <QDebug>

namespace Ui {
class RoomWindow;
}

class RoomWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit RoomWindow(QTcpSocket* socket,QWidget *parent = 0);
    void setName(const char* name);//设置用户名
    const char* getName() const;//获取用户名
    void refreshRoomList(package pack);//刷新房间列表
    ~RoomWindow();
protected:
    virtual void closeEvent(QCloseEvent *event);
private slots:
    void on_btn_exit_clicked();//退出
    void on_btn_room_clicked();//创建房间
    void on_btn_refresh_clicked();//刷新房间
    void on_lw_room_doubleClicked(const QModelIndex &index);//进入房间
private:
    QTcpSocket* socket;
    char name[20];
    Ui::RoomWindow *ui;
};

#endif // ROOMWINDOW_H
