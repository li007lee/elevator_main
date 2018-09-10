//////////////////////////////////////////////////////////////////////////////
// 版权所有，2009-2012，北京汉邦高科数字技术有限公司
// 本文件是未公开的，包含了汉邦高科的机密和专利内容
////////////////////////////////////////////////////////////////////////////////
// 文件名： ipc_common.h
// 作者：   乔勇
// 版本：   1.0
// 日期：   2012-11-10
// 描述：IPC整个工程通用头文件
// 历史记录：
////////////////////////////////////////////////////////////////////////////////

#ifndef _IPC_COMMON_H
#define _IPC_COMMON_H

#include "ipc_include.h"

///////////////////////////////////////////////////////////////////////////////////////////
//数据类型定义
///////////////////////////////////////////////////////////////////////////////////////////
typedef	unsigned char		HB_U8;
typedef unsigned short		HB_U16;
typedef unsigned int		HB_U32;
typedef	unsigned long long 	HB_U64;
typedef signed	char		HB_S8;
typedef	short				HB_S16;
typedef int					HB_S32;
typedef long long			HB_S64;
typedef char				HB_CHAR;
typedef float               HB_FLOAT;
typedef	void				HB_VOID;
typedef void *  			HB_HANDLE;
//typedef enum _tagHB_BOOL
//{
//	HB_FALSE	=	0,
//	HB_TRUE		=	1
//}HB_BOOL;

#ifndef NULL
#define NULL	0L
#endif

#define	HB_NULL		0L
#define HB_SUCCESS	0
#define HB_FAILURE	-1

#endif
