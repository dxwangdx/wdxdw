#include "lotteryLink.h"

/*
	函数功能:用户链表节点创建
	函数参数:用户结构体数据
	返 回 值:clientNewNode 用户结构体节点指针
*/
ClientPointer clientCreatNode(ClientData data){
	ClientPointer clientNewNode = calloc(1, sizeof(Client));
	clientNewNode->data = data;
	return clientNewNode;
}

/*
	函数功能:用户节点后向插入用户链表
	函数参数:用户链表头节点指针 用户结构体数据
	返 回 值:0用户节未被注册  1用户节已被注册
*/
int clientInsertAfter(ClientPointer clientHead, ClientData data){
	ClientPointer temp = clientHead;
	ClientPointer clientNewNode = clientCreatNode(data);
	if(NULL == clientSearchByName(clientHead, data.clientName)){
		while(NULL != temp->next){
			temp = temp->next;
		}
		temp->next = clientNewNode;
	}else{
		free(clientNewNode);
		clientNewNode = NULL;
		printf("该用户名已被注册！！！\n");
		return 1;
	}
	return 0;
}

/*
	函数功能:打印所有用户节点
	函数参数:用户链表头节点指针
	返 回 值:无
*/
void clientPrintAll(ClientPointer clientHead){
	ClientPointer temp = clientHead;
	while(NULL != temp->next){
		temp = temp->next;
		printf("ID:%d\t用户名:%s\t密码:%s\t状态%d\t账户金额%.2f\n",\
						temp->data.id,\
						temp->data.clientName,\
						temp->data.clientPassword,\
						temp->data.clientState,\
						temp->data.account);
	}
	printf("\n");
}

/*
	函数功能:将用户链表数据保存至文件
	函数参数:用户链表头节点指针
	返 回 值:无
*/
void clientSaveTxt(ClientPointer clientHead){
	FILE *fp;
	fp = fopen("./data/client.txt","w");
	if(fp == NULL){
		printf("打开文件失败\n");
		return;
	}
	ClientPointer temp = clientHead;
	temp = clientHead;
	while(temp->next != NULL){
		temp = temp->next;
		fprintf(fp,"ID:%d\t用户名:%s\t密码:%s\t状态:%d\t账户金额:%f\n",\
						temp->data.id,\
						temp->data.clientName,\
						temp->data.clientPassword,\
						temp->data.clientState,\
						temp->data.account);
	}
	fclose(fp);
}

/*
	函数功能:从文件将用户数据加载至内存(堆)中
	函数参数:用户链表头节点指针
	返 回 值:无
*/
void clientLoadTxt(ClientPointer clientHead){
	FILE *fp;
	fp = fopen("./data/client.txt","r");
	if(fp == NULL){
		fp=fopen("./data/client.txt","w");
		if(fp == NULL){
			printf("%s %d ERROR\n",__FILE__,__LINE__);
			return;
		}
	}
	ClientData data;
	int flag=0;
	while(1){
		flag=fscanf(fp,"ID:%d\t用户名:%s\t密码:%s\t状态:%d\t账户金额:%f\n",\
						&data.id,\
						data.clientName,\
						data.clientPassword,\
						&data.clientState,\
						&data.account);
		if(flag == -1){
			break;
		}
		clientInsertAfter(clientHead,data);
	}
	fclose(fp);
	return;
}

/*
	函数功能:获取用户链表长度
	函数参数:用户链表头节点指针
	返 回 值:count 用户链表长度 即用户数量
*/
int clientGetLength(ClientPointer clientHead){
	int count = 0;
	ClientPointer temp = clientHead;
	while(NULL != temp->next){
		temp = temp->next;
		count++;
	}
	return count;
}

/*
	函数功能:按用户名查找用户
	函数参数:用户链表头节点指针 用户名
	返 回 值:previous 所查找用户的前一个节点指针
*/
ClientPointer clientSearchByName(ClientPointer clientHead, char *name){
	ClientPointer previous = clientHead;
	ClientPointer current = clientHead;
	while(NULL != current->next){
		previous = current;
		current=current->next;
		if((strcmp(name,current->data.clientName)) == 0){
			return previous;
		}
	}
	return NULL;
}

