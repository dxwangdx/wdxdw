#include "clientMenu.h"

/*
	函数功能:主函数 程序入口
	函数参数:无
	返 回 值:无
*/
int main(void){
	//SIGALRM信号登记
	if(signal(SIGALRM,sighandler) == SIG_ERR){
		perror("perror sigalrm error");
		exit(1);
	}
	//客户端创建套接字
	clientSocketCreate();
	return 0;
}