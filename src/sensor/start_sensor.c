/*
 * main.c
 *
 *  Created on: 2016年8月3日
 *      Author: root
 */

#include "my_include.h"

#include "dev_opt.h"
#include "elevator_module.h"
#include "../common/udp_opt.h"

HB_VOID *start_sensor(HB_VOID *arg)
{
	pthread_detach(pthread_self());
	pthread_attr_t attr;

	while (1)
	{
		if (OpenDev() < 0)
		{
			sleep(3);
		}
		else
		{
			break;
		}
	}

	InitSensorGlobleVar();
	elevator_data_list_init();
	set_header();

#if 1
	pthread_t scanning_pthread_id;
	pthread_attr_init(&attr);
	pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);
	pthread_create(&scanning_pthread_id, &attr, scanning_task, NULL);
	pthread_attr_destroy(&attr);
#endif
#if 1
	//传感器数据接收线程
	pthread_t sdata_recv_pthread_id;
	pthread_attr_init(&attr);
	pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);
	pthread_create(&sdata_recv_pthread_id, &attr, elevator_recv_data_task, NULL);
	pthread_attr_destroy(&attr);
#endif

#if 1
	//传感器数据发送线程
	pthread_t sdata_send_pthread_id;
	pthread_attr_init(&attr);
	pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);
	pthread_create(&sdata_send_pthread_id, &attr, elevator_send_data_task, NULL);
	pthread_attr_destroy(&attr);
#endif

	while(1)
	{
		sleep(60);
	}

	CloseDev();

	pthread_exit(NULL);
}


