#ifndef _CLIENTMENU_H
#define _CLIENTMENU_H

#include "clientFunction.h"

#include <fcntl.h>
#include <sys/stat.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <signal.h>
#include <pthread.h>

//客户端套接字创建函数
void clientSocketCreate();

//主菜单功能处理函数
void clientMainMenu(int);

//二级菜单功能处理函数
void clientSecondaryMenu(int,Protocol);

//线程处理函数 接收数据包并处理
void *threadFunction(void *);

//线程处理函数 定时发送心跳数据包
void *threadFunctionHeart(void *);

//信号处理函数
void sighandler(int);

#endif