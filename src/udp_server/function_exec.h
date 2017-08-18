/*
 * function_exec.h
 *
 *  Created on: 2017年7月11日
 *      Author: root
 */

#ifndef UDP_SERVER_FUNCTION_EXEC_H_
#define UDP_SERVER_FUNCTION_EXEC_H_

#include "my_include.h"
#include "server_udp_opt.h"

//解析json串
int analysis_json(HB_CHAR *pSrcJson, HB_CHAR *pKey, HB_CHAR *pValue, HB_S32 iValueSize);
//获取电梯配置
HB_VOID get_elevator_config(UDP_CLIENT_INFO_HANDLE pUdpClient, HB_CHAR *pSaveKey);
//设置电梯配置
int set_elevator_config(UDP_CLIENT_INFO_HANDLE pUdpClient, HB_CHAR *pKey, HB_CHAR *pSaveKey);
//测试网络连接
int get_net_status(UDP_CLIENT_INFO_HANDLE pUdpClient);
//获取电梯程序运行状态
HB_VOID get_program_status(UDP_CLIENT_INFO_HANDLE pUdpClient);
//获取报警图片
HB_VOID get_alarm_photo(UDP_CLIENT_INFO_HANDLE pUdpClient);
//获取传感器数据上传信息
HB_S32 get_data_upload_info(UDP_CLIENT_INFO_HANDLE pUdpClient);
//获取电梯相关参数（电梯编号，SIM卡号，安装位置）
void get_version(UDP_CLIENT_INFO_HANDLE pUdpClient);


#endif /* UDP_SERVER_FUNCTION_EXEC_H_ */
