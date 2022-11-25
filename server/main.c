/*********************************************************************************
 *      Copyright:  (C) 2022 Deng Yonghao<dengyonghao2001@163.com>
 *                  All rights reserved.
 *
 *       Filename:  main.c
 *    Description:  This file server main 
 *                 
 *        Version:  1.0.0(2022年11月12日)
 *         Author:  Deng Yonghao <dengyonghao2001@163.com>
 *      ChangeLog:  1, Release initial version on "2022年11月12日 20时53分47秒"
 *                 
 ********************************************************************************/

#include "main.h"

int main(int argc, char **argv)
{
	int					listenfd, connfd;
	int					serv_port = 0;
	int					daemon_run = 0;
	char				*progname = NULL;
	int					opt;
	int					rv;
	int					i, j;
	int					found;
	char				buf[1024];
	int					epollfd;
	struct				epoll_event event;
	struct				epoll_event event_array[MAX_EVENTS];
	int					events;
	sqlite3				*db;
	char				SN[16];
	float				temp;
	char				datime[100];

	struct		option long_options[] =
	{ 
		{"port", required_argument, NULL, 'p'},
		{"daemon", no_argument, NULL, 'b'},
		{"help", no_argument, NULL, 'h'},
		{NULL, 0, NULL, 0}
	}; 

	progname = basename(argv[0]);

	/* Parser the command line parameters */
	while ((opt = getopt_long(argc, argv, "p:bh", long_options, NULL)) != -1)
	{ 
		switch (opt)
		{ 
			case 'p':
				serv_port = atoi(optarg);
				break; 
			case 'b':
                daemon_run=1;
                break;
			case 'h': /* Get help information */
				print_usage(progname);
				return EXIT_SUCCESS;
			default:
				break;
		} 
	} 
	if( !serv_port )
	{ 
		print_usage(progname);
		return -1;
	}
	if(logger_init("stdout",LOG_LEVEL_DEBUG)<0)
	{
		fprintf(stderr, "initial logger system failure\n");
		dbg_print("initial logger system failure\n");
		return -2;
	}
	
	set_socket_rlimit(); /* set max open socket count */
	
	signal(SIGINT, stop);
	signal(SIGTERM, stop);	

	if( (listenfd=socket_server_init(NULL, serv_port)) < 0 )
	{
		printf("ERROR: %s server listen on port %d failure\n", argv[0],serv_port);
		return -3;
	}
	printf("%s server start to listen on port %d\n", argv[0],serv_port);

	/* set program running on background */
	if( daemon_run )
	{
		daemon(0, 0);
	}

	Create_Database(&db);

	if( (epollfd=epoll_create(MAX_EVENTS)) < 0 )
	{
		printf("epoll_create() failure: %s\n", strerror(errno));
		return -3;
	}

	//event.events = EPOLLIN|EPOLLET;
	event.events = EPOLLIN;
	event.data.fd = listenfd;
	if( epoll_ctl(epollfd, EPOLL_CTL_ADD, listenfd, &event) < 0)
	{
		printf("epoll add listen socket failure: %s\n", strerror(errno));
		return -4;
	}
	while(!pro_stop)
	{
		/* program will blocked here */
		events = epoll_wait(epollfd, event_array, MAX_EVENTS, -1);
		if(events < 0)
		{
			printf("epoll failure: %s\n", strerror(errno));
			break;
		}
		else if(events == 0)
		{
			printf("epoll get timeout\n");
			continue;
		}
	
		/* rv>0 is the active events count */
		for(i=0; i<events; i++)
		{
			if ( (event_array[i].events&EPOLLERR) || (event_array[i].events&EPOLLHUP) )
			{
				printf("epoll_wait get error on fd[%d]: %s\n", event_array[i].data.fd, strerror(errno));
				epoll_ctl(epollfd, EPOLL_CTL_DEL, event_array[i].data.fd, NULL);
				close(event_array[i].data.fd);
			}
		
			/* listen socket get event means new client start connect now */
			if( event_array[i].data.fd == listenfd )
			{
				if( (connfd=accept(listenfd, (struct sockaddr *)NULL, NULL)) < 0)
				{
					printf("accept new client failure: %s\n", strerror(errno));
					continue;
				}
				event.data.fd = connfd;
		
				//event.events = EPOLLIN|EPOLLET;
				event.events = EPOLLIN;
				if( epoll_ctl(epollfd, EPOLL_CTL_ADD, connfd, &event) < 0 )
				{
					printf("epoll add client socket failure: %s\n", strerror(errno));
					close(event_array[i].data.fd);
					continue;
				}
				printf("epoll add new client socket[%d] ok.\n", connfd);
			}
			else /* already connected client socket get data incoming */
			{
				memset(buf, 0, sizeof(buf));
				if( (rv=read(event_array[i].data.fd, buf, sizeof(buf))) <= 0)
				{
					printf("socket[%d] read failure or get disconncet and will be removed.\n",
							event_array[i].data.fd);
					epoll_ctl(epollfd, EPOLL_CTL_DEL, event_array[i].data.fd, NULL);
					close(event_array[i].data.fd);
					continue;
				}
				else
				{
					printf("socket[%d] read get %d bytes data\n", event_array[i].data.fd, rv);
					
					SN = strtok(buf, "/");
					log_info("SN: %s", SN);
					datime = strtok(NULL, "/");
					log_info("datime: %s", datime);
					temp = atof(strtok(NULL, "\n"));
					log_info("temp: %f", temp);

					Create_Table(db, SN);
					Insert_Table(db, SN, datime, temp);
				}
			}
		} /* for(i=0; i<rv; i++) */
	} /* while(1) */
CleanUp:
	close(listenfd);
	return 0;
}

void stop(int signum)
{
    pro_stop = 1;
}

