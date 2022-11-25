/********************************************************************************
 *      Copyright:  (C) 2022 Deng Yonghao<dengyonghao2001@163.com>
 *                  All rights reserved.
 *
 *       Filename:  functions.h
 *    Description:  This file functions.h
 *
 *        Version:  1.0.0(2022年11月23日)
 *         Author:  Deng Yonghao <dengyonghao2001@163.com>
 *      ChangeLog:  1, Release initial version on "2022年11月23日 10时25分44秒"
 *                 
 ********************************************************************************/

#ifndef _FUNCTIONS_H_
#define _FUNCTIONS_H_

#include <stdio.h>
#include <time.h>
#include <stdlib.h>

#include "logger.h"

#define CONFIG_DEBUG
#ifdef  CONFIG_DEBUG
#define dbg_print(format,args...) printf(format, ##args)
#else      /* -----  not CONFIG_DEBUG  ----- */
#define dbg_print(format,args...) do{} while(0)
#endif     /* -----  not CONFIG_DEBUG  ----- */

void print_usage(char *progname);

#endif
