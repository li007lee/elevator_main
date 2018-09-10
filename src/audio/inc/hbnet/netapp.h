#ifndef   _NETAPP_H
#define   _NETAPP_H

#include "common/ipc_common.h"
#include "hbnet/sysstatus.h"
#include "mfs/mfs.h"

//#include "types.h"
#pragma pack(1)
#define	INFO_LEN		32
#define  MAX_VOD_NUM               1

#ifdef DM36X
#define EEPROM_PAGE0   0X50
#endif
#define SDK7000 1
#define ONVIF 2
typedef struct  _tagNET_BACKUP_TIMESEG
{
	HB_CHAR    	nPort;
	HB_CHAR    	type;
    MFS_TIME 	starttime;
    MFS_TIME   	endtime;
}NET_BACKUP_TIMESEG_OBJ, NET_BACKUP_TIMESEG_HANDLE;

#define NET_SDVR_LOGIN 							0x00 //网络登陆主机
#define NET_SDVR_LOGOUT 						0x01 //注销网络用户
//#define NET_SDVR_REAL_PLAY 0x02 					 //请求实时视频
//#define NET_SDVR_REAL_STOP 0x03 					 //关闭实时视频
#define NET_SDVR_VEFF_GET 						0x04 //获取视频参数
#define NET_SDVR_VEFF_SET 						0x05 //设置视频参数
#define NET_SDVR_KEYFRAME 						0x06 //请求关键帧
#define NET_SDVR_PTZ_CTRL 						0x07 //云台控制
#define NET_SDVR_PTZ_TRANS 						0x08 //透明云台控制
//#define NET_SDVR_PLAY_CTRL 					0x10 //点播流控制
//#define NET_SDVR_BACKUP_REQ 					0x11 //下载文件
//#define NET_SDVR_BACKUP_STOP					0x13 //停止备份录像文件段
//#define NET_SDVR_BACKUP_POS 					0x14 //获取下载进度
#define NET_SDVR_CTRL 							0x15 //主机控制(包括重启,关机等)
#define NET_SDVR_UPDATE_START 					0x16 //升级控制
#define NET_SDVR_FORMAT_DISK 					0x17 //格式化主机硬盘
#define NET_SDVR_ALARM_GET 						0x19 //获取报警输出
#define NET_SDVR_ALARM_SET						0x1A //设置报警输出
//#define NET_SDVR_VOICE_START 					0x1B //打开对讲操作
//#define NET_SDVR_VOICE_STOP 					0x1C //关闭对讲操作
#define NET_SDVR_SERIAL_START 					0x1D //打开透明通道
#define NET_SDVR_SERIAL_STOP 					0x1E //关闭透明通道
#define NET_SDVR_CLICK_KEY 						0x1F //网络键盘
#define NET_SDVR_MANURECORD_SET					0x20 //设置手动录像
#define NET_SDVR_MANURECORD_GET 				0x21 //获取手动录像状态
#define NET_SDVR_WORK_STATE 					0x22 //获取主机工作状态
#define NET_SDVR_LOG_QUERY 						0x23 //主机日志查询
#define NET_SDVR_DEVICECFG_GET 					0x26 //获取设备信息
#define NET_SDVR_DEVICECFG_SET 					0x27 //设置设备信息
#define NET_SDVR_NETCFG_GET 					0x28 //获取设备网络参数
#define NET_SDVR_NETCFG_SET 					0x29 //设置设备网络参数
#define NET_SDVR_PICCFG_GET 					0x2A //获取通道参数
#define NET_SDVR_PICCFG_SET 					0x2B //设置通道参数
#define NET_SDVR_COMPRESSCFG_GET 				0x2C //获取压缩参数
#define NET_SDVR_COMPRESSCFG_SET 				0x2D //设置压缩参数
#define NET_SDVR_RECORDCFG_GET 					0x2E //获取定时录像状态
#define NET_SDVR_RECORDCFG_SET 					0x2F //设置定时录像
#define NET_SDVR_DECODERCFG_GET 				0x30 //获取解码器参数(云台参数)
#define NET_SDVR_DECODERCFG_SET 				0x31 //设置解码器参数(云台参数)
#define NET_SDVR_ALARMINCFG_GET 				0x32 //获取报警输入参数
#define NET_SDVR_ALARMINCFG_SET 				0x33 //设置报警输入参数
#define NET_SDVR_ALARMOUTCFG_GET 				0x34 //获取报警输出参数
#define NET_SDVR_ALARMOUTCFG_SET 				0x35 //设置报警输出参数
#define NET_SDVR_TIMECFG_GET 					0x36 //获取主机时间
#define NET_SDVR_TIMECFG_SET 					0x37 //设置主机时间
#define NET_SDVR_USERCFG_GET 					0x38 //获取用户权限
#define NET_SDVR_USERCFG_SET 					0x39 //设置用户权限
#define NET_SDVR_SERIAL_GET 					0x3A //获取串口参数
#define NET_SDVR_SERIAL_SET 					0x3B //设置串口参数
#define NET_SDVR_MD5ID_GET 						0x40 //获取MD5特征码,登陆时使用
#define NET_SDVR_REFRESH_FLASH 					0x41 //更新DVR FLASH（参数保存）
#define NET_SDVR_RECOVER_DEFAULT 				0x42 //恢复DVR缺省参数
#define NETCOM_QUERY_RECFILE 					0x45 //PC向DVR发送的查询录像文件段信息请求
#define NETCOM_VOD_RECFILE_REQ 					0x49 //PC向DVR发送的点播录像文件请求
#define NETCOM_VOD_RECFILE_REQ_EX 				0x4a //PC向DVR发送的点播按时间段播放录像文件请求
#define NETCOM_VOD_RECFILE_CTL 					0x4c //视频点播流控制
#define NETCOM_VOD_RECFILE_END 					0x4f //PC向DVR发送的点播结束
#define NETCOM_BACKUP_RECFILE_REQ 				0x51 //PC向DVR发送的备份录像文件请求
#define NETCOM_BACKUP_FILEHEAD 					0x5a //DVR向PC发送的备份文件头标志(在备份的码流中)
#define NETCOM_BACKUP_END 						0x5c //DVR向PC发送的备份文件结束标志(在备份的码流中)
#define NETCOM_BACKUP_RECFILE_OK 				0x53 //DVR向PC发送的备份录像文件请求成功
#define NETCOM_BACKUP_RECFILE_NOOK 				0x55 //DVR向PC发送的备份录像文件请求失败
#define NET_SDVR_DDNS_GET 						0x60 //获取DDNS
#define NET_SDVR_DDNS_SET 						0x61 //设置DDNS  sDDNSState=1时候登陆
#define NET_SDVR_PPPoE_GET 						0x62 //获取PPPoE
#define NET_SDVR_PPPoE_SET 						0x63 //设置PPPoE  sPPPoEState=1时候拨号
#define NET_SDVR_SERVERCFG_GET 					0x64 //获取平台服务器参数
#define NET_SDVR_SERVERCFG_SET 					0x65 //设置平台服务器参数
#define NET_SDVR_CLEARALARM 					0x66 //报警清除
#define NET_SDVR_GET_PHOTO 						0x70 //远程抓图
#define NET_SDVR_GET_DVRTYPE 					0x71 //获取设备类型
#define NET_SDVR_SET_DVRTYPE 					0x72 //设置设备类型
#define NET_SDVR_SET_PRESETPOLL 				0x73 //设置多预置点轮巡
#define NET_SDVR_GET_PRESETPOLL 				0x74 //获取多预置点轮巡
#define NET_SDVR_SET_VIDEOSYS 					0x75 //设置视频制式
#define NET_SDVR_GET_VIDEOSYS 					0x76 //获取视频制式
//#define NET_SDVR_PTZTYPE_GET 					0x79 //获取云台协议
#define NET_SDVR_SHAKEHAND 						0xFF //握手协议（心跳保持）
#define NET_SDVR_GET_REAL_DEFENCE 				0x7A //获取实时布防状态
#define NET_SDVR_SET_REAL_DEFENCE 				0x7B //设置实时布防（即从设防开始启动）
#define NET_SDVR_IFRAMERATE_GET 				0x84 //获取I帧帧间隔
#define NET_SDVR_IPCWIRELESS_SET 				0x87 //设置IPC无线参数配置
#define NET_SDVR_IPCWIRELESS_GET 				0x88 //获取IPC无线参数配置
//#define NET_SDVR_IFRAMERATE_SET 				0x89 //设置I帧帧间隔
#define NET_SDVR_NTPCONFIG_SET 					0x90 //设置NTP配置
#define NET_SDVR_NTPCONFIG_GET 					0x91 //获取NTP配置
#define NET_SDVR_POLLCONFIG_SET 				0x94 //设置轮巡配置
#define NET_SDVR_POLLCONFIG_GET 				0x95 //获取轮巡配置
#define NET_SDVR_IPCWORKPARAM_GET 				0xB0 //获取IPC工作参数
#define NET_SDVR_IPCWORKPARAM_SET 				0xB1 //设置IPC工作参数
#define NET_SDVR_DEVICECFG_GET_EX 				0xC6 //获取设备信息(扩展)
#define NET_SDVR_DEVICECFG_SET_EX  				0xC7 //设置设备信息(扩展)
#define NET_SDVR_LOG_QUERY_EX 					0xC3 //NVR日志信息查询
/////////////////////NOt SUPPORT/////////////////////
#define NETCOM_QUERY_RECFILE_EX 				0x46 //PC向DVR发送的查询录像文件段信息请求(按卡号查询)
#define NET_SDVR_SET_SERIALID 					0x67 //设置序列号
#define NET_SDVR_GET_SERIALID 					0x68 //获取序列号
#define NET_SDVR_GET_VLOSTSTATUS 				0x69 //获取视频丢失状态
#define NET_SDVR_DECODERCUSTOMIZE_GET 			0x77 //获取自定义球机协议
#define NET_SDVR_DECODERCUSTOMIZE_SET 			0x78 //设置自定义球机协议
#define NET_SDVR_GET_PHOTO_TIMEWAIT 			0x7C //商铺项目延时抓拍
#define NET_SDVR_BUZCTRL 						0x80 //蜂鸣器控制
#define NET_SDVR_BUZSTATUS 						0x81 //蜂鸣器状态
#define NET_SDVR_SMTPCONFIG_SET 				0x92 //设置SMTP配置
#define NET_SDVR_SMTPCONFIG_GET 				0x93 //获取SMTP配置
#define NET_SDVR_VIDEOMATRIX_SET 				0x96 //设置视频矩阵
#define NET_SDVR_VIDEOMATRIX_GET 				0x97 //获取视频矩阵设置
#define NET_SDVR_GET_VCOVER_DETECT 				0x98 //获取遮挡报警设置
#define NET_SDVR_SET_VCOVER_DETECT 				0x99 //设置遮挡报警设置
#define NET_SDVR_ALARM_CONNECT 					0xA0 //建立智能报警上报链路
#define NET_SDVR_ALARM_REPORT 					0xA1 //智能报警上报消息
#define NET_SDVR_INTELLECTCFG_SET 				0xA2 //智能报警设置
#define NET_SDVR_INTELLECTCFG_GET 				0xA3 //智能报警查询
#define NET_SDVR_INTELLECTCFG_ALGORITHM_RESET 	0xA4 //智能算法复位
#define NET_SDVR_GET_REAL_DEFENCE_EX 			0xA5 //获取实时布防状态(通用命令)
#define NET_SDVR_SET_REAL_DEFENCE_EX 			0xA6 //设置实时布防、撤防状态(通用命令)
#define NET_SDVR_GET_DISCONNECT_ALMINFO 		0xA7 //获取主机掉线期间的报警信息
#define NET_SDVR_GET_CHN_DEV_TYPE 				0xC0 //NVR获取通道对应设备类型
#define NET_SDVR_GET_PLATFORM_PARAM 			0xF0 //获取平台参数
#define NET_SDVR_SET_PLATFORM_PARAM 			0xF1 //设置平台参数
/////////////////////////////////////////////////////////////////////////////////////
#define NET_SDVR_AUDIO_START 					0xE0
#define NET_SDVR_AUDIO_STOP 					0xE1
#define NET_HXHT_QUERY_RECFILE 					0xE2
#define NET_SDVR_AUDIO_SET 						0x8A
#define NET_SDVR_AUDIO_GET 						0x8B
#define NET_SDVR_SNAP_SET 						0x8C
#define NET_SDVR_SNAP_GET 						0x8D
#define NET_SDVR_PROTOCL_SET                    0x8F

#define NET_SDVR_GET_PORTMAP                    0xD0


#define STREAM_MAIN		1
#define STREAM_SECOND	2
#define STREAM_THIRD	3

#if 0
#define HB_S16            HB_S16
#define HB_U16           unsigned HB_S16
#define HB_U32            unsigned HB_S32
#endif

#define MACADDR_LEN		6
#define MAX_DAYS		8
#define MAX_TIMESEGMENT	2

//命令头
typedef struct _tagCMD_HEAD
{
	HB_U32	flag;              	//固定为 “SDVR”
	HB_U32	userid;        		//用户ID：登陆后返回的ID
	HB_U16	cmd;            	//命令：见表2-1
	HB_U16	len;          		//数据buff的长度(不包括STRUCT_CMD_HEAD长度)
	HB_U16	result;        		//DVR返回的结果 0-失败  1-成功
	union
	{
		HB_S16  nErrorCode;    	//失败时，当错误码处理
		HB_U16 nLenHeigh;    	//前端抓图等一些命令，使用该字段表示长度的高16位
    }u;
}CMD_HEAD_OBJ, *CMD_HEAD_HANDLE;

//#define MAX_CH 16 // for max channel num
#define NAME_LEN        	32
#define PASSWD_LEN        	16
#define SERIALNO_LEN    	48
#define CH_NAME_LEN        	NAME_LEN << 4

