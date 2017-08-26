#include "lotteryFunction.h"

/*
	函数功能:管理员彩票发行
	函数参数:每期彩票链表头节点
	返 回 值:无
*/
void adminLotteryIssue(LotteryPerPointer lotteryPerHead){
	int account = 1000000;
	LotteryPerPointer temp = lotteryPerHead;
	if(lotteryPerHead->next != NULL){
		while(NULL != temp->next){
			temp = temp->next;
		}
		if(0 == temp->data.lotteryPerState){
			printf("上期未开奖，暂不能发行！！！\n");
			while(getchar() != '\n');
			printf("按回车键返回~~~\n");
			getchar();
			return;
		}else{
			account = temp->data.account;
		}
	}
	int price=2;
	printf("输入彩票单价:");
	scanf("%d",&price);
	LotteryPerData data;
	memset(&data,0,sizeof(data));
	data.issue =1 + lotteryPerGetLength(lotteryPerHead);
	data.price = price;
	data.count = 0;
	data.lotteryPerState = 0;
	data.account = account;
	lotteryPerInsertAfter(lotteryPerHead,data);
	lotteryPerSaveTxt(lotteryPerHead);
	printf("发行成功！！！\n");
	while(getchar() != '\n');
	printf("按回车键返回~~~\n");
	getchar();
	return;
}

/*
	函数功能:管理员查看开奖信息
	函数参数:每期彩票链表头节点
	返 回 值:无
*/
void adminLotteryInformation(LotteryPerPointer lotteryPerHead){
	LotteryPerPointer temp = lotteryPerHead;
	if(lotteryPerHead->next != NULL){
		while(NULL != temp->next){
			temp = temp->next;
		}
		if(0 == temp->data.lotteryPerState){
			printf("暂未开奖，请稍后查询！！！\n");
			while(getchar() != '\n');
			printf("按回车键返回~~~\n");
			getchar();
		}else{
			int i=0;
			printf("本期中奖号码：");
			for(i=0;i<6;i++){
				printf("%-4d",temp->data.number[i]);
			}
			printf("\n");
			while(getchar() != '\n');
			printf("按回车键返回~~~\n");
			getchar();
		}
	}else{
		printf("暂未发行！！！\n");
		while(getchar() != '\n');
		printf("按回车键返回~~~\n");
		getchar();
	}
	return;
}

/*
	函数功能:管理员查看销售记录
	函数参数:每张彩票链表头节点
	返 回 值:无
*/
void adminLotterySaleRecord(LotteryPointer lotteryHead){
	if(lotteryHead->next == NULL){
		printf("暂未售出！！！\n");
		while(getchar() != '\n');
		printf("按回车键返回~~~\n");
		getchar();
		return;
	}
	int issue = 1;
	int count = 0;
	printf("请输入需查询的期号:");
	scanf("%d",&issue);
	printf("%d期彩票销售信息如下:\n",issue);
	count = lotterySearchPrintAllByIssue(lotteryHead,issue);
	if(count == 0){
		printf("无%d期彩票销售信息！！！\n",issue);
		while(getchar() != '\n');
		printf("按回车键返回~~~\n");
		getchar();
	}else{
		printf("%d期彩票共售%d张！！！\n",issue,count);
		printf("所有彩票共售%d张！！！\n",lotteryGetLength(lotteryHead));
		while(getchar() != '\n');
		printf("按回车键返回~~~\n");
		getchar();
	}
	return;
}

/*
	函数功能:管理员查找用户
	函数参数:用户链表头节点
	返 回 值:无
*/
void adminSearchClient(ClientPointer clientHead){
	char name[20]="";
	printf("请输入需要查询的用户名:");
	scanf("%s",name);
	ClientPointer temp = clientSearchByName(clientHead, name);
	if(NULL == temp){
		printf("%s用户名不存在！！！\n",name);
		while(getchar() != '\n');
		printf("按回车键返回~~~\n");
		getchar();
		return;
	}
	clientInformation(temp->next);
	while(getchar() != '\n');
	printf("按回车键返回~~~\n");
	getchar();
}

/*
	函数功能:管理员找回注销账号
	函数参数:用户链表头节点
	返 回 值:无
*/
void adminResumeClient(ClientPointer clientHead){
	char name[20]="";
	printf("请输入需要恢复的用户名:");
	scanf("%s",name);
	ClientPointer temp = clientSearchByName(clientHead, name);
	if(NULL == temp){
		printf("%s用户名不存在！！！\n",name);
		while(getchar() != '\n');
		printf("按回车键返回~~~\n");
		getchar();
		return;
	}
	temp->next->data.clientState = 1;
	clientSaveTxt(clientHead);
	printf("%s用户已找回！！！\n",name);
	while(getchar() != '\n');
	printf("按回车键返回~~~\n");
	getchar();
}

