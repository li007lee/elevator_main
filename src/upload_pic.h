/*
 * upload_pic.h
 *
 *  Created on: 2017年6月19日
 *      Author: root
 */

#ifndef ALARM_UPLOAD_PIC_UPLOAD_PIC_H_
#define ALARM_UPLOAD_PIC_UPLOAD_PIC_H_

#define GET_PICTURE	"/usr/bin/get_picture300"
#define ALARM_PIC_PATH	"/tmp/Alarm/alarm.jpg"
#define RM_ALARM_PIC_PATH "rm /tmp/Alarm/alarm.jpg"//删除原来的报警图

void *elevator_get_token(void *arg);
void *thread_upload_picture(void *arg);

void *thread_send_signal_to_http(void *arg);

#endif /* ALARM_UPLOAD_PIC_UPLOAD_PIC_H_ */
