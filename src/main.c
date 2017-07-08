/*
 * main.c
 *
 *  Created on: 2017年6月15日
 *      Author: root
 */

#include "my_include.h"
#include "libavformat/avformat.h"

#include "./common/hf_plant_api.h"
#include "./sensor/start_sensor.h"
#include "upload_pic.h"

extern void start_listening();

DEV_INFO_OBJ dev_info;

static void init_dev_info()
{
	memset(&dev_info, 0, sizeof(DEV_INFO_OBJ));
	dev_info.sample_frequency = 1;
	get_sys_mac(dev_info.mac, sizeof(dev_info.mac));
	get_sys_sn(dev_info.sn, sizeof(dev_info.sn));
}

int main()
{
	pthread_attr_t attr;

	signal(SIGPIPE, SIG_IGN);
	system("mkdir /tmp/Alarm");
	av_register_all();
	avformat_network_init();

	init_dev_info();

	elevator_get_token();//获取令牌

#if 1
	pthread_t get_sensor_pthread_id;
	pthread_attr_init(&attr);
	pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);
	pthread_create(&get_sensor_pthread_id, &attr, start_sensor, NULL);
	pthread_attr_destroy(&attr);
#endif

	start_listening();

	return 0;
}