/*
	函数功能:管理员对用户进行排序(按姓名)
	函数参数:每期彩票链表头节点
	返 回 值:无
*/
void adminSortClient(ClientPointer clientHead){
	char  ch = '\0';
	printf("按用户名排序！！！\n");
	clientSortByName(clientHead);
	clientPrintAll(clientHead);
	printf("排序完成！！！\n");
	printf("是否保存按用户名排序(y/n):");
	scanf(" %c",&ch);
	if(ch == 'Y' || ch == 'y'){
		clientSaveTxt(clientHead);
	}else{
		printf("恢复原始序列！！！\n");
		clientSortByID(clientHead);
		clientPrintAll(clientHead);
		clientSaveTxt(clientHead);
		while(getchar() != '\n');
		printf("按回车键返回~~~\n");
		getchar();
	}
	return;
} 




/*
	函数功能:用户查看账户信息
	函数参数:用户链表中的当前用户节点指针
	返 回 值:无
*/
void clientInformation(ClientPointer clientCurrent){
	printf("ID:%d\t用户名:%s\t密码:%s\t状态:%d\t账户金额:%.2f\n",\
						clientCurrent->data.id,\
						clientCurrent->data.clientName,\
						clientCurrent->data.clientPassword,\
						clientCurrent->data.clientState,\
						clientCurrent->data.account);
}

/*
	函数功能:用户修改密码
	函数参数:用户链表头节点指针 用户链表中的当前用户节点指针
	返 回 值:无
*/
void clientModifyPassword(ClientPointer clientHead, ClientPointer clientCurrent){
	char oldPassword[20] = "";
	char newPassword[20] = "";
	char newPasswordConfirm[20] = "";
	char ch='\0';
	getchar();
	printf("请输入原密码:");
	getPassword(oldPassword);
	printf("请输入新密码:");
	getPassword(newPassword);
	printf("请确认新密码:");
	getPassword(newPasswordConfirm);
	printf("确认是否修改(y/n):");
	scanf(" %c",&ch);
	if(ch == 'y' || ch == 'Y'){
		if(0 == strcmp(oldPassword,clientCurrent->data.clientPassword)\
			&& 0 == strcmp(newPassword,newPasswordConfirm)){
			strcpy(clientCurrent->data.clientPassword,newPasswordConfirm);
			clientSaveTxt(clientHead);
			printf("密码修改成功！！！\n");
			printf("3秒后自动返回！！！\n");
			sleep(3);
		}else{
			printf("输入有误，密码修改失败！！！\n");
			printf("3秒后自动返回！！！\n");
			sleep(3);
		}
	}else{
		printf("放弃修改！！！\n");
		printf("3秒后自动返回！！！\n");
		sleep(3);
	}	
	return;
}

/*
	函数功能:用户充值
	函数参数:用户链表头节点指针 用户链表中的当前用户节点指针
	返 回 值:无
*/
void clientAccountRecharge(ClientPointer clientHead,ClientPointer clientCurrent){
	float money=0.0;
	printf("请输入充值金额:");
	scanf("%f",&money);
	while(money < 0){
		printf("输入金额不能为负，请重新输入:");
		scanf("%f",&money);
	}
	clientCurrent->data.account += money;
	clientSaveTxt(clientHead);
	printf("充值成功！！！\n");
	printf("当前余额:%.2f\n",clientCurrent->data.account);
	while(getchar() != '\n');
	printf("按回车键返回~~~\n");
	getchar();
	return;
}

/*
	函数功能:用户注销
	函数参数:用户链表头节点指针 用户链表中的当前用户节点指针
	返 回 值:0注销成功  1注销失败或放弃注销
*/
int clientLogoff(ClientPointer clientHead,ClientPointer clientCurrent){
	char ch='\0';
	char password[20] = "";
	printf("是否注销(y/n):");
	scanf(" %c",&ch);
	if(ch == 'y' || ch == 'Y'){
		getchar();
		printf("请输入密码:");
		getPassword(password);
		if(0 == strcmp(password,clientCurrent->data.clientPassword)){
			clientCurrent->data.clientState = 0;
			clientSaveTxt(clientHead);
			printf("注销成功！！！\n");
			printf("3秒后自动返回！！！\n");
			sleep(3);
			return 0;
		}else{
			printf("注销失败！！！\n");
			printf("3秒后自动返回！！！\n");
			sleep(3);
			return 1;
		}
	}else{
		printf("注销失败！！！\n");
		printf("3秒后自动返回！！！\n");
		sleep(3);
	}
	return 1;
}

