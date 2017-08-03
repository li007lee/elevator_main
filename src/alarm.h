/*
 * alarm.h
 *
 *  Created on: 2017年8月3日
 *      Author: root
 */

#ifndef SRC_ALARM_H_
#define SRC_ALARM_H_

typedef struct _ALARM_INFO {
	int iHandAlarm; //手动报警
	int iLevelling; //平层信号
	int iDoorClose; //关门到位
	int iDoorOpen;	//开门到位

	int iSendFlag; //用来统计报警信号变化，变化了值为1,为变化值为0,值为1是将会把上面的信号上传到服务器
}ALARM_INFO;

extern ALARM_INFO stAlarmInfo;

//手动报警处理函数
void deal_hand_alarm();
#endif /* SRC_ALARM_H_ */
