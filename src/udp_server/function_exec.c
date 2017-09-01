/*
 * function_exec.c
 *
 *  Created on: 2017年7月11日
 *      Author: root
 */

#include "function_exec.h"
#include "../common/file_opt.h"
#include "../common/cJSON.h"
#include "../common/common.h"
#include "md5gen.h"
#include "../common/tcp_opt.h"
#include "../upload_pic.h"
#include "../common/udp_opt.h"

extern LOCAL_UDP_SERVER_INFO stUdpServerInfo;

/****************************************
 * Function: 获取电梯相关参数（电梯编号，SIM卡号，安装位置）
 * @param pUdpClient: [IN]UDP客户端的信息结构体
 * @param pSaveKey: [IN] 存储在本地文件的key信息（elevator_code，elevator_sim，elevator_addr）
 *
 * @return : 成功返回0
 ****************************************/
void get_elevator_config(UDP_CLIENT_INFO_HANDLE pUdpClient, HB_CHAR *pSaveKey)
{
	HB_CHAR arrcReturnJson[SEND_BUF_LEN] = {0};

//	GetIniKeyString(NULL, pSaveKey, arrcElevatorValue, ELEVATOR_CONFIG);

	if (strcmp(pSaveKey, "elevator_code") == 0)
	{
		snprintf(arrcReturnJson, sizeof(arrcReturnJson), "{\"code\":\"0\",\"msg\":\"获取成功\",\"elevator_id\":\"%s\"}", elevator_properties.elevator_id);
	}
	else if (strcmp(pSaveKey, "elevator_sim") == 0)
	{
		snprintf(arrcReturnJson, sizeof(arrcReturnJson), "{\"code\":\"0\",\"msg\":\"获取成功\",\"sim_card\":\"%s\"}", elevator_properties.elevator_sim);
	}
	else if (strcmp(pSaveKey, "elevator_addr") == 0)
	{
		snprintf(arrcReturnJson, sizeof(arrcReturnJson), "{\"code\":\"0\",\"msg\":\"获取成功\",\"address\":\"%s\"}", elevator_properties.elevator_addr);
	}
	server_send_udp_data(&stUdpServerInfo, pUdpClient, arrcReturnJson, strlen(arrcReturnJson), 0);
}


/****************************************
 * Function: 设置电梯相关参数（电梯编号，SIM卡号，安装位置）
 * @param pUdpClient: [IN]UDP客户端的信息结构体
 * @param pKey: [IN]需要设置的类型选项（elevator_id，elevator_sim，address）
 *
 * @return : 成功返回0,失败返回-1
 ****************************************/
int set_elevator_config(UDP_CLIENT_INFO_HANDLE pUdpClient, HB_CHAR *pKey)
{
	HB_CHAR arrcElevatorValue[512] = {0};
	HB_CHAR arrcReturnJson[SEND_BUF_LEN] = {0};

	analysis_json(pUdpClient->arrcRecvBuf, pKey, arrcElevatorValue, sizeof(arrcElevatorValue));
	if (strlen(arrcElevatorValue) == 0)
	{
		strncpy(arrcReturnJson, "{\"code\":\"-30001\",\"msg\":\"该配置不能为空\"}", sizeof(arrcReturnJson));
		server_send_udp_data(&stUdpServerInfo, pUdpClient, arrcReturnJson, strlen(arrcReturnJson), 0);
		return -1;
	}

	if (strcmp("elevator_id", pKey) == 0)
	{
		strncpy(elevator_properties.elevator_id, arrcElevatorValue, sizeof(elevator_properties.elevator_id));
		printf("elevator_id:[%s]\n", elevator_properties.elevator_id);
	}
	else if (strcmp("sim_card", pKey) == 0)
	{
		strncpy(elevator_properties.elevator_sim, arrcElevatorValue, sizeof(elevator_properties.elevator_sim));
		printf("elevator_sim:[%s]\n", elevator_properties.elevator_sim);
	}
	else if (strcmp("address", pKey) == 0)
	{
		strncpy(elevator_properties.elevator_addr, arrcElevatorValue, sizeof(elevator_properties.elevator_addr));
		printf("elevator_addr:[%s]\n", elevator_properties.elevator_addr);
	}
//
//	//此处存储电梯配置
//	if (SetConfigKeyValue(NULL, pSaveKey, ELEVATOR_CONFIG, arrcElevatorValue) < 0)
//	{
//		strncpy(arrcReturnJson, "{\"code\":\"-30002\",\"msg\":\"配置写入失败\"}", sizeof(arrcReturnJson));
//		server_send_udp_data(&stUdpServerInfo, pUdpClient, arrcReturnJson, strlen(arrcReturnJson), 0);
//		return -1;
//	}

	if (strcmp(pKey, "elevator_id") == 0)
	{
		//设置了电梯编号，需要重新获取令牌
		pthread_attr_t attr;
		pthread_t get_token_pthread_id;
		pthread_attr_init(&attr);
		pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);
		pthread_create(&get_token_pthread_id, &attr, elevator_get_token, NULL);
		pthread_attr_destroy(&attr);
		usleep(200*1000);
	}

	//成功返回
	snprintf(arrcReturnJson, sizeof(arrcReturnJson), "{\"code\":\"0\",\"msg\":\"配置成功\"}");
	server_send_udp_data(&stUdpServerInfo, pUdpClient, arrcReturnJson, strlen(arrcReturnJson), 0);
	return 0;
}


