/********************************************************************************
 *      Copyright:  (C) 2022 Deng Yonghao<dengyonghao2001@163.com>
 *                  All rights reserved.
 *
 *       Filename:  sersql.h
 *    Description:  This file server sqlite.h
 *
 *        Version:  1.0.0(2022年11月22日)
 *         Author:  Deng Yonghao <dengyonghao2001@163.com>
 *      ChangeLog:  1, Release initial version on "2022年11月22日 11时21分57秒"
 *                 
 ********************************************************************************/

#ifndef _SERSQL_H_
#define _SERSQL_H_

#include <sqlite3.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "logger.h"

#define CONFIG_DEBUG
#ifdef  CONFIG_DEBUG
#define dbg_print(format,args...) printf(format, ##args)
#else      /* -----  not CONFIG_DEBUG  ----- */
#define dbg_print(format,args...) do{} while(0)
#endif     /* -----  not CONFIG_DEBUG  ----- */

#define TABLENAME "server_table"

int Create_Database(sqlite3 **db);
static int callback(void *NotUsed, int argc, char **argv, char **azColName);
int Create_Table(sqlite3 *db);
int Insert_Table(sqlite3 *db, char *SN, char *datime, float temp);

#endif
