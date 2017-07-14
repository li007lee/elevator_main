/*
 * my_include.h
 *
 *  Created on: 2014年12月11日
 *      Author: root
 */

#ifndef MY_INCLUDE_H_
#define MY_INCLUDE_H_

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <linux/types.h>
#include <string.h>
#include <pthread.h>
#include <assert.h>
#include <linux/i2c.h>
#include <linux/i2c-dev.h>
#include <unistd.h>
#include <termios.h>
#include <errno.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <resolv.h>
#include <dirent.h>
#include <sys/stat.h>
#include <sys/file.h>
#include <sys/wait.h>
#include <stdarg.h>
#include <sys/types.h>
#include <time.h>
#include <sys/prctl.h>
#include <sys/msg.h>
#include <sys/time.h>
#include <memory.h>
#include <linux/rtc.h>
#include <semaphore.h>
#include <netdb.h>
#include <signal.h>
#include <ctype.h>
#include <netinet/tcp.h>
#include <netinet/in.h>
#include <net/if_arp.h>
#include <net/if.h>
#include <sys/shm.h>
#include <linux/input.h>


///////////////////////////////////////////////////////////////////////////////////////////
//数据类型定义
///////////////////////////////////////////////////////////////////////////////////////////
typedef unsigned char              HB_U8;
typedef unsigned short            HB_U16;
typedef unsigned int                 HB_U32;
typedef unsigned long long    HB_U64;
typedef signed char                   HB_S8;
typedef short                                HB_S16;
typedef int                                     HB_S32;
typedef long long                        HB_S64;
typedef char                                 HB_CHAR;
typedef float                                 HB_FLOAT;
typedef void                                  HB_VOID;
typedef void *                               HB_HANDLE;
typedef enum _tagHB_BOOL
{
    HB_FALSE = 0,
    HB_TRUE  = 1
}HB_BOOL;


#ifndef NULL
#define NULL  0L
#endif

#define HB_NULL     0L
#define HB_SUCCESS  0
#define HB_FAILURE  -1

//#define UDP_SERVER_IP "alarmtest.hbydt.net"		//(139.217.17.108)
//#define UDP_SERVER_IP "aegisci.ivview.com"

//图片上传服务器
#define PT_ADDR_IP  "elevator.hbydt.cn"
#define PT_PORT     8088
//传感器数据上传服务器
//#define UDP_SERVER_IP "elevator.hbydt.cn"	//正式服务器
#define UDP_SERVER_IP "alarmtest.hbydt.net" //测试服务器
#define UDP_SERVER_PORT 9001

//报警到来发送信号到服务器
#define PT_Alarm_ADDR_IP  "www.chorstar.com" //发送到中融智达服务器
#define PT_Alarm_PORT     8081

#define MAX_ERR_CRITICAL	10
#define MAX_ERR_TIMES		3

#define PIC_MAX_SIZE	(102400) //图片最大为100K
#define ETHX  "eth0"

typedef struct _tagDEV_INFO//设备信息结构体
{
	HB_S32 sample_frequency; //传感器数据采集频率,秒/条
	HB_S32 return_token;	//获取token的成功标志
	HB_S32 upload_pic_success_flag;
    HB_CHAR mac[32];	//设备mac地址
    HB_CHAR sn[32];		//设备序列号
    HB_CHAR access_token[64]; //获取到的token
    HB_CHAR sessionId[64];	//上传传感器数据是需要的sessionId

}DEV_INFO_OBJ, *DEV_INFO_HANDLE;

typedef struct _SENSOR_INFO
{
    //统计计数
	HB_U32 send_sensor_data_total_cout;	//发送传感器数据的总次数
	HB_U32 send_sensor_data_success_count; //发送传感器数据成功的总次数
	HB_U32 send_sensor_data_resend_count; //传感器数据重发的总次数
	HB_U32 send_sensor_data_miss_count; //缓冲区满后丢包总次数
	HB_U32 alarm_pic_upload_count; //报警图片上传成功总张数
}SENSOR_INFO;

extern DEV_INFO_OBJ dev_info;
extern SENSOR_INFO sensor_info;

#define DEBUG
#ifdef DEBUG
#define COLOR_STR_NONE          "\033[0m"
#define COLOR_STR_RED              "\033[1;31m"
#define COLOR_STR_GREEN         "\033[1;32m"
#define COLOR_STR_YELLOW      "\033[1;33m"
#define COLOR_STR_BLUE		     "\033[0;32;34m"

#define TRACE_LOG(str, args...)  printf(COLOR_STR_GREEN  "\n########   FILE:%s  FUNCTION: %s, "str COLOR_STR_NONE,__FILE__, __FUNCTION__,## args);
#define TRACE_ERR(str, args...)   printf(COLOR_STR_RED "\n########   FILE:%s  FUNCTION: %s, "str COLOR_STR_NONE,__FILE__, __FUNCTION__,## args);
#define TRACE_DBG(str, args...)  printf(COLOR_STR_YELLOW  str COLOR_STR_NONE, ## args);
#else
#define TRACE_LOG(str, args...)   do{} while(0)
#define TRACE_ERR(str, args...)    do{} while(0)
#define TRACE_DBG(str, args...)   do{} while(0)
#endif /* ERR_DEBUG */


#endif /* MY_INCLUDE_H_ */
