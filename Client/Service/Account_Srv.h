/*************************************************************************
	>    File Name: Account_Srv.h
	>       Author: lun
	> Created Time: 2024年06月12日
 ************************************************************************/

#ifndef _ACCOUNT_SRV_H
#define _ACCOUNT_SRV_H
#include "../Common/cJSON.h"
#include "Connect.h"

void Account_Srv_RecvIsOnline(char *JSON);

/*
 * 注销登录
 */
int Account_Srv_Out(int uid);

int Account_Srv_SignIn(const char *name , int sex ,const char *password);

int Account_Srv_Login(const char *name , const char *password);

#endif