/*
	函数功能:按用户名排序
	函数参数:用户链表头节点指针
	返 回 值:无
*/
void clientSortByName(ClientPointer clientHead){
	ClientPointer minStore = NULL;		//中间变量，存放最小值
	ClientPointer match = NULL;			//链表中参加比较的数
	ClientPointer minStorePre = NULL;	//存放最小值前面的指针
	ClientPointer newTail = NULL;		//先链表的尾指针
	ClientPointer newHead = NULL;		//存放最小值前面的指针
	ClientPointer temp = clientHead->next;
	//对原链表进行循环，找出最小值
	while(temp != NULL){
		//循环一次，找到一个最小值
		for(match = temp,minStore=temp;match->next != NULL;match = match->next){
			if(strcmp(minStore->data.clientName,\
				match->next->data.clientName) > 0){
				minStore = match->next;
				minStorePre = match;
			}
		}
		//找到最小值后，将最小值放入新的链表中，采用后向插入法
		if(NULL == newHead){
			newHead = minStore;
		}else{
			newTail->next = minStore;
		}
		newTail = minStore;
		//找到最小值后，将原链表中的这个值删除
		if(minStore == temp){
			 temp = temp->next;
		}else{
			minStorePre->next = minStore->next;
		}
	}
	//排序完成后，为新的链表的最后一个节点做结束标志
	clientHead->next = newHead;
}

/*
	函数功能:按ID排序
	函数参数:用户链表头节点指针
	返 回 值:无
*/
void clientSortByID(ClientPointer clientHead){
	ClientPointer minStore = NULL;		//中间变量，存放最小值
	ClientPointer match = NULL;			//链表中参加比较的数
	ClientPointer minStorePre = NULL;	//存放最小值前面的指针
	ClientPointer newTail = NULL;		//先链表的尾指针
	ClientPointer newHead = NULL;		//存放最小值前面的指针
	ClientPointer temp = clientHead->next;
	//对原链表进行循环，找出最小值
	while(temp != NULL){
		//循环一次，找到一个最小值
		for(match = temp,minStore = temp;match->next != NULL;match = match->next){
			if(minStore->data.id > match->next->data.id){
				minStore = match->next;
				minStorePre = match;
			}
		}
		//找到最小值后，将最小值放入新的链表中，采用后向插入法
		if(NULL == newHead){
			newHead = minStore;
		}else{
			newTail->next = minStore;
		}
		newTail = minStore;
		//找到最小值后，将原链表中的这个值删除
		if(minStore == temp){
			 temp = temp->next;
		}else{
			minStorePre->next = minStore->next;
		}
	}
	//排序完成后，为新的链表的最后一个节点做结束标志
	clientHead->next = newHead;
}




/*
	函数功能:每张彩票链表节点创建
	函数参数:每张彩票结构体数据
	返 回 值:lotteryNewNode 每张彩票结构体节点指针
*/
LotteryPointer lotteryCreatNode(LotteryData data){
	LotteryPointer lotteryNewNode = calloc(1, sizeof(Lottery));
	lotteryNewNode->data = data;
	return lotteryNewNode;
}

/*
	函数功能:每张彩票节点后向插入每张彩票链表
	函数参数:每张彩票链表头节点指针 每张彩票结构体数据
	返 回 值:无
*/
void lotteryInsertAfter(LotteryPointer lotteryHead, LotteryData data){
	LotteryPointer temp = lotteryHead;
	LotteryPointer lotteryNewNode = lotteryCreatNode(data);
	while(NULL != temp->next){
		temp = temp->next;
	}
	temp->next = lotteryNewNode;
}