//登录请求消息
typedef struct _tagSDVR_LOGUSER
{
    HB_CHAR		UserName[32];      		//用户名：按字符串处理，以’\0’结束，需要存储’\0’
    HB_CHAR   	PassWord[16];          	//密码（MD5加密了的）：按字符串处理，以’\0’结束，需要存储’\0’
    HB_U32		dwNamelen;          	//有效的用户名长度
    HB_U32		dwPWlen;          		//有效的密码长度，（MD5加密返回的长度）
}SDVR_LOGUSER_OBJ, *SDVR_LOGUSER_HANDLE;
//STRUCT_SDVR_LOGUSER;

//登录应答消息
typedef struct _tagSDVR_DEVICE
{
    HB_CHAR   	sSerialNumber[48];			//序列号：主机端必须返回，从前往后处理，其余补零
    HB_U8    	byAlarmInPortNum;			//DVR报警输入个数
    HB_U8    	byAlarmOutPortNum;			//DVR报警输出个数
    HB_U8    	byDiskNum;					//存储设备个数：硬盘/SD卡个数
    HB_U8    	byProtocol;				//协议版本  0x20
    HB_U8    	byChanNum;					//DVR通道个数
    HB_U8    	byStartChan;				//保留
    HB_CHAR		sDvrName[32];				//主机名：须以’\0’结束
    HB_CHAR		sChanName[128][32];		//通道名称：须以’\0’结束
}SDVR_DEVICE_OBJ, *SDVR_DEVICE_HANDLE;


//实时视频应答消息
typedef struct _tagSDVR_REALPLAY
{
	HB_CHAR		byChannel;        			//通道号
    HB_CHAR		byLinkMode;        			// 0-主码流 1-子码流
    HB_CHAR		byMultiCast;        		//是否多播（当主机设置了多播模式，使用UDP方式开视频的时候会自动选择多播）
    HB_U32   	sMultiCastIP;       		//多播IP地址(大字节序)
    HB_CHAR		OSDCharEncodingScheme;    	// OSD字符的编码格式
    HB_CHAR		reserve[11];        		//保留
    HB_U16		wPort;            			//多播端口(小字节序)
}SDVR_REALPLAY_OBJ, *SDVR_REALPLAY_HANDLE;


//关闭实时视频请求消息
typedef struct _tagSDVR_REALPLAY_STOP
{
    HB_CHAR 	byChannel;             //通道号
    HB_CHAR 	byLinkMode;            //0-主码流 1-子码流
    HB_U16 		wPort;                 //本地端口
}SDVR_REALPLAY_STOP_OBJ, *SDVR_REALPLAY_STOP_HANDLE;


//视频参数设置请求消息
typedef struct _tagSDVR_VIDEOPARAM
{
	HB_U32	dwBrightValue;        	//亮度：		取值[0, 127]
	HB_U32	dwContrastValue;        //对比度：	取值[0, 127]
	HB_U32	dwSaturationValue;      //饱和度：	取值[0, 127]
	HB_U32	dwHueValue;            	//色度：   	 取值[0, 127]
}SDVR_VIDEOPARAM_OBJ, *SDVR_VIDEOPARAM_HANDLE;


typedef struct _tagSDVR_SCHEDULE_VIDEOPARAM
{
	HB_U16					wStartTime;		//开始时间，高8位表示小时[0,23] 低8位表示分钟[0,59]
    HB_U16					wEndTime;		//结束时间，高8位表示小时[0,23] 低8位表示分钟[0,59]
    SDVR_VIDEOPARAM_OBJ		VideoParam;
}SDVR_SCHEDULE_VIDEOPARAM_OBJ, *SDVR_SCHEDULE_VIDEOPARAM_HANDLE;


typedef struct _tagSDVR_VIDEOEFFECT
{
    HB_CHAR    						byChannel;            	//通道号
    SDVR_SCHEDULE_VIDEOPARAM_OBJ	Schedule_VideoParam[2];	//可设置两个时间段 不在时间段内的按照默认参数调整视频
    SDVR_VIDEOPARAM_OBJ	  			Default_VideoParam; 	//默认值
}SDVR_VIDEOEFFECT_OBJ, *SDVR_VIDEOEFFECT_HANDLE;


//云台控制请求消息
typedef struct _tagSDVR_PTZ_CTRL
{
	HB_CHAR	byPort;			//云台号（对应通道号）
	HB_U32	dwPTZCommand;  	//控制命令（见下表） 为0x00010028则停止
    HB_U32	dwStop;			//保留
    HB_U32	dwIndex;		//预制点号(受球机有效值范围影响)[0, 255]
    HB_U32	dwSpeed;		//控制速度 [0, 255] ，0的速度是最慢的。
}SDVR_PTZ_CTRL_OBJ, *SDVR_PTZ_CTRL_HANDLE;


//设置云台轮巡请求消息
typedef struct _tagHB_SDVR_PRESETPOLL
{
	HB_U32	byChannel;		//设置通道 [0, n-1] n:通道数
    HB_U16	Preset[16];		//预置点[1，254]，255是无效值，而有的球机0有效，有的球机0无效。如果预置点少于16个，多余的填255
    HB_U16	PresetPoll;		//多预置点轮巡开启或关闭表示(0, 关闭； 1，开启)
    HB_U16	presettime;		//多预置点轮巡间隔时间(单位秒) [1, 99]
}HB_SDVR_PRESETPOLL_OBJ, *HB_SDVR_PRESETPOLL_HANDLE;


//透明云台请求消息
typedef struct _tagSDVR_PTZ_TRANS
{
	HB_CHAR	byPort; 		// (云台号)
	HB_U32	dwSize;			//云台控制码有效长度[1, 256]
	HB_CHAR	sCtrlBuf[256];	//云台控制码数据
}SDVR_PTZ_TRANS_OBJ, *SDVR_PTZ_TRANS_HANDLE;


typedef struct _tagSDVR_RECFIND
{
	HB_CHAR 	byChannel;	//通道号[0, n－1]，n:通道数
	HB_CHAR 	dwType;		//查询的录像类型，下表是值和录像类型对应关系
	MFS_TIME 	starttime;	//查询的开始时间
	MFS_TIME 	endtime;	//查询的结束时间
	HB_U16 		dwStart;	//从第几个文件开始查询，一般为0（用于由于时间段内文件数过多而分多次查询的情况，第一次查询为0，以后递加成功查询出的文件数）
	HB_U16 		dwNum;		//一次查询的个数，现在定义是100；协议二中该项保留
}SDVR_RECFIND_OBJ, *SDVR_RECFIND_HANDLE;


//远程录像查询应答消息
typedef struct _tagSDVR_MFS_RECSEG_INFO
{
    MFS_TIME		begin_time, end_time;  //录像段的开始时间，结束时间，结构同上，年份-2000
    HB_U32			lengh;                 //文件大小
    HB_CHAR			ch;                    //录像的通道号
    HB_CHAR			type;                  //文件类型
    HB_CHAR			cRes1;                 //保留
    HB_CHAR			cRes2;                 //保留
}SDVR_MFS_RECSEG_INFO_OBJ, *SDVR_MFS_RECSEG_INFO_HANDLE;


typedef struct	_tagSDVR_RECINFO
{
    HB_U32 						Totalnum;		//查找到的文件个数
    SDVR_MFS_RECSEG_INFO_OBJ	recdata[100];
}SDVR_RECINFO_OBJ, *SDVR_RECINFO_HANDLE;


//远程录像点播请求消息
typedef struct _tagSDVR_VOD
{
    HB_CHAR 		Channel;        //通道号    [0, n-1],n:通道数
    HB_CHAR 		dwType;        	//点播类型
    MFS_TIME 		dwtime;   		//点播开始时间，同录像查询请求消息中定义，年份-2000
    HB_CHAR 		btRes1;         //保留
    HB_CHAR 		btRes2;         //保留
}SDVR_VOD_OBJ, *SDVR_VOD_HANDLE;


//远程录像点播应答消息
typedef struct _tagSDVR_VOD_ANS
{
    HB_U32  dwVodID;
}SDVR_VOD_ANS_OBJ, *SDVR_VOD_ANS_HANDLE;


//远程录像点播请求消息
typedef struct _tagSDVR_VOD_EX
{
    HB_CHAR 	Channel;            //通道号 0 1 2 3[0, n-1], n:通道数
    HB_CHAR 	dwType;            	//点播类型
    MFS_TIME 	dwtime_start;    	//点播开始时间
    MFS_TIME 	dwtime_end;    		//点播结束时间，时间跨度一天之内
    HB_CHAR 	btRes1;             //保留
    HB_CHAR 	btRes2;             //保留
}SDVR_VOD_EX_OBJ, *SDVR_VOD_EX_HANDLE;


//远程录像点播控制请求消息
typedef struct _tagSDVR_VODCTL
{
	HB_U32		ID;        		//视频点播ID，在远程录像点播应答消息给出。
    HB_CHAR		ctrl;        	//0-正常1-暂停 2-快进 3- 快退 4-帧进 5-慢放
    HB_CHAR		speed;        	//快进快退慢放速度(协议二中0~3)
    HB_CHAR		seekflag;    	//拉进度条标志 (协议二中 0:非进度条控制 1:进度条控制)
    HB_CHAR		pecent;        	//进度百分比 (seekflag = 1时有效,  0~99)
}SDVR_VODCTL_OBJ, *SDVR_VODCTL_HANDLE;


//远程录像点播结束请求消息
typedef struct _tagSDVR_VODSTREAM
{
	HB_U32	vodid;    //视频点播ID，在远程录像点播应答消息给出。
}SDVR_VODSTREAM_OBJ, *SDVR_VODSTREAM_HANDLE;


//远程录像文件备份请求消息
typedef struct _tagSDVR_BACKINFO
{
	HB_CHAR		byChannel;           //通道号 [0, n-1], n:通道数
	HB_CHAR		type;                //备份类型：0-手动；1-定时；2-移动；3-探头报警；0x0f-所有录像
	MFS_TIME 	starttime;        	 //开始时间，结构体同上，注意年份-2000
	MFS_TIME 	endtime;       		 //结束时间
}SDVR_BACKINFO_OBJ, *SDVR_BACKINFO_HANDLE;


//远程录像文件备份文件头标志消息
typedef struct _tagSDVR_FILEINFO
{
	HB_U32 		port;				//通道号
    HB_U32 		filelen;			//本文件长度  以B为单位
    MFS_TIME 	filestarttime;		//本录像文件开始时间
    MFS_TIME 	fileendtime;		//本录像文件结束时间
    HB_U32 		totalFileLen;		//总文件长度，表示NETCOM_BACKUP_RECFILE_REQ命令所给的时间段内的总长度(注：该时间段内有可能有多个文件)，以KB为单位
}SDVR_FILEINFO_OBJ, *SDVR_FILEINFO_HANDLE;


//服务器型号获取应答消息
typedef struct _tagSDVR_INFO
{
	HB_U32	dvrtype;				//7004 8004 2201 2004
	HB_U16	device_type;			// 设备类型		枚举NET_DEV_TYPE_E
    HB_U16	memory_size;			// 内存大小		枚举NET_MEMSIZE_E
    HB_U32	reserve2;			    // 保留
}SDVR_INFO_OBJ, *SDVR_INFO_HANDLE;



//获取报警输出状态应答消息
typedef struct _tagSDVR_ALARM_OUT
{
	HB_CHAR	byAlarm; 				//报警输出状态 0-不报警 1-报警
	HB_U16	wAlarm;  				//报警输出状态 bit0-15代表16个报警输出, 0-状态不变 1-执行byAlarm操作
}SDVR_ALARM_OUT_OBJ, *SDVR_ALARM_OUT_HANDLE;


//设置/获取远程手动录像请求消息
typedef struct _tagSDVR_MANURECORD
{
	HB_U8	channel[128];        	//通道录像状态 1.录像 0.停止录像
}SDVR_MANURECORD_OBJ, *SDVR_MANURECORD_HANDLE;


//网络键盘请求消息
typedef struct _tagSDVR_NETKEY
{
	HB_U32	dwKey;       			//键值，见下表（3-5）按键定义
	HB_U32	dwKeyCode;   			//参数（当键值为字母或数时使用）
}SDVR_NETKEY_OBJ, *SDVR_NETKEY_HANDLE;


//获取设备工作状态应答消息
typedef struct _tagSDVR_DISKSTATE
{
    HB_U32	dwVolume;            	//硬盘的容量（MB）
    HB_U32	dwFreeSpace;			//硬盘的剩余空间（MB）
    HB_U32	dwHardDiskStatic;		//硬盘状态（dwVolume有值时有效） 0-正常 1-磁盘错误 2-文件系统出错
}SDVR_DISKSTATE_OBJ, *SDVR_DISKSTATE_HANDLE;


typedef struct _tagSDVR_CHANNELSTATE
{
	HB_CHAR		byRecordStatic;			// 通道是否在录像,0-不录像,1-录像
	HB_CHAR		bySignalStatic;			// 连接的信号状态,0-正常,1-信号丢失

    HB_CHAR 	byHardwareStatic;		// 保留
    HB_CHAR 	reservedData;
    HB_U32 		dwBitRate;				// 实际码率

    HB_U32 		dwLinkNum;				// 客户端连接的个数：同一通道当前时间的实时流的连接数。不分主子码流，同一IP多个连接算多个连接
    HB_U32 		dwClientIP[32];			// 保留
}SDVR_CHANNELSTATE_OBJ, *SDVR_CHANNELSTATE_HANDLE;


typedef struct _tagSDVR_WORKSTATE
{
    HB_U32 						dwDeviceStatic;         // 保留
    SDVR_DISKSTATE_OBJ  		struHardDiskStatic[16];	//硬盘状态
    SDVR_CHANNELSTATE_OBJ 		struChanStatic[128];    //通道的状态
    HB_U32  					alarmin_status[128];	//报警输入端口的状态
    HB_U32  					alarmout_status[128];	//报警输出端口的状态
    HB_U32  					dwLocalDisplay;			// 保留
}SDVR_WORKSTATE_OBJ, *SDVR_WORKSTATE_HANDLE;


