/*
 * main.c
 *
 *  Created on: 2017年6月15日
 *      Author: root
 */

#include "my_include.h"
#include "libavformat/avformat.h"

#include "hf_plant_api.h"
#include "./sensor/start_sensor.h"
//#include "upload_pic.h"
#include "udp_server.h"
#include "audio/start_audio.h"
#include "uart/uart.h"
#include "net_to_rs485/net_to_rs485.h"
#include "common.h"

//extern void start_listening();

DEV_INFO_OBJ dev_info;
SENSOR_INFO sensor_info;
ELEVATOR_PROPERTIES elevator_properties; //存储电梯编号等信息

static void init_dev_info()
{
	memset(&dev_info, 0, sizeof(DEV_INFO_OBJ));
	dev_info.sample_frequency = 500000; //500ms
	get_sys_mac(dev_info.mac, sizeof(dev_info.mac));
	get_sys_sn(dev_info.sn, sizeof(dev_info.sn));

	sensor_info.send_sensor_data_total_cout = 0;	//发送传感器数据的总次数
	sensor_info.send_sensor_data_success_count = 0; //发送传感器数据成功的总次数
	sensor_info.send_sensor_data_resend_count = 0; //传感器数据重发的总次数
	sensor_info.send_sensor_data_miss_count = 0; //缓冲区满后丢包总次数
	sensor_info.alarm_pic_upload_count = 0; //报警图片上传总张数
}

int main()
{
	pthread_attr_t attr;

	signal(SIGPIPE, SIG_IGN);
	system("mkdir /tmp/Alarm");
	av_register_all();
	avformat_network_init();

	init_dev_info();
	elevator_get_token(NULL);//获取令牌

#if 1 //加速度陀螺仪模块
	pthread_t get_sensor_pthread_id;
	pthread_attr_init(&attr);
	pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);
	pthread_create(&get_sensor_pthread_id, &attr, start_sensor, NULL);
	pthread_attr_destroy(&attr);
#endif

#if 0 //手机端配置模块
	pthread_t start_udp_server_thread_id;
	pthread_attr_init(&attr);
	pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);
	pthread_create(&start_udp_server_thread_id, &attr, thread_udp_server, NULL);
	pthread_attr_destroy(&attr);
#endif

#if 0 //音频采集模块
	pthread_t start_audio_thread_id;
	pthread_attr_init(&attr);
	pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);
	pthread_create(&start_audio_thread_id, &attr, thread_start_audio_moudle, NULL);
	pthread_attr_destroy(&attr);
#endif

#if 1 //温湿度采集模块
	pthread_t start_wsd_thread_id;
	pthread_attr_init(&attr);
	pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);
	pthread_create(&start_wsd_thread_id, &attr, thread_read_uart, NULL);
	pthread_attr_destroy(&attr);
#endif

#if 1 //激光测距模块
	pthread_t start_get_distance_thread_id;
	pthread_attr_init(&attr);
	pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);
	pthread_create(&start_get_distance_thread_id, &attr, thread_get_distance_moudle, NULL);
	pthread_attr_destroy(&attr);
#endif

	pause();

	return 0;
}
