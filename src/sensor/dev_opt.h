/*
 * dev_opt.h
 *
 *  Created on: 2016-9-12
 *      Author: li007lee
 */

#ifndef DEV_OPT_H_
#define DEV_OPT_H_

//#define ACCL_DEV "/dev/event0"
//#define GYRO_DEV "/dev/event2"
#define ACCL_DEV "/dev/input/event0"
#define GYRO_DEV "/dev/input/event2"

int OpenDev();
void CloseDev();

//初始化全局变量
void InitSensorGlobleVar();

#endif /* DEV_OPT_H_ */
