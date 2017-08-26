#ifndef _CONTROL_H
#define _CONTROL_H

#include "view.h"
#include "menu.h"
#include "lotteryLink.h"
#include <unistd.h>
#include <time.h>

//登录功能
int login(ClientPointer,LotteryPointer,LotteryPerPointer);

//注册用户功能
void enroll(ClientPointer);

//生成验证码
void identifyCode(char*);

#endif