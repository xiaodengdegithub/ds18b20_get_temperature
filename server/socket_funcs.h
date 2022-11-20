/********************************************************************************
 *      Copyright:  (C) 2022 Deng Yonghao<dengyonghao2001@163.com>
 *                  All rights reserved.
 *
 *       Filename:  socket_funcs.h
 *    Description:  This file socket_funcs.h
 *
 *        Version:  1.0.0(2022年11月20日)
 *         Author:  Deng Yonghao <dengyonghao2001@163.com>
 *      ChangeLog:  1, Release initial version on "2022年11月20日 21时51分42秒"
 *                 
 ********************************************************************************/

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/types.h>          /* See NOTES */
#include <sys/socket.h>
#include <sys/resource.h>
#include <errno.h>

#define CONFIG_DEBUG
#ifdef  CONFIG_DEBUG
#define dbg_print(format,args...) printf(format, ##args)
#else      /* -----  not CONFIG_DEBUG  ----- */
#define dbg_print(format,args...) do{} while(0)
#endif     /* -----  not CONFIG_DEBUG  ----- */

int socket_server_init(char *listen_ip, int listen_port);
void set_socket_rlimit(void);
