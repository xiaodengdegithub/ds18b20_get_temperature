/********************************************************************************
 *      Copyright:  (C) 2022 Deng Yonghao<dengyonghao2001@163.com>
 *                  All rights reserved.
 *
 *       Filename:  logger.h
 *    Description:  This file logger.h
 *
 *        Version:  1.0.0(2022年11月22日)
 *         Author:  Deng Yonghao <dengyonghao2001@163.com>
 *      ChangeLog:  1, Release initial version on "2022年11月22日 19时58分13秒"
 *                 
 ********************************************************************************/

#ifndef  _LOGGER_H_
#define  _LOGGER_H_

/*
 * logger level
 */
enum
{
    LOG_LEVEL_ERROR,
    LOG_LEVEL_WARN,
    LOG_LEVEL_INFO,
    LOG_LEVEL_DEBUG,
    LOG_LEVEL_MAX,
};

/*
 * logger prefix string for different logging levels
 */
#define LOG_STRING_ERROR  "ERROR"
#define LOG_STRING_WARN   "WARN "
#define LOG_STRING_INFO   "INFO "
#define LOG_STRING_DEBUG  "DEBUG"


/*
 * logger initial and terminate functions
 */
int logger_init(char *filename, int loglevel);
void logger_term(void);

/*
 * logging methods by levels
 */
void log_error(char* format, ...);
void log_warn(char* format, ...);
void log_info(char* format, ...);
void log_debug(char* format, ...);

static void check_and_rollback(void);

#endif   /* ----- #ifndef _LOGGER_H_  ----- */


