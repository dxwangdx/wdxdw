#ifndef PACKAGE_H
#define PACKAGE_H

#define ENROLL_MESSAGE 1//注册信息
#define ENROLL_SUCCESS 2//注册成功
#define ENROLL_FAILED 3//注册失败
#define LOGIN_MESSAGE 4//登录信息
#define LOGIN_SUCCESS 5//登录成功
#define LOGIN_FAILED 6//登录失败
#define EXIT_MESSAGE 7//退出信息
#define EXIT_SUCC 8//退出成功
#define EXIT_FAIL 9//退出失败
#define ROOM_CREAT 10//创建房间
#define ROOM_SUCCESS 11//房间创建成功
#define ROOM_FAILED 12//房间创建失败
#define ROOM_REFRESH 13//刷新房间
#define ENTER_ROOM 14//进入房间
#define ENTER_SUCCESS 15//进入房间成功
#define ENTER_FAILED 16//进入房间失败
#define PERSON_REFRESH 17//刷新房间成员
#define SEND_MESSAGE 18//发送消息
#define EXIT_ROOM 19//退出房间
#define SEND_BS 20//发送弹幕

//消息数据包
typedef struct package
{
    int type;
    char name[20];
    char roomName[20];
    char password[20];
    char message[1024];
    int port;
}package;

#endif // PACKAGE_H
