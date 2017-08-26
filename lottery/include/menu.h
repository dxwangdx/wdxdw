#ifndef _MAIN_MENU_H
#define _MAIN_MENU_H

#include "view.h"
#include "control.h"
#include "lotteryFunction.h"
#include <string.h>
#include <stdlib.h>

//主菜单
void mainMenu(ClientPointer,LotteryPointer,LotteryPerPointer);

//管理员菜单
void adminMenu(ClientPointer,LotteryPointer,LotteryPerPointer);

//用户菜单
void clientMenu(ClientPointer,ClientPointer,LotteryPointer,LotteryPerPointer);

//公证员菜单
void notaryMenu(ClientPointer,LotteryPointer,LotteryPerPointer);

#endif