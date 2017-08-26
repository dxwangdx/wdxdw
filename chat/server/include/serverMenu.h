#ifndef _SERVERCONTROL_H
#define _SERVERCONTROL_H

#include "serverFunction.h"

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <signal.h>

//服务器端套接字创建函数
void serverSocketCreate(ClientPointer,ClientPointer);

//线程处理函数 接收数据包 处理 发送数据包
void *threadFunction(void *);

#endif