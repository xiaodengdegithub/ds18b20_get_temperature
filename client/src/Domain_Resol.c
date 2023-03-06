/*********************************************************************************
 *      Copyright:  (C) 2022 Deng Yonghao<dengyonghao2001@163.com>
 *                  All rights reserved.
 *
 *       Filename:  Domain_Resol.c
 *    Description:  This file  Domain Resolution
 *                 
 *        Version:  1.0.0(2022年11月19日)
 *         Author:  Deng Yonghao <dengyonghao2001@163.com>
 *      ChangeLog:  1, Release initial version on "2022年11月19日 16时22分44秒"
 *                 
 ********************************************************************************/

#include "Domain_Resol.h"

int domain_getaddrinfo(char **servdn)
{
	/*getaddrinfo*/
	int                getaddrfd = -1;  //定义getaddrinfo函数返回值
	struct addrinfo    ainfo;    //定义一个结构体
	struct addrinfo    *res;     //定义函数返回的结构体链表的指针
	struct addrinfo    *hand;    //定义一个遍历链表的指针
	struct sockaddr_in *seraddr;   //定义一个存储返回域名IP信息的结构体指针

	memset(&ainfo, 0, sizeof(ainfo));   //将存放信息的结构体清零
	ainfo.ai_flags = AI_PASSIVE;      //写入期望返回的结构体的相关信息
	ainfo.ai_socktype = SOCK_STREAM;
	ainfo.ai_family = AF_INET;
	ainfo.ai_protocol = 0;

	getaddrfd = getaddrinfo(*servdn, NULL, &ainfo, &res); // 调用函数

	if(getaddrfd != 0)   //如果函数调用失败
	{
		log_error("Analyze faliure:%s\n",strerror(errno));
		return -1;
	}

	log_info("Analyze successfully\n");  //调用函数成功

	for (hand = res; hand != NULL; hand = hand->ai_next)   //遍历链表每一个节点，查询关于存储返回的IP的信息
	{
		seraddr = (struct sockaddr_in *)hand->ai_addr;  //将返回的IP信息存储在addr指向的结构体中
		log_info("IP address: %s\n", inet_ntoa(seraddr->sin_addr));  //inet_ntoa函数将字符串类型IP地址转化为点分十进制
		*servdn=inet_ntoa(seraddr->sin_addr);
	}
	freeaddrinfo(res);
}