/*
	函数功能:打印当前这张彩票的信息
	函数参数:每张彩票链表中当前节点指针
	返 回 值:无
*/
void lotteryPrintCurrent(LotteryPointer temp){
	printf("期号:%d\nID:%d\n用户名:%s\n注数:%d\n\
所选号码:\n%-4d%-4d%-4d%-4d%-4d%-4d\n%-4d%-4d%-4d%-4d\
%-4d%-4d\n%-4d%-4d%-4d%-4d%-4d%-4d\n%-4d%-4d\
%-4d%-4d%-4d%-4d\n%-4d%-4d%-4d%-4d%-4d%-4d\n\
开奖状态:%d\n中奖状态:%d\n中奖金额:%.2f\n",\
				temp->data.issue,\
				temp->data.id,\
				temp->data.lotteryName,\
				temp->data.count,\
				temp->data.number[0][0],temp->data.number[0][1],temp->data.number[0][2],\
				temp->data.number[0][3],temp->data.number[0][4],temp->data.number[0][5],\
				temp->data.number[1][0],temp->data.number[1][1],temp->data.number[1][2],\
				temp->data.number[1][3],temp->data.number[1][4],temp->data.number[1][5],\
				temp->data.number[2][0],temp->data.number[2][1],temp->data.number[2][2],\
				temp->data.number[2][3],temp->data.number[2][4],temp->data.number[2][5],\
				temp->data.number[3][0],temp->data.number[3][1],temp->data.number[3][2],\
				temp->data.number[3][3],temp->data.number[3][4],temp->data.number[3][5],\
				temp->data.number[4][0],temp->data.number[4][1],temp->data.number[4][2],\
				temp->data.number[4][3],temp->data.number[4][4],temp->data.number[4][5],\
				temp->data.lotteryState,\
				temp->data.winState,\
				temp->data.account);
	printf("\n");
}

/*
	函数功能:将每张彩票链表数据保存至文件
	函数参数:每张彩票链表头节点指针
	返 回 值:无
*/
void lotterySaveTxt(LotteryPointer lotteryHead){
	FILE *fp;
	fp = fopen("./data/lottery.txt","w");
	if(fp == NULL){
		printf("打开文件失败\n");
		return;
	}
	LotteryPointer temp = lotteryHead;
	temp = lotteryHead;
	while(temp->next != NULL){
		temp = temp->next;
		fprintf(fp,"期号:%d\tID:%d\t用户名:%s\t注数:%d\t\
所选号码:%-4d%-4d%-4d%-4d%-4d%-4d\t%-4d%-4d%-4d%-4d\
%-4d%-4d\t%-4d%-4d%-4d%-4d%-4d%-4d\t%-4d%-4d\
%-4d%-4d%-4d%-4d\t%-4d%-4d%-4d%-4d%-4d%-4d\t\
开奖状态:%d\t中奖状态:%d\t中奖金额:%f\n",\
					temp->data.issue,\
					temp->data.id,\
					temp->data.lotteryName,\
					temp->data.count,\
					temp->data.number[0][0],temp->data.number[0][1],temp->data.number[0][2],\
					temp->data.number[0][3],temp->data.number[0][4],temp->data.number[0][5],\
					temp->data.number[1][0],temp->data.number[1][1],temp->data.number[1][2],\
					temp->data.number[1][3],temp->data.number[1][4],temp->data.number[1][5],\
					temp->data.number[2][0],temp->data.number[2][1],temp->data.number[2][2],\
					temp->data.number[2][3],temp->data.number[2][4],temp->data.number[2][5],\
					temp->data.number[3][0],temp->data.number[3][1],temp->data.number[3][2],\
					temp->data.number[3][3],temp->data.number[3][4],temp->data.number[3][5],\
					temp->data.number[4][0],temp->data.number[4][1],temp->data.number[4][2],\
					temp->data.number[4][3],temp->data.number[4][4],temp->data.number[4][5],\
					temp->data.lotteryState,\
					temp->data.winState,\
					temp->data.account);
	}
	fclose(fp);
}