//日志信息查询请求消息
typedef struct _tagHB_SDVR_REQLOG
{
	HB_U16	dwYear;
    HB_CHAR	dwMonth;
    HB_CHAR	dwDay;
    HB_U16	dwStart;	//查询从第几条开始，一般为0。
    HB_U16	dwnum;  	//一次查询个数，最多为100。
}HB_SDVR_REQLOG_OBJ, *HB_SDVR_REQLOG_HANDLE;


#define MAX_LOGO_NUM 100

typedef struct _tagMFS_LOG_DAT_NET
{
    MFS_TIME		time;			//结构体同前面定义
    HB_U8			type;			// 类型
    HB_U8			operate;		// 操作码
    HB_CHAR			account[18];	// 用户
    HB_U32			ip_addr;		// 0-Local other-ip
    HB_U32			input;			// 事件输入输出
    HB_U32			output;
    HB_CHAR			data[28];		// 其他信息
}MFS_LOG_DAT_NET_OBJ, *MFS_LOG_DAT_NET_HANDLE;


typedef struct _tagSDVR_LOGINFO_NET
{
    HB_U32				Totalnum;
    MFS_LOG_DAT_NET_OBJ logdata[MAX_LOGO_NUM];
}SDVR_LOGINFO_NET_OBJ, *SDVR_LOGINFO_NET_HANDLE;


//心跳应答消息
typedef struct _tagSDVR_ALARM
{
	HB_U8	alarmin_status[128];		//探头报警0-无报警  1-有报警
    HB_U8	vlost_status[128];			//视频丢失0-无报警  1-有报警
    HB_U8	motion_status[128];			//移动报警0-无报警  1-有报警
    HB_U8	hide_status[128];			//遮挡报警0-无报警  1-有报警
    HB_U8	disk_status[16];			//硬盘错误0-无报警  1-有报警
}SDVR_ALARM_OBJ, *SDVR_ALARM_HANDLE;


//格式化硬盘应答消息
typedef struct _tagSDVR_FORMAT
{
	HB_U32	dwCurrentFormatDisk;	//正在格式化的硬盘号[0, 15]
	HB_U32	dwCurrentDiskPos;		//正在格式化的硬盘进度[0, 100]
	HB_U32	dwFormatStatic;			//格式化状态 0-正在格式化 1-格式化完成 2-格式化错误 3-要格式化的磁盘不存在 4-格式化中途错误 5-磁盘正在被使用
}SDVR_FORMAT_OBJ, *SDVR_FORMAT_HANDLE;


//获取设备信息应答消息
typedef struct _tagSDVR_DEVICEINFO
{
	HB_U32		dwSize;                        	//长度（结构体大小）―――sizeof(STRUCT_SDVR_DEVICEINFO)
    HB_CHAR		sDVRName[32];                  	//DVR名称, 以’\0’结束字符串
    HB_U32		dwDVRID;                    	//保留   还未使用
    HB_U32		dwRecycleRecord;                //协议二: //录像覆盖策略 0-循环覆盖 1-提示覆盖
    HB_CHAR		sSerialNumber[48];				//序列号
    HB_CHAR		sSoftwareVersion[16];			//软件版本号以’\0’结束字符串协议二: （主机型号 软件版本号）
    HB_CHAR		sSoftwareBuildDate[16];			//软件生成日期以’\0’结束字符串协议二:（Build 100112）
    HB_U32		dwDSPSoftwareVersion;        	//DSP软件版本   还未使用
    HB_CHAR		sPanelVersion[16];				//前面板版本，以’\0’结束字符串，IPC无
    HB_CHAR		sHardwareVersion[16];			//协议二: 当软件版本号超过16字节时会使用作为主机型号显示
    HB_CHAR		byAlarmInPortNum;				//DVR报警输入个数
    HB_CHAR		byAlarmOutPortNum;				//DVR报警输出个数
    HB_CHAR		byRS232Num;                    	//保留
    HB_CHAR		byRS485Num;                    	//保留
    HB_CHAR		byNetworkPortNum;				//保留
    HB_CHAR		byDiskCtrlNum;					//保留
    HB_CHAR		byDiskNum;						//DVR 硬盘个数
    HB_CHAR		byDVRType;        				//DVR类型, 1:DVR 2:ATM DVR 3:DVS 4:IPC 5:NVR （建议使用//NET_SDVR_GET_DVRTYPE命令）
    HB_CHAR		byChanNum;                    	//DVR 通道个数[1,128]
    HB_CHAR 	byStartChan;                    //保留
    HB_CHAR 	byDecordChans;					//保留    还未使用
    HB_CHAR 	byVGANum;						//保留    还未使用
    HB_CHAR 	byUSBNum;                    	//保留    还未使用
}SDVR_DEVICEINFO_OBJ, *SDVR_DEVICEINFO_HANDLE;


//获取网络信息应答消息
typedef struct _tagSDVR_ETHERNET
{
    HB_U32 		dwDVRIP;						//DVR IP地址
    HB_U32 		dwDVRIPMask;					//DVR IP地址掩码
    HB_U32 		dwNetInterface;					//网络接口1-10MBase-T 2-10MBase-T全双工3-100MBase-TX 4-100M全双工5-10M/100M自适应
    HB_U16 		wDVRPort;						//端口号
    HB_CHAR 	byMACAddr[MACADDR_LEN];        	//服务器的物理地址
}SDVR_ETHERNET_OBJ, *SDVR_ETHERNET_HANDLE;



typedef struct _tagSDVR_NETINFO
{
    HB_U32 					dwSize;				//长度（结构体大小）
    SDVR_ETHERNET_OBJ 		struEtherNet[2];	//以太网口 协议二: （T/IPC系列只使用了struEtherNet[0]，NVR都有使用）
    HB_U32 					dwManageHostIP;		//远程管理主机地址 协议二: （当前操作的客户端IP）使用大字节序
    HB_U16 					wManageHostPort;    //协议二: //远程管理主机端口（当前操作的客户端端口）使用大字节序
    HB_U32 					dwDNSIP;            //DNS服务器地址
    HB_U32 					dwMultiCastIP;      //多播组地址
    HB_U32 					dwGatewayIP;		//网关地址
    HB_U32 					dwNFSIP;			//保留
    HB_CHAR 				sNFSDirectory[128]; //保留
    HB_U32 					dwPPPOE;            //0-不启用,1-启用
    //协议二:
    //获取时为PPPOE状态 0-连接不成 1-连接成功
    //设置时为PPPOE功能使能 0-关闭 1-启用

    HB_CHAR 					sPPPoEUser[32];                        //PPPoE用户名
    HB_CHAR 					sPPPoEPassword[16];                    //PPPoE密码
    HB_U32 					dwPPPoEIP;                        //PPPoE IP地址(只读)
    HB_U16 					wHttpPort;                            //HTTP端口号
}SDVR_NETINFO_OBJ, *SDVR_NETINFO_HANDLE;


//获取通道信息请求消息
typedef struct _tagSDVR_HANDLEEXCEPTION
{
	HB_U32		dwHandleType;    	//按位 2-声音报警5-监视器最大化 //6-邮件上传
	HB_CHAR		alarmOut[128];		//报警输出触发通道
}SDVR_HANDLEEXCEPTION_OBJ, *SDVR_HANDLEEXCEPTION_HANDLE;


typedef struct _tagSDVR_SCHEDTIME
{
    HB_CHAR    byEnable;			// 布防时间使能  0-撤防 1-布防
    HB_CHAR    byStartHour;		//开始小时 0-23
    HB_CHAR    byStartMin;			//开始分钟 0-59
    HB_CHAR    byStopHour;			//结束小时  0-23
    HB_CHAR    byStopMin;			//结束分钟  0-59
}SDVR_SCHEDTIME_OBJ, *SDVR_SCHEDTIME_HANDLE;
			//全天布防 00:00 – 23:59

typedef struct _tagSDVR_MOTION
{
	HB_CHAR						byMotionScope[18][22];	//侦测区域,共有22*18个小宏块,为1表示该宏块是移动侦测区域,0-表示不是
    HB_CHAR						byMotionSensitive;		//移动侦测灵敏度, 0 - 5,越高越灵敏
    HB_CHAR						byEnableHandleMotion;	// 移动侦测布防使能 0-撤防 1-布防
    SDVR_HANDLEEXCEPTION_OBJ 	struMotionHandleType;	//报警联动策略
    SDVR_SCHEDTIME_OBJ 			struAlarmTime[8][2];	//布防时间
    HB_CHAR 					record_channel[128];	//联动的录像通道，为0-不联动 1-联动
}SDVR_MOTION_OBJ, *SDVR_MOTION_HANDLE;


typedef struct _tagSDVR_HIDEALARM
{
    HB_U32 						dwEnableHideAlarm;						//0，不使能； 1，使能。
    HB_U16 						wHideAlarmAreaTopLeftX;					//遮挡区域的x坐标 [0, 实际宽－1]
    HB_U16 						wHideAlarmAreaTopLeftY;					//遮挡区域的y坐标 [0, 实际高－1]
    HB_U16 						wHideAlarmAreaWidth;					//遮挡区域的宽 [16, 实际宽]
    HB_U16 						wHideAlarmAreaHeight; 					//遮挡区域的高[16, 实际高]
    SDVR_HANDLEEXCEPTION_OBJ 	strHideAlarmHandleType;					//处理方式 保留
    SDVR_SCHEDTIME_OBJ 			struAlarmTime[MAX_DAYS][MAX_TIMESEGMENT];//布防时间保留
}SDVR_HIDEALARM_OBJ, *SDVR_HIDEALARM_HANDLE;


typedef struct _tagSDVR_VILOST
{
    HB_CHAR 					byEnableHandleVILost;	//视频丢失报警使能 0-不报警 1-报警；为0，可不关注后2字段
    SDVR_HANDLEEXCEPTION_OBJ 	strVILostHandleType;    //处理方式
    SDVR_SCHEDTIME_OBJ 			struAlarmTime[8][2];	//布防时间，[0][0,1]表示每天，[1～7][0,1]表示星期; [0][0,1]有被使能则按每天处理，不关注星期几
}SDVR_VILOST_OBJ, *SDVR_VILOST_HANDLE;


typedef struct _tagSDVR_SHELTER
{
	HB_U16	wHideAreaTopLeftX;	//遮盖区域的x坐标  0~704
    HB_U16 	wHideAreaTopLeftY;	//遮盖区域的y坐标  0~576
    HB_U16	wHideAreaWidth;		//遮盖区域的宽 0~704
    HB_U16	wHideAreaHeight;	//遮盖区域的高 0~576
}SDVR_SHELTER_OBJ, *SDVR_SHELTER_HANDLE;


typedef struct _tagSDVR_PICINFO
{
	HB_CHAR 				byChannel;			//通道号 [0, n－1] n:通道数
    HB_U32 					dwSize;				//长度（结构体大小）
    HB_CHAR 				sChanName[32];		// 通道名 以’\0’结束字符串
    HB_U32 					dwVideoFormat;  	// 保留
    HB_CHAR 				byBrightness; 		// 亮度   0~255
    HB_CHAR 				byContrast;     	// 对比度 0~255
    HB_CHAR 				bySaturation;  		// 饱和度 0~255
    HB_CHAR 				byHue;          	// 色度   0~255
    HB_U32 					dwShowChanName;		// 是否显示通道名 0-显示 1-不显示
    HB_U16 					wShowNameTopLeftX;	// 通道名称显示位置的x坐标 左->右 0~视频实际宽度－通道名长度
    HB_U16 					wShowNameTopLeftY;	// 通道名称显示位置的y坐标 上->下 0~视频实际高度－字体高度
    SDVR_VILOST_OBJ 		struVILost;			// 视频信号丢失报警
    SDVR_MOTION_OBJ 		struMotion;			// 移动侦测
    SDVR_HIDEALARM_OBJ 		struHideAlarm;		// 遮挡报警
    HB_U32 					dwEnableHide;		// 视频遮挡使能 ,0-不遮挡,1-遮挡
    SDVR_SHELTER_OBJ    	struShelter[4];		// 视频遮挡区域
    HB_U32 					dwShowTime; 		// 是否显示时间 0-显示 1-不显示
    HB_U16 					wOSDTopLeftX;		// 时间osd坐标X [0, 实际宽－时码长度]
    HB_U16 					wOSDTopLeftY;		// 时间osd坐标Y[0, 实际高－字体高度]
    HB_CHAR 				byOSDType;			// 格式及语言，为0表示默认(需确认)，其他定义再补充
    HB_CHAR 				byDispWeek;			// 是否显示星期 0-显示 1-不显示
    HB_CHAR 				byOSDAttrib;		// 通道名 1-不透明 2-透明（只针对PC端显示）
}SDVR_PICINFO_OBJ, *SDVR_PICINFO_HANDLE;


//获取数据流信息请求消息
typedef struct _tagSDVR_COMPRESSION
{
	HB_CHAR	byStreamType;	//码流类型    0-无音频 ,1-有音频
	HB_CHAR	byResolution;	//分辨率    0-CIF 1-HD1, 2-D1 协议二:增加  3-QCIF 4-720p 5-1080p 6.768x432
	HB_CHAR	byBitrateType;	//码率类型    0:变码率，1:定码率
	HB_CHAR	byPicQuality;	//图象质量    1-最好 2-次好 3-较好 4-一般5-较差 6-差
	HB_U32	dwVideoBitrate; //协议一:视频码率 0-100K 1-128K，2-256K，3-512K，4-1M，5-2M，6-3M，7-4M，8-6M，9-8M，10-12M ,11-自定义
    //协议二://视频码率 0-100K 1-128K，2-256K，3-512K，4-1M，5-1.5M，6-2M，7-3M, 8-4M 其他：码率值（kbps）有效范围 30~2^32
    //大于等于32，以K为单位
    HB_U32	dwVideoFrameRate;    //帧率        2 至 25 考虑到30帧 [2, 30],可能非线性，与主机有关
}SDVR_COMPRESSION_OBJ, *SDVR_COMPRESSION_HANDLE;


