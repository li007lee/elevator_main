/*
 * uart.h
 *
 *  Created on: 2018年9月7日
 *      Author: lijian
 */

#ifndef SRC_UART_UART_H_
#define SRC_UART_UART_H_

#include "my_include.h"

//温湿度信息结构体
typedef struct _WSD_INFO
{
	HB_CHAR cTemperature[8];
	HB_CHAR cHumidity[8];
}WSD_INFO_OBJ, *WSD_INFO_HANDLE;

HB_S32 open_uart(char *pPath, speed_t speed);
HB_S32 send_to_uart(HB_S32 iUartFd, HB_CHAR *pData, HB_S32 iDataLen);
HB_S32 read_from_uart(HB_S32 iUartFd, HB_CHAR *pData, HB_S32 iDataSize);
HB_VOID close_uart(HB_S32 *pUartFd);
HB_VOID *thread_read_uart(HB_HANDLE hArg);

WSD_INFO_OBJ glWSDInfo;

#endif /* SRC_UART_UART_H_ */