/****************************************
 * Function: 设置电梯相关参数（电梯编号，SIM卡号，安装位置）
 * @param pUdpClient: [IN]UDP客户端的信息结构体
 *
 * @return : 成功返回0,失败返回-1
 ****************************************/
int get_net_status(UDP_CLIENT_INFO_HANDLE pUdpClient)
{
	FILE *fp;
	HB_CHAR tmp[256] = {0};
	HB_CHAR arrcReturnJson[128] = {0};

	fp = popen("ifconfig ppp0 | grep \"Link\"", "r");
//	fp = popen("ifconfig eth0 | grep \"Link\"", "r");
	fgets(tmp, sizeof(tmp), fp);
	pclose(fp);
	TRACE_LOG("\n######  mac: [%s]\n", tmp);
	if (strlen(tmp)>0 && strstr(tmp, "Link encap:"))
	{
#if 0
		//4G 已经启动，测试网络
		memset(tmp, 0, sizeof(tmp));
//		fp = popen("ping -I ppp0 www.baidu.com -c 1 -w 2", "r");
		fp = popen("ping -c 1 -I eth0 www.baidu.com", "r");
		while(fgets(tmp, 256, fp) != NULL)
		{
			if(strstr(tmp, "ttl=") != NULL)//网络正常
			{
				printf("\n#############  net alive!\n");
				pclose(fp);

				snprintf(arrcReturnJson, sizeof(arrcReturnJson), "{\"code\":\"0\",\"msg\":\"网络已启动\"}");
				send_udp_data(&stUdpServerInfo, pUdpClient, arrcReturnJson, strlen(arrcReturnJson), 0);
				return 0;
			}
			memset(tmp, 0, sizeof(tmp));
		}
		pclose(fp);
		snprintf(arrcReturnJson, sizeof(arrcReturnJson), "{\"code\":\"-30003\",\"msg\":\"连接广域网失败\"}");
		send_udp_data(&stUdpServerInfo, pUdpClient, arrcReturnJson, strlen(arrcReturnJson), 0);
#endif
		snprintf(arrcReturnJson, sizeof(arrcReturnJson), "{\"code\":\"0\",\"msg\":\"网络已启动\"}");
		server_send_udp_data(&stUdpServerInfo, pUdpClient, arrcReturnJson, strlen(arrcReturnJson), 0);
	}
	else
	{
		snprintf(arrcReturnJson, sizeof(arrcReturnJson), "{\"code\":\"-30004\",\"msg\":\"4G启动失败\"}");
		server_send_udp_data(&stUdpServerInfo, pUdpClient, arrcReturnJson, strlen(arrcReturnJson), 0);
		return -1;
	}

	return -1;
}



void get_program_status(UDP_CLIENT_INFO_HANDLE pUdpClient)
{
	FILE *fp = NULL;
	int start_flag = 0;
	int elevator_main_start_flag = 0;
	int alarm_in_start_flag = 0;
	char tmp[128] = {0};
	char arrcReturnJson[128] = {0};

//	if((fp = popen("ps | grep elevator_main300 | grep -v grep | wc -l","r")) != NULL)
//	{
//		if( (fgets(tmp, sizeof(tmp), fp)) != NULL )
//		{
//			pclose(fp);
//			start_flag = atoi(tmp);
//			if(start_flag > 0)
//			{
				elevator_main_start_flag = 1;
//			}
//		}
//	}

	start_flag = 0;
	memset(tmp, 0, sizeof(tmp));
	if((fp = popen("ps | grep alarm_in | grep -v grep | wc -l","r")) != NULL)
	{
		if( (fgets(tmp, sizeof(tmp), fp)) != NULL )
		{
			pclose(fp);
			start_flag = atoi(tmp);
			if(start_flag > 0)
			{
				alarm_in_start_flag = 1;
			}
		}
	}

	snprintf(arrcReturnJson, sizeof(arrcReturnJson), \
			"{\"code\":\"0\",\"msg\":\"获取成功\",\"datas\":{\"elevator_main\":\"%d\",\"alarm_in\":\"%d\"}}", \
			elevator_main_start_flag, alarm_in_start_flag);
	server_send_udp_data(&stUdpServerInfo, pUdpClient, arrcReturnJson, strlen(arrcReturnJson), 0);
}