typedef struct _tagSDVR_COMPRESSINFO
{
	HB_CHAR 				byChannel;		//通道号
	HB_U32 					dwSize;
	HB_CHAR 				byRecordType;	//0x0:手动录像，0x1:定时录象，0x2:移动侦测，0x3:报警，0x0f:所有类型
	SDVR_COMPRESSION_OBJ 	struRecordPara;	//录像流（主码流）
	SDVR_COMPRESSION_OBJ 	struNetPara;    //网传流（子码流）
}SDVR_COMPRESSINFO_OBJ, *SDVR_COMPRESSINFO_HANDLE;


//获取定时录像信息应答消息
typedef struct _tagSDVR_RECORDSCHED
{
    SDVR_SCHEDTIME_OBJ 	struRecordTime;
    HB_CHAR 			byRecordType;		// 保留    协议二:未启用该项
    HB_CHAR 			reservedData[3];	// 保留
}SDVR_RECORDSCHED_OBJ, *SDVR_RECORDSCHED_HANDLE;


typedef struct _tagSDVR_RECORDDAY
{
    HB_U16	wAllDayRecord;	// 全天录像
    HB_CHAR	byRecordType;	// 录像类型
    HB_CHAR	reservedData;
}SDVR_RECORDDAY_OBJ, *SDVR_RECORDDAY_HANDLE;


typedef struct _tagSDVR_RECORDINFO
{
	HB_CHAR					byChannel;               //通道号[0, n-1]， n:通道数
    HB_U32					dwSize;
    HB_U32					dwRecord;               //是否录像 0-否 1-是
    SDVR_RECORDDAY_OBJ 		struRecAllDay[8];		//保留
    SDVR_RECORDSCHED_OBJ	struRecordSched[8][2];	//时间段
    HB_U32 					dwPreRecordTime;        // 保留
}SDVR_RECORDINFO_OBJ, *SDVR_RECORDINFO_HANDLE;


//获取云台协议应答消息
#ifndef _PTZ_TYPE
#define _PTZ_TYPE
typedef struct _tagSDVR_PTZTYPE
{
	HB_S32		ptznum;				//协议个数（限制为最多100个）
    HB_CHAR		ptztype[100][10];	//协议名列表―――0，unknow;
}SDVR_PTZTYPE_OBJ, *SDVR_PTZTYPE_HANDLE;

#endif

//获取云台配置信息应答消息
typedef struct _tagSDVR_DECODERINFO
{
	HB_CHAR	byChannel;				//通道号
	HB_U32	dwSize;
	HB_U32	dwBaudRate;            	// 波特率(bps)：50 75 110 150 300 600 1200 2400 4800 9600 19200 38400 57600 76800 115.2k
    //协议二:波特率 0-default,1-2400,2-4800,3-9600,4-19200,5-38400
    // DVR目前使用协议二，设置波特率时，用户既可以选择设定的值，也可以自己输入波特率的值
    //自定义取值范围[300，115200]。
    HB_CHAR 	byDataBit;              // 数据位 5 6 7 8
    HB_CHAR 	byStopBit;              // 停止位 1 2
    HB_CHAR 	byParity;               // 协议二: 校验位(0-NONE,1-ODD,2-EVEN,3-SPACE)
    HB_CHAR 	byFlowcontrol;          // 流控(0-无,1-Xon/Xoff,2-硬件)
    HB_U16 		wDecoderType;        	// 云台协议值，最好先NET_SDVR_PTZTYPE_GET获取该列表
    HB_U16 		wDecoderAddress;        // 解码器地址:[0 – 255]
    HB_CHAR 	bySetPreset[128];       // 保留
    HB_CHAR 	bySetCruise[128];       // 保留
    HB_CHAR 	bySetTrack[128];        // 保留
}SDVR_DECODERINFO_OBJ, *SDVR_DECODERINFO_HANDLE;


//获取串口配置信息应答消息
typedef struct _tagSDVR_PPPCFG
{
	HB_CHAR	sRemoteIP[16];			// 远端IP地址
    HB_CHAR	sLocalIP[16];			// 本地IP地址
    HB_CHAR	sLocalIPMask[16]; 		// 本地IP地址掩码
    HB_CHAR	sUsername[32];        	// 用户名
    HB_CHAR	sPassword[16]; 			// 密码
    HB_CHAR	byPPPMode;             	// PPP模式, 0－主动，1－被动
    HB_CHAR	byRedial;              	// 是否回拨 ：0-否,1-是
    HB_CHAR	byRedialMode;			// 回拨模式,0-由拨入者指定,1-预置回拨号码
    HB_CHAR	byDataEncrypt;			// 数据加密,0-否,1-是
    HB_U32	dwMTU;					// MTU
    HB_CHAR	sTelephoneNumber[32];	//电话号码
}SDVR_PPPCFG_OBJ, *SDVR_PPPCFG_HANDLE;


typedef struct _tagSDVR_SERIALINFO
{
	HB_CHAR				bySerialType; 	// 串口类型[1,2]; 1,232; 2,485.
	HB_U32				dwSize;
	HB_U32 				dwBaudRate;		// 波特率(bps)
	HB_CHAR 			byDataBit;		// 数据有几位 5－8
    HB_CHAR 			byStopBit; 		// 停止位 1-2
    HB_CHAR 			byParity;		// 校验 0－无校验，1－奇校验，2－偶校验;
    HB_CHAR 			byFlowcontrol;	// 0－无，1－软流控,2-硬流控
    HB_U32 				dwWorkMode;		// 保留
    SDVR_PPPCFG_OBJ 	struPPPConfig; 	// 保留
}SDVR_SERIALINFO_OBJ, *SDVR_SERIALINFO_HANDLE;




//报警输入参数查询    NET_SDVR_ALARMINCFG_GET
typedef struct _tagSDVR_ALARMININFO
{
    HB_U8						byAlarmInPort;				//报警输入端口号[0, n-1], n:报警输入个数
    HB_U32						dwSize;
    HB_U8						sAlarmInName[32];           // 报警输入端口名， 以’\0’结束字符串
    HB_U8 						byAlarmType;                // 探头类型 0-常闭1-常开
    HB_U8 						byAlarmInHandle;			// 是否处理 0，不处理； 1，处理
    SDVR_HANDLEEXCEPTION_OBJ 	struAlarmHandleType;		//处理方式
    SDVR_SCHEDTIME_OBJ 			struAlarmTime[8][2];		//布防时间
    HB_U8 						byRelRecordChan[128];		//报警触发的录象通道,为1表示触发该通道
    HB_U8 						byEnablePreset[128];		//是否调用预置点 仅用byEnablePreset[0]来判断;
    HB_U8 						byPresetNo[128];			//调用的云台预置点序号,一个报警输入可以调用多个通道的云台预置点, 0xff表示不调用预置点 [1, 254]
    HB_U8 						byEnableCruise[128];		// 保留
    HB_U8 						byCruiseNo[128];			// 保留
    HB_U8 						byEnablePtzTrack[128];		// 保留
    HB_U8 						byPTZTrack[128];			// 保留
    HB_U8 						byRecordTm;					// 报警录像时间 1-99秒
}SDVR_ALARMININFO_OBJ, *SDVR_ALARMININFO_HANDLE;

//DVR to PC 消息参数
typedef struct _tagSDVR_ALARMOUTINFO
{
    HB_CHAR 			byALarmoutPort;					//报警输出通道号 [0, n-1], n:报警输出端口数
    HB_U32 				dwSize;
    HB_CHAR 			sAlarmOutName[32];				// 名称 以’\0’结束字符串
    HB_U32 				dwAlarmOutDelay;                // 输出保持时间 单位秒 [2, 300]
    HB_CHAR 			byEnSchedule;					// 报警输出布防时间激活 0-屏蔽 1-激活
    SDVR_SCHEDTIME_OBJ 	struAlarmOutTime[8][2];
//报警输出激活时间段 ，结构体同获取报警输入信息应答消息中定义。
}SDVR_ALARMOUTINFO_OBJ, *SDVR_ALARMOUTINFO_HANDLE;

//STRUCT_SDVR_ALARMOUTINFO, *LPSTRUCT_SDVR_ALARMOUTINFO;
//报警输出参数查询    NET_SDVR_ALARMOUTCFG_GET

typedef struct _tagSDVR_TIME
{
    HB_U32	dwYear;        	//年
    HB_U32	dwMonth;        //月
    HB_U32	dwDay;        	//日
    HB_U32	dwHour;        	//时
    HB_U32	dwMinute;       //分
    HB_U32	dwSecond;       //秒
}SDVR_TIME_OBJ, *SDVR_TIME_HANDLE;
//STRUCT_SDVR_TIME;


//用户权限查询    NET_SDVR_USERCFG_GET
typedef struct _tagSDVR_USER_INFO
{
	HB_U8	sUserName[32];			//用户名 以’\0’结束字符串
	HB_U8	sPassword[16];			//密码 以’\0’结束字符串
	HB_U8	dwLocalRight[32];		//本地权限 1.数组0未使用；2.取值：0-无权限，1-有权限
    /*数组 1: 常规设置*/
    /*数组 2: 录像设置*/
    /*数组 3: 输出设置*/
    /*数组 4: 报警设置*/
    /*数组 5: 串口设置*/
    /*数组 6: 网络设置*/
    /*数组 7: 录像回放*/
    /*数组 8: 系统管理*/
    /*数组 9: 系统信息*/
    /*数组 10: 报警清除*/
    /*数组 11: 云台控制*/
    /*数组 12: 关机重启*/
    /*数组 13: USB升级*/
    /*数组 14：备份*/
	HB_U8	LocalChannel[128];    //本地用户对通道的操作权限，最大128个通道，0-无权限，1-有权限
    HB_U8	dwRemoteRight[32];    //远程登陆用户所具备的权限 1.数组0未使用；2.取值：0-无权限，1-有权限
    /*数组 1: 远程预览*/
    /*数组 2: 参数设置*/
    /*数组 3: 远程回放*/
    /*数组 4: 远程备份*/
    /*数组 5: 查看日志*/
    /*数组 6: 语音对讲*/
    /*数组 7: 远程升级*/
    /*数组 8：远程重启*/
    HB_U8	RemoteChannel[128];  //用户远程登陆时对通道所具备的权限，最大128个通道，0-无权限，1-有权限
    HB_U32	dwUserIP;            //用户登录时PC机的MAC地址，为0表示任何PC机都可以使用该用户登陆到DVR上，不为0表示只有MAC地址为设定值的PC机才可以使用该用户登陆到DVR上
    HB_U8	byMACAddr[6];        //物理地址
}SDVR_USER_INFO_OBJ, *SDVR_USER_INFO_HANDLE;
//STRUCT_SDVR_USER_INFO,*LPSTRUCT_SDVR_USER_INFO;

typedef struct _tagSDVR_USER
{
    HB_U32				dwSize;
    SDVR_USER_INFO_OBJ	struUser[16];
}SDVR_USER_OBJ, *SDVR_USER_HANDLE;

typedef struct _tagSDVR_DDNS
{
    HB_U32	dwSize;            		//数据长度
    HB_CHAR	sDDNSUser[32];        	// DDNS账号，以’\0’结束字符串
    HB_CHAR	sDDNSPassword[32];    	// DDNS账号的密码 以’\0’结束字符串
    HB_CHAR	sDDNSAddress[4][32];    // DDNS解析的IP地址以’\0’结束字符串
    HB_CHAR	sDDNSALoginddress;    	// DDNS解析地址中sDNSAddress数组中的指定解析地址的行数
    HB_CHAR	sDDNSAutoCon;        	// 域名解析是否自动重连，0-不重连，1-自动重连
    HB_CHAR	sDDNSState;        		// DDNS登陆  0-注销 1-登陆
    HB_CHAR	sDDNSSave;        		// DDNS信息保存：获取的时候无意义，设置参数时，表示DVR是否保存参数，1-保存，0-不保存
    HB_U16	sDDNServer;        		// 0-- hanbang.org.cn 1--oray.net 2--dyndns.com
    HB_U16	reboot;            		// 保留
    HB_CHAR	sDDNSName[128];    		// 域名服务器名（hanbang.oray.net）
}SDVR_DDNS_OBJ, *SDVR_DDNS_HANDLE;
//STRUCT_SDVR_DDNS, *LPSTRUCT_SDVR_DDNS;

typedef struct _tagSDVR_PPPOE
{
    HB_U32		dwSize;
    HB_CHAR 	sPPPoEUser[32];             // PPPoE用户名以’\0’结束字符串
    HB_CHAR 	sPPPoEPassword[32];         // PPPoE密码以’\0’结束字符串
    HB_CHAR 	sPPPoEAutoCon;              // PPPoE自动重连
    HB_CHAR 	sPPPoEState;                //获取时作为PPPoE当前状态 0-不自动重连1-自动重连
    //设置时作为PPPoE手动命令 0-断开 1-连接
    //设置时，当sPPPoEAutoCon=1，该字段无效

    // union {
    // HB_CHAR    sPPPoEState;             // 获取时
    // HB_CHAR    sPPPoECon;               // 设置
    // }u;
    HB_CHAR	sPPPoESave;					// PPPOE信息保存: 0-不保存 1-保存
    HB_CHAR	reservedData;
}SDVR_PPPOE_OBJ, *SDVR_PPPOE_HANDLE;

