#include "view.h"

/*
	函数功能:主菜单界面
	函数参数:无
	返 回 值:无
*/
void mainMenuView(){
	printf("*****彩票系统界面*****\n");
	printf("**                  **\n");
	printf("**  1.登录          **\n");
	printf("**  2.注册          **\n");
	printf("**  0.退出          **\n");
	printf("**                  **\n");
	printf("**********************\n");
	return;
}

/*
	函数功能:管理员菜单界面
	函数参数:无
	返 回 值:无
*/
void adminMenuView(){
	printf("******管理员界面******\n");
	printf("**                  **\n");
	printf("**  1.发行彩票      **\n");
	printf("**  2.开奖信息      **\n");
	printf("**  3.销售记录      **\n");
	printf("**  4.彩民查询      **\n");
	printf("**  5.用户找回      **\n");
	printf("**  6.彩民排序      **\n");
	printf("**  0.返回系统      **\n");
	printf("**                  **\n");
	printf("**********************\n");
	return;	
}

/*
	函数功能:客户端菜单界面
	函数参数:无
	返 回 值:无
*/
void clientMenuView(){
	printf("******客户端界面******\n");
	printf("**                  **\n");
	printf("**  1.个人信息      **\n");
	printf("**  2.密码修改      **\n");
	printf("**  3.账户充值      **\n");
	printf("**  4.彩票购买      **\n");
	printf("**  5.购买记录      **\n");
	printf("**  6.注销用户      **\n");
	printf("**  0.返回系统      **\n");
	printf("**                  **\n");
	printf("**********************\n");
	return;
}

/*
	函数功能:公证员菜单界面
	函数参数:无
	返 回 值:无
*/
void notaryMenuView(){
	printf("******公证员界面******\n");
	printf("**                  **\n");
	printf("**  1.彩票开奖      **\n");	
	printf("**  2.开奖纪录      **\n");
	printf("**  0.返回系统      **\n");
	printf("**                  **\n");
	printf("**********************\n");
	return;
}