static int send_photo(UDP_CLIENT_INFO_HANDLE pUdpClient, HB_CHAR *pSendBuf, int iSendBufLen)
{
	HB_S32 iSockFd = -1;
	HB_S32 iRet = -1;
	struct sockaddr_in server_addr;
	int trueflag = 1;
    struct timeval wait_time;
	fd_set  writeset;
	int len = 0;
	int send_len = 0;

	iSockFd = socket(AF_INET, SOCK_STREAM, 0);
    setsockopt(iSockFd, SOL_SOCKET, SO_REUSEADDR, (void *)&trueflag, sizeof(trueflag));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = inet_addr(pUdpClient->arrcClientIp);
    server_addr.sin_port = htons(pUdpClient->iClientPort);
//    memset(server_addr.sin_zero, 0, 8);

    printf("Photo upload server:[%s]:[%d]\n", pUdpClient->arrcClientIp, pUdpClient->iClientPort);

    iRet = connect(iSockFd, (struct sockaddr *)&server_addr, sizeof(struct sockaddr_in));
    if (iRet != 0)
    {
    	sleep(1);
    	iRet = connect(iSockFd, (struct sockaddr *)&server_addr, sizeof(struct sockaddr_in));
    	if (iRet != 0)
    	{
    		printf("connect to server failed! so send alarm file failed!\n");
    		return -1;
    	}
    }

	while (iSendBufLen > 0)
	{
		FD_ZERO(&writeset);
		FD_SET(iSockFd, &writeset);
		wait_time.tv_sec = 1;
		wait_time.tv_usec = 0;

		iRet = select(FD_SETSIZE, NULL, &writeset, NULL, &wait_time);
		if (iRet < 0)
		{
			TRACE_ERR("select err=%d(%s)\n", errno, strerror(errno));
			close(iSockFd);
			return -2;
		}
		else if (iRet == 0)
		{
			TRACE_LOG("select timeout\n");
			close(iSockFd);
			return -3;
		}
		if ((len = send(iSockFd, pSendBuf, iSendBufLen, 0)) <= 0)
		{
			if (errno == EINTR)
			{
				TRACE_ERR("send err=%d(%s), again\n", errno, strerror(errno));
				continue; /* just an interrupted system call */
			}
			else
			{
				TRACE_ERR("send err=%d(%s)\n", errno, strerror(errno));
				close(iSockFd);
				return -4;
			}
		}
		send_len += len;
		pSendBuf += len;
		iSendBufLen -= len;
	}

//    system(RM_ALARM_PHOTO);
	close(iSockFd);
	printf("send len = [%d]\n", send_len);
	return send_len;
}

