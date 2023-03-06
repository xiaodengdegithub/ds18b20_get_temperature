/*********************************************************************************
 *      Copyright:  (C) 2022 Deng Yonghao<dengyonghao2001@163.com>
 *                  All rights reserved.
 *
 *       Filename:  clisql.c
 *    Description:  This file server sqlite.c
 *                 
 *        Version:  1.0.0(2022年11月22日)
 *         Author:  Deng Yonghao <dengyonghao2001@163.com>
 *      ChangeLog:  1, Release initial version on "2022年11月22日 11时23分55秒"
 *                 
 ********************************************************************************/

#include "clisql.h"

/*Creat Database*/
int Create_Database(sqlite3 **db)//如果仅仅是*db,main函数的db不会变，所以创建表时出错，改为**db
{
   char *zErrMsg = 0;
   int rc;

   rc = sqlite3_open("tempdata.db", db);

   if( rc != SQLITE_OK ){
      log_error("Can't open database\n");
      return -1;
   }else{
      log_info("Opened database successfully\n");
	  return 0;
   }
}

static int callback(void *NotUsed, int argc, char **argv, char **azColName)
{
   int i;
   for(i=0; i<argc; i++){
      log_info("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
   }
   return 0;
}

int Create_Table(sqlite3 *db)
{
	char			buf[256];
 	char			*zErrMsg = 0;

	memset(buf, 0, sizeof(buf));
	snprintf(buf, sizeof(buf), "CREATE TABLE %s (SN CHAR(20), DATIME CHAR(100), TEMPERATURE FLOAT);", TABLENAME);
	log_info("buf:%s\n", buf);

	if(SQLITE_OK != sqlite3_exec(db, buf, callback, 0, &zErrMsg))
	{
		log_error("create table error:%s\n", zErrMsg);
		sqlite3_free(zErrMsg);
		return -1;
	}
	else
	{
		log_info("creat table successfully\n");
		return 0;
	}
}

int Insert_Table(sqlite3 *db, char *SN, char *datime, float temp)
{
	char			buf[256];
	char 			*zErrMsg = 0;

	memset(buf, 0, sizeof(buf));
	snprintf(buf, sizeof(buf), "INSERT INTO %s(SN, DATIME, TEMPERATURE)VALUES('%s', '%s', '%f');", TABLENAME, SN, datime, temp);
	log_info("buf:%s\n", buf);

	if(SQLITE_OK != sqlite3_exec(db, buf, callback, 0, &zErrMsg))
    {
        log_error("insert table error:%s\n", zErrMsg);
        sqlite3_free(zErrMsg);
        return -1;
    }
    else
    {
        log_info("insert table successfully\n");
        return 0;
    }

}

int Table_check_write_clean(sqlite3 *db,int sockfd,char *SN)
{
	char			buf[256];
	char			*zErrMsg = 0;
	char			**dbResult;
	int				nRow = 0;
	int				nColumn = 0;
	int				rv;

	memset(buf, 0, sizeof(buf));
	snprintf(buf, sizeof(buf), "SELECT * FROM %s;", TABLENAME);

	rv = sqlite3_get_table(db, buf, &dbResult, &nRow, &nColumn, &zErrMsg);
	if(nRow<1)
	{
		log_warn("no more data\n");
		sqlite3_free(zErrMsg);
		sqlite3_free_table(dbResult);
		return 0;
	}
	
	if(SQLITE_OK != rv)
	{
		log_error("got data error\n");
		sqlite3_free(zErrMsg);
		sqlite3_free_table(dbResult);
		return -1;
	}

	memset(buf, 0, sizeof(buf));
	for(int i=1; i<=nRow; i++)
	{
		memset(buf, 0, sizeof(buf));
		snprintf(buf, sizeof(buf), "%s/%s/%f\n", dbResult[i*nColumn + 0], dbResult[i*nColumn + 1], atof(dbResult[i*nColumn + 2]) );
		
		rv = write(sockfd, buf, strlen(buf));
		if(rv < 0)
		{
			log_error("write to server by sockfd[%d] failure : %s\n",
					sockfd, strerror(errno));
			break;
		}
		else
		{
			log_info("write a row of client table to server[%d] successfully\n",
					sockfd);
		}
	}
	sqlite3_free_table(dbResult);

	memset(buf, 0, sizeof(buf));
	snprintf(buf, sizeof(buf), "DELETE  FROM %s;", TABLENAME);

	if(SQLITE_OK != sqlite3_exec(db, buf, callback, 0, &zErrMsg))
    {
        log_error("delete data error\n");
        sqlite3_free(zErrMsg);
        return -2;
    }

}
