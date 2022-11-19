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
	printf("%s usage: \n", progname);
	printf("-i(--ipaddr): sepcify server IP address.\n");
	printf("-d(--domain name): sepcify server domain name.\n");
	printf("-p(--port): sepcify server port.\n");
	printf("-h(--Help): print this help information.\n");

	return ;
}
