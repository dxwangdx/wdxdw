#include "clientMenu.h"
#include "clientView.h"

/*
	函数功能:客户端套接字创建函数
	函数参数:无
	返 回 值:无
*/
void clientSocketCreate(){
	system("clear");
	clientMainMenuView();	
	FILE *config_fd = NULL;
	char port[7] = {'\0'};
	char addr[17] = {'\0'};
	//从文件加载IP地址和端口
	config_fd = fopen("./data/serverConfig.txt","r");
	if(config_fd < 0){
		perror("open config file error");
		return;
	}
	fgets(addr,sizeof(addr),config_fd);
	fgets(port,sizeof(port),config_fd);
	fclose(config_fd);
	int client_fd = -1;
	//创建套接字
	client_fd = socket(AF_INET,SOCK_STREAM,0);
	if(client_fd < 0){
		perror("socket error");
		exit(1);
	}
	struct sockaddr_in sock_addr;
	memset(&sock_addr,0,sizeof(sock_addr));
	sock_addr.sin_family = AF_INET;
	sock_addr.sin_port = htons(atoi(port));
	sock_addr.sin_addr.s_addr = inet_addr(addr);
	//连接服务器
	if(connect(client_fd,(struct sockaddr *)&sock_addr,sizeof(sock_addr)) < 0){
		perror("connect error");
		close(client_fd);
		exit(1);
	}
	//互斥锁初始化
	pthread_mutex_init(&mutex,NULL);
	pthread_t thread = 0;
	pthread_attr_t attr;
	//线程属性初始化
	pthread_attr_init(&attr);
	//设置线程分离属性
	pthread_attr_setdetachstate(&attr,PTHREAD_CREATE_DETACHED);
	//创建线程
	if(0 != pthread_create(&thread,&attr,threadFunction,(void *)&client_fd)){
		perror("pthread create error");
		return;
	}
	clientMainMenu(client_fd);
	
	
	//线程取消
	int retval = pthread_cancel(thread);
	if(retval != 0){
		perror("pthread cancel error");
	}
	sleep(1);
	//线程销毁
	pthread_attr_destroy(&attr);
	//销毁锁
	pthread_mutex_destroy(&mutex);
	close(client_fd);
	return;
}

/*
	函数功能:主菜单功能处理函数
	函数参数:套接字文件描述符
	返 回 值:无
*/
void clientMainMenu(int client_fd){
	Heart heart;
	memset(&heart,0,sizeof(heart));
	pthread_t thread = 0;
	pthread_attr_t attr;
	pthread_attr_init(&attr);
	Protocol packageData;
	memset(&packageData,'\0',sizeof(packageData));
	printf("请输入选择的编号：\n");
	while(1){
		int choose = 3;
		scanf("%d",&choose);
		switch(choose){
			case 0:	//退出系统
			printf("系统退出！！！\n");
			sleep(1);
			system("clear");
			return;
			case 1:	//登录
			packageData = clientSendLogin(client_fd);
			sleep(1);
			//加锁
			pthread_mutex_lock(&mutex);
			if(count == 3){
				//解锁
				pthread_mutex_unlock(&mutex);
				printf("系统退出！！！\n");
				sleep(1);
				system("clear");
				return;
			}else if(count == -1){
				//解锁
				pthread_mutex_unlock(&mutex);
				count = 0;
				strcpy(heart.name,packageData.data.usrName);
				heart.socket_fd = client_fd;
				pthread_attr_setdetachstate(&attr,PTHREAD_CREATE_DETACHED);
				if(0 != pthread_create(&thread,&attr,threadFunctionHeart,(void *)&heart)){
					perror("pthread create error");
					return;
				}
				system("clear");
				clientSecondaryMenuView();
				strcpy(packageData.data.usrPassword,"******\n");
				clientSecondaryMenu(client_fd,packageData);
				//线程销毁
				pthread_attr_destroy(&attr);
				system("clear");
				clientMainMenuView();
				printf("请输入选择的编号：\n");
			}else{
				//解锁
				pthread_mutex_unlock(&mutex);
				printf("3秒后自动返回！！！\n");
				sleep(3);
				system("clear");
				clientMainMenuView();
				printf("请输入选择的编号：\n");
				break;
			}
			break;
			case 2:	//注册
			clientSendEnroll(client_fd);
			sleep(1);
			//加锁
			pthread_mutex_lock(&mutex);
			printf("3秒后自动返回！！！\n");
			sleep(3);
			system("clear");
			clientMainMenuView();
			printf("请输入选择的编号：\n");
			//解锁
			pthread_mutex_unlock(&mutex);
			break;
			default:
			fflush(stdout);
			system("clear");
			clientMainMenuView();
			printf("请输入选择的编号：\n");
			while(getchar()!='\0'){
				break;	
			}
			break;	
		}
	}
	return;
}

