/*
 * dev_opt.c
 *
 *  Created on: 2016-9-12
 *      Author: li007lee
 */

#include "my_include.h"

#include "dev_opt.h"
#include "sensor_opt.h"
#include "hf_plant_api.h"


void InitSensorGlobleVar()
{
	sensor_ctx.sock_fd = -1;
	sensor_ctx.exit_flag = 0;
	sensor_ctx.accl_x = 0;
	sensor_ctx.accl_y = 0;
	sensor_ctx.accl_z = 0;
	sensor_ctx.gyro_x = 0;
	sensor_ctx.gyro_y = 0;
	sensor_ctx.gyro_z = 0;
	pthread_mutex_init(&sensor_ctx.mutex_lock_data,NULL);
//	get_sys_mac(sensor_ctx.mac, sizeof(sensor_ctx.mac));
}

int OpenDev()
{
	int accl_fd = 0;
	int gyro_fd = 0;

	accl_fd = open(ACCL_DEV, O_RDONLY);
	if (accl_fd < 0)
	{
		printf("Open "ACCL_DEV" failed!\n");
		return -1;
	}
	else
	{
		sensor_ctx.accl_ctx.dev_fd = accl_fd;
		sensor_ctx.accl_ctx.sensitivity = 1.0;
	}

	gyro_fd = open(GYRO_DEV, O_RDONLY);
	if (gyro_fd < 0)
	{
		close(accl_fd);
		printf("Open "GYRO_DEV"failed!\n");
		usleep(1000 * 500);
		return -2;
	}
	else
	{
		sensor_ctx.gyro_ctx.dev_fd = gyro_fd;
		sensor_ctx.gyro_ctx.sensitivity = 62.5;
	}

	return 0;
}

void CloseDev()
{
	if (sensor_ctx.accl_ctx.dev_fd > 0)
	{
		close(sensor_ctx.accl_ctx.dev_fd);
		sensor_ctx.accl_ctx.dev_fd = 0;
	}
	if (sensor_ctx.gyro_ctx.dev_fd > 0)
	{
		close(sensor_ctx.gyro_ctx.dev_fd);
		sensor_ctx.gyro_ctx.dev_fd = 0;
	}
}
