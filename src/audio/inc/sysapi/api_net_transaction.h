//////////////////////////////////////////////////////////////////////////////// 
// 版权所有，2009-2010，北京汉邦高科数字技术有限公司。
// 该文件是未公开的，包含了汉邦高科机密和专利内容。
//////////////////////////////////////////////////////////////////////////////// 
// 文件名：	api_net_transaction.h
// 作者：	lurao
// 版本：	1.0
// 日期：	2010.5.18
// 描述： 平台io参数与ipc全局结构体转换
// 历史记录：
//////////////////////////////////////////////////////////////////////////////// 

#ifndef _API_NET_TRANSACTION_H
#define _API_NET_TRANSACTION_H

#include "hbnet/netapp.h"

#define MAX_CMDLEN 1024


//ipc全局信息
typedef struct _tagG_NETSTATUS
{
	NET_STATUS_OBJ g_api;
	HB_S32 g_api_flag;
}ALL_NETSTATUS_OBJ, *ALL_NETSTATUS_HANDLE;


//平台io参数
typedef struct _tagIOPARAM
{
	HB_S32 handle;
	HB_S32 cmd;
	HB_S32 channel;
	HB_VOID *pparam;
	HB_S32 size_of_param;
}IO_PARAM_OBJ, *IO_PARAM_HANDLE;


//平台io参数处理
HB_S32 sysapi_cmd_io(ALL_NETSTATUS_HANDLE pnetstatus, IO_PARAM_HANDLE pio_param);
#endif

