#include "menu.h"

/*
	函数功能:主菜单
	函数参数:用户链表头节点指针 每张彩票链表头节点指针 每期彩票链表头节点指针
	返 回 值:无
*/
void mainMenu(ClientPointer clientHead,\
				LotteryPointer lotteryHead,\
				LotteryPerPointer lotteryPerHead){
	int count=0;
	system("clear");
	while(1){
		int choose=3;
		mainMenuView();
		printf("请输入选择的编号：");
		scanf("%d",&choose);
		switch(choose){
			case 0:
			system("clear");
			printf("系统退出！！！\n");
			return;
			case 1:
			count = login(clientHead,lotteryHead,lotteryPerHead);
			if(count == 3){
				system("clear");
				printf("系统退出！！！\n");
				return;
			}
			break;
			case 2:
			enroll(clientHead);
			system("clear");
			break;
			default:
			system("clear");
			while(getchar()!='\0'){
				break;	
			}
		}
	}
	return;
}

/*
	函数功能:管理员菜单
	函数参数:用户链表头节点指针 每张彩票链表头节点指针 每期彩票链表头节点指针
	返 回 值:无
*/
void adminMenu(ClientPointer clientHead,\
				LotteryPointer lotteryHead,\
				LotteryPerPointer lotteryPerHead){
	while(1){
		int choose=7;
		adminMenuView();
		printf("请输入选择的编号：");
		scanf("%d",&choose);
		switch(choose){
			case 0:
			system("clear");
			return;
			case 1:
			adminLotteryIssue(lotteryPerHead);
			system("clear");
			break;
			case 2:
			adminLotteryInformation(lotteryPerHead);
			system("clear");
			break;
			case 3:
			adminLotterySaleRecord(lotteryHead);
			system("clear");
			break;
			case 4:
			adminSearchClient(clientHead);
			system("clear");
			break;
			case 5:
			adminResumeClient(clientHead);
			system("clear");
			break;
			case 6:
			adminSortClient(clientHead);
			system("clear");
			break;
			default:
			system("clear");
			while(getchar()!='\0'){
				break;	
			}
		}
	}
	return;
}

/*
	函数功能:用户菜单
	函数参数:用户链表头节点指针 用户链表中的当前用户节点指针
			 每张彩票链表头节点指针 每期彩票链表头节点指针
	返 回 值:无
*/
void clientMenu(ClientPointer clientHead,\
				ClientPointer clientCurrent,\
				LotteryPointer lotteryHead,\
				LotteryPerPointer lotteryPerHead){
	int count = 1;
	while(1){
		int choose=7;
		clientMenuView();
		printf("请输入选择的编号：");
		scanf("%d",&choose);
		switch(choose){
			case 0:
			system("clear");
			return;
			case 1:
			clientInformation(clientCurrent);
			while(getchar() != '\n');
			printf("按回车键返回~~~\n");
			getchar();
			system("clear");
			break;
			case 2:
			clientModifyPassword(clientHead,clientCurrent);
			system("clear");
			break;
			case 3:
			clientAccountRecharge(clientHead,clientCurrent);
			system("clear");
			break;
			case 4:
			clientBuyLottery(clientHead,clientCurrent,lotteryHead,lotteryPerHead);
			system("clear");
			break;
			case 5:
			clientBuyLotteryRecord(clientCurrent,lotteryHead);
			system("clear");
			break;
			case 6:
			count = clientLogoff(clientHead,clientCurrent);
			if(count == 0){
				system("clear");
				return;
			}
			system("clear");
			break;
			default:
			system("clear");
			while(getchar()!='\0'){
				break;	
			}
		}
	}
	return;
}

/*
	函数功能:公证员菜单
	函数参数:用户链表头节点指针 每张彩票链表头节点指针 每期彩票链表头节点指针
	返 回 值:无
*/
void notaryMenu(ClientPointer clientHead,\
				LotteryPointer lotteryHead,\
				LotteryPerPointer lotteryPerHead){
	while(1){
		int choose=3;
		notaryMenuView();
		printf("请输入选择的编号：");
		scanf("%d",&choose);
		switch(choose){
			case 0:
			system("clear");
			return;
			case 1:
			notaryLotteryDraw(clientHead,lotteryHead,lotteryPerHead);
			system("clear");
			break;
			case 2:
			notaryLotteryRecord(lotteryPerHead);
			system("clear");
			break;
			default:
			system("clear");
			while(getchar()!='\0'){
				break;	
			}
		}
	}
	return;
}