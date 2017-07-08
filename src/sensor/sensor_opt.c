/*
 * sensor_opt.c
 *
 *  Created on: 2017年4月12日
 *      Author: root
 */

#include "my_include.h"

#include "sensor_opt.h"
#include "dev_opt.h"
#include "elevator_module.h"

SENSOR_DEV_INFO sensor_ctx; //定义传感器

void *ReadGyroData(void * arg)
{
	int i;
	int retval;
	int rd_len;
	int sync = 0;
	fd_set rfds;
	float x=0.0, y=0.0, z=0.0;
	struct timeval tv;
	struct input_event ies[100];

	while (!sensor_ctx.exit_flag)
	{
		FD_ZERO(&rfds);
		FD_SET(sensor_ctx.gyro_ctx.dev_fd, &rfds);

		//两次SYN_REPORT之间为一组数据
		tv.tv_sec = 1;
		tv.tv_usec = 0; //500ms
		retval = select(sensor_ctx.gyro_ctx.dev_fd + 1, &rfds, NULL, NULL, &tv);
		if (retval == -1)
		{
			perror("select()");
			break;
		}
		else if (retval)
		{
			rd_len = read(sensor_ctx.gyro_ctx.dev_fd, ies, sizeof(ies));
			if (rd_len <= 0)
			{
				TRACE_ERR("read gyro event failed!\n");
				break;
			}

			for (i = 0; i < rd_len / sizeof(struct input_event); i++)
			{
				if (EV_SYN == ies[i].type && SYN_REPORT == ies[i].code)
				{
					if (!sync)
					{
						sync = 1;
					}
					else
					{
						//printf("gyro:%f|%f|%f\n", x, y, z);
						sensor_ctx.gyro_x = (long int)x;
						sensor_ctx.gyro_y = (long int)y;
						sensor_ctx.gyro_z = (long int)z;
						//读取陀螺仪数据成功，返回0
//						*gyro_x = (long int)x;
//						*gyro_y = (long int)y;
//						*gyro_z = (long int)z;
						sync = 0;
					}
				}
				if (EV_ABS == ies[i].type)
				{
					switch (ies[i].code)
					{
						case ABS_X:
//							x = ies[i].value * sensor_ctx.gyro_ctx.sensitivity / 1000;
							x = ies[i].value * sensor_ctx.gyro_ctx.sensitivity; //内核中此值放大了1000倍，使用时需除1000
							break;
						case ABS_Y:
//							y = ies[i].value * gyro_ctx.sensitivity / 1000;
							y = ies[i].value * sensor_ctx.gyro_ctx.sensitivity; //内核中此值放大了1000倍，使用时需除1000
							break;
						case ABS_Z:
//							z = ies[i].value * gyro_ctx.sensitivity / 1000;
							z = ies[i].value * sensor_ctx.gyro_ctx.sensitivity; //内核中此值放大了1000倍，使用时需除1000
							break;
						default:
							TRACE_ERR("Invalid e.code!\n");
							break;
					}
				}
			}
		}
		else
		{
			//timeout
			TRACE_ERR("select read gyro data timeout, return value=%d!\n", retval);
			break;
		}
	}

	printf("ReadGyroData task exit!\n");
	sensor_ctx.exit_flag = 1;

	pthread_exit(NULL);
}


//int ReadAcclData(long int *accl_x, long int *accl_y, long int *accl_z)
void *ReadAcclData(void * arg)
{
	//pthread_detach(pthread_self());
	int i;
	int retval;
	int rd_len;
	int sync = 0;
	fd_set rfds;
	float x=0.0, y=0.0, z=0.0;
	struct timeval tv;
	struct input_event ies[100];

	while (!sensor_ctx.exit_flag)
	{
		FD_ZERO(&rfds);
		FD_SET(sensor_ctx.accl_ctx.dev_fd, &rfds);
		//两次SYN_REPORT之间为一组数据
		tv.tv_sec = 1;
		tv.tv_usec = 0;
		retval = select(sensor_ctx.accl_ctx.dev_fd + 1, &rfds, NULL, NULL, &tv);
		if (retval == -1)
		{
			perror("select()");
			break;
		}
		else if (retval)
		{
			rd_len = read(sensor_ctx.accl_ctx.dev_fd, ies, sizeof(ies));
			if (rd_len <= 0)
			{
				printf("read Accl failed!\n");
				break;
			}

			for (i = 0; i < rd_len / sizeof(struct input_event); i++)
			{
				if (EV_SYN == ies[i].type && SYN_REPORT == ies[i].code)
				{
					if (!sync)
					{
						sync = 1;
					}
					else
					{
						//printf("acc:%f|%f|%f\n", x, y, z);
						sensor_ctx.accl_x = (long int)x;
						sensor_ctx.accl_y = (long int)y;
						sensor_ctx.accl_z = (long int)z;
//
//						*accl_x = (long int)x;
//						*accl_y = (long int)y;
//						*accl_z = (long int)z;
						sync=0;
					}
				}
				if (EV_ABS == ies[i].type)
				{
					switch (ies[i].code)
					{
						case ABS_X:
							//acc_x = ies[i].value * sensor_ctx.accl_ctx.sensitivity / 1000;
							x = ies[i].value * sensor_ctx.accl_ctx.sensitivity; //内核中此值放大了1000倍，使用时需除1000
							break;
						case ABS_Y:
//							acc_y = ies[i].value * sensor_ctx.accl_ctx.sensitivity / 1000;
							y = ies[i].value * sensor_ctx.accl_ctx.sensitivity; //内核中此值放大了1000倍，使用时需除1000
							break;
						case ABS_Z:
//							acc_z = ies[i].value * sensor_ctx.accl_ctx.sensitivity / 1000;
							z = ies[i].value * sensor_ctx.accl_ctx.sensitivity; //内核中此值放大了1000倍，使用时需除1000
							break;
						default:
							printf("Invalid e.code!\n");
							break;
					}
				}
			}
		}
		else
		{
			TRACE_ERR("select read acc data error, return value=%d!\n", retval);
			break;
		}
	}

	printf("ReadAcclData task exit!\n");
	sensor_ctx.exit_flag = 1;

	pthread_exit(NULL);
}

