/*
 * alarm.c
 *
 *  Created on: 2017年8月3日
 *      Author: root
 */

#include "my_include.h"
#include "alarm.h"
#include "upload_pic.h"

ALARM_INFO stAlarmInfo;

void deal_hand_alarm()
{
	pthread_t thread_SendSignal = 0;
	pthread_t thread_UploadPicId = 0;

	pthread_create(&thread_SendSignal, NULL, thread_send_signal_to_http, NULL);
	pthread_create(&thread_UploadPicId, NULL, thread_upload_picture, NULL);

	usleep(500*1000);//等待线程创建
}
