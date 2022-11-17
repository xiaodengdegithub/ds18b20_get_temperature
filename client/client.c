/*********************************************************************************
 *      Copyright:  (C) 2022 Deng Yonghao<dengyonghao2001@163.com>
 *                  All rights reserved.
 *
 *       Filename:  client.c
 *    Description:  This file 
 *                 
 *        Version:  1.0.0(2022年11月12日)
 *         Author:  Deng Yonghao <dengyonghao2001@163.com>
 *      ChangeLog:  1, Release initial version on "2022年11月12日 20时06分58秒"
 *                 
 ********************************************************************************/

#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <dirent.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <getopt.h>
#include <netdb.h>
#include <sys/socket.h>

//四元素：原IP、目的IP、原端口、目的端口；客户端原IP由操作系统自行分配
#define MSG_STR "Hello, here is client!\n"

int get_temperature(float *temp)
{
	int				fd = -1;
	char			buf[128];
	char			*ptr =NULL;
	DIR				*dirp = NULL;
	struct dirent	*direntp = NULL;
	char			w1_path[64]="/sys/bus/w1/devices/";
	char			chip_sn[32];
	int				found = 0;

	dirp=opendir(w1_path);
	if( !dirp )
	{
		printf("open floder %s failure: %s\n", w1_path, strerror(errno));
		return -1;
	}

	while( NULL != (direntp=readdir(dirp)) )
	{
		if( strstr(direntp->d_name, "28-"))
		{
			strncpy(chip_sn, direntp->d_name, sizeof(chip_sn));
			found = 1;
		}
	}

	closedir(dirp);

	if( !found )
	{
		printf("Can not find ds18b20 chipset\n");
		return -2;
	}

	strncat(w1_path, chip_sn, sizeof(w1_path)-strlen(w1_path));
	strncat(w1_path, "/w1_slave", sizeof(w1_path)-strlen(w1_path));

	if( (fd=open(w1_path, O_RDONLY)) < 0)
	{
		printf("open file failure: %s\n", strerror(errno));
		perror("open file failure");
		return -3;
	}

	memset(buf, 0, sizeof(buf));

	if(read(fd, buf, sizeof(buf)) < 0)
	{
		printf("read data from fd=%d failure %s\n", fd, strerror(errno));
		return -4;
	}
	ptr=strstr(buf, "t=");
	if( !ptr )
	{
		printf("Can not find t= string\n");
		return -5;
	}

	ptr += 2;

	*temp = atof(ptr)/1000;
	printf("temperature: %f\n", *temp);

	close(fd);

	return 0;
}

void print_usage(char *progname)
{
	printf("%s usage: \n", progname);
	printf("-i(--ipaddr): sepcify server IP address.\n");
	printf("-d(--domain name): sepcify server domain name.\n");
	printf("-p(--port): sepcify server port.\n");
	printf("-h(--Help): print this help information.\n");

	return ;
}

int main(int argc, char **argv)
{
	int                 getaddrfd = -1;  //定义getaddrinfo函数返回值
	struct addrinfo     ainfo;    //定义一个结构体
	struct addrinfo     *res;     //定义函数返回的结构体链表的指针
	struct addrinfo     *hand;    //定义一个遍历链表的指针
	struct sockaddr_in  *seraddr;   //定义一个存储返回域名IP信息的结构体指针
	int					sockfd = -1;
	int					rv = -1;
	struct sockaddr_in	servaddr;//我们是ipv4
	char				*servip = NULL;
	char				*servdn = NULL;
	struct hostent		*servhost = NULL;
	char                **hostip = NULL;
	char				ipstr[32];
	int					port = 0;
	char				buf[1024];
	int					ch;
	float				temp;
	char				tstr[]="temperature: ";
	char				str[64];
	struct option		opts[] = {
		{"ipaddr", required_argument, NULL, 'i'},
		{"domain name", required_argument, NULL, 'd'},
		{"port", required_argument, NULL, 'P'},
		{"help", no_argument, NULL, 'h'},
		{NULL, 0, NULL, 0}
	};

	while( (ch=getopt_long(argc, argv, "i:d:p:h", opts, NULL)) != -1)//h不用加参数,所以后面不加":"
	{
		switch(ch)
		{
			case 'i':
				servip=optarg;
				break;
			case 'd':
				servdn=optarg;
				break;
			case 'p':
				port=atoi(optarg);
				break;
			case 'h':
				print_usage(argv[0]);
				return 0;
		}

	}

	if( !(!servip ^ !servdn) || !port )
	{
		print_usage(argv[0]);
		return 0;
	}

	if(!servip)
	{
		memset(&ainfo, 0, sizeof(ainfo));   //将存放信息的结构体清零
		ainfo.ai_flags = AI_PASSIVE;      //写入期望返回的结构体的相关信息
		ainfo.ai_socktype = SOCK_STREAM;
		ainfo.ai_family = AF_INET;
		ainfo.ai_protocol = 0;

		getaddrfd = getaddrinfo(servdn, NULL, &ainfo, &res); // 调用函数

		if(getaddrfd != 0)   //如果函数调用失败
		{
			printf("Analyze faliure:%s\n",strerror(errno));
			return -1;
		}

		printf("Analyze successfully\n");  //调用函数成功

		for (hand = res; hand != NULL; hand = hand->ai_next)   //遍历链表每一个节点，查询关于存储返回的IP的信息
		{
			seraddr = (struct sockaddr_in *)hand->ai_addr;  //将返回的IP信息存储在addr指向的结构体中
			printf("IP address: %s\n", inet_ntoa(seraddr->sin_addr));  //inet_ntoa函数将字符串类型IP地址转化为点分十进制
			servip=inet_ntoa(seraddr->sin_addr);
		}

		freeaddrinfo(res);  
	}

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

	rv = connect(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr));//我们servaddr是sockaddr_in类型的，而我们的connect中第二个参数需要sockaddr类型，所以用一个强制转换
	if(rv < 0)
	{
		printf("Connect to server[%s:%d] failure: %s\n",
				servip, port, strerror(errno));
		return -2;
	}
	printf("Connect to server[%s:%d] successfully!\n", servip, port);

	while(1)
	{
		/*		rv = write(sockfd, MSG_STR, strlen(MSG_STR));
				if(rv < 0)
				{
				printf("write to server by sockfd[%d] failure : %s\n",
				sockfd, strerror(errno));
				break;
				}	*/

		rv = get_temperature(&temp);
		if(rv<0)
		{
			printf("get temperature failure, return value: %d", rv);
			break;
		}

		sprintf(str,"%s%f\n",tstr,temp);
		rv = write(sockfd, str, strlen(str));
		if(rv < 0)
		{
			printf("write to server by sockfd[%d] failure : %s\n",
					sockfd, strerror(errno));
			break;
		}	

		memset(buf, 0, sizeof(buf));
		rv = read(sockfd, buf, sizeof(buf));
		if(rv < 0)
		{
			printf("Read data from server by sockfd[%d] failure: %s\n",
					sockfd, strerror(errno));
			break;
		}
		else if(rv == 0)
		{
			printf("Socket[%d] get disconnected\n", sockfd);
			break;
		}
		else if(rv > 0)
		{
			printf("Read %d bytes data from Server: %s\n",
					rv, buf);
			sleep(10);
		}	

	}

	close(sockfd);
}
