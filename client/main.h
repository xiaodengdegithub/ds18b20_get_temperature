/********************************************************************************
 *      Copyright:  (C) 2022 Deng Yonghao<dengyonghao2001@163.com>
 *                  All rights reserved.
 *
 *       Filename:  main.h
 *    Description:  This file is main.h
 *
 *        Version:  1.0.0(2022年11月18日)
 *         Author:  Deng Yonghao <dengyonghao2001@163.com>
 *      ChangeLog:  1, Release initial version on "2022年11月18日 20时11分15秒"
 *                 
 ********************************************************************************/

#include <stdio.h>//定义输入／输出函数。
#include <errno.h>//定义错误码。
#include <string.h>//字符串处理。
#include <unistd.h>//是POSIX标准定义的unix类系统定义符号常量的头文件read(),write()等系统调用函数。
#include <dirent.h>//dirent.h是用于目录操作的头文件opendir()打开目录，并返回句柄;readdir()读取句柄，返回dirent结构体;telldir()返回当前指针的位置，表示第几个元素;close()关闭句柄等。
#include <fcntl.h>//文件的打开、数据写入、数据读取、关闭文件,如open()，close()等。
#include <sys/types.h>//是Unix/Linux系统的基本系统数据类型的头文件，含有size_t，time_t，pid_t等类型。
#include <sys/socket.h>//Socket相关函数
#include <arpa/inet.h>//在linux下网络编程程中常用头文件，主要是信息转换，将客户端信息，转换为字符串信息。
#include <stdlib.h>//包含了C语言的一些常用库函数。如动态内存相关的malloc, realloc,zalloc,calloc,free等。随机数相关的rand,srand等。系统相关的system, getenv,setenv等。
#include <getopt.h>//getopt()原型是int getopt( int argc, char *const argv[], const char *optstring ); 调用一次，返回一个选项。 在命令行选项参数再也检查不到optstring中包含的选项时，返回－1，同时optind储存第一个不包含选项的命令行参数。
#include <netdb.h>//包含域名解析中的getaddrinfo()函数和gethostbyname()


#include "ds18b20_get_temp.h"
#include "functions.h"

int pro_stop=0;
