/*
 * main.c
 *
 *  Created on: 2017年7月10日
 *      Author: root
 */

#include "my_include.h"
#include "server_udp_opt.h"
#include "../common/file_opt.h"
#include "function_exec.h"

LOCAL_UDP_SERVER_INFO stUdpServerInfo;

static void *deal_cmd_thread(void *arg)
{
	pthread_detach(pthread_self());
	UDP_CLIENT_INFO_HANDLE pUdpClient = (UDP_CLIENT_INFO_HANDLE)arg;
	HB_CHAR arrcCmd[128] = {0};

	printf("arrcRecvBuf:[%s]\n", pUdpClient->arrcRecvBuf);
	analysis_json(pUdpClient->arrcRecvBuf, "Command", arrcCmd, sizeof(arrcCmd));

	if (strcmp(arrcCmd, "get_elevator_code") == 0)//获取电梯编号
		get_elevator_config(pUdpClient, "elevator_code");
	else if (strcmp(arrcCmd, "set_elevator_code") == 0)//设置电梯编号
		set_elevator_config(pUdpClient, "elevator_id");
	else if (strcmp(arrcCmd, "get_elevator_sim") == 0) //获取SIM卡号
		get_elevator_config(pUdpClient, "elevator_sim");
	else if (strcmp(arrcCmd, "set_sim_card") == 0) //设置SIM卡号
		set_elevator_config(pUdpClient, "sim_card");
	else if (strcmp(arrcCmd, "get_elevator_address") == 0) //获取盒子安装位置
		get_elevator_config(pUdpClient, "elevator_addr");
	else if (strcmp(arrcCmd, "set_elevator_address") == 0) //设置盒子安装位置
		set_elevator_config(pUdpClient, "address");
	else if (strcmp(arrcCmd, "get_net_status") == 0)	//获取网络状态
		get_net_status(pUdpClient);
	else if (strcmp(arrcCmd, "get_program_status") == 0) //获取电梯程序运行状态
		get_program_status(pUdpClient);
	else if (strcmp(arrcCmd, "get_alarm_photo") == 0) //获取报警图片
		get_alarm_photo(pUdpClient);
	else if (strcmp(arrcCmd, "get_data_upload_info") == 0) //获取传感器数据上传信息
		get_data_upload_info(pUdpClient);
	else if (strcmp(arrcCmd, "get_version") == 0) //获取电梯型号及版本号信息
		get_version(pUdpClient);
	else if (strcmp(arrcCmd, "get_alarm_in_status") == 0) //获取报警输入信号状态
	{
		HB_CHAR arrcAlarmType[32] = {0};
		HB_CHAR arrcReturnJson[SEND_BUF_LEN] = {0};
		analysis_json(pUdpClient->arrcRecvBuf, "alarm_type", arrcAlarmType, sizeof(arrcAlarmType));

		if (strcmp(arrcAlarmType, "get_door_open_status") == 0)
		{
			//开门到位
			snprintf(arrcReturnJson, sizeof(arrcReturnJson), \
				"{\"code\":\"0\",\"msg\":\"获取成功\",\"status\":\"%d\"}", \
				sensor_info.door_opened_ok_flag);
		}
		else if (strcmp(arrcAlarmType, "get_door_close_status") == 0)
		{
			//关门到位
			snprintf(arrcReturnJson, sizeof(arrcReturnJson), \
				"{\"code\":\"0\",\"msg\":\"获取成功\",\"status\":\"%d\"}", \
				sensor_info.door_closed_ok_flag);
		}
		else if (strcmp(arrcAlarmType, "get_levelling_status") == 0)
		{
			//平层信号
			snprintf(arrcReturnJson, sizeof(arrcReturnJson), \
				"{\"code\":\"0\",\"msg\":\"获取成功\",\"status\":\"%d\"}", \
				sensor_info.levelling_ok_flag);
		}

		server_send_udp_data(&stUdpServerInfo, pUdpClient, arrcReturnJson, strlen(arrcReturnJson), 0);
	}
	else
	{
		HB_CHAR arrcReturnJson[64] = {0};
		strncpy(arrcReturnJson, "{\"code\":\"-30007\",\"msg\":\"Command有误\"}", sizeof(arrcReturnJson));
		server_send_udp_data(&stUdpServerInfo, pUdpClient, arrcReturnJson, strlen(arrcReturnJson), 0);
		printf("Command error!\n");
	}
	free(pUdpClient);
	pthread_exit(NULL);
}

void *thread_udp_server(void *arg)
{
//	pthread_detach(pthread_self());
	pthread_mutex_init(&(stUdpServerInfo.mutexLock), NULL);
	create_socket_and_set_server(&stUdpServerInfo, UDP_SERVER_LISTEN_PORT);
	while (1)
	{
		pthread_mutex_lock(&(stUdpServerInfo.mutexLock));
		pthread_t threadDealCmd =  -1;
		UDP_CLIENT_INFO_HANDLE pUdpClient = server_recv_udp_data(&stUdpServerInfo);
		if (pUdpClient != NULL)
		{
			pthread_create(&threadDealCmd, NULL, deal_cmd_thread, (void *)pUdpClient);
		}
		usleep(500*1000);
		pthread_mutex_unlock(&(stUdpServerInfo.mutexLock));
	}
	pthread_exit(NULL);
}