typedef struct _tagSDVR_SERVERCFG
{
    HB_CHAR	sServerIP[16];              //服务器IP地址
    HB_U32	nPort;                		//服务器端口号
    HB_CHAR	puId[32];                   //主机ID号
    HB_U32	nInternetIp ;            	//外网IP
    HB_U32	nVideoPort;            		//实时视频端口
    HB_U32	nTalkPort;            		//对讲端口
    HB_U32	nCmdPort;            		//命令端口
    HB_U32	nVodPort;            		//视频点播端口
    HB_U32	tran_mode;            		// 1 子码流  0 主码流
    HB_U32	ftp_mode;               	// 以FTP方式进行中心存储 1 开启 0 关闭
    HB_U32	max_link;               	// 最大连接数 0 - 32
}SDVR_SERVERCFG_OBJ, *SDVR_SERVERCFG_HANDLE;
//STRUCT_SDVR_SERVERCFG, *LPSTRUCT_SDVR_SERVERCFG;

//NTP设置
typedef struct _tagSDVR_NTPCONFIG
{
    HB_CHAR server[32];     // 服务器以’\0’结束字符串
    HB_U32 	port;         	// 端口
    HB_U32 	auto_enbale;    // 开启ntp服务,0-表示手动,1-表示自动
    HB_U32 	server_index;   // 服务器索引号
    HB_U32 	sync_period;    // 同步周期：[1，60]
    HB_U32 	sync_unit;     	// 同步周期，0-分钟 1-小时 2-天 3-星期 4-月
    HB_U32 	sync_time;     	// 保留
    HB_S32 	time_zone;    	// 时区：[-12，13]
    HB_U32 	reserve;        // 保留
}SDVR_NTPCONFIG_OBJ, *SDVR_NTPCONFIG_HANDLE;
//STRUCT_SDVR_NTPCONFIG, *LPSTRUCT_SDVR_NTPCONFIG;
//轮巡配置
typedef struct _tagSDVR_POLLCONFIG
{
    HB_U32	poll_type; 		//轮巡类型；0-普通轮巡，1-SOPT轮巡，获取或设置前此值必须赋值，表示要获取或设置普通轮巡还是SPOT轮巡的参数。
    HB_U32	enable; 		// Enable：启用轮巡该类型的轮巡，0-不启用，1-启用。

    HB_U32	period; 		//轮巡间隔，单位秒。取值是[1，99]。
    HB_U32	format; 		//画面格式，0—off，1—1画面，2—2画面，4—2*2画面，9---3*3画面，16---4*4画面。
    HB_U8	ch_list[128];	// 轮巡通道，最大128个通道，0—表示该通道不轮巡，1—表示该通道轮巡。
}SDVR_POLLCONFIG_OBJ, *SDVR_POLLCONFIG_HANDLE;
//STRUCT_SDVR_POLLCONFIG, *LPSTRUCT_SDVR_POLLCONFIG;

//I帧间隔
typedef struct _tagSDVR_IFRAMERATE
{
    HB_CHAR	channel; 			//通道号
    HB_S16	iframerate; 		//帧间隔
    HB_CHAR	Reserve;			//byStreamType 0，主码流； 1，子码流1； 2， 子码流2….
}SDVR_IFRAMERATE_OBJ, *SDVR_IFRAMERATE_HANDLE;

typedef struct _tagSDVR_REQIPCWORKPARAM
{
	HB_CHAR  cbStreamType;      	//码流类型 0-主流1-子流 2-第三码流
	HB_CHAR  cbReserve[3];			//保留
}SDVR_REQIPCWORKPARAM_OBJ, *SDVR_REQIPCWORKPARAM_HANDLE;



typedef struct _tagSDVR_SCHEDTIME_IPC
{
	HB_CHAR	cbStartHour;  	//开始小时 0-23
	HB_CHAR	cbStartMin;  	//开始分钟 0-59
	HB_CHAR	cbStopHour; 	//结束小时  0-23
	HB_CHAR	cbStopMin;  	//结束分钟  0-59
}SDVR_SCHEDTIME_IPC_OBJ, *SDVR_SCHEDTIME_IPC_HANDLE;


typedef struct _tagSDVR_ICRTIME
{
	HB_U16 						wLightRange;	//ICR亮度切换临界值
	HB_U16 						wEnable;        // 0--亮度值有效  1--时间段有效
	SDVR_SCHEDTIME_IPC_OBJ 		stSchedTime[2];
}SDVR_ICRTIME_OBJ, *SDVR_ICRTIME_HANDLE;

typedef struct _tagSDVR_SHUUTERVAL
{
	HB_U32	dwShutterIndex; //当前快门时间索引值,表示基于dwShutterVal中的位置，例如dwShutterIndex = 2，
	//则当前快门时间为dwShutterVal[2];
	HB_U32	dwShutterVal[32];	//获取快门时间的支持参数列表,当dwShutterVal[1]=0,表示是一个取值范围，如
	//dwShutterVal[0]= 4096,则表示取值范围为：1/[1,4096*2],当dwShutterVal[1] != 0时，
	//表示有多个具体的索引值，比如：dwShutterVal[0]= 2048，dwShutterVal[1]=4096，当dwShutterVal[x]=0则表示数据共有x个。
}SDVR_SHUUTERVAL_OBJ, *SDVR_SHUUTERVAL_HANDLE;

typedef struct _tagSDVR_SCENEVAL
{
	HB_U32	dwSceneIndex;	//当前镜头索引值，表示基于cbSceneVal中的位置，例如dwSceneIndex = 2，
	//则当前镜头为：cbSceneVal[2] = "JCD661 lens"，当cbSceneVal[x] ="\0"表示总共有
	//x个数据项；
	HB_CHAR	cbSceneVal[8][32];	//该机型支持的镜头种类,//0 - Full Maual lens,1 - DC Iris lens, //2 - JCD661 lens,
	//3 - Ricom NL3XZD lens,4 - Tamron 18X lens，
}SDVR_SCENEVAL_OBJ, *SDVR_SCENEVAL_HANDLE;

typedef struct _tagSDVR_RESOLUTION
{
	HB_U32	dwResoluIndex;	//当前分辨率索引值，表示基于dwResolution中的位置，例如dwResoluIndex= 2，
	//则当前分辨率为dwResolution[2]中所指定的分辨率
	HB_U32	dwResolution[16];	//该机型支持的分辨率，用DWORD来表示支持的分辨率，例如：
	//dwResolution[0]=0x07800438，高两字节（0x0780=1920）、低两字节（0x0438=1080）；
}SDVR_RESOLUTION_OBJ, *SDVR_RESOLUTION_HANDLE;

typedef struct _tagSDVR_AGCVAL
{
	HB_U32	dwAgcIndex;    //当前AGC的索引值，表示基于cbAgcVal中的位置，例如cbAgcVal =2，则表示AGC
	//值为cbAgcVal[2]中的值；
	HB_CHAR	cbAgcVal[32];	  //AGC（自动增益）的支持参数列表,当cbAgcVal[1]= 0时表示cbAgcVal[0]中存储的是
	//一个取值范围，如cbAgcVal[0]= 128,则表示取值范围为：[1,128],当cbAgcVal[1]!=0
	//时，则表示cbAgcVal数组中存储的是具体的值，例如 cbAgcVal[0]= 32，//cbAgcVal[1]=64等，当cbAgcVal [x] =0表示总共有x个数据项。
}SDVR_AGCVAL_OBJ, *SDVR_AGCVAL_HANDLE;

typedef struct _tagSDVR_FRAMERATE
{
	HB_CHAR		cbMinFrameRate;	//该机型支持的最小编码帧率值;
	HB_CHAR		cbMaxFrameRate;	//该机型支持的最大编码帧率值;
	HB_CHAR		cbCurFrameRate;	//该机型设置的当前编码帧率值;
	HB_CHAR   	cbreserve;			//保留
}SDVR_FRAMERATE_OBJ, *SDVR_FRAMERATE_HANDLE;

typedef struct _tagSDVR_REIPCWORKPARAM
{
	HB_U32 					dwLength;			//结构体长度
	HB_CHAR  				cbStreamEnable;   	//是否开启当前码流
	HB_CHAR   				cbStreamType;   	//码流类型 0-主流1-子流 2-第三码流
	HB_CHAR  				cbAudioEnable;    	//音频使能 0-无音频 ,1-有音频
	HB_CHAR  				cbAntiFlicker;     	//抗闪烁设置 0-60HZ   1-50HZ
	SDVR_FRAMERATE_OBJ  	stFrameRate;		//编码帧率设置;
	SDVR_SHUUTERVAL_OBJ 	stShutterVal;		//快门相关参数获取
	SDVR_SCENEVAL_OBJ		stSceneVal;			//镜头相关参数获取
	SDVR_RESOLUTION_OBJ		stResolution;		//解析度相关
	SDVR_AGCVAL_OBJ			stAgcVal;			//Agc相关
	HB_U32					dwBitRateVal;		//视频码率 0-100K 1-128K，2-256K，3-512K，4-1M，5-1.5M，6-2M，7-3M, 8-4M
							//9-5M，10-6M，11-7M，12-8M, 13-9M，14-10M，15-11 M，16-12M
	//其他：码率值（kbps）有效范围 32~2^32,大于等于32，以K为单位；
	HB_CHAR					cbFoucusSpeedVal;	//光学变焦速度值，0：不支持
	HB_CHAR					cbDigitalFoucusVal;	//数字变焦值，0：不支持
	HB_CHAR					cbImageTurnVal;		//当前图像翻转设置 //1-不翻转,2-水平翻转 3-垂直翻转, 4-水平&垂直,0-不支持
	HB_CHAR					cbBlackWhiteCtrlVal; //当前黑白模式设置 //1- Off, 2- On, 3-Auto, 0-不支持
	HB_CHAR					cbIRISCtrl;		 	//Iris control mode 光圈控制模式设置，1-Off,2-Basic, 3-Advanced,0-不支持
	HB_CHAR					cbAutoFoucusVal;	//是否支持自动对焦，//0-不支持,1-支持
	HB_CHAR 				cbAWBVal;			//白平衡场景模式设置，1-auto_wide, 2-auto_normal, 3-sunny, 4-shadow, 5-indoor,
	//6-lamp, 7-FL1, 8-FL2,0-不支持
	HB_CHAR 				cbA3Ctrl;      		//3A控制0-off; 1-Auto Exposure; 2-Auto White Balance; 3-both, (Auto Focus no support)
	SDVR_ICRTIME_OBJ 		stICRTime; 			//ircut(滤光片切换模式设置)仅在模式4时才设置获取该值
	HB_CHAR					cbFNRSuppVal;		//当前帧降噪设置，1-开,2-关,0-不支持
	HB_CHAR					cbStreamKindVal;	//当前码流类型，1-定码流,2-变码流
	HB_CHAR					cbVideoOutKindVal;	//vout视频输出设置：0-disable, 1-CVBS, 2-HDMI,3-YPbPr等等
	HB_CHAR					cbWDRVal;			//该机型是否支持宽动态设置,0-不支持,1-支持
	HB_CHAR   				cbColorMode;    	//色彩风格设置 0-TV   1--PC
	HB_CHAR   				cbSharpNess;		//锐度设置，取值范围为：[1,255]
	HB_CHAR					cbPlatformType;		//平台类别
	HB_CHAR					cbReserve[17];		//保留
}SDVR_REIPCWORKPARAM_OBJ, *SDVR_REIPCWORKPARAM_HANDLE;


typedef struct _tagSDVR_IPCWEP
{
    HB_CHAR		safeoption;	//安全选项设置，取值范围[0,2]  0:自动选择  1：开放系统   2：共享密钥
    HB_CHAR		pswformat;	//密钥格式设置，取值范围[0,1]  0：16进制   1：ASCII码
    HB_CHAR		pswtype;	//密 钥 类 型设置，取值范围[0,3]   0：禁用  1：64位  2:128位   3:152位
    HB_CHAR 	pswword[62];//密码，以’\0’结尾，定义62byte是为了与STRUCT_SDVR_IPCWPAPSK等大小。
	//【备注：密码长度说明，选择64位密钥需输入16进制数字符10个，或者ASCII码字符5个。选择128位密钥需
	//输入16进制数字符26个，或者ASCII码字符13个。选择152位密钥需输入16进制数字符32个，或者ASCII
	//码字符16个。】
    HB_CHAR 	reserve[3];    //保留
}SDVR_IPCWEP_OBJ, *SDVR_IPCWEP_HANDLE;

typedef struct _tagSDVR_IPCWPAPSK
{
    HB_CHAR	safeoption;		//安全选项设置，取值范围[0,2] 0：自动选择   1：WPA-PSK    2:WPA2-PSK
    HB_CHAR	pswmod;			//加密方法设置,取值范围[0,2]  0：自动选择   1：TKIP   2:AES
    HB_CHAR	pawword[64];	//psk密码，8到63个字符，以’\0’结尾
    HB_CHAR	reserve[2];    	//保留
}SDVR_IPCWPAPSK_OBJ, *SDVR_IPCWPAPSK_HANDLE;

typedef struct _tagSDVR_IPCWIRELESS
{
    HB_U32 	nSize;         		//建议添加，结构体长度。
    HB_CHAR 	ssid[50];		//SSID号以’\0’结尾
    HB_CHAR 	wirelessIP[16];	//无线ip以’\0’结尾
    HB_CHAR 	safetype; 		//安全类型设置，取值范围[0,2]    0：WEB、1：WPA-PSK/WPA2-PSK、2：无加密
    HB_CHAR 	reserve[3];    	//保留
    union 						//因为以下两个结构体不可能同时使用，建议用联合体。
    {
    	SDVR_IPCWEP_OBJ 	ipcwep;		//安全类型为WEP时参数结构体
    	SDVR_IPCWPAPSK_OBJ 	ipcwpapsk;	//安全类型为WPA-PSK/WPA2-PSK时参数结构体
    }u;
}SDVR_IPCWIRELESS, *SDVR_IPCWIRELESS_HANDLE;

