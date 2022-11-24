/*********************************************************************************
 *      Copyright:  (C) 2022 Deng Yonghao<dengyonghao2001@163.com>
 *                  All rights reserved.
 *
 *       Filename:  functions.c
 *    Description:  This file functions.c
 *                 
 *        Version:  1.0.0(2022年11月23日)
 *         Author:  Deng Yonghao <dengyonghao2001@163.com>
 *      ChangeLog:  1, Release initial version on "2022年11月23日 10时34分15秒"
 *                 
 ********************************************************************************/

#include "functions.h"

static inline void print_usage(char *progname)
{
    log_warn("Usage: %s [OPTION]...\n", progname);

    log_warn(" %s is a socket server program, which used to verify client and echo back string from it\n",
            progname);
    log_warn("\nMandatory arguments to long options are mandatory for short options too:\n");

    log_warn(" -p[port ] Socket server port address\n");
    log_warn(" -b[daemon ] set program running on background\n");
    log_warn(" -h[help ] Display this help information\n");

    log_warn("\nExample: %s -p 8900 -b\n", progname);
    return ;
}

