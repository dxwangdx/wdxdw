#include "clientFunction.h"

/*
	函数功能:用户发送退出信息函数
	函数参数:客服端套接字文件描述符 数据包结构体
	返 回 值:无
*/
void clientSendUsrExit(int client_fd,Protocol packageData){
	strcpy(packageData.data.chatName,"服务器");
	strcpy(packageData.data.data,"退出\n");
	packageData.data.timsec = time(NULL);
	strcpy(packageData.data.timstr,ctime(&packageData.data.timsec));
	packageData.data.type = TYPE_EXIT;
	if(write(client_fd,&packageData,sizeof(packageData)) < 0){
		perror("write usr exit error");
	}
	return;
}

/*
	函数功能:用户发送登录信息函数
	函数参数:客服端套接字文件描述符
	返 回 值:无
*/
Protocol clientSendLogin(int client_fd){
	Protocol packageData;
	memset(&packageData,'\0',sizeof(packageData));
	printf("登录用户名:");
	scanf("%s",packageData.data.usrName);
	printf("输入密码:");
	scanf("%s",packageData.data.usrPassword);
	strcpy(packageData.data.chatName,"服务器");
	strcpy(packageData.data.data,"登录\n");
	packageData.data.timsec = time(NULL);
	strcpy(packageData.data.timstr,ctime(&packageData.data.timsec));
	packageData.data.type = TYPE_LOGIN;
	if(write(client_fd,&packageData,sizeof(packageData)) < 0){
		perror("write login message error");
	}
	return packageData;
}

/*
	函数功能:用户发送注册信息函数
	函数参数:客服端套接字文件描述符
	返 回 值:无
*/
void clientSendEnroll(int client_fd){
	Protocol packageData;
	memset(&packageData,'\0',sizeof(packageData));
	char password[20] = "";
	printf("注册用户名:");
	scanf("%s",packageData.data.usrName);
	printf("输入密码:");
	scanf("%s",password);
	printf("确认密码:");
	scanf("%s",packageData.data.usrPassword);
	strcpy(packageData.data.chatName,"服务器");
	strcpy(packageData.data.data,"注册\n");
	packageData.data.timsec = time(NULL);
	strcpy(packageData.data.timstr,ctime(&packageData.data.timsec));
	if(0 != strcmp(password,packageData.data.usrPassword)){
		printf("两次输入密码不同，注册失败！！！\n");	
		return;
	}
	packageData.data.type = TYPE_ENROLL;
	if(write(client_fd,&packageData,sizeof(packageData)) < 0){
		perror("write enroll message error");
	}
	return;
}

/*
	函数功能:用户发送shell命令函数
	函数参数:客服端套接字文件描述符
	返 回 值:0继续输入shell命令 1退出输入shell命令功能
*/
int clientSendCommand(int client_fd){
	sleep(1);
	Protocol packageData;
	memset(&packageData,'\0',sizeof(packageData));
	strcpy(packageData.data.chatName,"服务器");
	printf("\n请输入shell命令(输入exit退出):\n");
	fgets(packageData.data.data,sizeof(packageData.data.data),stdin);
	packageData.data.timsec = time(NULL);
	strcpy(packageData.data.timstr,ctime(&packageData.data.timsec));
	if(strcmp(packageData.data.data,"exit\n") == 0){
		return 1;
	}
	packageData.data.type = TYPE_COMMAND;
	if(write(client_fd,&packageData,sizeof(packageData)) < 0){
		perror("write shell command error");
	}
	return 0;
}

/*
	函数功能:用户发送单聊信息函数
	函数参数:客服端套接字文件描述符 数据包结构体
	返 回 值:0继续输入单聊信息 1退出输入单聊功能
*/
int clientSendSingleChat(int client_fd,Protocol packageData){
	sleep(1);
	printf("请输入用户:\n");
	scanf("%s",packageData.data.chatName);
	printf("请输入消息(输入exit退出):\n");
	getchar();
	memset(&packageData.data.data,'\0',sizeof(packageData.data.data));
	fgets(packageData.data.data,sizeof(packageData.data.data),stdin);
	packageData.data.timsec = time(NULL);
	strcpy(packageData.data.timstr,ctime(&packageData.data.timsec));
	if(strcmp(packageData.data.data,"exit\n") == 0){
		return 1;
	}
	packageData.data.type = TYPE_SINGLECHAT;
	if(write(client_fd,&packageData,sizeof(packageData)) < 0){
		perror("write single chat error");
	}
	return 0;
}

