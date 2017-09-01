/*
 * upload_pic.h
 *
 *  Created on: 2017年6月19日
 *      Author: root
 */

#ifndef ALARM_UPLOAD_PIC_UPLOAD_PIC_H_
#define ALARM_UPLOAD_PIC_UPLOAD_PIC_H_

void *elevator_get_token(void *arg);
void *thread_upload_picture(void *arg);

void *thread_send_signal_to_http(void *arg);

#endif /* ALARM_UPLOAD_PIC_UPLOAD_PIC_H_ */
