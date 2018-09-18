/*
 * net_to_rs485.h
 *
 *  Created on: 2018年9月17日
 *      Author: lijian
 */

#ifndef SRC_NET_TO_RS485_NET_TO_RS485_H_
#define SRC_NET_TO_RS485_NET_TO_RS485_H_

#include "my_include.h"

//测距模块结构体
typedef struct DISTANCE_INFO
{
	HB_S32 iDistance; //单位mm（毫米级精度）
}DISTANCE_INFO_OBJ, *DISTANCE_INFO_HANDLE;

DISTANCE_INFO_OBJ stDistance;

HB_VOID *thread_get_distance_moudle(HB_HANDLE hArg);

#endif /* SRC_NET_TO_RS485_NET_TO_RS485_H_ */