/*
	函数功能:用户发送群聊信息函数
	函数参数:客服端套接字文件描述符 数据包结构体
	返 回 值:0继续输入群聊信息 1退出输入群聊功能
*/
int clientSendGroupChat(int client_fd,Protocol packageData){
	printf("请输入消息(输入exit退出):\n");
	memset(&packageData.data.data,'\0',sizeof(packageData.data.data));
	fgets(packageData.data.data,sizeof(packageData.data.data),stdin);
	packageData.data.timsec = time(NULL);
	strcpy(packageData.data.timstr,ctime(&packageData.data.timsec));
	if(strcmp(packageData.data.data,"exit\n") == 0){
		return 1;
	}
	packageData.data.type = TYPE_GROUPCHAT;
	if(write(client_fd,&packageData,sizeof(packageData)) < 0){
		perror("write group chat error");
	}
	return 0;
}

/*
	函数功能:用户发送获取在线客户函数
	函数参数:客服端套接字文件描述符 数据包结构体
	返 回 值:无
*/
void clientSendOnlineUsr(int client_fd,Protocol packageData){
	strcpy(packageData.data.chatName,"服务器");
	strcpy(packageData.data.data,"获取在线用户\n");
	packageData.data.timsec = time(NULL);
	strcpy(packageData.data.timstr,ctime(&packageData.data.timsec));
	packageData.data.type = TYPE_ONLINEUSR;
	if(write(client_fd,&packageData,sizeof(packageData)) < 0){
		perror("write online usr error");
	}
	return;
}

/*
	函数功能:用户发送心跳信息函数
	函数参数:客服端套接字文件描述符 数据包结构体
	返 回 值:无
*/
void clientSendHeart(int client_fd,Protocol packageData){
	strcpy(packageData.data.chatName,"服务器");
	strcpy(packageData.data.data,"运行正常\n");
	packageData.data.timsec = time(NULL);
	strcpy(packageData.data.timstr,ctime(&packageData.data.timsec));
	packageData.data.type = TYPE_HEART;
	if(write(client_fd,&packageData,sizeof(packageData)) < 0){
		perror("write online status error");
	}
	return;
}




/*
	函数功能:用户接收退出信息函数
	函数参数:客服端套接字文件描述符 数据包结构体指针
	返 回 值:无
*/
void clientReceiveUsrExit(int client_fd,ProtocolPointer packageDataP){
	if(write(STDOUT_FILENO,packageDataP->data.data,\
				sizeof(packageDataP->data.data)) < 0){
		perror("write receive exit message error");
	}
	return;
}

/*
	函数功能:用户接收登录信息函数
	函数参数:客服端套接字文件描述符 数据包结构体指针
	返 回 值:无
*/
void clientReceiveLogin(int client_fd,ProtocolPointer packageDataP){
	if(write(STDOUT_FILENO,packageDataP->data.data,\
				sizeof(packageDataP->data.data)) < 0){
		perror("write receive login message error");
	}
	if(strcmp(packageDataP->data.data,"该用户名不存在！！！\n") == 0||\
		strcmp(packageDataP->data.data,"登录密码有误！！！\n") == 0){
		count++;
		if(count < 3){
			printf("您还有%d次登录机会！！！\n",3-count);
		}
	}else{
		count = -1;
	}
	if(strcmp(packageDataP->data.data,"该用户已经在线！！！\n") == 0){
		count = 0;
	}
	return;
}

/*
	函数功能:用户接收注册信息函数
	函数参数:客服端套接字文件描述符 数据包结构体指针
	返 回 值:无
*/
void clientReceiveEnroll(int client_fd,ProtocolPointer packageDataP){
	if(write(STDOUT_FILENO,packageDataP->data.data,\
				sizeof(packageDataP->data.data)) < 0){
		perror("write receive enroll message error");
	}
	return;
}