/*
	函数功能:从文件将每张彩票数据加载至内存(堆)中
	函数参数:每张彩票链表头节点指针
	返 回 值:无
*/
void lotteryLoadTxt(LotteryPointer lotteryHead){
	if(NULL == lotteryHead){
		printf("ERROR\n");
		return;
	}
	FILE *fp;
	fp = fopen("./data/lottery.txt","r");
	if(fp == NULL){
		fp=fopen("./data/lottery.txt","w");
		return;
	}
	LotteryData data;
	int flag=0;
	while(1){
		flag=fscanf(fp,"期号:%d\tID:%d\t用户名:%s\t注数:%d\t\
所选号码:%4d%4d%4d%4d%4d%4d\t%4d%4d%4d%4d\
%4d%4d\t%4d%4d%4d%4d%4d%4d\t%4d%4d\
%4d%4d%4d%4d\t%4d%4d%4d%4d%4d%4d\t\
开奖状态:%d\t中奖状态:%d\t中奖金额:%f\n",\
						&data.issue,\
						&data.id,\
						data.lotteryName,\
						&data.count,\
						&data.number[0][0],&data.number[0][1],&data.number[0][2],\
						&data.number[0][3],&data.number[0][4],&data.number[0][5],\
						&data.number[1][0],&data.number[1][1],&data.number[1][2],\
						&data.number[1][3],&data.number[1][4],&data.number[1][5],\
						&data.number[2][0],&data.number[2][1],&data.number[2][2],\
						&data.number[2][3],&data.number[2][4],&data.number[2][5],\
						&data.number[3][0],&data.number[3][1],&data.number[3][2],\
						&data.number[3][3],&data.number[3][4],&data.number[3][5],\
						&data.number[4][0],&data.number[4][1],&data.number[4][2],\
						&data.number[4][3],&data.number[4][4],&data.number[4][5],\
						&data.lotteryState,\
						&data.winState,\
						&data.account);
		if(flag == -1){
			break;
		}
		lotteryInsertAfter(lotteryHead,data);
	}
	fclose(fp);
}

/*
	函数功能:获取每张彩票链表长度
	函数参数:每张彩票链表头节点指针
	返 回 值:count 每张彩票链表长度 即彩票张数
*/
int lotteryGetLength(LotteryPointer lotteryHead){
	int count = 0;
	LotteryPointer temp = lotteryHead;
	while(NULL != temp->next){
		temp = temp->next;
		count++;
	}
	return count;
}

/*
	函数功能:按未开奖状态查找彩票
	函数参数:每张彩票链表头节点指针
	返 回 值:current 所查找的当前每张彩票节点指针
*/
LotteryPointer lotterySearchByState(LotteryPointer lotteryHead){
	LotteryPointer current = lotteryHead;
	while(NULL != current->next){
		current=current->next;
		if(0 == current->data.lotteryState){
			return current;
		}
	}
	return NULL;
}

/*
	函数功能:按期号查找彩票
	函数参数:每张彩票链表头节点指针 彩票期号
	返 回 值:count 所查找的当期彩票总张数
*/
int lotterySearchPrintAllByIssue(LotteryPointer lotteryHead, int issue){
	int count = 0;
	LotteryPointer current = lotteryHead;
	while(NULL != current->next){
		current=current->next;
		if(issue == current->data.issue){
			lotteryPrintCurrent(current);
			count++;
		}
	}
	return count;
}




/*
	函数功能:每期彩票链表节点创建
	函数参数:每期彩票结构体数据
	返 回 值:lotteryPerNewNode 每期彩票结构体节点指针
*/
LotteryPerPointer lotteryPerCreatNode(LotteryPerData data){
	LotteryPerPointer lotteryPerNewNode = calloc(1, sizeof(LotteryPer));
	lotteryPerNewNode->data = data;
	return lotteryPerNewNode;
}

/*
	函数功能:每期彩票节点后向插入每期彩票链表
	函数参数:每期彩票链表头节点指针 每期彩票结构体数据
	返 回 值:无
*/
void lotteryPerInsertAfter(LotteryPerPointer lotteryPerHead,\
							LotteryPerData data){
	if(NULL == lotteryPerHead){
		return ;
	}
	LotteryPerPointer temp = lotteryPerHead;
	LotteryPerPointer lotteryPerNewNode = lotteryPerCreatNode(data);
	while(NULL != temp->next){
		temp = temp->next;
	}
	temp->next = lotteryPerNewNode;
}

