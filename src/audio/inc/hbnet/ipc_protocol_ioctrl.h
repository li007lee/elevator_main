﻿#ifndef  _IPC_PROTOCOL_IOCTRL_H
#define  _IPC_PROTOCOL_IOCTRL_H

//新协议参数获取
///////////////////////////////////////////////////////////////    
// 函数名：ipc_config_get 
// 描述：  新协议参数获取   
// 参数：  handle ：新协议参数句柄
// 返回值： -1 失败 1 成功
// 说明：
//////////////////////////////////////////////////////////////
HB_S32  ipc_config_get(HB_IPC_CFG_HANDLE handle);


//////////////////////////////////////////////////////////
// 函数名：cmd_ipc_config_get_handle
// 描述：  新协议命令处理 
// 参数：  handle ：新协议参数句柄
// 返回值： -1 失败 1 成功
// 说明：
//////////////////////////////////////////////////////////  
HB_S32  cmd_ipc_config_get_handle(HB_IPC_CFG_HANDLE handle);

#endif