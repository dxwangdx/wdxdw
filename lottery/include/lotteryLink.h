#ifndef _LOTTERY_LINK_H
#define _LOTTERY_LINK_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <termios.h>
#include <sys/stat.h>
#include <time.h>
#include <unistd.h>

//用户结构体数据
typedef struct{
	char clientName[20];
	char clientPassword[20];
	int id;
	int clientState;
	float account;
}ClientData;

//用户结构体
typedef struct client{
	ClientData data;
	struct client *next;
}Client,*ClientPointer;



//每张彩票结构体数据
typedef struct{
	char lotteryName[20];
	int number[5][6];
	int count;
	int issue;
	int id;
	int lotteryState;
	int winState;
	float account;
}LotteryData;

//每张彩票结构体
typedef struct lottery{
	LotteryData data;
	struct lottery *next;
}Lottery,*LotteryPointer;



//每期彩票结构体数据
typedef struct{
	int number[6];
	int issue;
	int price;
	int count;
	int lotteryPerState;
	float account;
}LotteryPerData;

//每期彩票结构体
typedef struct lotteryPer{
	LotteryPerData data;
	struct lotteryPer *next;
}LotteryPer,*LotteryPerPointer;




//用户链表节点创建
ClientPointer clientCreatNode(ClientData);

//用户节点后向插入用户链表
int clientInsertAfter(ClientPointer, ClientData);

//打印所有用户节点
void clientPrintAll(ClientPointer);

//将用户链表数据保存至文件
void clientSaveTxt(ClientPointer);

//从文件将用户数据加载至内存(堆)中
void clientLoadTxt(ClientPointer);

//获取用户链表长度
int clientGetLength(ClientPointer);

//按用户名查找用户
ClientPointer clientSearchByName(ClientPointer,char *);

//按用户名排序
void clientSortByName(ClientPointer clientHead);

//按ID排序
void clientSortByID(ClientPointer clientHead);




//每张彩票链表节点创建
LotteryPointer lotteryCreatNode(LotteryData);

//每张彩票节点后向插入每张彩票链表
void lotteryInsertAfter(LotteryPointer, LotteryData);

//打印当前这张彩票的信息
void lotteryPrintCurrent(LotteryPointer);

//将每张彩票链表数据保存至文件
void lotterySaveTxt(LotteryPointer);

//从文件将每张彩票数据加载至内存(堆)中
void lotteryLoadTxt(LotteryPointer);

//获取每张彩票链表长度
int lotteryGetLength(LotteryPointer);

//按未开奖状态查找彩票
LotteryPointer lotterySearchByState(LotteryPointer);

//按期号查找彩票
int lotterySearchPrintAllByIssue(LotteryPointer, int);




//每期彩票链表节点创建
LotteryPerPointer lotteryPerCreatNode(LotteryPerData);

//每期彩票节点后向插入每期彩票链表
void lotteryPerInsertAfter(LotteryPerPointer, LotteryPerData);

//打印当前这期彩票的信息
void lotteryPerPrintCurrent(LotteryPerPointer);

//将每期彩票链表数据保存至文件
void lotteryPerSaveTxt(LotteryPerPointer);

//从文件将每期彩票数据加载至内存(堆)中
void lotteryPerLoadTxt(LotteryPerPointer);

//获取每期彩票链表长度
int lotteryPerGetLength(LotteryPerPointer);

//查找未开奖的一期彩票
LotteryPerPointer lotteryPerSearchByState(LotteryPerPointer);

//兑奖功能
void lotteryIssue(ClientPointer,LotteryPointer,LotteryPerPointer);




//设置终端为不回显不缓冲，并获取按键的键值
int getch();

//调用getch获取键值保存到pcPWD中并单个回显 用于获取密码
void getPassword(char *);

//释放用户链表
void freeClientLink(ClientPointer);

//释放每张彩票链表
void freeLotteryLink(LotteryPointer);

//释放每期彩票链表
void freeLotteryPerLink(LotteryPerPointer);

#endif