//蜂鸣器开关状态
typedef struct _tagSDVR_BUZZER
{
    HB_S32 ctrl;            //1.开  0.关
}SDVR_BUZZER_OBJ, *SDVR_BUZZER_HANDLE;

///////////////////////////////NVR///////////////////////
//获取通道对应设备类型
typedef struct _tagCHN_DEV_TYPE
{
	HB_CHAR		byChannel;    	//   	通道号[0, n-1], n为设备通道数
	HB_CHAR		reserve1[3];    //   	保留
    HB_U32		devType;        //   	设备类型    同NET_SDVR_GET_DVRTYPE
    HB_U32		streamType;    	//    	帧头类型    1-00DC   2-HBMS   3-0xFF620068
    HB_U32		encType;        //   	通道编码类型 (保留)
    HB_U32		vendorType;    	//   	设备厂商类型 (保留)
    HB_U32		reserve2[4];    //   	保留
} CHN_DEV_TYPE_OBJ, *CHN_DEV_TYPE_HANDLE;

//清除NVR报警
typedef struct _tagNVR_ALRM_CLEAR
{
    HB_CHAR		Type;              	//  0xff-全部(包括NVR本地和NVR前端所连接的设备) 1-通道(只清除NVR前端
    //  连接设备的报警，此时byChannel有效)  2-NVR本地报警
    HB_CHAR		byChannel;          //  [0, n-1],n:通道数
    HB_CHAR		reserve[14];        //  保留
}NVR_ALRM_CLEAR_OBJ, *NVR_ALRM_CLEAR_HANDLE;


typedef struct _tagSDVR_CHANNELSTATE_EX
{
    HB_CHAR	byRecordStatic;		// 通道是否在录像,0-不录像,1-录像
    HB_CHAR	bySignalStatic;		// 连接的信号状态,0-正常,1-信号丢失
    HB_CHAR	byHardwareStatic;	// 保留
    HB_CHAR	byLinkNum;			// 客户端连接的个数：同一通道当前时间的实时流的连接数。不分主子码流，同一IP多个连接算多个连接
    HB_U32	dwBitRate;			// 实际码率
}SDVR_CHANNELSTATE_EX_OBJ, *SDVR_CHANNELSTATE_EX_HANDLE;

typedef struct _tagSDVR_WORKSTATE_EX
{
    HB_U32 						dwSize ;               		// 结构体大小
    SDVR_DISKSTATE_OBJ  		struHardDiskStatic[16]; 	// 硬盘状态
    SDVR_CHANNELSTATE_EX_OBJ 	struChanStatic[128];    	// 通道的状态
    HB_CHAR 					alarminStatusLocal[128]; 	// 本地报警输入端口的状态
    HB_CHAR 					alarmoutStatusLocal[128];	// 本地报警输出端口的状态
    HB_U32 						reserve[4];                 // 保留
}SDVR_WORKSTATE_EX_OBJ, *SDVR_WORKSTATE_EX_HANDLE;

//获取对应通道连接的客户端IP列表
typedef struct _tagSDVR_CLIENT_IP_INFO
{
    HB_U32 		dwSize; 		// 结构体大小
    HB_CHAR     byChannel;		// 通道号[0, n-1],n:通道数
    HB_CHAR     cllientIpNum;	// 此通道连接客户端IP个数
    HB_CHAR   	reserve1[2]; 	// 保留
    HB_U32 		dwClientIP[64]; // 客户端IP列表
    HB_U32 		reserve2[4];    // 保留
}SDVR_CLIENT_IP_INFO_OBJ, *SDVR_CLIENT_IP_INFO_HANDLE;

//NVR日志信息查询 (IPC是否使用?)发送数据
typedef struct _tagREQLOG_EX
{
    HB_U16		dwYear;			// 年: 2000~2063
    HB_CHAR		dwMonth;		// 月: 1~12
    HB_CHAR		dwDay;			// 日: 1~31
    HB_U16		dwStart;		// 查询从第几条开始，一般为0。
    HB_U16		dwnum;			// 一次查询个数，最多为100。
    HB_CHAR		priType;		// 主类型 （需扩展所有）
    HB_CHAR		secType;		// 次类型
    HB_CHAR		reserve[6];		// 保留
}REQLOG_EX_OBJ, *REQLOG_EX_HANDLE;

//应答消息
typedef struct _tagSDVR_LOGINFO_EX
{
    HB_U32		dwSize;                	// 结构体大小
    HB_U32		totalLogNum;        	// 日志总条数
    HB_U32		curLogNum;           	// 本次查到的条数
    HB_U32		dwStart;                // 本次查询到的日志的起始编号
    HB_CHAR    	encType;                // 编码格式 1- UTF-8  2-gb2312
    HB_CHAR   	reserve[3];            	// 保留
    HB_CHAR 	sigalLogData[100][128]; // 日志信息 (每次查询最多支持100条日志，日志多于100条时，
    								// 需要多次调用，每条128字节，每条以‘\0’结束)
} SDVR_LOGINFO_EX_OBJ, *SDVR_LOGINFO_EX_HANDLE;

//建立NVR透明通道
typedef struct _tagNVR_SERIAL_START
{
    HB_CHAR  opType;		//  0-（混合DVR,设置本地），1-前端设备所属的 (为1时byChannel生效)
    HB_CHAR  seriaType;	//  一个字节的串口类型，1：232  2：485。
    HB_CHAR  byChannel;	//  [0, n-1],n:通道数
    HB_CHAR  reserve[5];	//　保留
}NVR_SERIAL_START_OBJ, *NVR_SERIAL_HANDLE;

//获取设备信息扩展 (建议IPC/8000T都用此协议)
typedef struct _tagSDVR_DEVICEINFO_EX
{
    HB_U32		dwSize;						// 结构体大小
    HB_CHAR		sDVRName[32];				// 设备, 以’\0’结束字符串
    HB_U32		dwDVRID;                    // 保留
    HB_U32		dwRecycleRecord;			// 协议二: //录像覆盖策略 0-循环覆盖 1-提示覆盖
    HB_CHAR		sSerialNumber[48];			// 序列号
    HB_CHAR		sSoftwareVersion[64];		// 软件版本号以’\0’结束字符串协议二: （主机型号 软件版本号）
    HB_CHAR		sSoftwareBuildDate[32];		// 软件生成日期以’\0’结束字符串协议二:（Build 100112）
    HB_U32		dwDSPSoftwareVersion;       // DSP软件版本
    HB_CHAR		sPanelVersion[32];          // 前面板版本，以’\0’结束字符串，IPC无
    HB_CHAR		sHardwareVersion[32];		// (保留)协议二: 当软件版本号超过16字节时会使用作为主机型号显示
    HB_CHAR 	byAlarmInPortNum;			// 报警输入个数, NVR只取本地报警输入
    HB_CHAR 	byAlarmOutPortNum;			// 报警输出个数, NVR只取本地报警输出
    HB_CHAR 	byRS232Num;                 // 保留
    HB_CHAR 	byRS485Num;                 // 保留
    HB_CHAR 	byNetworkPortNum;           // 保留
    HB_CHAR 	byDiskCtrlNum;              // 保留
    HB_CHAR 	byDiskNum;                  // 硬盘个数
    HB_CHAR 	byDVRType;                  // DVR类型, 1:NVR 2:ATM NVR 3:DVS 4:IPC 5:NVR （建议使用//NET_SDVR_GET_DVRTYPE命令）
    HB_CHAR 	byChanNum;                  // 通道个数[0, 128]
    HB_CHAR 	byStartChan;                // 保留
    HB_CHAR 	byDecordChans;              // 保留
    HB_CHAR 	byVGANum;                   // 保留
    HB_CHAR 	byUSBNum;                   // 保留
    HB_CHAR 	reserve[3];                        // 保留
}SDVR_DEVICEINFO_EX_OBJ, *SDVR_DEVICEINFO_EX_HANDLE;

//获取NVR云台协议列表发送数据
typedef struct _tagNVR_PTZLIST
{
    HB_CHAR  Type;         //  0-NVR本地云台，1-前端设备云台 (为1时byChannel生效)
    HB_CHAR  byChannel;       //  [0, n-1],n:通道数
    HB_CHAR  reserve[2];    // 保留
}NVR_PTZLIST_OBJ, *NVR_PTZLIST_HANDLE;

//接收数据：
typedef struct _tagNVR_PTZLIST_INFO
{
    HB_U32 		ptznum;                	// 协议个数（限制为最多100个）
    HB_CHAR    	reserve[4];            	// 保留
    HB_CHAR   	ptztype[100][10];       // 协议名列表―――0，unknow;
}NVR_PTZLIST_INFO_OBJ, *NVR_PTZLIST_INFO_HANDLE;

typedef struct _tagNVR_ALRMIN
{
    HB_U32 						dwSize;						// 结构体大小
    HB_CHAR 					opType;						// 0-本地 1-前端 (为1时,byChannel有效)
    HB_CHAR 					byChannel;					// 操作前端某通道设备 [0, n-1], n:通道个数
    HB_CHAR 					byAlarmInPort;				// 报警输入端口号[0, n-1], n:报警输入个数
    HB_CHAR 					sAlarmInName[32];			// 报警输入端口名， 以’\0’结束字符串
    HB_CHAR 					byAlarmType;				// 探头类型 0-常闭1-常开
    HB_CHAR 					byEnSchedule;				// 报警输入布防时间激活 0-屏蔽 1-激活
    HB_CHAR 					weekEnable;					// 每天使能位0-不使能 1-使能(若使能,只取struAlarmTime[0][0~7]来设置每一天)
    HB_CHAR 					allDayEnable[8];			// 全天使能 ,0-不使能 1-使能若此项使能,则对应的天为全天布防,不用判断时间段
    SDVR_SCHEDTIME_OBJ 			struAlarmTime[8][8];  		// 布防时间段
    HB_U32    					dwHandleType;				// 按位 2-声音报警 5-监视器最大化 //6-邮件上传

    // 联动报警输出
    HB_CHAR  					alarmOut_local[16];			// 报警输出端口(本地)
    HB_CHAR  					alarmOut_remote[128][16];	// 报警输出端口(前端设备)

    // 联动录像
    HB_CHAR 					byRelRecordChan[128];		// 报警触发的录象通道,为1表示触发该通道

    // 联动其他
    HB_CHAR 					byEnablePreset[128];		// 是否调用预置点 仅用byEnablePreset[0]来判断
    HB_CHAR 					byPresetNo[128];            // 调用的云台预置点序号,一个报警输入可以调用多个通道的云台预置点, 0xff表示不调用预置点 [1, 254]
    HB_CHAR 					reserve[32];				// 保留
}NVR_ALRMIN_OBJ, *NVR_ALRMIN_HANDLE;

typedef struct _tagNVR_ALARMOUTINFO
{
    HB_U32					dwSize;					// 结构体大小
    HB_CHAR 				opType;					// 0-本地 1-前端 (为1时,byChannel有效)
    HB_CHAR 				byChannel;				// 操作前端某通道设备 [0, n-1], n:通道个数
    HB_CHAR 				byALarmoutPort;			// 报警输出通道号 [0, n-1], n:报警输出端口数
    HB_CHAR 				sAlarmOutName[32];		// 名称 以’\0’结束字符串
    HB_U32 					dwAlarmOutDelay;		// 输出保持时间 单位秒 [2, 300]
    HB_CHAR 				byAlarmType;			// 探头类型 0-常闭1-常开 (保留)
    HB_CHAR 				byEnSchedule;			// 报警输出布防时间激活 0-屏蔽 1-激活
    HB_CHAR 				weekEnable;             // 每天使能位0-不使能 1-使能(若使能,只取struAlarmTime[0][0~7]对每天做设置)
    HB_CHAR 				fullDayEnable[8];       // 完整天录像 0-不使能(缺省值) 1-使能
    SDVR_SCHEDTIME_OBJ 		struAlarmTime[8][8]; 	//布防时间段, 8个时间段

    HB_CHAR  				reserve[32];			// 保留
}NVR_ALARMOUTINFO_OBJ, *NVR_ALARMOUTINFO_HANDLE;

//获取NVR报警输入状态
typedef struct _tagNVR_ALRMIN_STATUS
{
    HB_CHAR  	opType;            	//  0-本地 1-前端 (为1时,byChannel有效)
    HB_CHAR  	byChannel;         	// 操作前端某通道设备 [0, n-1], n:通道个数
    HB_CHAR  	byAlarm;			// 保留
    HB_CHAR  	reserve1;			// 保留
    HB_CHAR    	byAlarmIn[128];		// 报警输入状态 128个报警输入, 0-无输入 1-有输入
    HB_CHAR  	reserve2[32];		// 保留
}NVR_ALRMIN_STATUS_OBJ, *NVR_ALRMIN_STATUS_HANDLE;


typedef struct _tagVIDEO_INFO
{
    HB_CHAR 	brightness;			// 亮度      取值范围[0，255] 缺省值128
    HB_CHAR 	constrast;			// 对比度    取值范围[0，255] 缺省值128
    HB_CHAR 	saturation;			// 饱和度    取值范围[0，255] 缺省值128
    HB_CHAR 	hue;				// 色度      取值范围[0，255] 缺省值128
    HB_CHAR 	sharp;				// 锐度      0（缺省值）或1
    HB_U32 		reserved;			// 预留
}VIDEO_INFO_OBJ, *VIDEO_INFO_HANDLE;


