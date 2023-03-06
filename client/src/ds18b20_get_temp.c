/*********************************************************************************
 *      Copyright:  (C) 2022 Deng Yonghao<dengyonghao2001@163.com>
 *                  All rights reserved.
 *
 *       Filename:  ds18b20_get_temp.c
 *    Description:  This file ds18b20_get_temp.c
 *                 
 *        Version:  1.0.0(2022年11月16日)
 *         Author:  Deng Yonghao <dengyonghao2001@163.com>
 *      ChangeLog:  1, Release initial version on "2022年11月16日 15时43分49秒"
 *                 
 ********************************************************************************/

#include "ds18b20_get_temp.h"

int get_temperature(float *temp)
{
	int				fd = -1;
	char			buf[128];
	char			*ptr =NULL;
	DIR				*dirp = NULL;
	struct dirent	*direntp = NULL;
	char			w1_path[64]="/sys/bus/w1/devices/";
	char			chip_sn[32];
	int				found = 0;

	dirp=opendir(w1_path);
	if( !dirp )
	{
		//dbg_print("open floder %s failure: %s\n", w1_path, strerror(errno));
		log_error("open floder %s failure: %s\n", w1_path, strerror(errno));
		return -1;
	}

	while( NULL != (direntp=readdir(dirp)) )
	{
		if( strstr(direntp->d_name, "28-"))
		{
			strncpy(chip_sn, direntp->d_name, sizeof(chip_sn));
			found = 1;
		}
	}

	closedir(dirp);

	if( !found )
	{
		log_error("Can not find ds18b20 chipset\n");
		return -2;
	}

	strncat(w1_path, chip_sn, sizeof(w1_path)-strlen(w1_path));
	strncat(w1_path, "/w1_slave", sizeof(w1_path)-strlen(w1_path));

	if( (fd=open(w1_path, O_RDONLY)) < 0)
	{
		log_error("open file failure: %s\n", strerror(errno));
		perror("open file failure\n");
		return -3;
	}

	memset(buf, 0, sizeof(buf));

	if(read(fd, buf, sizeof(buf)) < 0)
	{
		log_error("read data from fd=%d failure %s\n", fd, strerror(errno));
		return -4;
	}
	ptr=strstr(buf, "t=");
	if( !ptr )
	{
		log_error("Can not find t= string\n");
		return -5;
	}

	ptr += 2;

	*temp = atof(ptr)/1000;
	log_info("temperature: %f\n", *temp);

	close(fd);

	return 0;
}
