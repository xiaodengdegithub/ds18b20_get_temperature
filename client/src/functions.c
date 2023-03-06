/*********************************************************************************
 *      Copyright:  (C) 2022 Deng Yonghao<dengyonghao2001@163.com>
 *                  All rights reserved.
 *
 *       Filename:  functions.c
 *    Description:  This file functions for main
 *                 
 *        Version:  1.0.0(2022年11月18日)
 *         Author:  Deng Yonghao <dengyonghao2001@163.com>
 *      ChangeLog:  1, Release initial version on "2022年11月18日 19时48分36秒"
 *                 
 ********************************************************************************/

#include "functions.h"

void print_usage(char *progname)
{
	log_warn("%s usage: \n", progname);
    log_warn("-i(--ipaddr): sepcify server IP address.\n");
    log_warn("-d(--domain name): sepcify server domain name.\n");
    log_warn("-p(--port): sepcify server port.\n");
	log_warn("-t(--time): sepcify time.\n");
    log_warn("-h(--Help): print this help information.\n");
	
	dbg_print("%s usage: \n", progname);
    dbg_print("-i(--ipaddr): sepcify server IP address.\n");
    dbg_print("-d(--domain name): sepcify server domain name.\n");
    dbg_print("-p(--port): sepcify server port.\n");
	dbg_print("-t(--time): sepcify time (default 10 seconds).\n");
    dbg_print("-h(--Help): print this help information.\n");

	return ;
}

int get_sn(char* SN,int len)  
{
    int sn=1;
    memset(SN,0,sizeof(SN));
    snprintf(SN,len,"dsdyh%04d",sn);
    return 0;
}

long get_time(char *datime,int len)       
{
	long                    times;
	time_t					nowsec;
	struct tm               *t;
	time(&nowsec);
	//gmtime(&t, &nowsec);
	t = localtime(&nowsec);
	
	memset(datime, 0, sizeof(datime));
	snprintf(datime, len,"%04d-%02d-%02d %02d:%02d:%02d", t->tm_year+1900, t->tm_mon+1, t->tm_mday, t->tm_hour, t->tm_min, t->tm_sec);
	
	times = time(NULL);
	log_info("times:%ld\n", times);

	return times;
}