/*
	函数功能:打印当前这期彩票的信息
	函数参数:每期彩票链表中当前节点指针
	返 回 值:无
*/
void lotteryPerPrintCurrent(LotteryPerPointer temp){
	printf("期号:%d\t单价:%d\t开奖号码:%-4d%-4d%-4d%-4d%-4d%-4d\n开奖状态:%d\t出售总数:%d\t奖池金额:%.2f\n",\
				temp->data.issue,\
				temp->data.price,\
				temp->data.number[0],\
				temp->data.number[1],\
				temp->data.number[2],\
				temp->data.number[3],\
				temp->data.number[4],\
				temp->data.number[5],\
				temp->data.lotteryPerState,\
				temp->data.count,\
				temp->data.account);
	printf("\n");
}

/*
	函数功能:将每期彩票链表数据保存至文件
	函数参数:每期彩票链表头节点指针
	返 回 值:无
*/
void lotteryPerSaveTxt(LotteryPerPointer lotteryPerHead){
	if(NULL == lotteryPerHead){
		printf("ERROR\n");
		return;
	}
	FILE *fp;
	fp = fopen("./data/lotteryPer.txt","w");
	if(fp == NULL){
		printf("打开文件失败\n");
		return;
	}
	LotteryPerPointer temp = lotteryPerHead;
	temp = lotteryPerHead;
	while(temp->next != NULL){
		temp = temp->next;
		fprintf(fp,"期号:%d\t单价:%d\t开奖号码:%-4d%-4d%-4d%-4d%-4d%-4d\t\
开奖状态:%d\t出售总数:%d\t奖池金额:%f\n",\
					temp->data.issue,\
					temp->data.price,\
					temp->data.number[0],\
					temp->data.number[1],\
					temp->data.number[2],\
					temp->data.number[3],\
					temp->data.number[4],\
					temp->data.number[5],\
					temp->data.lotteryPerState,\
					temp->data.count,\
					temp->data.account);
	}
	fclose(fp);
}

/*
	函数功能:从文件将每期彩票数据加载至内存(堆)中
	函数参数:每期彩票链表头节点指针
	返 回 值:无
*/
void lotteryPerLoadTxt(LotteryPerPointer lotteryPerHead){
	if(NULL == lotteryPerHead){
		printf("ERROR\n");
		return;
	}
	FILE *fp;
	fp = fopen("./data/lotteryPer.txt","r");
	if(fp == NULL){
		fp=fopen("./data/lotteryPer.txt","w");
		return;
	}
	LotteryPerData data;
	int flag=0;
	while(1){
		flag=fscanf(fp,"期号:%d\t单价:%d\t开奖号码:%4d%4d%4d%4d%4d%4d\t\
开奖状态:%d\t出售总数:%d\t奖池金额:%f\n",\
						&data.issue,\
						&data.price,\
						&data.number[0],\
						&data.number[1],\
						&data.number[2],\
						&data.number[3],\
						&data.number[4],\
						&data.number[5],\
						&data.lotteryPerState,\
						&data.count,\
						&data.account);
		if(flag == -1){
			break;
		}
		lotteryPerInsertAfter(lotteryPerHead,data);
	}
	fclose(fp);
}

/*
	函数功能:获取每期彩票链表长度
	函数参数:每期彩票链表头节点指针
	返 回 值:count 每期彩票链表长度 即彩票期数
*/
int lotteryPerGetLength(LotteryPerPointer lotteryPerHead){
	int count = 0;
	LotteryPerPointer temp = lotteryPerHead;
	while(NULL != temp->next){
		temp = temp->next;
		count++;
	}
	return count;
}

/*
	函数功能:查找未开奖的一期彩票
	函数参数:每期彩票链表头节点指针
	返 回 值:current 所查找的当前每期彩票节点指针
*/
LotteryPerPointer lotteryPerSearchByState(LotteryPerPointer lotteryPerHead){
	LotteryPerPointer current = lotteryPerHead;
	while(NULL != current->next){
		current=current->next;
		if(0 == current->data.lotteryPerState){
			return current;
		}
	}
	return NULL;
}