typedef struct _tagNVR_CHN_ATTR_INFO
{
    HB_U32 				dwSize;				// 长度（结构体大小)
// 通道名相关
    HB_CHAR 			sChanName[32];		// 通道名 以’\0’结束字符串
    HB_CHAR 			byChannel;			// 通道号 [0, n－1] n:通道数
    HB_U32 				dwShowChanName;		// 是否显示通道名 0-显示 1-不显示
    HB_CHAR 			byOSDAttrib;		// 通道名 1-不透明 2-透明（只针对PC端显示）
    HB_U16 				wShowNameTopLeftX;	// 通道名称显示位置的x坐标 左->右 0~视频实际宽度－通道名长度
    HB_U16 				wShowNameTopLeftY;	// 通道名称显示位置的y坐标 上->下 0~视频实际高度－字体高度

    // 日期相关
    HB_U32 				dwShowTime;			// 是否显示时间 0-显示 1-不显示
    HB_U16 				wOSDTopLeftX;		// 时间osd坐标X [0, 实际宽－时码长度]
    HB_U16 				wOSDTopLeftY;		// 时间osd坐标Y[0, 实际高－字体高度]
    HB_CHAR 			byDateFormat;		// 日期格式
    //  0 - YYYY-MM-DD    （缺省值）
    //  1 - MM-DD-YYYY
    //  2 - YYYY年MM月DD日
    //  3 - MM月DD日YYYY年

    // 星期相关
    HB_CHAR 			byDispWeek;			// 是否显示星期 0-显示 1-不显示
    HB_CHAR 			byOSDLanguage;		// 星期语言 0-中文 1-英文 (可扩展)

    // 亮度色度相关
    VIDEO_INFO_OBJ  	videoinfo;			// 视频信息

    // 遮挡区域相关
    HB_U32 				dwEnableHide;		// 视频遮挡使能 ,0-不遮挡,1-遮挡(遮挡区域全黑) 2-遮挡(遮挡区域马赛克)
    SDVR_SHELTER_OBJ	struShelter[16];    // 视频遮挡区域
    HB_U32 				reserve[32];        // 保留
}NVR_CHN_ATTR_INFO_OBJ, *NVR_CHN_ATTR_INFO_HANDLE;

//NVR录像参数
typedef struct _tagNVR_RECORD_PARAM
{
    HB_CHAR    streamtype;           // 流类型     0-变码流（缺省值） 1-定码流
    HB_CHAR    quality;              // 视频质量   1-最高 2-较高 3-高（缺省值） 4-中 5-低 6-最低
    HB_CHAR    resolution;           // 主码流     0-DIF 1-D1（缺省值） 2-720P 3-1080P
    // 子码流     0-CIF 1-D1(缺省值)
    HB_CHAR    framerate;            // 帧率       取值范围[2,25] 缺省值25
    HB_CHAR    maxbitrate;           // 码流(主)   0-100K 1-128K 2-256K 3-512K 4-1M 5-1.5M 6-2M（缺省值） 7-3M 8-4M 9-6M 10-8M
    // 码流（子） 0-30K 1-45K 2-60K 3-75K 4-90K 5-100K 6-128K 7-256K 8-512K(缺省值) 9-1M 10-2M
    HB_CHAR    audio;                // 音频标识   0-无音频 1-有音频（缺省值）
    HB_U32   reserved;             // 预留
}NVR_RECORD_PARAM_OBJ,  *NVR_RECORD_PARAM_HANDLE;

typedef struct _tagREC_TIME_PERIOD
{
    HB_CHAR 	starth;				// 起始时间-时
    HB_CHAR 	startm;				// 起始时间-分
    HB_CHAR 	stoph;				// 结束时间-时
    HB_CHAR 	stopm;				// 结束时间-分
    HB_CHAR 	recType;			// 录像类型  0 - 无 1-手动(无效)  2-定时  3-移动  4-报警 5-移动 | 报警  6 -移动 & 报警
    HB_CHAR 	reserve[3];			// 保留
}REC_TIME_PERIOD_OBJ, *REC_TIME_PERIOD_HANDLE;

typedef struct _tagFULL_DAY
{
    HB_CHAR	Enable;      		// 完整天使能  0-不使能(缺省值) 1-使能
    HB_CHAR	recType;     		// 完整天对应的录像类型 0 - 无 1-手动(无效)  2-定时  3-移动  4-报警 5-移动 | 报警  6- 移动 & 报警
    HB_CHAR	reserve[2];    		// 保留
}FULL_DAY_OBJ, *FULL_DAY_HANDLE;

typedef struct
{
    HB_CHAR 				enable;                 // 使能时间表 0-不使能(缺省值) 1-使能
    HB_CHAR 				weekEnable;             // 每天使能位 0-不使能 1-使能(若使能,只取struAlarmTime[0][0~7]对每天做设置)
    FULL_DAY_OBJ   			fullDayEnable[8]; 		// 完整天录像
    REC_TIME_PERIOD_OBJ 	struAlarmTime[8][8]; 	// [0-7][0]代表全天使能的设置项
    HB_U32  				reserved;            	// 预留
}REC_TIME_SCHEDULE_OBJ, *REC_TIME_SCHEDULE_HANDLE;

typedef struct _tagRECORD_SET
{
    HB_U32   				dwSize;				// 结构体大小
    HB_CHAR    				byChannel;			// 通道号
    HB_U16    				preRecTime;			// 预录时间      取值范围[5，30]秒  缺省值10
    HB_U32    				delayRecTime;		// 录像持续时间  取值范围[0,180]秒  缺省值30 (对3-移动录像 4-报警录像 5-移动 | 报警  6-移动 & 报警 有效)
    REC_TIME_SCHEDULE_OBJ 	timeschedule;		// 录像时间表与录像类型设置

    NVR_RECORD_PARAM_OBJ    timerecord;			// 定时           录像参数
    NVR_RECORD_PARAM_OBJ    moverecord;			// 移动           录像参数
    NVR_RECORD_PARAM_OBJ    alarmrecord;		// 报警           录像参数
    NVR_RECORD_PARAM_OBJ    moveOrAlarmrecord;	// 移动 | 报警    录像参数
    NVR_RECORD_PARAM_OBJ    moveAndAlarmrecord;	// 移动 & 报警   录像参数
    NVR_RECORD_PARAM_OBJ    neRecParam[4];		// 子码流     录像参数 (保留)

    HB_U32  reserved[32];                          	// 预留
}RECORD_SET, *RECORD_SET_HANDLE;

typedef struct _tagNVR_MOTION
{
    HB_U32					dwSize;					//长度（结构体大小）
    HB_CHAR 				byChannel;				//通道号 [0, n－1] n:通道数

    HB_CHAR 				byMotionScope[32][32];	//侦测区域,共有32*32个小宏块,为1表示该宏块是移动侦测区域,0-表示不是
    HB_CHAR 				byMotionSensitive;		//移动侦测灵敏度, 0 - 5,越高越灵敏

    // 时间表相关
    HB_CHAR 				byEnableHandleMotion; 	// 移动侦测布防使能 0-撤防 1-布防
    HB_CHAR 				weekEnable;           	// 设置每天0-不使能 1-使能(若使能,只取struAlarmTime[0][0~7]对每天做设置)
    HB_CHAR 				fullDayEnable[8];       // 完整天录像 0-不使能(缺省值) 1-使能,若此项使能,则对应的天为全天布防,不用判断时间段
    SDVR_SCHEDTIME_OBJ 	struAlarmTime[8][8];   	//布防时间段, 8个时间段
    HB_U32    				dwHandleType;			//按位 2-声音报警5-监视器最大化 //6-邮件上传

    // 联动报警输出
    HB_CHAR    				alarmOut_local[16];			//报警输出端口(本地)
    HB_CHAR    				alarmOut_remote[128][16];	//报警输出端口(前端设备)

    // 联动录像
    HB_CHAR 					record_channel[128];		// 联动的录像通道，为0-不联动 1-联动

    // 联动其他
    HB_U8 					byEnablePreset[128];		// 是否调用预置点 仅用byEnablePreset[0]来判断;
    HB_U8 					byPresetNo[128];			// 调用的云台预置点序号,一个报警输入可以调用多个通道的云台预置点, 0xff表示不调用预置点 [1, 254]
    HB_U32 					reserve[32];				// 保留
}NVR_MOTION_OBJ, *NVR_MOTION_HANDLE;

typedef struct _tagNVR_ABNORMAL
{
    HB_U32 					dwSize;                   	//长度（结构体大小）
    HB_CHAR 				abnormalAlarmType;     		// 1-视频丢失 2-网络断开 3-温度过高 4-遮挡报警...
    HB_CHAR 				byChannel;             		// 通道号 (对视频丢失, 遮挡报警, 网络断开…有效)

    HB_CHAR 				byEnableAbnormal;        	// 异常报警使能 0-不报警 1-报警；
    HB_U16 					wHideAlarmAreaTopLeftX;		// [0, 实际宽－1]（遮挡报警时有效）
    HB_U16 					wHideAlarmAreaTopLeftY;		// [0, 实际高－1]（遮挡报警时有效）
    HB_U16 					wHideAlarmAreaWidth;		// [16, 实际宽] （遮挡报警时有效）
    HB_U16 					wHideAlarmAreaHeight;		// [16, 实际高] （遮挡报警时有效）

    // 联动报警输出
    HB_CHAR    				alarmOut_local[16];			//报警输出端口(本地)
    HB_CHAR    				alarmOut_remote[128][16];	//报警输出端口(前端设备)

    HB_CHAR 				weekEnable;           		//设置每天0-不使能 1-使能(若使能,只取struAlarmTime[0][0~7]对每天做设置)
    HB_CHAR 				fullDayEnable[8];       	//完整天录像 0-不使能(缺省值) 1-使能,若此项使能,则对应的天为全天布防,不用判断时间段
    SDVR_SCHEDTIME_OBJ 	struAlarmTime[8][8];   		//布防时间段, 8个时间段
    HB_U32    				dwHandleType;        		// 处理方式 按位  2-声音报警5-监视器最大化 //6-邮件上传

    HB_U32 					reserve[32];          		// 保留
}NVR_ABNORMAL_OBJ, *NVR_ABNORMAL_HANDLE;

//主机参数文件查询(参数导入/导出时使用)
typedef struct _tagPARAM_FILEINFO
{
    HB_U16 	fileNum;             	// 参数文件个数
    HB_CHAR fileVersion[32];        // 文件版本号以’\0’结束字
    HB_CHAR fileName[100][32];    	// 参数文件文件名(最多100个文件)
    HB_U32 	fileSize[100];     		// 每个文件的大小
    HB_U32 	reserve[32];        	// 保留
}PARAM_FILEINFO_OBJ, *PARAM_FILEINFO_HANDLE;

//主机参数文件导出
typedef struct _tagEXPT_FILEINFO
{
    HB_CHAR	fileName[32];  		// 需要导出的文件名
    HB_CHAR	reserve[4];        	//保留
}EXPT_FILEINFO_OBJ, *EXPT_FILEINFO_HANDLE;

//应答消息
typedef struct _tagEXPT_REQ
{
    HB_CHAR		fileName[32];   	// 导出的文件名
    HB_U32 		fileSize;        	// 导出文件的大小
    HB_CHAR   	reserve[4];    		// 保留
    HB_CHAR 	*pFileData;     	// 参数文件数据
}EXPT_REQ_OBJ, *EXPT_REQ_HANDLE;

//NVR主机参数文件导入
typedef struct _tagIMPT_INFO
{
    HB_CHAR		fileName[32];   // 导入参数文件的文件名
    HB_U32 		fileSize;       // 文件大小
    HB_CHAR   	reserve[4];    	// 保留
    HB_CHAR 	*pFileData;     // 参数文件数据
}IMPT_INFO_OBJ, *IMPT_INFO_HANDLE;

typedef struct _tagSDVR_SNAP
{
	SDVR_SCHEDTIME_OBJ 		schedule[MAX_DAYS][MAX_TIMESEGMENT];//布防时间设置
    HB_CHAR 				byEnable;							//是否启动
    HB_S32 					snaptimes;							//抓拍次数
    HB_S32 					snaptimeval;						//抓拍间隔 以秒为单位
}SDVR_SNAP_OBJ, *SDVR_SNAP_HANDLE;


//////////////////////////////////////////////////////////////////////////////
//协议选择支持类型
//////////////////////////////////////////////////////////////////////////////
typedef enum _tagPROTOCL_TYPE
{
    PROTOCL_TYPE_NOSUPPORT = 0,
    PROTOCL_TYPE_7000SDK,
    PROTOCL_TYPE_ONVIF,
}PROTOCL_TYPE_E;

//////////////////////////////////////////////////////////////////////////////
//协议选择结构体
//////////////////////////////////////////////////////////////////////////////
typedef struct _tagPROTOCL
{
    HB_S32 len;          //结构体长度
    HB_S8  protocl_type; //0-不支持 1-7000SDK 2-ONVIF
    HB_U8  pack_type;     //  0-无包头 1-HBGK
    HB_S8  reserve[4];   //保留
}PROTOCL_OBJ, *PROTOCL_HANDLE;

//////////////////////////////////////////////////////////////////////////////
// onvif协议参数
//////////////////////////////////////////////////////////////////////////////
typedef struct _tagPLATFORM_ONVIF_INFO
{
    HB_S32  enable;                    //使能 -1-不支持 0-off, 1-on
    HB_U16  protocol_port;             //协议端口，现在汉邦的IPC默认为8888
    HB_U16  video_port;                //音视频端口，现在汉邦的IPC默认为554
}PLATFORM_ONVIF_INFO_OBJ, *PLATFOR_ONVIFM_INFO_HANDLE;

//////////////////////////////////////////////////////////////////////////////
// PSIA协议参数
//////////////////////////////////////////////////////////////////////////////
typedef struct _tagPLATFORM_PSIA_INFO
{
    HB_S32  enable;                    //使能 -1-不支持 0-off, 1-on
    HB_U16  protocol_port;             //协议端口，现在汉邦的IPC默认为8888
    HB_U16  video_port;                //音视频端口，现在汉邦的IPC默认为554
}PLATFORM_PSIA_INFO_OBJ, *PLATFORM_PSIA_INFO_HANDLE;

