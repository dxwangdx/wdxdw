#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "enrollwindow.h"
#include "sclicklabel.h"
#include "package.h"
#include "roomwindow.h"
#include "myroomwindow.h"
#include <QTcpSocket>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
protected:
    virtual void closeEvent(QCloseEvent *event);

private slots:
    void on_btn_login_clicked();//登录
    void onEnrollWindow();//注册
    void onPwdGetBack();//修改密码
    void onError(QAbstractSocket::SocketError socketError);//错误处理
    void onReadyRead();//读取数据包

private:
    Ui::MainWindow *ui;
    EnrollWindow* enrollWindow;
    RoomWindow* roomWindow;
    MyRoomWindow* myRoomWindow;
    QTcpSocket* socket;

};

#endif // MAINWINDOW_H
