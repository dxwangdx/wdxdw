#include "menu.h"

/*
	函数功能:主函数 程序的入口和出口
	函数参数:无
	返 回 值:0正常退出  -1初始化失败
*/
int main(void){
	
	ClientPointer clientHead = calloc(1, sizeof(Client));
	if(clientHead == NULL){
		printf("%s %d ERROR\n",__FILE__,__LINE__);
		return -1;
	}
	clientLoadTxt(clientHead);
	
	LotteryPointer lotteryHead = calloc(1, sizeof(Lottery));
	if(lotteryHead == NULL){
		printf("%s %d ERROR\n",__FILE__,__LINE__);
		return -1;
	}
	lotteryLoadTxt(lotteryHead);
	
	LotteryPerPointer lotteryPerHead = calloc(1, sizeof(LotteryPer));
	if(lotteryPerHead == NULL){
		printf("%s %d ERROR\n",__FILE__,__LINE__);
		return -1;
	}
	lotteryPerLoadTxt(lotteryPerHead);
	
	mainMenu(clientHead,lotteryHead,lotteryPerHead);
	
	freeClientLink(clientHead);

	freeLotteryLink(lotteryHead);

	freeLotteryPerLink(lotteryPerHead);
	
	return 0;
}