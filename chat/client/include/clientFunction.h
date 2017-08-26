#ifndef _CLIENTFUNCTION_H
#define _CLIENTFUNCTION_H

#include "clientView.h"

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#define TYPE_EXIT 0		//退出数据包
#define TYPE_LOGIN 1	//登录数据包
#define TYPE_ENROLL 2	//注册数据包
#define TYPE_COMMAND 3	//命令数据包
#define TYPE_SINGLECHAT 4	//单聊消息数据包
#define TYPE_GROUPCHAT 5	//群聊消息数据包
#define TYPE_ONLINEUSR 6	//在线用户数据包
#define TYPE_HEART 7		//心跳数据包

int count;		//三次登录失败标识
int alarmFlag;	//alarm信号标识
int exitFlag;	//用户正常退出标识
pthread_mutex_t mutex;	//互斥锁

typedef struct{
	int type;
	char usrName[20];
	char usrPassword[20];
	char chatName[20];
	char data[2048];
	time_t timsec;
	char timstr[40];
}ProtocolData;	//数据包数据结构体

typedef struct protocol{
	ProtocolData data;
	struct protocol *next;
}Protocol,*ProtocolPointer;	//数据包结构体

typedef struct{
	char name[20];
	int socket_fd;
}Heart;	//心跳信息发送结构体

//用户发送退出信息函数
void clientSendUsrExit(int,Protocol);

//用户发送登录信息函数
Protocol clientSendLogin(int);

//用户发送注册信息函数
void clientSendEnroll(int);

//用户发送shell命令函数
int clientSendCommand(int);

//用户发送单聊信息函数
int clientSendSingleChat(int,Protocol);

//用户发送群聊信息函数
int clientSendGroupChat(int,Protocol);

//用户发送获取在线客户函数
void clientSendOnlineUsr(int,Protocol);

//用户发送心跳信息函数
void clientSendHeart(int,Protocol);

//用户接收退出信息函数
void clientReceiveUsrExit(int,ProtocolPointer);

//用户接收登录信息函数
void clientReceiveLogin(int,ProtocolPointer);

//用户接收注册信息函数
void clientReceiveEnroll(int,ProtocolPointer);

//用户接收shell命令信息函数
void clientReceiveCommand(int,ProtocolPointer);

//用户接收单聊信息函数
void clientReceiveSingleChat(int,ProtocolPointer);

//用户接收群聊信息函数
void clientReceiveGroupChat(int,ProtocolPointer);

//用户接收在线用户函数
void clientReceiveOnlineUsr(int,ProtocolPointer);

//用户接收信息保存函数
void messageSaveTxt(Protocol);

#endif