/*
	函数功能:兑奖功能
	函数参数:用户链表当前节点指针 每张彩票链表当前节点指针 每期彩票链表当前节点指针
	返 回 值:无
*/
void lotteryIssue(ClientPointer clientTemp,LotteryPointer current,LotteryPerPointer temp){
	int i = 0;
	int j = 0;
	int k = 0;
	int count = 0;
	int winCount = 0;
	current->data.lotteryState = temp->data.lotteryPerState;
	for(i = 0;i < current->data.count;i++){
		count = 0;
		for(j = 0;j < 6;j++){
			for(k = 0;k <6;k++){
				if(temp->data.number[j] == current->data.number[i][k]){
					count++;
				}
			}
		}
		if(count >= 3){
			winCount++;
		}
		if(count == 3){
			temp->data.account -= temp->data.price * 2;
			current->data.account += temp->data.price * 2;
			clientTemp->data.account += temp->data.price * 2;
		}
		if(count == 4){
			temp->data.account -= temp->data.price * 10;
			current->data.account += temp->data.price * 10;
			clientTemp->data.account += temp->data.price * 10;
		}
		if(count == 5){
			temp->data.account -= temp->data.price * 100;
			current->data.account += temp->data.price * 100;
			clientTemp->data.account += temp->data.price * 100;
		}
		if(count == 6){
			temp->data.account -= temp->data.price * 2000;
			current->data.account += temp->data.price * 2000;
			clientTemp->data.account += temp->data.price * 2000;
		}
	}
	current->data.winState = winCount;
}




/*
	函数功能:设置终端为不回显不缓冲，并获取按键的键值
	函数参数:无
	返 回 值:按键的键值int型
*/
int getch(){
	struct termios tm, tm_old;
	int fd = STDIN_FILENO, ch;
	if(tcgetattr(fd, &tm) < 0)	{
		return -1;
	}
	tm_old = tm;
	cfmakeraw(&tm);	//就是将终端设置为原始模式，该模式下所有的输入数据以字节为单位被处理。
					//在原始模式下，终端是不可回显的，而且所有特定的终端输入/输出模式不可用。
	if(tcsetattr(fd, TCSANOW, &tm) < 0){//不等数据传输完毕就立即改变属性 成功返回0 失败返回-1
		return -1;
	}
	ch = fgetc(stdin);
	if(tcsetattr(fd, TCSANOW, &tm_old) < 0){
		return -1;
	}
	return ch;
}

/*
	函数功能:调用getch获取键值保存到pcPWD中并单个回显
			 可以分别用backspace删除输入和回车确认输入
			 用于获取密码
	函数参数:字符数组指针pcPWD
	返 回 值:无
*/
void getPassword(char *pcPWD){
	int ch=0;
	int i=0;
	for(i=0;i<20;){
		ch=getch();
		if(ch==-1){
			continue;
		}
		if((ch == 127 || ch == 8) && i>0){
			putchar('\b');
			putchar(' ');
			putchar('\b');
			i--;
		}else if(ch==10 || ch == 13){
			pcPWD[i]=0;
			putchar('\n');
			return;
		}else if(i==0&&(ch==127 ||ch == 8)){
			printf("\a");
		}else if(i<19){
			pcPWD[i]=(char)ch;
			putchar('*');
			i++;
		}else{
			printf("\a");
		}
	}
}




/*
	函数功能:释放用户链表
	函数参数:用户链表头节点指针
	返 回 值:无
*/
void freeClientLink(ClientPointer clientHead){
	ClientPointer temp = clientHead;
	while(NULL != clientHead){
		temp = clientHead;
		clientHead = clientHead->next;
		free(temp);
	}
	return;
}

/*
	函数功能:释放每张彩票链表
	函数参数:每张彩票链表头节点指针
	返 回 值:无
*/
void freeLotteryLink(LotteryPointer lotteryHead){
	LotteryPointer temp = lotteryHead;
	while(NULL != lotteryHead){
		temp = lotteryHead;
		lotteryHead = lotteryHead->next;
		free(temp);
	}
	return;
}

/*
	函数功能:释放每期彩票链表
	函数参数:每期彩票链表头节点指针
	返 回 值:无
*/
void freeLotteryPerLink(LotteryPerPointer lotteryPerHead){
	LotteryPerPointer temp = lotteryPerHead;
	while(NULL != lotteryPerHead){
		temp = lotteryPerHead;
		lotteryPerHead = lotteryPerHead->next;
		free(temp);
	}
	return;
}
