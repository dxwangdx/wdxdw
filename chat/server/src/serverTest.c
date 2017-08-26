#include "serverMenu.h"

/*
	函数功能:主函数 程序入口
	函数参数:无
	返 回 值:无
*/
int main(void){
	//SIGINT信号登记
	if(signal(SIGINT,sighandler) == SIG_ERR){
		perror("signal sigint error");
		exit(1);	
	}
	//SIGALRM信号登记
	if(signal(SIGALRM,sighandler) == SIG_ERR){
		perror("signal sigalrm error");
		exit(1);	
	}
	//申请注册用户链表头节点
	ClientPointer clientHead = calloc(1, sizeof(Client));
	if(clientHead == NULL){
		printf("%s %d ERROR\n",__FILE__,__LINE__);
		return -1;
	}
	//从文件中加载注册用户至内存中
	clientLoadTxt(clientHead);
	//申请在线用户链表头节点
	ClientPointer clientOnlineHead = calloc(1, sizeof(Client));
	if(clientOnlineHead == NULL){
		printf("%s %d ERROR\n",__FILE__,__LINE__);
		perror("calloc clientOnlineHead error");
	}
	//服务器端创建套接字
	serverSocketCreate(clientHead,clientOnlineHead);
	
	//释放在线用户链表
	freeClientLink(clientOnlineHead);
	
	//释放注册用户链表
	freeClientLink(clientHead);

	printf("\nserver exit\n");
	
	return 0;
}
