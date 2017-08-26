#include "serverMenu.h"

/*
	函数功能:服务器端套接字创建函数
	函数参数:注册用户链表头指针 在线用户链表头指针
	返 回 值:无
*/
void serverSocketCreate(ClientPointer clientHead,ClientPointer clientOnlineHead){
	FILE *config_fd = NULL;
	char port[7] = {'\0'};
	char addr[17] = {'\0'};
	//从文件加载IP地址和端口
	config_fd = fopen("./data/serverConfig.txt","r");
	if(config_fd == NULL){
		perror("fopen config file error");
		return;
	}
	fgets(addr,sizeof(addr),config_fd);
	fgets(port,sizeof(port),config_fd);
	fclose(config_fd);
	int server_fd = -1;
	//创建套接字
	server_fd = socket(AF_INET,SOCK_STREAM,0);
	if(server_fd < 0){
		perror("socket error");
		exit(1);
	}
	printf("server_fd = %d\n",server_fd);
	
	//设置套接字为非阻塞模式
	int retval = fcntl(server_fd, F_GETFL, 0);
	if(retval < 0){
		perror("fcntl server_fd error");
		exit(1);
	}
	retval = fcntl(server_fd, F_SETFL, retval | O_NONBLOCK); 
		if(retval < 0){
		perror("fcntl socket error");
		exit(1);
	}
	
	struct sockaddr_in sock_addr;
	memset(&sock_addr,0,sizeof(sock_addr));
	sock_addr.sin_family = AF_INET;
	sock_addr.sin_port = htons(atoi(port));
	sock_addr.sin_addr.s_addr = inet_addr(addr);
	//绑定IP地址和端口
	if(0 > bind(server_fd,(struct sockaddr *)&sock_addr,sizeof(sock_addr))){
		perror("bind error");
		close(server_fd);
		exit(1);
	}
	//监听
	if(listen(server_fd,20) < 0){
		perror("listen error");
		close(server_fd);
		exit(1);
	}
	alarm(15);
	struct sockaddr_in client_addr;
	memset(&client_addr,0,sizeof(client_addr));
	socklen_t len = sizeof(client_addr);
	Parameter param;
	memset(&param,0,sizeof(param));
	param.linkHead = clientHead;
	param.linkOnlineHead = clientOnlineHead;
	int client_fd = -1;
	pthread_t thread = 0;
	pthread_attr_t attr;
	//循环接收处理客户端连接请求
	while(1){
		//心跳异常检测
		if(alarmFlag == 1){
			alarmFlag = 0;
			if(clientHeartHead != NULL){
				ClientPointer pre = NULL;
				ClientPointer temp = NULL;
				temp = clientHeartHead;
				time_t timsec = time(NULL);
				while(temp->next != NULL){
					pre = temp;
					temp = temp->next;
					if((timsec-(temp->data.timsec)) > 15){
						clientDelete(clientOnlineHead, temp->data.name);
						pre->next = temp->next;
						free(temp);
						temp = NULL;
						temp = pre;
					}
				}
			}
		}
		//ctrl+c退出 释放资源
		if(exitFlag == 1){
			sleep(1);
			//线程取消
			int retval = pthread_cancel(thread);
			if(retval < 0){
				perror("pthread cancel error");
			}
			//释放心跳链表
			if(clientHeartHead != NULL){
				freeClientLink(clientHeartHead);
			}
			//关闭套接字
			close(server_fd);
			return;
		}
		//接收处理客户端连接请求(非阻塞模式)
		client_fd = accept(server_fd,(struct sockaddr *)&client_addr,&len);
		if(client_fd == -1){
			continue;
		}
		param.socket_fd = client_fd;
		param.port = ntohs(client_addr.sin_port);
		strcpy(param.ip,inet_ntoa(client_addr.sin_addr));
		printf("client_fd = %d\n",client_fd);
		printf("client IP:%s,PORT:%d\n",inet_ntoa(client_addr.sin_addr),ntohs(client_addr.sin_port));
		//线程属性初始化
		pthread_attr_init(&attr);
		//设置线程分离属性
		pthread_attr_setdetachstate(&attr,PTHREAD_CREATE_DETACHED);
		//创建线程
		if(0 != pthread_create(&thread,&attr,threadFunction,(void *)&param)){
			perror("pthread create error");
			return;
		}
		//线程销毁
		pthread_attr_destroy(&attr);
	}
	return;
}

/*
	函数功能:线程处理函数 接收数据包 处理 发送数据包
	函数参数:Parameter结构体地址
	返 回 值:无
*/
void *threadFunction(void *arg){
	printf("Enter:%s\n",__func__);
	//允许退出线程
	int res = pthread_setcancelstate(PTHREAD_CANCEL_ENABLE,NULL);   
	if(res != 0){
		perror("Thread cancelation failed");
	}
	//设置立即取消
	res = pthread_setcanceltype(PTHREAD_CANCEL_ASYNCHRONOUS,NULL);
	if(res != 0){
		perror("Thread cancelation failed");
	}
	int retval = -1;
	int client_fd = ((Parameter*)arg)->socket_fd;
	ClientPointer clientHead = ((Parameter*)arg)->linkHead;
	ClientPointer clientOnlineHead = ((Parameter*)arg)->linkOnlineHead;
	printf("client_fd = %d\n",client_fd);
	Protocol packageData;
	while(1){
		memset(&packageData,'\0',sizeof(packageData));
		retval = read(client_fd,&packageData,sizeof(packageData));
		printf("retval = %d\n",retval);
		if(retval < 0){
			perror("read error");
			break;
		}
		if(retval == 0){
			perror("finish read");
			break;
		}
		if(retval != sizeof(packageData)){
			perror("read message error");
			break;
		}
		//保存数据包数据至文件
		messageSaveTxt(packageData);
		//消息类型判断
		switch(packageData.data.type){
			case TYPE_EXIT:		//退出数据包
			serverHandleUsrExit(client_fd,clientOnlineHead,packageData);
			break;
			case TYPE_LOGIN:	//登录数据包
			serverHandleLogin(arg,client_fd,clientHead,clientOnlineHead,packageData);
			break;
			case TYPE_ENROLL:	//注册数据包
			serverHandleEnroll(client_fd,clientHead,packageData);
			break;
			case TYPE_COMMAND:	//命令数据包
			serverHandleCommand(client_fd,packageData);
			break;
			case TYPE_SINGLECHAT:	//单聊消息数据包
			serverHandleSingleChat(client_fd,clientOnlineHead,packageData);
			break;
			case TYPE_GROUPCHAT:	//群聊消息数据包
			serverHandleGroupChat(client_fd,clientOnlineHead,packageData);
			break;
			case TYPE_ONLINEUSR:	//在线用户数据包
			serverHandleOnlineUsr(client_fd,clientOnlineHead,packageData);
			break;
			case TYPE_HEART:		//心跳数据包
			serverHandleHeart(client_fd,clientOnlineHead,packageData);
			break;
			default:
			perror("unknown data type");
			break;
		}
	}
	//关闭accept返回的套接字
	close(client_fd);
	//线程退出
	pthread_exit(NULL);
	return NULL;
}
