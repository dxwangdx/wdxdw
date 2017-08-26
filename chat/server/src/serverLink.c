#include "serverLink.h"

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
	if(NULL == clientSearchByName(clientHead, data.name)){
		ClientPointer clientNewNode = clientCreatNode(data);
		while(NULL != temp->next){
			temp = temp->next;
		}
		temp->next = clientNewNode;
	}else{
		return 1;	//用户名已经被注册
	}
	return 0;
}

/*
	函数功能:删除用户
	函数参数:用户链表头节点指针 用户名
	返 回 值:无
*/
void clientDelete(ClientPointer clientHead, char *name){
	ClientPointer pre = NULL;
	ClientPointer cur = NULL;
	pre = clientSearchByName(clientHead,name);
	if(pre == NULL){	//用户未在在线链表
		printf("链表中不存在该用户！！！\n");
	}else{
		cur = pre->next;
		pre->next = cur->next;
		free(cur);
		cur = NULL;
	}
	return;
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
	int retval=0;
	while(temp->next != NULL){
		temp = temp->next;
		retval = fprintf(fp,"用户名:%s\t密码:%s\n",\
					temp->data.name,temp->data.password);
		if(retval == -1){
			perror("fprintf error");
			break;
		}
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
	int retval=0;
	while(1){
		retval=fscanf(fp,"用户名:%s\t密码:%s\n",\
						data.name,data.password);
		if(retval == 0){
			break;
		}
		if(retval == -1){
			break;
		}
		clientInsertAfter(clientHead,data);
	}
	fclose(fp);
	return;
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
		if((strcmp(name,current->data.name)) == 0){
			return previous;
		}
	}
	return NULL;
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
	函数功能:信号处理函数
	函数参数:信号量
	返 回 值:无
*/
void sighandler(int signo){
	if(signo == SIGINT){
		exitFlag = 1;
	}
	if(signo == SIGALRM){
		alarmFlag = 1;
		alarm(15);
	}
}

/*
	函数功能:客户端登录信息保存函数
	函数参数:用户结构体
	返 回 值:无
*/
void loginSaveTxt(ClientData clientData){
	FILE *fp;
	fp = fopen("./data/loginlog.txt","a+");
	if(fp == NULL){
		printf("打开文件失败\n");
		return;
	}
	int retval=0;
	retval = fprintf(fp,"name:%s\tIP:%s\tport:%d\tsocket_fd:%d\ttime:%s",\
					clientData.name,clientData.ip,clientData.port,\
					clientData.socket_fd,clientData.timstr);
	if(retval == -1){
		perror("fprintf error");
	}
	fclose(fp);
}

/*
	函数功能:服务端消息记录保存函数
	函数参数:数据包结构体
	返 回 值:无
*/
void messageSaveTxt(Protocol packageData){
	FILE *fp;
	fp = fopen("./data/messagelog.txt","a+");
	if(fp == NULL){
		printf("打开文件失败\n");
		return;
	}
	int retval=0;
	retval = fprintf(fp,"Type:%d\tUsrName:%s\tChatName:%s\tTime:%sData:\n%s",\
					packageData.data.type,packageData.data.usrName,packageData.data.chatName,\
					packageData.data.timstr,packageData.data.data);
	if(retval == -1){
		perror("fprintf error");
	}
	fclose(fp);
}