/*
	函数功能:用户购买彩票
	函数参数:用户链表头节点指针 用户链表中的当前用节点指针 每张彩票链表头节点指针 每期彩票链表头节点指针
	返 回 值:无
*/
void clientBuyLottery(ClientPointer clientHead,\
						ClientPointer clientCurrent,\
						LotteryPointer lotteryHead,\
						LotteryPerPointer lotteryPerHead ){
	LotteryPerPointer temp = lotteryPerSearchByState(lotteryPerHead);
	if(temp == NULL){
		printf("暂未发行！！！\n");
		while(getchar() != '\n');
		printf("按回车键返回~~~\n");
		getchar();
		return;
	}
	LotteryData data;
	memset(&data,0,sizeof(data));
	strcpy(data.lotteryName, clientCurrent->data.clientName);
	data.lotteryState = temp->data.lotteryPerState;
	data.winState = 0;
	data.issue = temp->data.issue;
	data.id = 1 + lotteryGetLength(lotteryHead);
	printf("请输入注数(最多5注):");
	scanf("%d",&data.count);
	if(data.count < 1 || data.count > 5){
		printf("输入有误！！！\n");
		while(getchar() != '\n');
		printf("按回车键返回~~~\n");
		getchar();
		return;
	}
	if((clientCurrent->data.account-(data.count * temp->data.price)) < 0){
		printf("余额不足，请充值！！！\n");
		while(getchar() != '\n');
		printf("按回车键返回~~~\n");
		getchar();
		return;
	}
	clientCurrent->data.account -= (data.count * temp->data.price); 
	temp->data.count += data.count;
	temp->data.account += (data.count * temp->data.price);
	printf("每注为1~20之间6个互不相同的随机数！！！\n");
	printf("请输入所选号码:\n");
	int i = 0;
	int j = 0;
	for(i = 0;i < data.count;i++){
		for(j = 0;j < 6;j++){
			scanf("%d",&data.number[i][j]);
		}
	}
	lotteryInsertAfter(lotteryHead, data);
	clientSaveTxt(clientHead);
	lotterySaveTxt(lotteryHead);
	lotteryPerSaveTxt(lotteryPerHead);
	printf("购买成功！！！\n");
	while(getchar() != '\n');
	printf("按回车键返回~~~\n");
	getchar();
	return;
}

/*
	函数功能:用户购买记录
	函数参数:用户链表中的当前用户节点指针 每张彩票链表头节点指针
	返 回 值:无
*/
void clientBuyLotteryRecord(ClientPointer clientCurrent,\
							LotteryPointer lotteryHead){
	int count = 0;
	LotteryPointer current = lotteryHead;
	while(NULL != current->next){
		current=current->next;
		if(strcmp(clientCurrent->data.clientName,\
					current->data.lotteryName) == 0){
			lotteryPrintCurrent(current);
			count++;
		}
	}
	printf("共购买%d张彩票！！！\n",count);
	while(getchar() != '\n');
	printf("按回车键返回~~~\n");
	getchar();
	return;
}




/*
	函数功能:公证员开奖
	函数参数:用户链表头节点 每张彩票链表头节点 每期彩票链表头节点
	返 回 值:无
*/
void notaryLotteryDraw(ClientPointer clientHead,\
						LotteryPointer lotteryHead,\
						LotteryPerPointer lotteryPerHead){
	LotteryPerPointer temp = lotteryPerSearchByState(lotteryPerHead);
	if(temp == NULL){
		printf("暂未发行！！！\n");
		while(getchar() != '\n');
		printf("按回车键返回~~~\n");
		getchar();
		return;
	}
	temp->data.lotteryPerState = 1;
	printf("本期中奖号码:\n");
	int i = 0;
	int j = 0;
	srand((unsigned int)time( NULL )+getpid());
	for(i = 0;i < 6;i++){
		temp->data.number[i]=rand()%20+1;
		for(j = 0;j < i;j++){
			if(temp->data.number[j] == temp->data.number[i]){
				i--;
				break;
			}
		}
	}
	for(i = 0;i < 6;i++){
		printf("%-4d",temp->data.number[i]);
	}
	printf("\n");
	LotteryPointer current = lotteryHead;
	while(NULL != current->next){
		current=current->next;
		if(temp->data.issue == current->data.issue){
			ClientPointer clientTemp = clientHead;
			while(NULL != clientTemp->next){
				clientTemp = clientTemp->next;
				if(strcmp(current->data.lotteryName,\
					clientTemp->data.clientName) == 0){
					lotteryIssue(clientTemp,current,temp);
				}
			}
		}
	}
	clientSaveTxt(clientHead);
	lotterySaveTxt(lotteryHead);
	lotteryPerSaveTxt(lotteryPerHead);
	printf("开奖完成！！！\n");
	while(getchar() != '\n');
	printf("按回车键返回~~~\n");
	getchar();
	return;
}

/*
	函数功能:公证员查看每期彩票记录
	函数参数:每期彩票链表头节点
	返 回 值:无
*/
void notaryLotteryRecord(LotteryPerPointer lotteryPerHead){
	if(lotteryPerHead->next == NULL || lotteryPerHead == NULL){
		printf("无开奖记录！！！\n");
		while(getchar() != '\n');
		printf("按回车键返回~~~\n");
		getchar();
		return;
	}else{
		LotteryPerPointer temp = lotteryPerHead;
		while(NULL != temp->next){
			temp = temp->next;
			if(temp->data.lotteryPerState == 1){
				lotteryPerPrintCurrent(temp);
			}
		}
		while(getchar() != '\n');
		printf("按回车键返回~~~\n");
		getchar();
	}
	return;
}