/*********************************************************************************
 *      Copyright:  (C) 2022 Deng Yonghao<dengyonghao2001@163.com>
 *                  All rights reserved.
 *
 *       Filename:  sersql.c
 *    Description:  This file server sqlite.c
 *                 
 *        Version:  1.0.0(2022年11月22日)
 *         Author:  Deng Yonghao <dengyonghao2001@163.com>
 *      ChangeLog:  1, Release initial version on "2022年11月22日 11时23分55秒"
 *                 
 ********************************************************************************/

#include "sersql.h"

/*Creat Database*/
int Creat_Database(sqlite3 *db)
{
   char *zErrMsg = 0;
   int rc;

   rc = sqlite3_open("tempdata.db", &db);

   if( rc ){
      log_error("Can't open database: %s\n", sqlite3_errmsg(db));
      return -1;
   }else{
      log_info("Opened database successfully\n");
	  return 0;
   }
}

static int callback(void *NotUsed, int argc, char **argv, char **azColName){
   int i;
   for(i=0; i<argc; i++){
      log_info("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
   }
   return 0;
}

int Creat_Table(sqlite3 *db, char SN)
{
	char			buf[256];
 	char			*zErrMsg = 0;

	memset(buf, 0, sizeof(buf));
	snprintf(buf, sizeof(buf), "CREATE TABLE %s(ID INTEGER PRIMARY KEY, SN CHAR(20), DATIME CHAR(100), TEMPERATURE CHAR(48));", SN);

	if(SQLITE_OK != sqlite3_exec(db, buf_table, callback, 0, &zErrMsg))
	{
		log_error("create table error:%s\n", zErrMsg);
		sqlite3_free(zErrMsg);
		return -2;
	}
	else
	{
		log_info("creat table successfully\n");
		return 0;
	}
}

int Insert_Table(sqlite3 *db, char SN)
{

}


