/*
 * elevator_module.h
 *
 *  Created on: 2016年8月2日
 *      Author: root
 */

#ifndef ELEVATOR_MODULE_H_
#define ELEVATOR_MODULE_H_
#include "my_list.h"

#define MAX_SAVE_DATA	(5000) //网络不好时，缓冲的最大长度

typedef struct _tagSONSER_DATA_NODE
{
	HB_CHAR  *msg_buf;		//传感器数据
	HB_S32	    buf_len;	//传感器数据长度
}SONSER_DATA_NODE_OBJ, *SONSER_DATA_NODE_HANDLE;


typedef struct _tagELEVATOR_DATA_LIST
{
	LIST_HANDLE	plist;			     //链表指针
	HB_BOOL	b_wait;			 //等待标志位
	pthread_mutex_t	list_mutex;	 //链表互斥锁
	pthread_cond_t	list_empty;	 //链表空的条件锁
}ELEVATOR_DATA_LIST_OBJ, *ELEVATOR_DATA_LIST_HANDLE;

ELEVATOR_DATA_LIST_OBJ ele_data_list;

////////////////////////////////////////////////////////////////////////////////
// 函数名：elevator_data_list_init
// 描述：电梯数据链表初始化
// 参数：
//  ［IN］
// 返回值：
//  	HB_FAILURE - 失败
//		HB_SUCCESS - 成功
// 说明：
////////////////////////////////////////////////////////////////////////////////
HB_S32 elevator_data_list_init();

HB_VOID *elevator_recv_data_task(HB_VOID *param);

HB_VOID *elevator_send_data_task(HB_VOID *param);

HB_VOID *scanning_task(HB_VOID *param);

#endif /* ELEVATOR_MODULE_H_ */
