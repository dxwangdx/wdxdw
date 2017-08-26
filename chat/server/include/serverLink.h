#ifndef _SERVERLINK_H
#define _SERVERLINK_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <time.h>

#define TYPE_EXIT 0		//退出数据包
#define TYPE_LOGIN 1	//登录数据包
#define TYPE_ENROLL 2	//注册数据包
#define TYPE_COMMAND 3	//命令数据包
#define TYPE_SINGLECHAT 4	//单聊消息数据包
#define TYPE_GROUPCHAT 5	//群聊消息数据包
#define TYPE_ONLINEUSR 6	//在线用户数据包
#define TYPE_HEART 7		//心跳数据包

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
	char password[20];
	int socket_fd;
	time_t timsec;
	char timstr[40];
	char ip[17];
	int port;
}ClientData;	//用户结构体数据

typedef struct client{
	ClientData data;
	struct client *next;
}Client,*ClientPointer;	//用户结构体

int exitFlag;	//ctrl+c信号标识
int alarmFlag;	//alarm信号标识
ClientPointer clientHeartHead;	//心跳检测用户链表头节点

//用户链表节点创建
ClientPointer clientCreatNode(ClientData);

//用户节点后向插入用户链表
int clientInsertAfter(ClientPointer, ClientData);

//删除用户
void clientDelete(ClientPointer,char *);

//将用户链表数据保存至文件
void clientSaveTxt(ClientPointer);

//从文件将用户数据加载至内存(堆)中
void clientLoadTxt(ClientPointer);

//按用户名查找用户
ClientPointer clientSearchByName(ClientPointer,char *);

//释放用户链表
void freeClientLink(ClientPointer);

//信号处理函数
void sighandler(int);

//客户端登录信息保存函数
void loginSaveTxt(ClientData);

//服务端消息记录保存函数
void messageSaveTxt(Protocol);

#endif