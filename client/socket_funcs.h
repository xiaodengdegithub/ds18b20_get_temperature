/********************************************************************************
 *      Copyright:  (C) 2022 Deng Yonghao<dengyonghao2001@163.com>
 *                  All rights reserved.
 *
 *       Filename:  socket_funcs.h
 *    Description:  This file socket_funcs.h 
 *
 *        Version:  1.0.0(2022年11月19日)
 *         Author:  Deng Yonghao <dengyonghao2001@163.com>
 *      ChangeLog:  1, Release initial version on "2022年11月19日 20时20分08秒"
 *                 
 ********************************************************************************/

#ifndef _SOCKET_FUNCS_H_
#define _SOCKET_FUNCS_H_

#include <stdio.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/types.h>          /* See NOTES */
#include <sys/socket.h>
#include <errno.h>

#define CONFIG_DEBUG
#ifdef  CONFIG_DEBUG
#define dbg_print(format,args...) printf(format, ##args)
#else      /* -----  not CONFIG_DEBUG  ----- */
#define dbg_print(format,args...) do{} while(0)
#endif     /* -----  not CONFIG_DEBUG  ----- */

int socket_and_connect(char *servip, int port);

#endif