/*
	函数功能:二级菜单功能处理函数
	函数参数:套接字文件描述符 数据包结构体
	返 回 值:无
*/
void clientSecondaryMenu(int client_fd,Protocol packageData){
	int retval = 0;
	printf("请输入选择的编号：\n");
	while(1){
		int choose = 5;
		scanf("%d",&choose);
		switch(choose){
			case 0:	//用户退出
			exitFlag = 1;
			clientSendUsrExit(client_fd,packageData);
			sleep(1);
			//加锁
			pthread_mutex_lock(&mutex);
			while(getchar() != '\n');
			printf("按回车键返回~~~\n");
			getchar();
			//解锁
			pthread_mutex_unlock(&mutex);
			return;
			case 1:	//shell命令
			getchar();
			while(1){
				retval = clientSendCommand(client_fd);
				if(retval == 1){
					break;
				}
			}	
			sleep(1);
			//加锁
			pthread_mutex_lock(&mutex);
			printf("按回车键返回~~~\n");
			getchar();
			system("clear");
			clientSecondaryMenuView();
			printf("请输入选择的编号：\n");
			//解锁
			pthread_mutex_unlock(&mutex);
			break;
			case 2:	//单聊
			while(1){
				retval = clientSendSingleChat(client_fd,packageData);
				if(retval == 1){
					break;
				}
			}
			system("clear");
			clientSecondaryMenuView();
			printf("请输入选择的编号：\n");
			break;
			case 3:	//群聊
			getchar();
			while(1){
				retval = clientSendGroupChat(client_fd,packageData);
				if(retval == 1){
					break;
				}
			}
			system("clear");
			clientSecondaryMenuView();
			printf("请输入选择的编号：\n");
			break;
			case 4:	//在线用户
			clientSendOnlineUsr(client_fd,packageData);
			sleep(1);
			//加锁
			pthread_mutex_lock(&mutex);
			while(getchar() != '\n');
			printf("按回车键返回~~~\n");
			getchar();
			system("clear");
			clientSecondaryMenuView();
			printf("请输入选择的编号：\n");
			//解锁
			pthread_mutex_unlock(&mutex);
			break;
			default:
			fflush(stdout);
			system("clear");
			clientSecondaryMenuView();
			printf("请输入选择的编号：\n");
			while(getchar()!='\0'){
				break;	
			}
			break;	
		}
	}
	return;
}

/*
	函数功能:线程处理函数 接收数据包并处理
	函数参数:套接字文件描述符地址
	返 回 值:无
*/
void *threadFunction(void *arg){
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
	int client_fd = *(int*)arg;
	Protocol packageData;
	memset(&packageData,'\0',sizeof(packageData));
	while(1){
		retval = read(client_fd,&packageData,sizeof(packageData));
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
		messageSaveTxt(packageData);
		//消息类型判断
		switch(packageData.data.type){
			case TYPE_EXIT:		//退出数据包
			//加锁
			pthread_mutex_lock(&mutex);
			clientReceiveUsrExit(client_fd,&packageData);
			//解锁
			pthread_mutex_unlock(&mutex);
			break;
			case TYPE_LOGIN:		//登录数据包
			//加锁
			pthread_mutex_lock(&mutex);
			clientReceiveLogin(client_fd,&packageData);
			//解锁
			pthread_mutex_unlock(&mutex);
			break;
			case TYPE_ENROLL:	//注册数据包
			//加锁
			pthread_mutex_lock(&mutex);
			clientReceiveEnroll(client_fd,&packageData);
			//解锁
			pthread_mutex_unlock(&mutex);
			break;
			case TYPE_COMMAND:	//命令数据包
			//加锁
			pthread_mutex_lock(&mutex);
			clientReceiveCommand(client_fd,&packageData);
			//解锁
			pthread_mutex_unlock(&mutex);
			break;
			case TYPE_SINGLECHAT:	//单聊消息数据包
			clientReceiveSingleChat(client_fd,&packageData);
			break;
			case TYPE_GROUPCHAT:	//群聊消息数据包
			clientReceiveGroupChat(client_fd,&packageData);
			break;
			case TYPE_ONLINEUSR:	//在线用户数据包
			//加锁
			pthread_mutex_lock(&mutex);
			clientReceiveOnlineUsr(client_fd,&packageData);
			//解锁
			pthread_mutex_unlock(&mutex);
			break;
			default:
			perror("unknown data type");
			break;	
		}
	}
	close(client_fd);
	pthread_exit(NULL);
	return NULL;
}

/*
	函数功能:线程处理函数 定时发送心跳数据包
	函数参数:心跳信息发送结构体地址
	返 回 值:无
*/
void *threadFunctionHeart(void *argheart){
	int client_fd = ((Heart*)argheart)->socket_fd;
	Protocol packageData;
	memset(&packageData,'\0',sizeof(packageData));
	strcpy(packageData.data.usrName,((Heart*)argheart)->name);
	clientSendHeart(client_fd,packageData);
	alarm(3);
	while(1){
		if(alarmFlag == 1){
			alarmFlag = 0;
			clientSendHeart(client_fd,packageData);
		}
		if(exitFlag == 1){
			exitFlag = 0;
			break;
		}
	}
	pthread_exit(NULL);
	return NULL;
}

/*
	函数功能:信号处理函数
	函数参数:信号量
	返 回 值:无
*/
void sighandler(int signo){
	if(signo == SIGALRM){
		alarmFlag = 1;
		alarm(3);
	}
}