//获取报警图片
void get_alarm_photo(UDP_CLIENT_INFO_HANDLE pUdpClient)
{
	FILE *fp = NULL;
	HB_S32 iFileLen = 0;
	HB_S32 iReadLen = 0;
	HB_CHAR *pFileBuf = NULL;
	HB_CHAR arrcPhotoUploadPort[8] = {0};
	HB_CHAR arrcMd5[33] = {0};
	HB_CHAR arrcReturnJson[256] = {0};

	analysis_json(pUdpClient->arrcRecvBuf, "upload_port", arrcPhotoUploadPort, sizeof(arrcPhotoUploadPort));
	pUdpClient->iClientPort = atoi(arrcPhotoUploadPort);

	if (access(ALARM_PHOTO_PATH, F_OK) != 0)//报警图片不存在
	{
		strncpy(arrcReturnJson, "{\"code\":\"-30008\",\"msg\":\"报警图片不存在\"}", sizeof(arrcReturnJson));
		server_send_udp_data(&stUdpServerInfo, pUdpClient, arrcReturnJson, strlen(arrcReturnJson), 2);
		return ;
	}

	fp = fopen(ALARM_PHOTO_PATH, "rb");
	if (fp == NULL)
	{
		strncpy(arrcReturnJson, "{\"code\":\"-30009\",\"msg\":\"报警图片打开失败\"}", sizeof(arrcReturnJson));
		server_send_udp_data(&stUdpServerInfo, pUdpClient, arrcReturnJson, strlen(arrcReturnJson), 2);
		return ;
	}
	fseek(fp,0,SEEK_END); //定位到文件末
	iFileLen = ftell(fp); //文件长度
	fseek(fp,0,SEEK_SET); //跳回文件头

	pFileBuf = (HB_CHAR *)malloc(iFileLen);
	memset(pFileBuf, 0, iFileLen);

	iReadLen = fread(pFileBuf, 1, iFileLen, fp);
	printf("file_size:[%d], read_file_len:[%d]\n", iFileLen, iReadLen);

	if (iReadLen != iFileLen)
	{
		strncpy(arrcReturnJson, "{\"code\":\"-30010\",\"msg\":\"报警图片读取失败\"}", sizeof(arrcReturnJson));
		server_send_udp_data(&stUdpServerInfo, pUdpClient, arrcReturnJson, strlen(arrcReturnJson), 2);
		fclose(fp);
		fp = NULL;
		return ;
	}
	fclose(fp);

	//生成MD5值
	md5_packages_string(arrcMd5, pFileBuf, iFileLen);
	snprintf(arrcReturnJson, sizeof(arrcReturnJson), \
			"{\"code\":\"0\",\"msg\":\"获取成功\",\"datas\":{\"file_size\":\"%d\",\"file_md5\":\"%s\"}}", \
			iFileLen, arrcMd5);
	server_send_udp_data(&stUdpServerInfo, pUdpClient, arrcReturnJson, strlen(arrcReturnJson), 2);

	//tcp连接客户端ip和端口，并发送图片
	send_photo(pUdpClient, pFileBuf, iFileLen);

	free(pFileBuf);
	pFileBuf = NULL;

}



//获取传感器数据上传信息
HB_S32 get_data_upload_info(UDP_CLIENT_INFO_HANDLE pUdpClient)
{
	HB_CHAR arrcReturnJson[256] = {0};

	//发送到手机端
	snprintf(arrcReturnJson, sizeof(arrcReturnJson), \
		"{\"code\":\"0\",\"msg\":\"获取成功\",\"datas\":{\"send_total\":\"%u\",\"send_success\":\"%u\",\"resend\":\"%u\",\"miss\":\"%u\",\"alarm_pic_upload\":\"%u\"}}", \
		sensor_info.send_sensor_data_total_cout, sensor_info.send_sensor_data_success_count, \
		sensor_info.send_sensor_data_resend_count, sensor_info.send_sensor_data_miss_count, \
		sensor_info.alarm_pic_upload_count);
	server_send_udp_data(&stUdpServerInfo, pUdpClient, arrcReturnJson, strlen(arrcReturnJson), 2);

	return 0;
}


/****************************************
 * Function: 获取电梯相关参数（电梯编号，SIM卡号，安装位置）
 * @param pUdpClient: [IN]UDP客户端的信息结构体
 * @param pSaveKey: [IN] 存储在本地文件的key信息（elevator_code，elevator_sim，elevator_addr）
 *
 * @return : 成功返回0
 ****************************************/
void get_version(UDP_CLIENT_INFO_HANDLE pUdpClient)
{
	HB_CHAR	arrcElevatorType[64] = {0};
	HB_CHAR	arrcElevatorVersion[64] = {0};
	HB_CHAR arrcReturnJson[SEND_BUF_LEN] = {0};

	GetIniKeyString(NULL, "type", arrcElevatorType, ELEVATOR_VERSION_PATH);
	GetIniKeyString(NULL, "version", arrcElevatorVersion, ELEVATOR_VERSION_PATH);

//	printf("arrcElevatorVersion:[%s]\n", arrcElevatorVersion);

	snprintf(arrcReturnJson, sizeof(arrcReturnJson), \
				"{\"code\":\"0\",\"msg\":\"获取成功\",\"datas\":{\"elevator_type\":\"%s\",\"elevator_version\":\"%s\"}}", \
				arrcElevatorType, arrcElevatorVersion);

	server_send_udp_data(&stUdpServerInfo, pUdpClient, arrcReturnJson, strlen(arrcReturnJson), 0);
}
