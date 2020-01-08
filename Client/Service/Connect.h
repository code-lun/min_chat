/*************************************************************************
	>    File Name: Connect.h
	>       Author: lun
	> Created Time: 2024年06月12日
 ************************************************************************/

#ifndef _CONNECT_H
#define _CONNECT_H
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <linux/socket.h>
#include <arpa/inet.h>
#include "../Common/Common.h"


/*
 * 创建并保持socket连接
 */
void Connect(const char *host ,int port);


#endif
