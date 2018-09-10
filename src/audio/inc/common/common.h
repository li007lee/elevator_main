#ifndef COMMON_H
#define COMMON_H

// 数据类型定义
typedef signed char         sint8;
typedef signed short        sint16;
typedef signed int          sint32;
typedef signed long long    sint64;
typedef unsigned char       uint8;
typedef unsigned short      uint16;
typedef unsigned int        uint32;
typedef unsigned long long  uint64;

// 系统时间定义
typedef struct {
  unsigned int sec : 6;
  unsigned int min : 6;
  unsigned int hour : 5;
  unsigned int day : 5;
  unsigned int month : 4;
  unsigned int year : 6;
} SYSTIME, *PSYSTIME;

// 模块ID定义
typedef enum {
  COMP_COMMON = 0,
  COMP_VIDEOIN,
  COMP_VIDEOOUT,
  COMP_VIDEOENC,
  COMP_VIDEODEC,
  COMP_AUDIOIN,
  COMP_AUDIOOUT,
  COMP_AUDIOENC,
  COMP_AUDIODEC,
  COMP_RECORD,
  COMP_PLAYBACK = 10,
  COMP_STATMACH,
  COMP_NETMS,
  COMP_NETVOD,
  COMP_NETUPGRADE,
  COMP_NETCMD,
  COMP_WEBSERV,
  COMP_SERIAL,
  COMP_PTZ,
  COMP_GUI,
  COMP_FIFO = 20,
  COMP_EVENT,
//  COMP_MFS,
  COMP_MSHEAD = 23,
  COMP_OSD,
  COMP_VIDEOVPP,
  COMP_LINK,
  COMP_TIMER,
  COMP_RTC,
  COMP_ALARM,   // 报警模块
  COMP_MSG = 30,// 消息队列
  COMP_SEM,     // 进程间信号灯
  COMP_SHM,     // 进程间共享内存
  COMP_NTP,
  COMP_DDNS,
  COMP_PPPOE,
  COMP_SYS,
  COMP_NETWORK,
  COMP_TRANSUART,
  COMP_DEAMON,
  COMP_PROCFIFO = 40, 
  COMP_EXTCMD,
  COMP_SERIALKEYPAD,
  COMP_MAX,
} COMPID, *PCOMPID;

// 模块名称定义
/*static const char *COMPSTR[] = {
  "COMMON",   // 0
  "VIDEOIN",
  "VIDEOOUT",
  "VIDEOENC",
  "VIDEODEC",
  "AUDIOIN",
  "AUDIOOUT",
  "AUDIOENC",
  "AUDIODEC",
  "RECORD",
  "PLAYBACK", // 10
  "STATMACH",
  "NETMS",
  "NETVOD",
  "NETUPGRADE",
  "NETCMD",
  "WEBSERV",
  "SERIAL",
  "PTZ",
  "GUI",
  "FIFO",   // 20
  "EVENT",
  "MFS",
  "MSHEAD",
  "OSD",
  "VIDEOVPP",
  "LINK",
  "TIMER",
  "RTC",
  "ALARM",     // 报警模块
  "MSG",   // 30    // 消息队列
  "SEM",       // 进程间信号灯
  "SHM",        // 进程间共享内存
  "NTP",
  "DDNS",
  "PPPOE",
  "SYS",
  "NETWORK",
  "TRANS UART",
  "DEAMON",
  "PROCFIFO",  // 40
  "EXTCMD",
  "SKEYPAD",
};
*/
typedef struct {
  int common;
  int vi;
  int vo;
  int venc;
  int vdec;
  int ai;
  int ao;
  int aenc;
  int adec;
  int rec;
  int pb;
  int statm;
  int netms;
  int netvod;
  int upgrade;
  int netcmd;
  int webserv;
  int uart;
  int ptz;
  int gui;
  int fifo;
  int event;
  int mfs;
  int mshead;
  int osd;
  int vpp;
  int link;
  int timer;
  int rtc;
  int alm;
  int msg;
  int sem;
  int shmem;
  int ntp;
  int ddns;
  int pppoe;
  int sys;
  int network;
  int trans_uart;
  int daemon;
  int procfifo;
  int extcmd;
  int skeypad;
} COMPFD, *PCOMPFD;

COMPFD sys_handle;

/*********************************************************************************
* 函数介绍：数据处理回调
* 输入参数：idx: 通道号
            fifo: 数据缓存FIFO
            data: 数据接收缓冲区
            size: 数据接收缓冲区大小
* 输出参数：无
* 返回值  ：无
* 注: 当fifo为0时，数据存储于data中，size表示数据长度
*     当fifo不为0时，数据存储于fifo中，data表示用户缓冲区地址，size表示缓冲区长度
*     当fifo,data都为空时，表示无数据需要处理，也即数据处理结束标记
**********************************************************************************/
typedef void (*datacallback) (int idx, int fifo, char* data, int size);

/*********************************************************************************
* 函数介绍：消息通知回调
* 输入参数：wparam: 参数
            lparam: 参数
* 输出参数：无
* 返回值  ：无
**********************************************************************************/
typedef void (*notifycallback) (int wparam, int lparam);

/*************************************************************
* 函数介绍：线程启动函数
* 输入参数：priority: 线程优先级1~99
            func: 线程执行函数体
            wparam: 函数参数
* 输出参数：pid: 线程ID
* 返回值  ：0-成功，<0-错误代码
*************************************************************/
int pthread_start(int* pid, int priority, notifycallback func, int wparam);

/*************************************************************
* 函数介绍： 计算该月份总天数
* 输入参数：year: 年
                          month: 月份
* 输出参数：无
* 返回值  ：当前月份的天数
*************************************************************/
int time_dayofmonth(unsigned short year, unsigned char month);

/*************************************************************
* 函数介绍： 计算该日期的星期数
* 输入参数：year: 年
                          month: 月份
                          day: 日期
* 输出参数：无
* 返回值  ：0：星期天，1~6：星期一~星期六
*************************************************************/
int time_weekofdate(unsigned short year, unsigned char month, unsigned char day);

/*************************************************************
* 函数介绍： 从RTC同步系统当前时间
* 输入参数：无
* 输出参数：无
* 返回值  ：0：成功，<0：失败
*************************************************************/
int time_utcfromrtc();

/*************************************************************
* 函数介绍： 从系统当前时间同步RTC
* 输入参数：无
* 输出参数：无
* 返回值  ：0：成功，<0：失败
*************************************************************/
int time_utctortc();

/*************************************************************
* 函数介绍： 获取系统当前的当地时间
* 输入参数：无
* 输出参数：time
* 返回值  ：>0：成功(1~7:分别表示星期一到星期天)，<0：失败
*************************************************************/
int time_get(PSYSTIME sys_time);

/*************************************************************
* 函数介绍：设置系统当前的当地时间，并同步RTC
* 输入参数：time
* 输出参数：无
* 返回值  ：>0：成功，<0：失败
*************************************************************/
int time_set(PSYSTIME sys_time);

#endif

