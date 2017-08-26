#ifndef MYROOMWINDOW_H
#define MYROOMWINDOW_H

#include <QMainWindow>
#include <QTcpSocket>
#include <QUdpSocket>
#include "package.h"
#include <string.h>
#include <QCamera>
#include <QCameraInfo>
#include <QCameraViewfinder>
#include <QCameraImageCapture>
#include <QLabel>
#include <QDebug>
#include <QTime>
#include <QTimer>

namespace Ui {
class MyRoomWindow;
}

class MyRoomWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MyRoomWindow(QTcpSocket* socket,QWidget *parent = 0);
    void setName(const char* name);//用户名设置
    void setRoomName(const char* name);//房间名设置
    void setPort(int port);//udp端口设置
    const char* getName() const;//获取用户名
    const char* getRoomName() const;//获取房间名
    int getPort() const;//udp端口获取
    void refreshPersonList(package pack);//刷新房间成员
    void reveiceMessage(package pack);//接收消息
    void openCamera();//udp协议绑定启动
    void textScroll(package pack);//弹幕信息显示
    ~MyRoomWindow();
protected:
    virtual void closeEvent(QCloseEvent *event);//关闭事件
private slots:
    void on_btn_refresh_clicked();//刷新成员列表
    void on_btn_send_clicked();//发送消息
    void on_btn_camera_open_clicked();//开启视频
    void on_btn_camera_close_clicked();//关闭视频
    void UdpReadRead();//udp读取函数
    void onvideoChanged(QVideoFrame curFrame);//视频采集成图片
    void on_btn_bs_send_clicked();//发送弹幕
    void onTime();//定时器槽函数
private:
    QTcpSocket* socket;
    char name[20];
    char roomName[20];
    int port;
    Ui::MyRoomWindow *ui;

    QUdpSocket *socketWrite;
    QUdpSocket *socketRead;
    QHostAddress groupAddress;
    QCamera *camera;

    QTimer *timer;
    QLabel *label;
};

#endif // MYROOMWINDOW_H
