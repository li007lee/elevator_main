/*
 * elevator_module.c
 *
 *  Created on: 2016年8月2日
 *      Author: root
 */

#include "elevator_module.h"

#include "my_include.h"
#include "sensor_opt.h"
#include "../common/tcp_opt.h"
#include "../common/udp_opt.h"

HB_VOID *create_sensor_data_node()
{
	SONSER_DATA_NODE_HANDLE p_node = (SONSER_DATA_NODE_HANDLE)malloc(sizeof(SONSER_DATA_NODE_OBJ));
	if (NULL == p_node)
	{
		return NULL;
	}

	p_node->msg_buf = NULL;
	p_node->buf_len = 0;

	return (HB_VOID*)p_node;
}

HB_VOID delete_sensor_data_node(HB_VOID *p_node)
{
	SONSER_DATA_NODE_HANDLE handle = (SONSER_DATA_NODE_HANDLE)p_node;

	if (NULL != handle->msg_buf)
	{
		free(handle->msg_buf);
		handle->msg_buf = NULL;
	}

	free(handle);
	handle = NULL;
	return;
}

////////////////////////////////////////////////////////////////////////////////
// 函数名：elevator_data_list_init
// 描述：电梯数据链表初始化
// 参数：
//  ［IN］
// 返回值：
//  	HB_FAILURE - 失败
//		HB_SUCCESS - 成功
// 说明：
////////////////////////////////////////////////////////////////////////////////
HB_S32 elevator_data_list_init()
{
	ele_data_list.plist = list_create();
	ele_data_list.plist->new_node = create_sensor_data_node;
	ele_data_list.plist->del_node = delete_sensor_data_node;
	ele_data_list.b_wait = HB_FALSE;
	//list_reset(ele_data_list.plist);
	//list_add_node_to_end(ele_data_list.plist);
	pthread_mutex_init(&ele_data_list.list_mutex, NULL);
	pthread_cond_init(&(ele_data_list.list_empty), NULL);
	return HB_SUCCESS;
}


HB_VOID *elevator_recv_data_task(HB_VOID *param)
{
	char sensor_data[512] = {0};
	struct timeval tv;
	unsigned long long time_now;
	while (1)
	{
		sensor_ctx.exit_flag = 0;

		if (0 != pthread_create(&sensor_ctx.accl_thread_id, NULL, ReadAcclData, NULL))
		{
			printf("Open thread for Accelerometer failed!\n");
			continue;
		}
		if (0 != pthread_create(&sensor_ctx.gyro_thread_id, NULL, ReadGyroData, NULL))
		{
			printf("Open thread for Gyro failed!\n");
			sensor_ctx.exit_flag = 1;
			pthread_join(sensor_ctx.accl_thread_id, NULL);
			continue;
		}

		while(!sensor_ctx.exit_flag)
		{
			sleep(dev_info.sample_frequency);//采集传感器数据的频率
			pthread_mutex_lock(&sensor_ctx.mutex_lock_data);
			gettimeofday(&tv,NULL);
			time_now = (unsigned long long)tv.tv_sec*1000 + tv.tv_usec/1000;//取毫秒值
			snprintf(sensor_data, sizeof(sensor_data), "%s|%llu|%ld|%ld|%ld|%ld|%ld|%ld|",
								dev_info.mac, time_now,
								sensor_ctx.accl_x, sensor_ctx.accl_y, \
								sensor_ctx.accl_z, sensor_ctx.gyro_x, \
								sensor_ctx.gyro_y, sensor_ctx.gyro_z);
			printf("recv_sensor_data:[%s]\n", sensor_data);
			pthread_mutex_unlock(&sensor_ctx.mutex_lock_data);

			char *send_msg = (char *)malloc(strlen(sensor_data) + 1);
			memset(send_msg, 0, strlen(sensor_data) + 1);
			strncpy(send_msg, sensor_data, strlen(sensor_data));
			//如果缓冲区已满，从头节点开始删除
			if (ele_data_list.plist->cnt >= MAX_SAVE_DATA)
			{
				printf("Too many data not send! Free from head!!\n");
				pthread_mutex_lock(&(ele_data_list.list_mutex));
				list_remove_head_node(ele_data_list.plist);
				pthread_mutex_unlock(&(ele_data_list.list_mutex));
			}

			SONSER_DATA_NODE_HANDLE sonser_data_node = NULL;
			pthread_mutex_lock(&(ele_data_list.list_mutex));
			sonser_data_node = (SONSER_DATA_NODE_HANDLE)list_add_node_to_end(ele_data_list.plist);
			sonser_data_node->msg_buf = send_msg;
			sonser_data_node->buf_len = strlen(send_msg) + 1;
			pthread_mutex_unlock(&(ele_data_list.list_mutex));

			if(HB_TRUE == ele_data_list.b_wait)
			{
				pthread_mutex_lock(&(ele_data_list.list_mutex));
				pthread_cond_signal(&(ele_data_list.list_empty));
				pthread_mutex_unlock(&(ele_data_list.list_mutex));
			}

		}

		pthread_join(sensor_ctx.accl_thread_id, NULL);
		pthread_join(sensor_ctx.gyro_thread_id, NULL);
	}

	pthread_exit(NULL);
}

