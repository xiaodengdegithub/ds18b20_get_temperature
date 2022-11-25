/*********************************************************************************
 *      Copyright:  (C) 2022 Deng Yonghao<dengyonghao2001@163.com>
 *                  All rights reserved.
 *
 *       Filename:  main.c
 *    Description:  This file is main.c
 *                 
 *        Version:  1.0.0(2022年11月18日)
 *         Author:  Deng Yonghao <dengyonghao2001@163.com>
 *      ChangeLog:  1, Release initial version on "2022年11月18日 20时06分03秒"
 *                 
 ********************************************************************************/

#include "main.h"

int main(int argc, char **argv)
{
	/*getaddrinfo*/
	int                 getaddrfd = -1;  //定义getaddrinfo函数返回值
	struct addrinfo     ainfo;    //定义一个结构体
	struct addrinfo     *res;     //定义函数返回的结构体链表的指针
	struct addrinfo     *hand;    //定义一个遍历链表的指针
	struct sockaddr_in  *seraddr;   //定义一个存储返回域名IP信息的结构体指针
	/*ip or domain*/
	char				*servip = NULL;
	char				*servdn = NULL;
	/*socket*/
	int					sockfd = -1;
	int					rv = -1;
	struct sockaddr_in	servaddr;//我们是ipv4
	int					port = 0;
	/*time*/
	char				datime[100];
	long				T1=0;
	long				T2=0;
	/*excute*/
	sqlite3				*db;
	char				SN[16];
	char				buf[1024];
	float				temp;
	char				tstr[]="temperature: ";
	/*getopt*/
	int					time = 10;
	int					daemon_run = 0;
	int					ch;
	char				str[64];
	struct option		opts[] = {
		{"ipaddr", required_argument, NULL, 'i'},
		{"domain name", required_argument, NULL, 'd'},
		{"port", required_argument, NULL, 'P'},
		{"time", required_argument, NULL, 't'},
		{"daemon", no_argument, NULL, 'b'},
		{"help", no_argument, NULL, 'h'},
		{NULL, 0, NULL, 0}
	};

	while( (ch=getopt_long(argc, argv, "i:d:p:t:bh", opts, NULL)) != -1)//h不用加参数,所以后面不加":"
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
			case 't':
				time=atoi(optarg);
				break;
			case 'b':
				daemon_run=1;
				break;
			case 'h':
				print_usage(argv[0]);
				return 0;
		}

	}

	if( !(!servip ^ !servdn) || !port )//^两边的值不同为1，相同为0
	{
		print_usage(argv[0]);
		return 0;
	}

	if(!servip)
	{
		domain_getaddrinfo(&servdn);
		servip=servdn;
		log_info("%s",servdn);
		/*
		memset(&ainfo, 0, sizeof(ainfo));   //将存放信息的结构体清零
		ainfo.ai_flags = AI_PASSIVE;      //写入期望返回的结构体的相关信息
		ainfo.ai_socktype = SOCK_STREAM;
		ainfo.ai_family = AF_INET;
		ainfo.ai_protocol = 0;

		getaddrfd = getaddrinfo(servdn, NULL, &ainfo, &res); // 调用函数

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
			servip=inet_ntoa(seraddr->sin_addr);
		}

		freeaddrinfo(res);
		*/
	}

	//if(logger_init("running.log",LOG_LEVEL_DEBUG)<0)
	if(logger_init("stdout",LOG_LEVEL_DEBUG)<0)
	{
		fprintf(stderr, "initial logger system failure\n");
		dbg_print("initial logger system failure\n");
		return -1;
	}
	
	/*set signal */
	signal(SIGINT, stop);
	signal(SIGTERM, stop);

	/*daemon*/
	if(daemon_run)
	{
		daemon(0, 0);
		log_info("running daemon\n");
	}
	
	//get_sn(SN, sizeof(SN));
	Create_Database(&db);
	Create_Table(db);

	sockfd=socket_and_connect(servip, port);
/*
sockfd = socket(AF_INET, SOCK_STREAM, 0);//ipv4选AF_INET,为TCP所以选SOCK_STREAM，参数3自适应为0
	if(sockfd < 0)
	{
		log_error("Create socket failure: %s\n", strerror(errno));
		return -2;
	}
	log_info("Creact socket[%d] successfully!\n", sockfd);

	memset(&servaddr, 0, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(port);
	inet_aton(servip, &servaddr.sin_addr);

	rv = connect(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr));//我们servaddr是sockaddr_in类型的，而我们的connect中第二个参数需要sockaddr类型，所以用一个强制转换
	if(rv < 0)
	{
		log_error("Connect to server[%s:%d] failure: %s\n",
				servip, port, strerror(errno));
		return -2;
	}
	log_info("Connect to server[%s:%d] successfully!\n", servip, port);
*/	
	/*excute*/
	while(!pro_stop)//当它为0时就执行
	{
		/*rv = write(sockfd, MSG_STR, strlen(MSG_STR));
		if(rv < 0)
		{
			log_error("write to server by sockfd[%d] failure : %s\n",
					sockfd, strerror(errno));
			break;
		}*/

		rv = get_temperature(&temp);
		if(rv<0)
        {
            log_error("get temperature failure, return value: %d", rv);
            break;
        }
		
		get_sn(SN, sizeof(SN));
		T1 = get_time(datime, sizeof(datime));
		dbg_print("T1:%ld", T1);

		memset(buf, 0, sizeof(buf));
		snprintf(buf, 1024, "%s / %s / %f \n", SN, datime, temp);
		dbg_print("full data:%s", buf);
		while(!pro_stop)
		{
			if(socket_connect_state(sockfd)<0)
			{
				dbg_print("sockfd[%d] disconnected!\n", sockfd);
				log_error("sockfd[%d] disconnected!\n", sockfd);
				if(sockfd > 0)
				{
					close(sockfd);
					log_warn("sockfd[%d] close", sockfd);
				}
				sockfd = socket_and_connect(servip, port);
				log_info("socket connect again\n"); 
			}

			T2 = get_time(datime, sizeof(datime));
			dbg_print("T2:%ld\n", T2);
			
			if((T2 - T1) > time)
			{
				log_info("time reached\n");
				//snprintf(str,36,"%s%f\n",tstr,temp);
			
				if(socket_connect_state(sockfd)<0)
				{
					Insert_Table(db, SN, datime, temp);
					break;
				}

				rv = write(sockfd, buf, strlen(buf));
				if(rv < 0)
				{
						log_error("write to server by sockfd[%d] failure : %s\n",
								sockfd, strerror(errno));
						Insert_Table(db, SN, datime, temp);
						break;
				}
	
				memset(buf, 0, sizeof(buf));
				rv = read(sockfd, buf, sizeof(buf));
				if(rv < 0)
				{
					log_error("Read data from server by sockfd[%d] failure: %s\n",
							sockfd, strerror(errno));
					break;
				}
				else if(rv == 0)
				{
					log_warn("Socket[%d] get disconnected\n", sockfd);
					break;
				}
				else if(rv > 0)
				{
					log_info("Read %d bytes data from Server: %s\n",
							rv, buf);
					break;
				}

			}
			else
			{
				log_info("time not reached \n");
				
				rv = Table_check_write_clean(db, sockfd, SN);
				if(rv < 0)
				{
					log_warn("table_check_write_clean error\n");
					continue;
				}
				log_info("send all data of table and clean table\n");

				sleep(1);

				continue;
			}
		}
	}
	close(sockfd);
}

void stop(int signum)
{
    pro_stop = 1;
}

