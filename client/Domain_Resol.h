/********************************************************************************
 *      Copyright:  (C) 2022 Deng Yonghao<dengyonghao2001@163.com>
 *                  All rights reserved.
 *
 *       Filename:  Domain_Resol.h
 *    Description:  This file Domain_Resol.h
 *
 *        Version:  1.0.0(2022年11月19日)
 *         Author:  Deng Yonghao <dengyonghao2001@163.com>
 *      ChangeLog:  1, Release initial version on "2022年11月19日 16时38分25秒"
 *                 
 ********************************************************************************/

#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
//#include <netinet/in.h>	// 提供struct in_addr
#include <arpa/inet.h>	// 提供inet_ntoa()

int domain_getaddrinfo(char **servdn);
