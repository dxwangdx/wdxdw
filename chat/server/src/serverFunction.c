#include "serverFunction.h"

/*
	函数功能:服务器处理退出函数
	函数参数:accept返回的套接字文件描述符 在线用户链表头指针 数据包结构体
	返 回 值:无
*/
void serverHandleUsrExit(int client_fd,ClientPointer clientOnlineHead,\
									Protocol packageData){
	printf("Enter:%s\n",__func__);
	clientDelete(clientOnlineHead,packageData.data.usrName);
	strcpy(packageData.data.data,"退出成功！！！\n");
	if(write(client_fd,&packageData,sizeof(packageData)) < 0){
		perror("write exit message error");
	}
	return;
}

/*
	函数功能:服务器处理登录函数
	函数参数:线程处理函数参数结构体
			 accept返回的套接字文件描述符
			 注册用户链表头指针
			 在线用户链表头指针
			 数据包结构体
	返 回 值:无
*/
void serverHandleLogin(void *arg,int client_fd,ClientPointer clientHead,\
									ClientPointer clientOnlineHead,\
									Protocol packageData){
	printf("Enter:%s\n",__func__);
	ClientPointer pre = clientSearchByName(clientHead,packageData.data.usrName);
	if(pre == NULL){
		strcpy(packageData.data.data,"该用户名不存在！！！\n");
		if(write(client_fd,&packageData,sizeof(packageData)) < 0){
			perror("write login usrname message error");
		}
	}else{
		if(strcmp(pre->next->data.password,packageData.data.usrPassword) != 0){
			strcpy(packageData.data.data,"登录密码有误！！！\n");
			if(write(client_fd,&packageData,sizeof(packageData)) < 0){
				perror("write login password message error");
			}
		}else{
			//登录成功
			int retval = -1;
			ClientData data;
			memset(&data,'\0',sizeof(data));
			data.socket_fd = client_fd;
			data.timsec = time(NULL);
			strcpy(data.timstr,ctime(&data.timsec));
			strcpy(data.name,packageData.data.usrName);
			data.port = ((Parameter *)arg)->port;
			strcpy(data.ip,((Parameter *)arg)->ip);
			retval = clientInsertAfter(clientOnlineHead,data);
			if(retval == 1){
				strcpy(packageData.data.data,"该用户已经在线！！！\n");
				if(write(client_fd,&packageData,sizeof(packageData)) < 0){
					perror("write login message error");
				}
			}else{
				loginSaveTxt(data);
				strcpy(packageData.data.data,"登录成功！！！\n");
				if(write(client_fd,&packageData,sizeof(packageData)) < 0){
					perror("write login message error");
				}
			}
		}
	}
	return;
}

/*
	函数功能:服务器处理注册函数
	函数参数:accept返回的套接字文件描述符 注册用户链表头指针 数据包结构体
	返 回 值:无
*/
void serverHandleEnroll(int client_fd,ClientPointer clientHead,Protocol packageData){
	printf("Enter:%s\n",__func__);
	int retval = -1;
	ClientData clientData;
	memset(&clientData,'\0',sizeof(clientData));
	strcpy(clientData.name,packageData.data.usrName);
	strcpy(clientData.password,packageData.data.usrPassword);
	retval = clientInsertAfter(clientHead, clientData);
	clientSaveTxt(clientHead);
	if(retval == 1){
		strcpy(packageData.data.data,"该用户名已被注册，注册失败！！！\n");
		if(write(client_fd,&packageData,sizeof(packageData)) < 0){
			perror("write enroll message error");
		}
	}else{
		strcpy(packageData.data.data,"注册成功！！！\n");
		if(write(client_fd,&packageData,sizeof(packageData)) < 0){
			perror("write enroll message error");
		}
	}	
	return;
}

/*
	函数功能:服务器处理shell命令函数
	函数参数:accept返回的套接字文件描述符 数据包结构体
	返 回 值:无
*/
void serverHandleCommand(int client_fd,Protocol packageData){
	printf("Enter:%s\n",__func__);
	int command_fd = open("./data/shellCommand.txt",O_CREAT|O_RDWR|O_TRUNC,0777);
	if(command_fd < 0){
		perror("open shell command file error");
		return;
	}
	int Wcommand_fd = open("./data/wrongCommand.txt",O_CREAT|O_RDWR|O_TRUNC,0777);
	if(Wcommand_fd < 0){
		perror("open wrong shell command file error");
		return;
	}
	int retval = -1;
	int saveCmd_fd = dup(STDOUT_FILENO);
	int saveWcmd_fd = dup(STDERR_FILENO);
	dup2(command_fd,STDOUT_FILENO);
	dup2(Wcommand_fd,STDERR_FILENO);
	retval = system(packageData.data.data);
	if(retval < 0){
		perror("system error");
	}else if(retval > 0){
		fflush(stdout);
		if(lseek(Wcommand_fd,0,SEEK_SET) < 0){
			perror("lseek error");
		}
		if(read(Wcommand_fd,&packageData.data.data,sizeof(packageData.data.data)) < 0){
			perror("read wrong shell command message error");
		}
		if(write(client_fd,&packageData,sizeof(packageData)) < 0){
			perror("write wrong shell command message error");
		}
	}else{
		fflush(stdout);
		if(lseek(command_fd,0,SEEK_SET) < 0){
			perror("lseek error");
		}
		if(read(command_fd,&packageData.data.data,sizeof(packageData.data.data)) < 0){
			perror("read shell command message error");
		}
		if(write(client_fd,&packageData,sizeof(packageData)) < 0){
			perror("write shell command message error");
		}
	}
	dup2(saveCmd_fd,STDOUT_FILENO);
	dup2(saveWcmd_fd,STDERR_FILENO);
	close(command_fd);
	close(Wcommand_fd);


	return;
}

