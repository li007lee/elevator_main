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
	int iLevelling2;//如果1s内平层触发了两次，为保证数据不丢失，在此处将变化后的值一并发送。
	int iDoorClose; //关门到位
	int iDoorOpen;	//开门到位

	int iLevellingSendFlag; //用来记录当前的平层信号是否已经发送过，若未发送过，新的数据要存储到iLevelling2中
}ALARM_INFO;

extern ALARM_INFO stAlarmInfo;

//手动报警处理函数
void deal_hand_alarm();
#endif /* SRC_ALARM_H_ */