//////////////////////////////////////////////////////////////////////////////
// GB28181设备配置部分结构体
//////////////////////////////////////////////////////////////////////////////
typedef struct _tagGB28181_DEVICE_INFO
{
    HB_CHAR    device_id[32];             //设备ID
    HB_S32     device_port;               //设备命令端口
    HB_CHAR    device_domain_name[64];    //设备域名
    HB_CHAR    device_pwd[32];            //设备注册密码    默认值为12345678
    HB_S32     device_expires;            //注册过期时间 单位为秒   默认值为3600
    HB_S32     device_alarmin_num;        //设备报警输入数量，范围1-8 只读
    HB_CHAR     device_alarmin_id[8][32];         //设备报警ID
}GB28181_DEVICE_INFO_OBJ, *GB28181_DEVICE_INFO_HANDLE;

//////////////////////////////////////////////////////////////////////////////
// GB28181的sip服务器结构体定义
//////////////////////////////////////////////////////////////////////////////
typedef struct _tagGB28181_SIP_SERVER_INFO
{
    HB_CHAR    sip_svr_ip[32];            //sip服务器IP
    HB_CHAR    sip_svr_id[32];            //sip服务器ID
    HB_S32     sip_svr_port;              //sip服务器端口号   默认值为5060
    HB_CHAR    sip_svr_domain_name[64];   //sip服务器域名
}GB28181_SIP_SERVER_INFO_OBJ, *GB28181_SIP_SERVER_INFO_HANDLE;

//////////////////////////////////////////////////////////////////////////////
// GB28181的流媒体服务器结构体定义
//////////////////////////////////////////////////////////////////////////////
typedef struct _tagGB28181_SMS_SERVER_INFO
{
    HB_CHAR   sms_svr_ip[32];            //sms流媒体服务器接收IP
    HB_S32    sms_svr_port;              //sms流媒体服务器接收端口  默认值为6000
}GB28181_SMS_SERVER_INFO_OBJ, *GB28181_SMS_SERVER_INFO_HANDLE;

//////////////////////////////////////////////////////////////////////////////
// GB28181协议参数
//////////////////////////////////////////////////////////////////////////////
typedef struct _tagGB28181_INFO
{
    HB_S32                        enable;           //使能 -1-不支持 0-off, 1-on
    GB28181_DEVICE_INFO_OBJ       dev_info;         //GB28181设备配置信息
    GB28181_SMS_SERVER_INFO_OBJ   sms_server_info;  //GB28181流媒体服务器信息
    GB28181_SIP_SERVER_INFO_OBJ   sip_server_info;  //GB28181sip服务器信息
}GB28181_INFO_OBJ, *GB28181_INFO_HANDLE;

//////////////////////////////////////////////////////////////////////////////
// 接入平台信息
//////////////////////////////////////////////////////////////////////////////
typedef struct _tagPLATFORM_OBJ
{
    HB_S32    length;                  //结构体长度
    HB_S32    protocol_type;           //平台接入协议的选择 0-GB28181 1-onvif 2-PSIA
    PLATFORM_ONVIF_INFO_OBJ  onvif;     //onvif协议参数
    PLATFORM_PSIA_INFO_OBJ   psia;      //PSIA协议参数
    GB28181_INFO_OBJ         gb28181;   //GB28181协议参数
}PLATFORM_OBJ, *PLATFORM_HANDLE;

/////////////////////////////////////////////////////////////////////////////////////////
//端口映射
/////////////////////////////////////////////////////////////////////////////////////////
typedef   struct 
{ 
    HB_U32   nvrip;    //内网设备ip地址(路由连接的设备的ip) 
    HB_U16   iport;    //内网端口 
    HB_U16   eport;    //外网端口 
    HB_U16   proto;    //0-TCP,1-UDP 
    HB_U16   type;    //0-sdk服务端口,1-http端口,2-升级端口，3-telnet端口， 
    //4-rtsp端口，5-https端口，6-tftp 端口 
}struct_portmap_s; 

typedef    struct 
{ 
    HB_U32   iaddr;  //路由设备内网ip地址(路由ip) 
    HB_U32   eaddr;  //路由设备外网ip地址(路由拨号等获取的ip) 
    struct_portmap_s    portmap[32];    //服务端口表或映射端口表 
    HB_CHAR   reserve_dev[4];        //保留 
}struct_devinfo_s; 

typedef    struct         
{ 
    HB_S32    dev_num;   //出口路由设备个数，0表示没有做端口映射，但服务端口仍会在dev[0]中填充 
    struct_devinfo_s  dev[8];  //索引下的详细信息，从0开始 
    HB_CHAR   reserve[8];      //保留 
}STRUCT_SDVR_PORTMAP;
















typedef struct _tagNET_STATUS
{
    SDVR_DECODERINFO_OBJ 		decoder_info;
    SDVR_PTZ_CTRL_OBJ 			ptz_ctrl;
    SDVR_VIDEOEFFECT_OBJ	 	video_effect;
    SDVR_TIME_OBJ 				time;
    SDVR_REALPLAY_OBJ 			real_play;
    SDVR_NETINFO_OBJ 			net_info;
    SDVR_DEVICEINFO_OBJ 		device_info;
    SDVR_COMPRESSINFO_OBJ 		compression;
    SDVR_PICINFO_OBJ 			pic_info;
    SDVR_ALARMININFO_OBJ 		alarmin_info[2];
    SDVR_RECORDINFO_OBJ 		record_info;
    SDVR_RECFIND_OBJ	 		rec_find;
    SDVR_RECINFO_HANDLE 		prec_info;
    SDVR_ALARMOUTINFO_OBJ 		alarmout_info;
    SDVR_WORKSTATE_OBJ 			work_info;
    SDVR_SERIALINFO_OBJ 		serial;
    SDVR_ALARM_OUT_OBJ	 		alarmout_state;	//STRUCT_SDVR_ALARM_OUT alarmout_state;
    HB_CHAR 					currectype;		//当前录像类型
    HB_S32 						sharp;			//锐度
    HB_S32 						motion_snap;	//移动侦测抓拍
    HB_S32 						alarmin_snap;	//报警输入抓拍
    SDVR_SNAP_OBJ 				plan_snap;   	//not support
    HB_S32 						ptz_speed;		//云台速度
    HB_U32 						millitm; 		//毫秒
    HB_CHAR 					card_type[32];
    HB_U32 						uart_func;//0-no,1-ptz,2-keyboard,3-transparent uart
    HB_CHAR 					uart_enable;
    HB_CHAR 					support_talk_type[128];
    HB_CHAR 					current_talk_type[32];
    HB_CHAR 					mfs_info[128];
    HB_CHAR 					version[32];
    HB_SDVR_PRESETPOLL_OBJ 		preset ;//STRUCT_DVR_PRESETPOLL preset;
    HB_S32 						frmtype; //0 主码流 1 子码流
    SDVR_PPPOE_OBJ 				pppoe;//STRUCT_SDVR_PPPoE与统一接口的需求的信息不符，所以使用信息更多的PPPOE_Set
    SDVR_DDNS_OBJ 				ddns;
    SDVR_REIPCWORKPARAM_OBJ 	ipc_param_main;
    SDVR_REIPCWORKPARAM_OBJ 	ipc_param_sec;
   // STRUCT_SDVR_IPCCONFIG ipc_config;  //not support
#ifdef HB_ARCH_NEW
    PROTOCL_OBJ           protocl;
#endif
    PLATFORM_OBJ          platform;
}NET_STATUS_OBJ, *NET_STATUS_HANDLE;


#define NET_SDVR_REQ_OK				0x01
#define NET_SDVR_REQ_NOTOK			0x00
#define	INFO_LEN					32
#define	INFO_SEQ					4
#define MAX_PRESET					128
#define MAX_REC_NUM 				100
#define MAX_DISKNUM					16
#define MAX_CHANNUM					16
#define	MAX_ALARMOUT				4
//#define MAX_LINK			6
#define MAX_LINK					32
//0: 手动录像1:定时录像，2:移动侦测，3:报警录像,
typedef enum
{
	Manual = 0x0,
	Time  = 0x1,
	Move 	= 0x2,
	Alarm = 0x3,
	EnableAll  = 0x0f
} RecordType_t;

#define MAX_USERNUM			16
#define MAX_RIGHT			32
#define PHONENUMBER_LEN 	32
#define MAX_SHELTERNUM		4
#define SDVR_SHUTDOWN		0	//关闭设备
#define SDVR_REBOOT			1	//重启设备
#define SDVR_DEFAULT		2	//恢复出场设置

//////////////////////////////////////////////
#define HB_SDVR_NOERROR 			        0	//没有错误
#define HB_SDVR_PASSWORD_ERROR 				-1	//用户名密码错误
#define HB_SDVR_NOENOUGHPRI 				-2	//权限不足
#define HB_SDVR_NOINIT 					    -3	//没有初始化
#define HB_SDVR_CHANNEL_ERROR 				-4	//通道号错误
#define HB_SDVR_OVER_MAXLINK 				-5	//连接到DVR的客户端个数超过最大
#define HB_SDVR_VERSIONNOMATCH				-6	//版本不匹配
#define HB_SDVR_NETWORK_FAIL_CONNECT	    -7	//连接服务器失败
#define HB_SDVR_NETWORK_SEND_ERROR			-8	//向服务器发送失败
#define HB_SDVR_NETWORK_RECV_ERROR			-9	//从服务器接收数据失败
#define HB_SDVR_NETWORK_RECV_TIMEOUT	    -10	//从服务器接收数据超时
#define HB_SDVR_NETWORK_ERRORDATA			-11	//传送的数据有误
#define HB_SDVR_ORDER_ERROR				    -12	//调用次序错误
#define HB_SDVR_OPERNOPERMIT				-13	//无此权限
#define HB_SDVR_COMMANDTIMEOUT				-14	//DVR命令执行超时
#define HB_SDVR_ERRORSERIALPORT				-15 //串口号错误
#define HB_SDVR_ERRORALARMPORT				-16 //报警端口错误
#define HB_SDVR_PARAMETER_ERROR 			-17 //参数错误
#define HB_SDVR_CHAN_EXCEPTION				-18	//服务器通道处于错误状态
#define HB_SDVR_NODISK					    -19	//没有硬盘
#define HB_SDVR_ERRORDISKNUM				-20	//硬盘号错误
#define HB_SDVR_DISK_FULL				    -21	//服务器硬盘满
#define HB_SDVR_DISK_ERROR				    -22	//服务器硬盘出错
#define HB_SDVR_NOSUPPORT				    -23	//服务器不支持
#define HB_SDVR_BUSY					    -24	//服务器忙
#define HB_SDVR_MODIFY_FAIL				    -25	//服务器修改不成功
#define HB_SDVR_PASSWORD_FORMAT_ERROR		-26	//密码输入格式不正确
#define HB_SDVR_DISK_FORMATING				-27	//硬盘正在格式化，不能启动操作
#define HB_SDVR_DVRNORESOURCE				-28	//DVR资源不足
#define	HB_SDVR_DVROPRATEFAILED				-29	//DVR操作失败
#define HB_SDVR_OPENHOSTSOUND_FAIL 			-30	//打开PC声音失败
#define HB_SDVR_DVRVOICEOPENED 				-31	//服务器语音对讲被占用
#define	HB_SDVR_TIMEINPUTERROR				-32	//时间输入不正确
#define	HB_SDVR_NOSPECFILE				    -33	//回放时服务器没有指定的文件
#define HB_SDVR_CREATEFILE_ERROR			-34	//创建文件出错
#define	HB_SDVR_FILEOPENFAIL				-35	//打开文件出错
#define	HB_SDVR_OPERNOTFINISH				-36	//上次的操作还没有完成
#define	HB_SDVR_GETPLAYTIMEFAIL				-37	//获取当前播放的时间出错
#define	HB_SDVR_PLAYFAIL				    -38	//播放出错
#define HB_SDVR_FILEFORMAT_ERROR			-39	//文件格式不正确
#define HB_SDVR_DIR_ERROR				    -40	//路径错误
#define HB_SDVR_ALLOC_RESOUCE_ERROR			-41	//资源分配错误
#define HB_SDVR_AUDIO_MODE_ERROR			-42	//声卡模式错误
#define HB_SDVR_NOENOUGH_BUF				-43	//缓冲区太小
#define HB_SDVR_CREATESOCKET_ERROR		 	-44	//创建SOCKET出错
#define HB_SDVR_SETSOCKET_ERROR				-45	//设置SOCKET出错
#define HB_SDVR_MAX_NUM					    -46	//个数达到最大
#define HB_SDVR_USERNOTEXIST				-47	//用户不存在
#define HB_SDVR_WRITEFLASHERROR				-48	//写FLASH出错
#define HB_SDVR_UPGRADEFAIL				    -49	//DVR升级失败
#define HB_SDVR_CARDHAVEINIT				-50	//解码卡已经初始化过
#define HB_SDVR_PLAYERFAILED			    -51	//播放器中错误
#define HB_SDVR_MAX_USERNUM					-52	//用户数达到最大
#define HB_SDVR_GETLOCALIPANDMACFAIL	    -53	//获得客户端的IP地址或物理地址失败
#define HB_SDVR_NOENCODEING				    -54	//该通道没有编码
#define HB_SDVR_IPMISMATCH				    -55	//IP地址不匹配
#define HB_SDVR_MACMISMATCH				    -56	//MAC地址不匹配
#define HB_SDVR_UPGRADELANGMISMATCH			-57	//升级文件语言不匹配
#define HB_SDVR_USERISALIVE				    -58	//用户已登陆
#define HB_SDVR_UNKNOWNERROR				-59	//未知错误
#define HB_SDVR_IPERR			        	-101//IP地址不匹配
#define HB_SDVR_MACERR			    		-102//MAC地址不匹配
#define HB_SDVR_PSWERR			    		-103//密码不匹配
#define HB_SDVR_USERERR			    		-104//用户名不匹配
#define HB_SDVR_USERISFULL			    	-105//主机用户满

#pragma pack()

#endif

