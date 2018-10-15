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
#include "audio/audio_ctrl.h"
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


HB_VOID *thread_reboot_moudle(HB_VOID *arg)
{

#if 0
	struct tm
	{
	    int tm_sec;      /*代表目前秒数，正常范围为0-59，但允许至61秒 */
	    int tm_min;     /*代表目前分数，范围0-59*/
	    int tm_hour;   /* 从午夜算起的时数，范围为0-23 */
	    int tm_mday;  /* 目前月份的日数，范围01-31 */
	    int tm_mon;   /*代表目前月份，从一月算起，范围从0-11 */
	    int tm_year;   /*从1900 年算起至今的年数*/
	    int tm_wday;   /* 一星期的日数，从星期一算起，范围为0-6。1,2,3,4,5,6,0 */
	    int tm_yday;   /* Days in year.[0-365] */
	    int tm_isdst;   /*日光节约时间的旗标DST. [-1/0/1]*/
	};
#endif

	//每周四凌晨3-4点进行重启
	time_t stCurTime;//time_t就是long int 类型
	struct tm *pTblock;

	sleep(3600); //每次开机后先睡眠一小时再启动，防止刚刚重启还是3-4点之间导致频繁重启

	for(;;)
	{
		stCurTime = time(NULL);//这一句也可以改成time(&timer);
		pTblock = localtime(&stCurTime);

		printf("curtain time : pTblock->tm_wday=%d [%d:%d:%d]\n", pTblock->tm_wday, pTblock->tm_hour, pTblock->tm_min, pTblock->tm_sec);

		if(pTblock->tm_wday==4 && pTblock->tm_hour==3)
		{
			system("reboot");
		}

		sleep(1800); //每半小时获取一次时间
	}

	pthread_exit(NULL);
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

#if 1 //定时重启模块
	pthread_t reboot_thread_id;
	pthread_attr_init(&attr);
	pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);
	pthread_create(&reboot_thread_id, &attr, thread_reboot_moudle, NULL);
	pthread_attr_destroy(&attr);
#endif

#if 1 //加速度陀螺仪模块
	pthread_t get_sensor_pthread_id;
	pthread_attr_init(&attr);
	pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);
	pthread_create(&get_sensor_pthread_id, &attr, start_sensor, NULL);
	pthread_attr_destroy(&attr);
#endif

#if 1 //手机端配置模块
	pthread_t start_udp_server_thread_id;
	pthread_attr_init(&attr);
	pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);
	pthread_create(&start_udp_server_thread_id, &attr, thread_udp_server, NULL);
	pthread_attr_destroy(&attr);
#endif

#if 1 //音频采集模块
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