#if 1
HB_VOID *elevator_send_data_task(HB_VOID *param)
{
	HB_S32 iRet = 0;
	HB_CHAR *send_msg = NULL;
	UDP_HEADER stSendHeader;
	UDP_SERVER_INFO stUdpInfo;
	HB_CHAR arrcServerIp[16] = {0};
	HB_CHAR arrcRecvBuf[RECV_BUF_LEN] = {0};

	memset(&stUdpInfo, 0, sizeof(stUdpInfo));

RETRY:
	iRet = from_domain_to_ip(arrcServerIp, UDP_SERVER_IP, 2);
	if (iRet < 0)
	{
		TRACE_ERR("analysis domain failed!\n");
		sleep(5);
		goto RETRY;
	}

#if 0
	char *msg = "{\"DataType\":\"accl\",\"MAC\":\"621c7e758524\",\"DataTime\":6398,\"X\":-0.067,\"Y\":0.303,\"Z\":0.000}";
	create_socket_and_set_server(&stSendHeader, UDP_SERVER_IP, UDP_SERVER_PORT);
	while(1)
	{
    	set_header(&stSendHeader, 9, 0);
    	iRet = send_udp_data(&stSendHeader, &stUdpInfo, msg, strlen(msg), 1);
    	printf("SSSSSSSSSSSSSSSSSSSSSSSSend::::::::::sockfd=[%d], msg=[%s], head_size=[%d], strlen=[%d], sendlen=[%d]\n",\
    					stUdpInfo.iSockFd, msg, strlen(msg), iRet);
    	if(-1 == iRet)//发送数据失败
    	{
    		printf("send failed , continue!\n");
    		sleep(10);
    		continue;
    	}

		iRet = recv_udp_data(&stUdpInfo, arrcRecvBuf, sizeof(arrcRecvBuf), 2);
		printf("RRRRRRRRRRRRRRRRRRRRRRRRecv::::::::::recv[%d]:[%s]\n", iRet, arrcRecvBuf);

    	sleep(10);
	}
#else
	create_socket_and_set_server(&stUdpInfo, arrcServerIp, UDP_SERVER_PORT);
    while(1)
    {
    	while(ele_data_list.plist->cnt < 1)
    	{
    		pthread_mutex_lock(&(ele_data_list.list_mutex));
    		ele_data_list.b_wait = HB_TRUE;
    		pthread_cond_wait(&(ele_data_list.list_empty),&(ele_data_list.list_mutex));
    		ele_data_list.b_wait = HB_FALSE;
    		pthread_mutex_unlock(&(ele_data_list.list_mutex));
    	}
    	send_msg = ((SONSER_DATA_NODE_HANDLE)(ele_data_list.plist->p_head->p_value))->msg_buf;
    	set_header(&stSendHeader, 9);
    	iRet = send_udp_data(&stSendHeader, &stUdpInfo, send_msg, strlen(send_msg), 1);
    	printf("Send::::sockfd=[%d], msg=[%s], strlen=[%d], sendlen=[%d]\n",\
    					stUdpInfo.iSockFd, send_msg, strlen(send_msg), iRet);
    	if(-1 == iRet)//发送数据失败
    	{
    		sleep(2);
    		close_udp(&stUdpInfo);
    		create_socket_and_set_server(&stUdpInfo, arrcServerIp, UDP_SERVER_PORT);
    		continue;
    	}
    	else
    	{
    		//printf("\n>>>>>>>>># [%s]\n", send_msg);
    		memset(arrcRecvBuf, 0, sizeof(arrcRecvBuf));
    		iRet = recv_udp_data(&stUdpInfo, arrcRecvBuf, sizeof(arrcRecvBuf), 2);
    		if (iRet < 0)
    		{
    			printf("Recv::::recv[%d]:[%s]\n", iRet, arrcRecvBuf);
        		close_udp(&stUdpInfo);
        		create_socket_and_set_server(&stUdpInfo, arrcServerIp, UDP_SERVER_PORT);
    		}
    		else
    		{
				printf("Recv::::recv[%d]:[%s]\n", iRet, arrcRecvBuf);
				pthread_mutex_lock(&(ele_data_list.list_mutex));
				list_remove_head_node(ele_data_list.plist);
				pthread_mutex_unlock(&(ele_data_list.list_mutex));
    		}
    	}
    }
#endif
    printf("##################################Send thread exit!\n");
	return NULL;
}
#endif

HB_VOID *scanning_task(HB_VOID *param)
{
	while(1)
	{
		sleep(1);
		printf("\n#################  node num = [%d]\n",ele_data_list.plist->cnt);
		//debug_err_print("#################  node num = [%d]",ele_data_list.plist->cnt);
	}
}
