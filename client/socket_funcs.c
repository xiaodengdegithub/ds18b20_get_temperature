/*********************************************************************************
 *      Copyright:  (C) 2022 Deng Yonghao<dengyonghao2001@163.com>
 *                  All rights reserved.
 *
 *       Filename:  socket_funcs.c
 *    Description:  This file socket_funcs.c
 *                 
 *        Version:  1.0.0(2022年11月19日)
 *         Author:  Deng Yonghao <dengyonghao2001@163.com>
 *      ChangeLog:  1, Release initial version on "2022年11月19日 20时01分54秒"
 *                 
 ********************************************************************************/

#include "socket_funcs.h"

int socket_and_connect(char *servip, int port)
{
	int					sockfd=-1;
	int					rv=-1;
	struct sockaddr_in	servaddr;//我们是ipv4

	sockfd = socket(AF_INET, SOCK_STREAM, 0);//ipv4选AF_INET,为TCP所以选SOCK_STREAM，参数3自适应为0
	if(sockfd < 0)
	{
		printf("Create socket failure: %s\n", strerror(errno));
		return -2;
	}
	printf("Creact socket[%d] successfully!\n", sockfd);

	memset(&servaddr, 0, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(port);
	inet_aton(servip, &servaddr.sin_addr);

	rv = connect(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr));//                                                                                   我们servaddr是sockaddr_in类型的，而我们的connect中第二个参数需要sockaddr类型，所以用一个强制转换
	if(rv < 0)
	{
		printf("Connect to server[%s:%d] failure: %s\n",
				servip, port, strerror(errno));
		return -2;
	}
	printf("Connect to server[%s:%d] successfully!\n", servip, port);
	return sockfd;
}