/*
	函数功能:服务器处理单聊函数
	函数参数:accept返回的套接字文件描述符 注册用户链表头指针 数据包结构体
	返 回 值:无
*/
void serverHandleSingleChat(int client_fd,ClientPointer clientOnlineHead,Protocol packageData){
	printf("Enter:%s\n",__func__);
	int chatUsr_fd = -1;
	ClientPointer pre = NULL;
	printf("client_fd = %d\n",client_fd);
	pre = clientSearchByName(clientOnlineHead,packageData.data.chatName);
	if(pre != NULL){
		chatUsr_fd = pre->next->data.socket_fd;
		printf("chatUsr_fd = %d\n",chatUsr_fd);
		if(write(chatUsr_fd,&packageData,sizeof(packageData)) < 0){
			perror("write signal chat message error");
		}
	}else{
		strcpy(packageData.data.data,"不能向未在线用户发送消息！！！\n");
		if(write(client_fd,&packageData,sizeof(packageData)) < 0){
			perror("write retval signal chat message error");
		}
	}
	return;
}

/*
	函数功能:服务器处理群聊函数
	函数参数:accept返回的套接字文件描述符 注册用户链表头指针 数据包结构体
	返 回 值:无
*/
void serverHandleGroupChat(int client_fd,ClientPointer clientOnlineHead,\
										Protocol packageData){
	printf("Enter:%s\n",__func__);
	int chatUsr_fd = -1;
	ClientPointer temp = clientOnlineHead;
	temp = temp->next;
	while(temp != NULL){
		chatUsr_fd = temp->data.socket_fd;
		if(chatUsr_fd != client_fd){
			if(write(chatUsr_fd,&packageData,sizeof(packageData)) < 0){
				perror("write group chat message error");
			}
		}
		temp = temp->next;
	}
	return;
}

/*
	函数功能:服务器处理在线用户函数
	函数参数:accept返回的套接字文件描述符 注册用户链表头指针 数据包结构体
	返 回 值:无
*/
void serverHandleOnlineUsr(int client_fd,ClientPointer clientOnlineHead,\
										Protocol packageData){
	printf("Enter:%s\n",__func__);
	ClientPointer temp = clientOnlineHead;
	temp = temp->next;
	while(temp != NULL){
		memset(&packageData.data.data,'\0',sizeof(packageData.data.data));
		strcpy(packageData.data.timstr,temp->data.timstr);
		strcpy(packageData.data.data,temp->data.name);
		strcat(packageData.data.data,"\n");
		if(write(client_fd,&packageData,sizeof(packageData)) < 0){
			perror("write online usr name error");
		}
		temp = temp->next;
	}
	return;
}

/*
	函数功能:服务器处理心跳函数
	函数参数:accept返回的套接字文件描述符 注册用户链表头指针 数据包结构体
	返 回 值:无
*/
void serverHandleHeart(int client_fd,ClientPointer clientOnlineHead,\
										Protocol packageData){
	printf("Enter:%s\n",__func__);
	printf("用 户 名：");
	fflush(stdout);
	if(write(STDOUT_FILENO,packageData.data.usrName,sizeof(packageData.data.usrName)) < 0){
		perror("write usr name error");
	}
	printf("\n运行状态：");
	fflush(stdout);
	if(write(STDOUT_FILENO,packageData.data.data,sizeof(packageData.data.data)) < 0){
		perror("write usr name error");
	}
	printf("当前时间：");
	fflush(stdout);
	if(write(STDOUT_FILENO,packageData.data.timstr,sizeof(packageData.data.timstr)) < 0){
		perror("write usr name error");
	}
	ClientData heartData;
	memset(&heartData,'\0',sizeof(heartData));
	strcpy(heartData.name,packageData.data.usrName);
	heartData.timsec = packageData.data.timsec;
	//建在线用户心跳链表 刷新心跳时间
	if(clientHeartHead == NULL){
		ClientPointer clientHeartHeadHeap = calloc(1, sizeof(Client));
		clientHeartHead = clientHeartHeadHeap;
		if(clientHeartHead == NULL){
			perror("calloc error");
		}
		clientInsertAfter(clientHeartHead, heartData);
	}else{
		ClientPointer pre = NULL;
		pre = clientSearchByName(clientHeartHead,heartData.name);
		if(pre == NULL){
			clientInsertAfter(clientHeartHead, heartData);
		}else{
			pre->next->data.timsec = heartData.timsec;
		}
	}
	return;
}
