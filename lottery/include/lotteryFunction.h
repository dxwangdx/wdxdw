#ifndef _LOTTERY_FUNCTION_H
#define _LOTTERY_FUNCTION_H

#include "lotteryLink.h"
#include <unistd.h>
#include <time.h>

//管理员彩票发行
void adminLotteryIssue(LotteryPerPointer);

//管理员查看开奖信息
void adminLotteryInformation(LotteryPerPointer);

//管理员查看销售记录
void adminLotterySaleRecord(LotteryPointer);

//管理员查找用户
void adminSearchClient(ClientPointer);

//管理员找回注销账号
void adminResumeClient(ClientPointer);

//管理员对用户进行排序(按姓名)
void adminSortClient(ClientPointer);




//用户查看账户信息
void clientInformation(ClientPointer);

//用户修改密码
void clientModifyPassword(ClientPointer,ClientPointer);

//用户充值
void clientAccountRecharge(ClientPointer,ClientPointer);

//用户注销
int clientLogoff(ClientPointer,ClientPointer);

//用户购买彩票
void clientBuyLottery(ClientPointer,ClientPointer,LotteryPointer,LotteryPerPointer);

//用户购买记录
void clientBuyLotteryRecord(ClientPointer,LotteryPointer);




//公证员开奖
void notaryLotteryDraw(ClientPointer,LotteryPointer,LotteryPerPointer);

//公证员查看每期彩票记录
void notaryLotteryRecord(LotteryPerPointer);

#endif