/*
	函数功能:用户接收shell命令信息函数
	函数参数:客服端套接字文件描述符 数据包结构体指针
	返 回 值:无
*/
void clientReceiveCommand(int client_fd,ProtocolPointer packageDataP){
	printf("时间：");
	fflush(stdout);
	if(write(STDOUT_FILENO,packageDataP->data.timstr,\
				sizeof(packageDataP->data.timstr)) < 0){
		perror("write receive chat message error");
	}
	if(write(STDOUT_FILENO,packageDataP->data.data,\
				sizeof(packageDataP->data.data)) < 0){
		perror("write receive command message error");
	}
	return;
}

/*
	函数功能:用户接收单聊信息函数
	函数参数:客服端套接字文件描述符 数据包结构体指针
	返 回 值:无
*/
void clientReceiveSingleChat(int client_fd,ProtocolPointer packageDataP){
	printf("发 送 方：");
	fflush(stdout);
	if(write(STDOUT_FILENO,packageDataP->data.usrName,\
				sizeof(packageDataP->data.usrName)) < 0){
		perror("write receive chat message error");
	}
	printf("\n发送时间：");
	fflush(stdout);
	if(write(STDOUT_FILENO,packageDataP->data.timstr,\
				sizeof(packageDataP->data.timstr)) < 0){
		perror("write receive chat message error");
	}
	printf("消息内容：");
	fflush(stdout);
	if(write(STDOUT_FILENO,packageDataP->data.data,\
				sizeof(packageDataP->data.data)) < 0){
		perror("write receive chat message error");
	}
	return;
}

/*
	函数功能:用户接收群聊信息函数
	函数参数:客服端套接字文件描述符 数据包结构体指针
	返 回 值:无
*/
void clientReceiveGroupChat(int client_fd,ProtocolPointer packageDataP){
	printf("发 送 方：");
	fflush(stdout);
	if(write(STDOUT_FILENO,packageDataP->data.usrName,\
				sizeof(packageDataP->data.usrName)) < 0){
		perror("write receive chat message error");
	}
	printf("\n发送时间：");
	fflush(stdout);
	if(write(STDOUT_FILENO,packageDataP->data.timstr,\
				sizeof(packageDataP->data.timstr)) < 0){
		perror("write receive chat message error");
	}
	printf("消息内容：");
	fflush(stdout);
	if(write(STDOUT_FILENO,packageDataP->data.data,\
				sizeof(packageDataP->data.data)) < 0){
		perror("write receive chat message error");
	}
	return;
}

/*
	函数功能:用户接收在线用户函数
	函数参数:客服端套接字文件描述符 数据包结构体指针
	返 回 值:无
*/
void clientReceiveOnlineUsr(int client_fd,ProtocolPointer packageDataP){
	printf("在线用户：");
	fflush(stdout);
	if(write(STDOUT_FILENO,packageDataP->data.data,\
				sizeof(packageDataP->data.data)) < 0){
		perror("write receive online usr error");
	}
	printf("登录时间：");
	fflush(stdout);
	if(write(STDOUT_FILENO,packageDataP->data.timstr,\
				sizeof(packageDataP->data.timstr)) < 0){
		perror("write receive online usr error");
	}
	printf("\n");
	fflush(stdout);
	return;
}

/*
	函数功能:用户接收信息保存函数
	函数参数:客服端套接字文件描述符 数据包结构体指针
	返 回 值:无
*/
void messageSaveTxt(Protocol packageData){
	FILE *fp;
	fp = fopen("./data/messagelog.txt","a+");
	if(fp == NULL){
		printf("打开文件失败\n");
		return;
	}
	int retval = 0;
	retval = fprintf(fp,"Type:%d\tUsrName:%s\tChatName:%s\tTime:%sData:\n%s",\
					packageData.data.type,packageData.data.usrName,packageData.data.chatName,\
					packageData.data.timstr,packageData.data.data);
	if(retval == -1){
		perror("fprintf error");
	}
	fclose(fp);
}
