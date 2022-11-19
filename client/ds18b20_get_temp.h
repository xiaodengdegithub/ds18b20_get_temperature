/********************************************************************************
 *      Copyright:  (C) 2022 Deng Yonghao<dengyonghao2001@163.com>
 *                  All rights reserved.
 *
 *       Filename:  ds18b20_get_temp.h
 *    Description:  This file ds18b20_get_temp.h
 *
 *        Version:  1.0.0(2022年11月17日)
 *         Author:  Deng Yonghao <dengyonghao2001@163.com>
 *      ChangeLog:  1, Release initial version on "2022年11月17日 21时47分24秒"
 *                 
 ********************************************************************************/

#include<stdio.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<dirent.h>
#include<fcntl.h>
#include<unistd.h>
#include<string.h>
#include<stdlib.h>
#include<errno.h>

#define CONFIG_DEBUG
#ifdef  CONFIG_DEBUG
#define dbg_print(format,args...) printf(format, ##args)
#else      /* -----  not CONFIG_DEBUG  ----- */
#define dbg_print(format,args...) do{} while(0)
#endif     /* -----  not CONFIG_DEBUG  ----- */


int get_temperature(float *temp);
