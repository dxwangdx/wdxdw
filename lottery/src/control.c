#include "control.h"

#define ADMIN_NAME "admin"
#define ADMIN_PASSWORD "123456"
#define NOTARY_NAME "notary"
#define NOTARY_PASSWORD "123456"

/*
	函数功能:登录功能
	函数参数:用户链表头节点 每张彩票链表头节点 每期彩票链表头节点
	返 回 值:0管理员登录成功  1公证员登录成功  2用户登录成功  3登录失败
*/
int login(ClientPointer clientHead,\
			LotteryPointer lotteryHead,\
			LotteryPerPointer lotteryPerHead){
	char name[20]="";
	char password[20]="";
	char autoCode[5]="";
	char inputCode[5]="";
	int i=0;
	for(i=0;i<3;i++){
		ClientPointer clientCurrent = clientHead;
		system("clear");
		mainMenuView();
		printf("请输入用户名:");
		scanf("%s",name);
		getchar();
		printf("请输入密码:");
		getPassword(password);
		identifyCode(autoCode);
		printf("验证码:%s\n",autoCode);
		printf("请输入验证码:");
		scanf("%s",inputCode);
		if(0 == strcmp(name,ADMIN_NAME)&&\
			0 == strcmp(password,ADMIN_PASSWORD)&&\
			0 == strcmp(autoCode,inputCode)){
			system("clear");
			adminMenu(clientHead,lotteryHead,lotteryPerHead);
			return 0;
		}else if(0 == strcmp(name,NOTARY_NAME)&&\
			0 == strcmp(password,NOTARY_PASSWORD)&&\
			0 == strcmp(autoCode,inputCode)){
			system("clear");
			notaryMenu(clientHead,lotteryHead,lotteryPerHead);
			return 1;
		}else{
			while(clientCurrent->next != NULL){
				clientCurrent=clientCurrent->next;
				if(0==strcmp(name,clientCurrent->data.clientName)&&\
					0==strcmp(password,clientCurrent->data.clientPassword)&&\
					0 == strcmp(autoCode,inputCode)&&\
					clientCurrent->data.clientState == 1){
					system("clear");
					clientMenu(clientHead,clientCurrent,lotteryHead,lotteryPerHead);
					return 2;
				}
			}
		}
//		system("clear");
		if(i<2){
			printf("登录失败,您还有%d次机会！！！\n",2-i);
			printf("3秒后自动返回！！！\n");
		}else{
			printf("3秒后自动退出！！！\n");
		}
		sleep(3);
	}
	return 3;
}

/*
	函数功能:注册用户功能
	函数参数:用户链表头节点
	返 回 值:无
*/
void enroll(ClientPointer clientHead){
	char password[20] = "";
	char autoCode[5]="";
	char inputCode[5]="";
	ClientData data;
	data.account = 1000.00;
	data.clientState = 1;
	data.id = 10001+clientGetLength(clientHead);
	printf("注册用户名:");
	scanf("%s",data.clientName);
	getchar();
	printf("输入密码:");
	getPassword(password);
	printf("确认密码:");
	getPassword(data.clientPassword);
	identifyCode(autoCode);
	printf("验证码:%s\n",autoCode);
	printf("请输入验证码:");
	scanf("%s",inputCode);
	if(0 == strcmp(password,data.clientPassword)&&\
		0 == strcmp(autoCode,inputCode)){
		int temp = 0;
		temp = clientInsertAfter(clientHead, data);
		if(temp == 1){
			printf("3秒后自动返回！！！\n");
			sleep(3);
			return;
		}
		clientSaveTxt(clientHead);
		printf("注册成功，赠送1000元！！！\n");
		printf("3秒后自动返回！！！\n");
		sleep(3);
	}else{
		printf("输入有误，注册失败！！！\n");
		printf("3秒后自动返回！！！\n");
		sleep(3);
	}
	return;
}

/*
	函数功能:生成验证码
	函数参数:字符数组指针
	返 回 值:无
*/
void identifyCode(char *str){
	int i = 0;
	int pos = 0;
	int len = 0;
	char charLib[] = "0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJLMNOPQRSTUVWXYZ";
    len = strlen(charLib);
    srand((unsigned int)time(NULL)+getpid());
    for (i = 0;i < 4; i++) {
        pos = rand()%len;
        str[i] = charLib[pos];
    }
}