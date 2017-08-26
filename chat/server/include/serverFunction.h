#ifndef _SERVERFUNCTION_H
#define _SERVERFUNCTION_H

#include "serverLink.h"

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <pthread.h>

typedef struct{
	int socket_fd;
	ClientPointer linkHead;
	ClientPointer linkOnlineHead;
	char ip[17];
	int port;
}Parameter;	//线程处理函数参数结构体

//服务器处理退出函数
void serverHandleUsrExit(int,ClientPointer,Protocol);

//服务器处理登录函数
void serverHandleLogin(void *,int,ClientPointer,ClientPointer,Protocol);

//服务器处理注册函数
void serverHandleEnroll(int,ClientPointer,Protocol);

//服务器处理shell命令函数
void serverHandleCommand(int,Protocol);

//服务器处理单聊函数
void serverHandleSingleChat(int,ClientPointer,Protocol);

//服务器处理群聊函数
void serverHandleGroupChat(int,ClientPointer,Protocol);

//服务器处理在线用户函数
void serverHandleOnlineUsr(int,ClientPointer,Protocol);

//服务器处理心跳函数
void serverHandleHeart(int,ClientPointer,Protocol);

#endif