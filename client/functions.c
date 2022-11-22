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
	
	dbg_printf("%s usage: \n", progname);
    dbg_printf("-i(--ipaddr): sepcify server IP address.\n");
    dbg_printf("-d(--domain name): sepcify server domain name.\n");
    dbg_printf("-p(--port): sepcify server port.\n");
	dbg_printf("-t(--time): sepcify time.\n");
    dbg_printf("-h(--Help): print this help information.\n");

	return ;
}

int get_sn(char* SN,int len)  
{
    int sn=1;
    memset(SN,0,sizeof(SN));
    snprintf(SN,len,"dsdyh%04d",sn);
    return 0;
}
