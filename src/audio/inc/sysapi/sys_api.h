//////////////////////////////////////////////////////////////////////////////// 
// 版权所有，2009-2010，北京汉邦高科数字技术有限公司。
// 该文件是未公开的，包含了汉邦高科机密和专利内容。
//////////////////////////////////////////////////////////////////////////////// 
// 文件名：    sys_api.h
// 作者：
// 版本：    1.0
// 日期：    2010.5.18
// 描述：
// 历史记录：2010.5.28  添加 api_get_all函数 将协议数据转换为API全局变量数据  lurao
//         2010.5.28  添加 gPtStatas全局变量  lurao
//         2013.2.27  添加 _tag
//////////////////////////////////////////////////////////////////////////////// 

#ifndef _SYS_API_H
#define _SYS_API_H

#include "../common/ipc_common.h"
#define PT_MAX_ACCOUNT 	16
#define PT_GRP_ACCOUNT 	16

typedef HB_S32 PT_MFSDEV_HANDLE;  //设备操作句柄类型

#define    MAX_OSD_NUM   	6     //最多6行OSD
#define    MAX_MASK      	4     //最多4个屏蔽区域
#define    MAX_MOTION    	4     //最多4个移动侦测区域
#define    MAX_DEV_MFS   	16
#define    MAX_PRESET_API	16    // 1个巡航轨迹最多有16个预置点
#define    MAX_STRING    	32
#define    MAX_DNS       	4
#define    MAX_AM        	4
#define    MAX_CH        	16
#define    MAX_PERIOD    	2     //最多时间段
#define    MAX_AMOUT     	1
#define    PT_MAX_RESNUM    16    //最大清晰度个数   根据  PT_RESOLUTION_E

#define    SYSNETAPI_CMD_GET_SYSTIME           	1
#define    SYSNETAPI_CMD_SET_SCHEDULEPARAM     	2
#define    SYSNETAPI_CMD_REBOOT                	3
#define    SYSNETAPI_CMD_QUERY_RECFILESEG      	4
#define    SYSNETAPI_CMD_SET_SYSTIME           	5
#define    SYSNETAPI_CMD_GET_SYSVERSION        	6
#define    SYSNETAPI_CMD_SET_NETCONFIG         	7
#define    SYSNETAPI_CMD_GET_NETCONFIG         	8
#define    SYSNETAPI_CMD_QUERY_DISKINFO        	9
#define    SYSNETAPI_CMD_SET_ENCPARAM          	10
#define    SYSNETAPI_CMD_GET_ENCPARAM          	11
#define    SYSNETAPI_CMD_GET_VIDEOCOLOR        	12
#define    SYSNETAPI_CMD_GET_MULTIAREAMASK     	13
#define    SYSNETAPI_CMD_GET_OSDATTRIBUTE      	14
#define    SYSNETAPI_CMD_GET_CURRECTYPE        	15
#define    SYSNETAPI_CMD_GET_MOTIONPARAM       	16
#define    SYSNETAPI_CMD_GET_MASKLINKPLAN      	17
#define    SYSNETAPI_CMD_SET_VIDEOCOLOR        	18
#define    SYSNETAPI_CMD_SET_MULTIAREAMASK     	19
#define    SYSNETAPI_CMD_SET_OSDATTRIBUTE      	20
#define    SYSNETAPI_CMD_SET_CURRECTYPE        	21
#define    SYSNETAPI_CMD_SET_MOTIONPARAM       	22
#define    SYSNETAPI_CMD_SET_MASKLINKPLAN      	23
#define    SYSNETAPI_CMD_GET_TALKSTREAMFORMAT  	24
#define    SYSNETAPI_CMD_SET_UARTPARAM         	25
#define    SYSNETAPI_CMD_SET_ALMOUTSTATUS      	26
#define    SYSNETAPI_CMD_GET_ALMOUTSTATUS      	27
#define    SYSNETAPI_CMD_SET_ALARMINPARAM      	28

#define    SYSNETAPI_CMD_GET_PTCONFIG          	29
#define    SYSNETAPI_CMD_SET_PTCONFIG          	30
#define    SYSNETAPI_CMD_CLOSE_STREAM          	31
#define    SYSNETAPI_CMD_OPEN_TALKSTREAM       	32
#define    SYSNETAPI_CMD_CLOSE_TALKSTREAM      	33
#define    SYSNETAPI_CMD_OPEN_STREAM           	34
#define    SYSNETAPI_CMD_OPEN_REGALARMINFO     	35
#define    SYSNETAPI_CMD_CLOSE_REGALARMINFO    	36
#define    SYSNETAPI_CMD_GET_PTZCONF           	37
#define    SYSNETAPI_CMD_SET_PTZCONF           	38
#define    SYSNETAPI_CMD_CTRL_PTZ              	39
#define    SYSNETAPI_CMD_QUERYFRAME            	40
#define    SYSNETAPI_CMD_SET_ENCSTATUS         	41
#define    SYSNETAPI_CMD_SHUTDOWN              	42
#define    SYSNETAPI_CMD_SAVE_SYSCONFIG        	43
#define    SYSNETAPI_CMD_GET_PPPOE             	44
#define    SYSNETAPI_CMD_SET_PPPOE             	45
#define    SYSNETAPI_CMD_GET_DDNS              	46
#define    SYSNETAPI_CMD_SET_DDNS              	47
#define    SYSNETAPI_CMD_SET_SYSVERSION        	48
#define    SYSNETAPI_CMD_GET_ALARMINPARAM      	49
#define    SYSNETAPI_CMD_GET_SCHEDULEPARAM     	50
#define    SYSNETAPI_CMD_GET_VLOSTLINKPLAN     	51
#define    SYSNETAPI_CMD_SET_VLOSTLINKPLAN     	52
#define    SYSNETAPI_CMD_GET_ALMPLANCONFIG     	53
#define    SYSNETAPI_CMD_SET_ALMPLANCONFIG     	54
#define    SYSNETAPI_CMD_QUERY_LOGNUM          	55
#define    SYSNETAPI_CMD_QUERY_LOGINFO         	56
#define    SYSNETAPI_CMD_GET_RECCOVERMODE      	57
#define    SYSNETAPI_CMD_SET_RECCOVERMODE      	58
#define    SYSNETAPI_CMD_GET_VIDEOSTATE        	59
#define    SYSNETAPI_CMD_GET_SYSMODE           	60
#define    SYSNETAPI_CMD_SET_SYSMODE           	61
#define    SYSNETAPI_CMD_GET_CURRECSTYPE       	62
#define    SYSNETAPI_CMD_GET_PTZPRESETPOLL     	63
#define    SYSNETAPI_CMD_SET_PTZPRESETPOLL     	64
#define    SYSNETAPI_CMD_START_UPGRADE         	65
#define    SYSNETAPI_CMD_LOG_WRITE			   	66
#define    SYSNETAPI_CMD_GET_IOINFO    		   	67
#define    SYSNETAPI_CMD_GET_WIRELESSNET       	68
#define    SYSNETAPI_CMD_SET_WIRELESSNET       	69
#define    SYSNETAPI_CMD_SET_TALKSTREAMFORMAT  	70
#define    SYSNETAPI_CMD_GET_HOSTCONFIG        	71
#define    SYSNETAPI_CMD_SET_HOSTCONFIG        	72
#define    SYSNETAPI_CMD_GET_UARTPARAM         	73
#define    SYSNETAPI_CMD_SET_NETKEYBOARD       	74
#define    SYSNETAPI_CMD_GET_USERLIST          	75
#define    SYSNETAPI_CMD_SET_USERLIST          	76
#define    SYSNETAPI_CMD_DEFAULT               	77
#define    SYSNETAPI_CMD_GET_MANUALREC    		78
#define    SYSNETAPI_CMD_SET_MANUALREC    		79
#define    SYSNETAPI_CMD_OPEN_VIDEO				80
#define    SYSNETAPI_CMD_CLOSE_VIDEO			81
#define    SYSNETAPI_CMD_CLEARALARM    			82
#define    SYSNETAPI_CMD_SNAPSHOOT    			83
#define    SYSNETAPI_CMD_GET_PTZTYPELIST    	84
#define    SYSNETAPI_CMD_GET_CMSSERVER    		85
#define    SYSNETAPI_CMD_SET_CMSSERVER    		86
#define    SYSNETAPI_CMD_PLAYBACK_CTRL    		87
#define    SYSNETAPI_CMD_BACKUP_OPEN    		88
#define    SYSNETAPI_CMD_BACKUP_CLOSE    		89
#define    SYSNETAPI_CMD_OPEN_SERIALTRANSP    	90
#define    SYSNETAPI_CMD_CLOSE_SERIALTRANSP    	91
#define    SYSNETAPI_CMD_OPEN_VODSTREAM    		92
#define    SYSNETAPI_CMD_CLOSE_VODSTREAM    	93
#define    SYSNETAPI_CMD_RECFILE_OPEN    		94
#define    SYSNETAPI_CMD_RECFILE_CLOSE    		95
#define    SYSNETAPI_CMD_OPEN_UPCALLBACK    	96
#define    SYSNETAPI_CMD_CLOSE_UPCALLBACK    	97
#define    SYSNETAPI_CMD_GET_ALMOUSTATUS    	98
#define    SYSNETAPI_CMD_SET_ALMOUSTATUS    	99
#define    SYSNETAPI_CMD_ENCODESTREAMREADOPEN 	100
#define    SYSNETAPI_CMD_ENCODESTREAMREADCLOSE  101
#define    SYSNETAPI_CMD_GET_ALL    			102
#define    SYSNETAPI_CMD_OPEN_PSTREAM 			103
#define    SYSNETAPI_CMD_OPEN_SSTREAM 			104
#define    SYSNETAPI_CMD_CLOSE_PSTREAM 			105
#define    SYSNETAPI_CMD_CLOSE_SSTREAM 			106
 
//#define   SYSNETAPI_CMD_GET_IPCWORKPARAM 		105
//#define   SYSNETAPI_CMD_SET_IPCWORKPARAM 		106

#define   SYSNETAPI_CMD_OPEN_FORMATFUNC  		107
#define   SYSNETAPI_CMD_CLOSE_FORMATFUNC 		108
#define   SYSNETAPI_CMD_START_DISKFORMAT 		109
#define   SYSNETAPI_CMD_GET_FORMATSTAT   		110
#define   SYSNETAPI_CMD_GET_RESOLUTION_LIST      111
#define   SYSNETAPI_CMD_SET_RESOLUTION_LIST      112
#define   SYSNETAPI_CMD_GET_IPCWORKPARAM         113
#define   SYSNETAPI_CMD_SET_IPCWORKPARAM         114

#define   SYSNETAPI_CMD_GET_IPCPORTMAP           115
#define   SYSNETAPI_CMD_IPCONFIG_EX_GET          (0xBE)//190
#define   SYSNETAPI_CMD_IPCONFIG_EX_SET          (0xBF)//191

#if 0
#define RESOLUTION_1080P   						0x07800438
#define RESOLUTION_720P  						0x050002D0
#define RESOLUTION_D1       					0x02D00240
#define RESOLUTION_CIF							0x01600120
#endif

//默认开启A5选项
//#if defined(DM36X)|| defined(A5S)||defined(A2)
//#else
//#define A5S
//#endif

#if defined(DM36X) || defined(HI3518)
#define RESOLUTION_1080P       0x07800438
#define RESOLUTION_720P        0x050002D0
#define RESOLUTION_768x432     0x030001b0//768x432

#ifdef HB_ARCH_NEW
#define RESOLUTION_D1          0x02c00240
#define RESOLUTION_QVGA        0x014000C0
#else
#define RESOLUTION_D1          0x02c00240
#define RESOLUTION_QVGA        0x014000C0
//#define RESOLUTION_D1          0x02D001E0
//#define RESOLUTION_QVGA        0x014000BE
#endif

#define RESOLUTION_VGA	       0x02800170//640x368
#define RESOLUTION_CIF         0x01600120


//#define RESOLUTION_VGA	   0x02800170//640x368
#define RESOLUTION_D1_NEW      0x02c00240//704x576
#define RESOLUTION_QVGA_NEW    0x014000C0//320x192

#elif defined(A2)
#define RESOLUTION_1080P    0x07800438
#define RESOLUTION_720P     0x050002D0
#define RESOLUTION_D1       0x02D00240
#define RESOLUTION_CIF      0x01600120
#define RESOLUTION_VGA	    0xFFFFFFFF//640x368
#define RESOLUTION_768x432 0xFFFFFFFF
#define RESOLUTION_QVGA  0xFFFFFFFF

#elif defined(A5S)
#define RESOLUTION_1080P    0x07800438
#define RESOLUTION_960P     0x050003c0     // 1108 lili
#define RESOLUTION_720P     0x050002D0
#define RESOLUTION_CIF      0x01600120    //
#define RESOLUTION_VGA      0xffffffff
#define RESOLUTION_768x432  0xffffffff
#define RESOLUTION_QVGA      0xffffffff

#ifdef HB_ARCH_NEW
#define RESOLUTION_D1      0x02c00240//704x576
#else
#define RESOLUTION_D1       0x02D00240
#endif


#endif

#define   TM_COM_GUI_LOGIN        	0x00010000  //登录
#define   TM_COM_GUI_RECORD       	0x00010001  //录像
#define   TM_COM_GUI_PLAYBACK     	0x00010002  //回放
#define   TM_COM_GUI_SETUP        	0x00010003  //设置
#define   TM_COM_GUI_BACKUP       	0x00010004  //备份
#define   TM_COM_GUI_DN           	0x00010007  //主机号
#define   TM_COM_GUI_CN           	0x00010008  //中文
#define   TM_COM_GUI_DIGIT        	0x00010009  //数字（参数为0、1、2、3、 4、5、6、7、8、9）
#define   TM_COM_GUI_CHAR         	0x0001000a  //字符（参数为A、B、C…………..X、Y、Z、*、#）
#define   TM_COM_GUI_BKSPACE      	0x0001000b  //删除
#define   TM_COM_GUI_UP           	0x0001000c  //上
#define   TM_COM_GUI_DOWN         	0x0001000d  //下
#define   TM_COM_GUI_LEFT         	0x0001000e  //左
#define   TM_COM_GUI_RIGHT        	0x0001000f  //右
#define   TM_COM_GUI_PAGEUP       	0x00010010  //上页
#define   TM_COM_GUI_PAGEDOWN     	0x00010011  //下页
#define   TM_COM_GUI_RETURN       	0x00010012  //返回
#define   TM_COM_GUI_ENTER        	0x00010013  //确认
#define   TM_COM_GUI_NEAR         	0x00010014  //摄像头近
#define   TM_COM_GUI_FAR          	0x00010015  //摄像头远
#define   TM_COM_GUI_ZOOMIN       	0x00010016  //摄像头变焦近（ZOOM+）
#define   TM_COM_GUI_ZOOMOUT      	0x00010017  //摄像头变焦远（ZOOM-）
#define   TM_COM_GUI_APER_INC     	0x00010018  //摄像头光圈+
#define   TM_COM_GUI_APER_DEC     	0x00010019  //摄像头光圈-
#define   TM_COM_GUI_PRESET_SET   	0x0001001a  //摄像头预置
#define   TM_COM_GUI_PRESET_GET   	0x0001001b  //摄像头调用
#define   TM_COM_GUI_AUTO         	0x0001001c  //摄像头自动
#define   TM_COM_GUI_MUTE         	0x0001001d  //静音
#define   TM_COM_GUI_INFO         	0x0001001e  //信息
#define   TM_COM_GUI_STEP         	0x0001001f  //帧进
#define   TM_COM_GUI_PLAY         	0x00010020  //播放
#define   TM_COM_GUI_FASTF        	0x00010021  //快进
#define   TM_COM_GUI_FASTB        	0x00010022  //快退
#define   TM_COM_GUI_CLRALT       	0x00010023  //报警清除
#define   TM_COM_GUI_F1           	0x00010024
#define   TM_COM_GUI_F2           	0x00010025
#define   TM_COM_GUI_IGEFORMAT    	0x00010026  //画面格式
#define   TM_COM_GUI_IGESWITCH    	0x00010027  //画面轮换
#define   TM_COM_GUI_STOP         	0x00010028
#define   TM_COM_GUI_SHUTDOWN     	0x00010029   //电源
#define   TM_COM_GUI_PWDRST       	0x0001002a   //密码复位
#define   TM_COM_GUI_F1VGA2TV     	0x0001002b   //vga与电视切换
#define   TM_COM_GUI_MOUSESTATUS  	0x0001002c   //鼠标
#define   TM_COM_GUI_VIDEOPARAM   	0x0001002d   //视频参数
#define   TM_COM_GUI_BRUSH        	0x0001002e   //雨刷
//GUI TO COM

#define   TM_GUI_COM_SETTIME      	0x01000000 //设置时间
#define   TM_GUI_COM_SETPWD       	0x01000001 //密码设置
#define   TM_GUI_COM_BOOTSTART    	0x01000002 //开机
#define   TM_GUI_COM_REBOOT       	0x01000003 //重启
#define   TM_GUI_COM_SHUTDOWN     	0x01000004 //关机
#define   TM_GUI_COM_BUZZER       	0x01000005 //前面板蜂鸣器响

//GUI TO GUI
#define   TM_GUI_GUI_PIP            0x01010000 //开启画中画
#define   TM_GUI_GUI_PIPSWITCH      0x01010001 //画中画切换
#define   TM_GUI_GUI_SAVECFG        0x01010002 //save system status to flash
#define   TM_GUI_GUI_FORMAT         0x01010003
#define   TM_GUI_GUI_CONTINUE       0x01010004
#define   TM_GUI_GUI_INPUTINFO      0x01010005  //弹出输入框
#define   TM_GUI_GUI_VPARAM         0x01010006
#define   TM_GUI_GUI_NETCHANGE      0x01010007
#define   TM_GUI_GUI_SHUTDOWN       0x01010008
#define   TM_GUI_GUI_PLAY           0x01010009
#define   TM_GUI_GUI_SMARTSTATUS    0x0101000a
#define   TM_GUI_GUI_FDISK          0x0101000b

//root to gui
#define   TM_ROOT_GUI_START       	0x02010000
#define   TM_ROOT_GUI_FINISH      	0x02010001
#define   TM_ROOT_GUI_NOSPACE     	0x02010002
#define   TM_ROOT_GUI_NODISK      	0x02010003
#define   TM_ROOT_GUI_DISKPARTRAW 	0x02010004
#define   TM_ROOT_GUI_DISKRAW     	0x02010005
#define   TM_ROOT_GUI_NODATAPART  	0x02010006
#define   TM_ROOT_GUI_DISKINSTALL 	0x02010007
#define   TM_ROOT_GUI_DISKUNINSTL 	0x02010008

//sysstatcheck to com
#define   TM_RSTATUS_COM_RCDINFO    0x06000000  //录像指示灯
#define   TM_RSTATUS_COM_ALARMREC   0x06000001  //报警指示灯
#define   TM_RSTATUS_COM_LAMP       0x06000002  //0bit-alarm 1bit-lock 2bit-network

//sysstatcheck to gui
#define   TM_RSTATUS_GUI_LOG       	0x06010000

//GUI TO DEMUX
#define   TM_GUI_PLAYBAK_START  	0x01050000
#define   TM_GUI_PLAYBAK_STOP   	0x01050001
#define   TM_GUI_PLAYBAK_PAUSE  	0x01050002
#define   TM_GUI_PLAYBAK_PLAY   	0x01050003
#define   TM_GUI_PLAYBAK_FF     	0x01050004
#define   TM_GUI_PLAYBAK_SF     	0x01050005
#define   TM_GUI_PLAYBAK_FB     	0x01050006
#define   TM_GUI_PLAYBAK_SP     	0x01050007


#define   TM_PLAY_GUI_PLAYEND   	0x05010000
#define   TM_PLAY_GUI_NODATA    	0x05010001

#define   TM_NET_GUI_UPGRADE    	0x04010000
#define   TM_PPPOE_GUI_HANDLE   	0x04010001
#define   TM_DDNS_GUI_HANDLE    	0x04010002
#define   TM_DHCP_GUI_HANDLE    	0x04010003
#define   TM_NET_GUI_SETIP      	0x04010004
#define   TM_NET_GUI_DEFAULT    	0x04010005

#define   TM_BACKUP_GUI_RESULT  	0x09010000

#if 0
typedef HB_CHAR               HB_CHAR;
typedef short              sint16;
typedef HB_S32                HB_S32;
typedef long long          sint64;
//typedef HB_U8      HB_U8;
//typedef HB_U16     HB_U16;
typedef HB_U32       HB_U32;
typedef unsigned long long HB_U64;
#endif


#ifndef _BYTE
#define _BYTE
//typedef HB_U8 HB_U8;
#endif
#ifndef _DATE_DEFI_
#define _DATE_DEFI_

//typedef HB_U8 BOOL;
//typedef HB_U16 HB_U16;
//typedef unsigned long HB_U32;

#endif

//音视频数据发送函数指针
typedef HB_S32 (*PNETSETVSTREAM)(HB_S32 idx, HB_CHAR* data, HB_U32 size,HB_S32 flag, HB_VOID* paramin);

//对讲频数据发送（DVR-->PC）函数指针
typedef HB_S32 (*PNETSETASTREAM)(HB_CHAR* pdata, HB_U32 len, HB_S32 type, HB_VOID* paramin);

//报警信息上传函数指针
typedef HB_S32 (*PNETSETALARMINFO)(HB_S32 ch, HB_S32 type, HB_S32 clear, HB_VOID* paramin);

//处理ipc返回命令回调函数
HB_VOID cmd_data_callback(HB_U16 cmd, HB_CHAR *cmd_buf, HB_S32 cmd_len, HB_S32 result);
//格式化回调函数
typedef HB_VOID (*PNETNOTIFYCALL) (HB_S32 wparam, HB_S32 lparam);

typedef enum _tagPT_PROTOCOL_E
{
    PTZ_UNKNOWN, // 0
    PTZ_RV800,
    PTZ_TOTA120,
    PTZ_S1601,
    PTZ_CLT_168,
    PTZ_TD_500,
    PTZ_V1200,
    PTZ_ZION,
    PTZ_ANT,
    PTZ_CBC,
    PTZ_CS850A, // 10
    PTZ_CONCORD,
    PTZ_HD600,
    PTZ_SAMSUNG,
    PTZ_YAAN,
    PTZ_PIH, //利凌
    PTZ_MG_CS160,
    PTZ_WISDOM,
    PTZ_PHILIPS,
    PTZ_NEOCAM,
    PTZ_ZHCD, //20
    PTZ_DONGTIAN,
    PTZ_EMERSON,
    PTZ_TOTA160,
    PTZ_BANGTVD,
    PTZ_BANGTVP,
    PTZ_SANSHAND,
    PTZ_SANSHANP,
    PTZ_LILIN1,
    PTZ_LILIN2,
    PTZ_PDDR, // PLECOD东容 30
    PTZ_PPDR, //PLECOP东容
    PTZ_TOYANI,
    PTZ_HY,
    PTZ_TEOP,
    PTZ_PELCOD1,
    PTZ_PELCOD2,
    PTZ_PELCOD3,
    PTZ_PELCOD4,
    PTZ_PELCOD5,
    PTZ_PELCOD7, //40
    PTZ_PELCOD_ZH,
    PTZ_PELCOD_5F,
    PTZ_PELCOD,
    PTZ_PELCO_D,
    PTZ_PELCOP1,
    PTZ_PELCOP2,
    PTZ_PELCOP3,
    PTZ_PELCOP5,
    PTZ_PELCOP6,
    PTZ_PELCOP7, //50
    PTZ_PELCO_P
} PT_PROTOCOL_E;

typedef struct _tagPT_PTZPARAM
{
    HB_U32    type;      //云台类型 详细见PT_PTZTYPE_E
    HB_U32    addr;      //云台地址码
    HB_U32    speed;     //云台速度
   // HB_U32    rate;    //云台波特率
}PT_PTZPARAM_S;  //设置/获取云台配置参数===


typedef enum _tagPT_PTZCMD
{
    SYSNETAPIPTZ_CMD_STOP ,
    SYSNETAPIPTZ_CMD_UP,          //上
    SYSNETAPIPTZ_CMD_DOWN,        //下
    SYSNETAPIPTZ_CMD_LEFT,        //左
    SYSNETAPIPTZ_CMD_RIGHT,       //右
    SYSNETAPIPTZ_CMD_ZOOMIN,      //ZOOM+
    SYSNETAPIPTZ_CMD_ZOOMOUT,     //ZOOM-
    SYSNETAPIPTZ_CMD_APER_INC,    //光圈+
    SYSNETAPIPTZ_CMD_APER_DEC,    //光圈-
    SYSNETAPIPTZ_CMD_FAR,         //远
    SYSNETAPIPTZ_CMD_NEAR,        //近
    SYSNETAPIPTZ_CMD_F1,          //辅助
    SYSNETAPIPTZ_CMD_F1_1,
    SYSNETAPIPTZ_CMD_F2,          //辅助
    SYSNETAPIPTZ_CMD_F2_1,
    SYSNETAPIPTZ_CMD_AUTO,        //自动
    SYSNETAPIPTZ_CMD_AUTO_1,
    SYSNETAPIPTZ_CMD_PRESET_SET,  //预置
    SYSNETAPIPTZ_CMD_PRESET_GET,  //调用
    SYSNETAPIPTZ_CMD_SETUP,
    SYSNETAPIPTZ_CMD_ENTER,
    SYSNETAPIPTZ_CMD_PAGEUP,
    SYSNETAPIPTZ_CMD_PAGEDOWN,
    SYSNETAPIPTZ_CMD_BRUSH,      //雨刷
}PT_PTZCMD_E;


typedef struct _tagPT_PTZCTRL
{
    HB_U32   cmd;     //云台控制命令详见PT_PTZCMD_E
    HB_U32   param;   //设置参数
}PT_PTZCTRL_S; //设置的云台控制命令结构体===


typedef struct _tagPT_SYSCOLOR
{
    HB_U32    bright;        //亮度0-255
    HB_U32    contrast;      //对比度0-255
    HB_U32    saturation;    //饱和度0-255
    HB_U32    hue;           //色度0-255
    HB_U32    sharp;         //锐度 0或1
}PT_SYSCOLOR_S; //获取/设置的视频参数结构体指针===

typedef struct _tagPT_TIME
{
    HB_U16    year;    //年 如2009
    HB_U16    month;   //月 1-12
    HB_U8     day;     //日 1-31
    HB_U8     hour;    //小时 0-23
    HB_U8     minute;  //分钟 0-59
    HB_U8     second;  //秒 0-59
    HB_U32    msec;    //毫秒
}PT_TIME_S;

typedef enum _tagPT_WEEK_E
{
    PT_WEEK_SUN,    //星期日
    PT_WEEK_MON,    //星期一
    PT_WEEK_TUES,   //星期二
    PT_WEEK_WED,    //星期三
    PT_WEEK_THUR,   //星期四
    PT_WEEK_FRI,    //星期五
    PT_WEEK_SAT,    //星期六
}PT_WEEK_E;

typedef struct _tagPT_SYSTIME
{
    PT_TIME_S    time;
    PT_WEEK_E    week; //星期
}PT_SYSTIME_S;         //获取/设置的当前时间结构体指针===

typedef enum _tagPT_STREAMTYPE
{
    PT_TYPE_PRI,  //主码流
    PT_TYPE_SEC,  //子码流
}PT_STREAMTYPE_E;

typedef enum _tagPT_ENABLE
{
    PT_DISABLE,   //关闭
    PT_ENABLE,    //开启
}PT_ENABLE_E;

typedef enum _tagPT_NETMODE
{
    PT_AUTOMODE,       //自适应
    PT_HALFMODE_10M,   //10M半双工
    PT_FULLMODE_10M,   //10M全双工
    PT_HALFMODE_100M,  //100M半双工
    PT_FULLMODE_100M,  //100M全双工
    PT_FULLMODE_1000M  //1000M全双工
}PT_NETMODE_E;

typedef struct _tagPT_ENCSTATUS
{
    PT_STREAMTYPE_E    type;
    PT_ENABLE_E        enable;
}PT_ENCSTATUS_S; //编码状态结构体指针===

typedef struct _tagPT_MULTICAST
{
    HB_U32    enable;
    HB_U32    ip_addr;
    HB_U16    port[MAX_CH]; //多播端口
}PT_MULTICAST_S;//40

typedef struct _tagPT_IPCONFIG
{
    HB_CHAR         type[MAX_STRING];   //网卡类型 区别各个网卡
    HB_U32          ip;                 //dvr ip地址
    HB_U32          mask;               //dvr子码掩码
    HB_U32          gateway;            //网关
    HB_U32          dns[2];             //DNS
    HB_U8           mac_addr[8];        //物理地址
    PT_NETMODE_E    phy_mode;           //phy_mode
}PT_IPCONFIG_S; //64

typedef struct _tagPT_NETCONFIG
{
    HB_CHAR host_name[MAX_STRING];  //主机名
    PT_IPCONFIG_S ip_config;        
    HB_U16 cmdport;                 //主机命令端口
    HB_U16 httpport;                //主机http端口
    PT_MULTICAST_S multicast;       //多播配置
}PT_NETCONFIG_S; //设置/获取的网络配置结构体指针===

typedef enum _tagPT_AUTOENABLE_E
{
    PT_AUTO_DISABLE,  //不自动连接
    PT_AUTO_ENABLE,   //自动连接
}PT_AUTOENABLE_E;

typedef enum _tagPT_SAVEPWD_E
{
    PT_SAVEPWD_DISABLE,   //不保存密码
    PT_SAVEPWD_ENABLE,    //保存密码
}PT_SAVEPWD_E;

typedef enum _tagPT_SUCCESS_E
{
    PT_SUCCESS_FAIL,   //失败
    PT_SUCCESS_SUCC,   //成功
}PT_SUCCESS_E;

typedef enum _tagPT_CONNECT_E
{
    PT_CONNECT_NO,   //断开
    PT_CONNECT_YES,  //连接
    PT_NOOPERATE     //无动作
}PT_CONNECT_E;

typedef struct _tagPT_PPPOECONFIG
{
    HB_U8               user[MAX_STRING];     //用户名
    HB_U8               pwd[MAX_STRING];      //密码
    PT_AUTOENABLE_E     auto_connect;         //是否自动连接
    PT_SAVEPWD_E        save_pwd;             //是否保存密码
    PT_SUCCESS_E        status;               //是否解析成功
    PT_CONNECT_E        command;
    PT_IPCONFIG_S       ip_config;
}PT_PPPOECONFIG_S; //获取/设置的拨号网络配置结构体指针===

typedef struct _tagPT_DDNSCONFIG
{
    HB_U8               index;                        //ddns索引
    HB_U8               server[MAX_STRING];           //当前服务器地址
    HB_U8               user[MAX_STRING];             //用户名
    HB_U8               pwd[MAX_STRING];              //密码
    HB_U8               dn[MAX_DNS] [MAX_STRING];     //解析的地址 可支持返回最多4个DNS域名
    HB_U32              ip_addr;                      //服务器返回的IP地址
    PT_AUTOENABLE_E     auto_connect;                 //是否为自动连接
    PT_SUCCESS_E        status;                       //是否解析成功
    PT_CONNECT_E        command; 
}PT_DDNSCONFIG_S; //获取/设置的DDNS配置结构体指针===

typedef struct _tagPT_VERSION
{
    HB_U32    minver;     //阶段版本号
    HB_U32    secver;     //子版本号
    HB_U32    majver;     //主版本号
    PT_TIME_S time;
} PT_VERSION_S, *PPT_VERSION_S; //获取/设置的版本号结构体指针===

typedef enum _tagPT_AUSTREAMADD
{
    PT_AUSTREAM_DISABLE,   //视频流
    PT_AUSTREAM_ENABLE,    //复合流
}PT_AUSTREAMADD_E;

typedef enum _tagPT_RESOLUTION
{
    PT_QCIF,     //QCIF
    PT_QVGA,     //QVGA
    PT_CIF,      //CIF
    PT_DCIF,     //DCIF
    PT_HD1,      //HD1
    PT_VGA,      //VGA
    PT_FD1,      //FD1
    PT_SD,       //SD
    PT_HD,       //HD
    PT_1080P,    //1080p
    PT_960P,      //960p only a5 caozg add
    PT_768x432    //added new
}PT_RESOLUTION_E;

typedef enum _tagPT_BITRATETYPE
{
    PT_BITRATE_NOCHANGE,   //定码率
    PT_BITRATE_CHANGE,     //变码率
}PT_BITRATETYPE_E;

typedef enum _tagPT_VQUALITY
{
    PT_VQUALITY_BEST = 0,    //最好
    PT_VQUALITY_BETTER,      //次好
    PT_VQUALITY_GOOD,        //较好
    PT_VQUALITY_NORMAL,      //一般
    PT_VQUALITY_BAD,         //较差
    PT_VQUALITY_WORSE        //差
}PT_VQUALITY_E;

typedef struct _tagPT_ENCCONFIG
{
    PT_AUSTREAMADD_E    byStreamType;         //码流类型
    PT_RESOLUTION_E     byResolution;         //视频分辨率
    PT_BITRATETYPE_E    byBitrateType;        //码率类型
    PT_VQUALITY_E       byPicQuality;         //图像质量
    HB_U32              dwVideoBitrate;       //视频码率 实际码率
    HB_U16              dwVideoFrameRate;     //帧率 PAL 2-30 N 2-30
    HB_U16              quant;                //量化因子 1-31
}PT_ENCCONFIG_S;
//录像属性

typedef enum _tagPT_RECTYPE_E
{
    SYENETAPI_REC_TYPE_UNKNOW     =  0,
    SYENETAPI_REC_TYPE_MANUAL     =  1,     //手动录像
    SYENETAPI_REC_TYPE_SCHEDULE   =  2,     //定时录像
    SYENETAPI_REC_TYPE_MOTION     =  4,     //移动录像
    SYENETAPI_REC_TYPE_ALARM      =  8,     //报警录像
    SYENETAPI_REC_TYPE_ALL        =  0xff   //所有
}PT_RECTYPE_E;

typedef struct _tagPT_STREAMENCPARAM
{
    PT_STREAMTYPE_E    streamtype;     //要设置或者获取的码流类型
    PT_RECTYPE_E       rectype;        //录像类型
    PT_ENCCONFIG_S     enc;            //编码参数
}PT_STREAMENCPARAM_S; //设置/获取的视频流编码参数结构体指针===

typedef struct _tagPT_AREA
{
    HB_U32    left;       //起始点横坐标
    HB_U32    top;        //起始点纵坐标
    HB_U32    width;      //宽度
    HB_U32    height;     //高度
}PT_AREA_S;

typedef enum _tagPT_MASKENABLE_E
{
    PT_MASK_DISABLE,  //不屏蔽
    PT_MASK_ENABLE,   //屏蔽
}PT_MASKENABLE_E;

typedef struct _tagPT_MASKPARAM
{
    PT_MASKENABLE_E   enable; 
    HB_S32            num;             //区域个数
    PT_AREA_S         area[MAX_MASK];
}PT_MASKPARAM_S; //获取/设置的多区域屏蔽参数结构体指针===

typedef struct _tagPT_TMPERIOD
{
    HB_U32    starth;    //开始小时
    HB_U32    startm;    //开始分钟
    HB_U32    endh;      //结束小时
    HB_U32    endm;      //结束分钟
}PT_TMPERIOD_S;


typedef enum _tagPT_STATUS_E
{
    PT_STATUS_ON,    //NO/OFF
    PT_STATUS_OFF,   //YES/ON
}PT_STATUS_E;


typedef struct _tagPT_TMITEM
{
    PT_STATUS_E      bselect;              //0-no 1-yes
    PT_TMPERIOD_S    period[MAX_PERIOD];   //布防时间
}PT_TMITEM_S;


typedef struct _tagPT_TMSCHEDULE
{
    PT_STATUS_E    bstatus;     //0-off, 1-on
    PT_TMITEM_S    item[8];     //0-7: everyday, monday...sunday
}PT_TMSCHEDULE_S; //获取/设置的定时录像参数结构体指针===


typedef enum _tagPT_LINKSTATUS
{
    PT_LINKSTATUS_DISABLE,   //不联动
    PT_LINKSTATUS_ENABLE,    //联动
}PT_LINKSTATUS_E;


typedef enum _tagPT_SENSITIVITY
{
    PT_LOWER=1,   //最低
    PT_LOW,       //低
    PT_NORMAL,    //正常
    PT_HIGH,      //高
    PT_HIGHER,    //最高
}PT_SENSITIVITY_E;


typedef enum _tagPT_BLOCKENABLE
{
    PT_BLOCK_DISABLE,   //坐标设置移动侦测区域
    PT_BLOCK_ENABLE,    //块设置移动侦测区域
}PT_BLOCKENABLE_E;


typedef enum _tagPT_ALMTYPE
{
    PT_ALMTYPE_OPEN,    //常开
    PT_ALMTYPE_CLOSE,   //常闭
}PT_ALMTYPE_E;


typedef struct _tagPT_LINKOUTPARAM
{
    PT_TMSCHEDULE_S     schedule;     //布防时间设置
    HB_U32              almdelay;     //报警延时时间 缺省为0
    HB_U32              almoutsec;    //报警输出时间
}PT_LINKOUTPARAM_S;


typedef struct _tagPT_LINKRECPARAM
{
    PT_TMSCHEDULE_S   schedule;         //布防时间设置
    HB_U32            recordtime;       //联动报警录像时间
    HB_U32            prerecordtime;    //预录时间
}PT_LINKRECPARAM_S;


typedef struct _tagPT_LINKPRESETPARAM
{
    HB_U32              stay_time;                     //停留时间
    HB_U32              alm2preset[MAX_PRESET_API];    //联动跳预置点
    PT_TMSCHEDULE_S     schedule;                      //布防时间设置
}PT_LINKPRESETPARAM_S;


typedef struct _tagPT_LINKSNAPPARAM
{
    PT_TMSCHEDULE_S     schedule;       //布防时间设置
    HB_U32              snaptimes;      //抓拍次数
    HB_U32              snaptimeval;    //抓拍间隔 以秒为单位
}PT_LINKSNAPPARAM_S;


typedef struct _tagPT_ALMLINKPLAN
{
    HB_U32    almout[MAX_AMOUT];       //联动报警输出
    HB_U32    record[MAX_CH];          //联动录像
    HB_U32    presetenable[MAX_CH];    //联动跳预置点
    HB_U32    snap[MAX_CH];            //联动抓拍
}PT_ALMLINKPLAN_S;

typedef struct _tagPT_PLANCONFIG
{
    PT_LINKOUTPARAM_S       almout[MAX_AMOUT];
    PT_LINKRECPARAM_S       rec[MAX_CH];
    PT_LINKPRESETPARAM_S    preset[MAX_AM];
    PT_LINKSNAPPARAM_S      snap[MAX_CH];
}PT_PLANCONFIG_S;//获取/设置的主机报警预案配置参数结构体指针===

typedef struct _tagPT_MOTIONRECPARAM
{
    PT_TMSCHEDULE_S       schedule;            //布防时间设置
    PT_SENSITIVITY_E      sensitivity;         //
    HB_U32                block[18];           //移动侦测块设置侦测区域
    HB_U32                num;                 //移动侦测区域个数
    PT_BLOCKENABLE_E      block_enable;        //侦测区域设置方0-坐标设置侦测区域 1-移动侦测块设置侦测区域
    PT_AREA_S             area[MAX_MOTION];    //坐标设置移动侦测区域
    PT_ALMLINKPLAN_S      plan;                //报警联动预案
    HB_U16                enalmmax;            // 1-senor or move alarm to chang one real window
    HB_U16                almoutbuzzer;        //报警送蜂鸣器
    HB_U32                mail_enable;         //报警邮件全能 0-关闭   1-开启
}PT_MOTIONRECPARAM_S; //获取/设置的移动报警录像参数结构体指针===

typedef struct _tagPT_ALARMINRECPARAM
{
    HB_U8                almin_name[MAX_STRING];     //探头号
    HB_U16               enalmmax;                   // 1-senor or move alarm to chang one real window
    HB_U16               almoutbuzzer;               //报警送蜂鸣器
    PT_ALMTYPE_E         almtype;                    //探头类型 0-常闭 1-常开
    PT_TMSCHEDULE_S      schedule;                   //布防时间配置
    PT_ALMLINKPLAN_S     plan;                       //报警联动预案
}PT_ALARMINRECPARAM_S;                               //获取/设置的探头报警录像参数结构体指针===

typedef struct _tagPT_MFSTIME
{
    unsigned     second  :  6;     // 秒: 0~59
    unsigned     minute  :  6;     //分钟: 0~59
    unsigned     hour    :  5;     // 小时: 0~23
    unsigned     day     :  5;     // 日: 1~31
    unsigned     month   :  4;     // 月: 1~12
    unsigned     year    :  6;     // 年: 2000~2063
}PT_MFSTIME_S ;

typedef struct _tagPT_RecSegInfo
{
    PT_MFSTIME_S    begin_time, end_time;      //查询开始时间，结束时间
    HB_U32          lengh;
    HB_U8           ch;                        //通道名
    HB_U8           type;                      //录像类型
}PT_RecSegInfo_S; //打开的备份录像文件结构体指针===

typedef struct _tagPT_RECFILESEG
{
    PT_SYSTIME_S        time_bg,time_ed;     //查询开始时间，结束时间
    PT_RECTYPE_E        type;                //录像类型
    PT_RecSegInfo_S     *data;               //录像段信息buffer
    HB_U32              start;               //读取像段的起始号（从0开始）
    HB_U32              limit;               //想读取的录像段数(buffer_length / sizeof(PLATFORM_Mfs_RecSeg_Info))
    HB_U32              total_num;           //输出符合条件的录像段总数（output）
    HB_U32              realmum;             //实际读出录像数量（output）
}PT_RECFILESEG_S; //设置的定时录像参数结构体指针===


typedef struct _tagPT_SEGSTREAMREADOPEN
{
    PT_TIME_S        time;            //打开录像日期
    PT_RECTYPE_E     type;            //打开录像类型
    HB_U32           openrec_handle;  //打开录像句柄(output)
}PT_SEGSTREAMREADOPEN_S; //设置的打开流参数结构体指针===

//打开录像文件的结构体指针===
//以下是放像结构体说明
typedef enum _tagPT_PLAYBACKSTATUS_E
{ //放像控制命令
    SYSNETAPI_VOD_PLAY = 0,
    SYSNETAPI_VOD_PAUSE,        //暂停
    SYSNETAPI_VOD_STOP,         //停止
    SYSNETAPI_VOD_FASTFORWARD,  //
    SYSNETAPI_VOD_SLOWFORWARD,  //
    SYSNETAPI_VOD_FASTBACKWARD, //
    SYSNETAPI_VOD_FRAMEFORWARD, //
    SYSNETAPI_VOD_SEEK,         //拖进度条
    SYSNETAPI_VOD_TIMEJUMP,     //跳到指定时间
}PT_PLAYBACKSTATUS_E;

typedef enum _tagPT_PLAYBACKSPEED_E
{ //·放像速率
    SYSNETAPI_SPEED_2X,//
    SYSNETAPI_SPEED_4X,//
    SYSNETAPI_SPEED_16X,
    SYSNETAPI_SPEED_64X,
}PT_PLAYBACKSPEED_E;

typedef union _tagPT_MFSTIME_U
{
    HB_U32          longtime;
    PT_MFSTIME_S    fieldtime;
}PT_MFSTIME_U;
typedef struct _tagPT_PLAYBACKPARA
{
    PT_PLAYBACKSTATUS_E    status;
    HB_U32                 param;//当status 为SYSNETAPI_VOD_SEEK时，param为0-99 当status为SYSNETAPI_VOD_TIMEJUMP时，param为时间结构体PT_MFSTIME_U中的longtime
}PT_PLAYBACKPARA_S; //回放结构体指针===


typedef enum _tagPT_READSPEED
{ //放像速率
    SYSNETAPI_READ_NORMAL       =  0,
    SYSNETAPI_READ_FORWARD      =  0x10,      //关键帧进（不作为放像使用）
    SYSNETAPI_READ_FORWARD_1X   =  0x11,      //关键帧读出
    SYSNETAPI_READ_FORWARD_2X   =  0x12,      //2倍间隔关键帧读出
    SYSNETAPI_READ_FORWARD_3X   =  0x13,      //3倍
    SYSNETAPI_READ_FORWARD_4X   =  0x14,      //4倍
    SYSNETAPI_READ_FORWARD_5X   =  0x15,      //5倍
    SYSNETAPI_READ_BACKWARD     =  0x20,      //关键帧退（不作为放像使用）
    SYSNETAPI_READ_BACKWARD_1X  =  0x21,      //关键帧退
    SYSNETAPI_READ_BACKWARD_2X  =  0x22,      //2倍间隔关键帧退
    SYSNETAPI_READ_BACKWARD_3X  =  0x23,      //3倍
    SYSNETAPI_READ_BACKWARD_4X  =  0x24,      //4倍
    SYSNETAPI_READ_BACKWARD_5X  =  0x25,      //5倍
    SYSNETAPI_READ_SEEK = 0x40//读seek
}PT_READSPEED_E;


typedef struct _tagPT_ENCODESTREAMREAD
{
    HB_U32            openrec_handle;    //打开录像句柄
    PT_READSPEED_E    speed;             //读数据速度
    HB_U32            size;              //读取数据大小buffer长度
    PT_TIME_S         time;              //当前帧所在关键帧的所属时间(output)
    HB_U32            len;               //实际读出的码流长度(output)
    HB_U8             *data;             //存放读书数据缓冲区地址(output)
}PT_ENCODESTREAMREAD_S; //读出放像流===

typedef struct _tagPT_ENCODESTREAMREADSEG
{
    HB_U32             openrec_handle;    //打开录像句柄
    PT_READSPEED_E     speed;             //读数据速度
    HB_U32             size;              //读取数据大小buffer长度
    HB_U32             percent;           //当speed == SYSNETAPI_READ_SEEK , 用此值定义定位百分比(0~99)
    HB_U32             len;               //实际读出的码流长度(output)
    HB_U8              *data;             //存放读出数据缓冲区地址(output)
}PT_ENCODESTREAMREADSEG_S; //读取一段录像数据===

typedef enum _tagPT_SHOW_E
{
    PT_SHOW_DISABLE,   //不显示
    PT_SHOW_ENABLE,    //显示
}PT_SHOW_E;

typedef enum _tagPT_DATEFORMAT_E
{
    PT_DATE_Y_M_D,    //XXXX-XX-XX年月日
    PT_DATE_M_D_Y,    //XX-XX-XXXX月日年
    PT_DATE_YMD,      //XXXX年XX月XX日
    PT_DATE_MDY       //XX月XX日XXXX年
}PT_DATEFORMAT_E;
typedef struct _tagPT_OSDATTRI
{
    PT_SHOW_E     en_title;                // 1-显示OSD名0-不显示
    HB_CHAR         title[MAX_STRING];     //OSD名
    PT_AREA_S     pos_title;               //OSD名的坐标信息
}PT_OSDATTRI_S;


typedef struct _tagPT_OSDPARAM
{
    PT_OSDATTRI_S      osd[MAX_OSD_NUM];
    HB_U16             osdattrib;            //OSD属性 255-不透明 0-254 透明
    HB_U16             osdnum;               //OSD数目
    PT_DATEFORMAT_E    format_date;          //日期格式 如果有日期OSD则该参数有用
    PT_SHOW_E          en_week;              //是否显示星期 如果有日期OSD则该参数有用
}PT_OSDPARAM_S; //获取/设置的通道OSD参数结构体指针===

typedef struct _tagPT_VLOSTLINKPLAN
{
    HB_U16               enalmmax;          // 1-senor or move alarm to chang one real window
    HB_U16               almoutbuzzer;      //报警送蜂鸣器
    PT_ENABLE_E          enable;            //视频丢失报警使能
    PT_ALMLINKPLAN_S     plan;              //报警联动预案
}PT_VLOSTLINKPLAN_S; //获取/设置的视频丢失参数结构体指针===


typedef struct _tagPT_QUERYLOGNUM
{
    HB_U32       ch_host;     //用来对应唯一主机 input
    PT_TIME_S    date;        //查询日志时间input
    HB_U32       totalnum;    //查询指定时间内的日志总数output
}PT_QUERYLOGNUM_S; //查询日志参数结构体指针


//typedef enum
//{
//    PT_LOGTYPE_ALM  =  1,      //报警
//    PT_LOGTYPE_ALM  =  2,      //异常
//    PT_LOGTYPE_ALM  =  3,      //操作
//    PT_LOGTYPE_ALM  =  0xff    //全部
//}PT_LOGTYPE_E;


typedef struct _tagPT_LOGINFO
{
    PT_MFSTIME_S      time;            //日志时间
    HB_U8             pri_type;        //主类型
    HB_U8             sec_type;        //次类型
    HB_U8             param;           //操作类型
    HB_U8             channel;         //通道号
    HB_U32            host;            //0-主机 其他如远程IP0xc0a80006
    HB_U8             user[17];        //用户名
    HB_U8             hard_driver;     //硬盘号
    HB_U8             sensor_in;       //报警输入
    HB_U8             sensor_out;      //报警输出
    HB_U8             reserve[32];     //保留
}PT_LOGINFO_S; //记录日志的结构体指针===


typedef struct _tagPT_QUERYLOGINFO
{
    HB_U32           ch_host;     //用来对应唯一主机 input
    PT_TIME_S        date;        //查询日志时间input
    HB_U16           start;       //起始
    HB_U16           limit;       //想要获取日志的条数(info的大小 /sizeof(PT_LOGINFO_S)) input
    HB_U32           realnum;     //读出的实际日志条数(output)
    PT_LOGINFO_S     *info;       //日志具体信息(output)
}PT_QUERYLOGINFO_S; //查询日志参数结构体指针===


typedef struct _tagPT_RECCOVERMODE
{
    HB_U32   ch_host;      //用来对应唯一主机 input
    HB_U32   covermode;    //录像覆盖方式
}PT_RECCOVERMODE_S; //获取/设置录像覆盖方式结构体指针===


typedef enum _tagPT_DEVICETYPE_E
{
    PT_NullDevice,      /* Null device. */
    PT_IdeDevice,       /* IDE hard disk. */
    PT_RamDevice,       /* RAM disk */
    PT_UsbDevice,       /* USB host device */
    PT_FlashDevice,     /* Flash memory */
    PT_SdDevice,        /* SD Card */
    PT_DvdDevic         /* DVD Rom*/
}PT_DEVICETYPE_E;


typedef enum _tagPT_DEVSTATUS_E
{
    PT_DEV_NORMAL,         //正常
    PT_DEV_DISK_ERROR,     //磁盘错误
    PT_DEV_FS_FAILED       //文件系统出错
}PT_DEVSTATUS_E;
//raid_status 定义


typedef enum _tagPT_RAIDSTATUS_E
{
    PT_DEV_RAID_NORMAL,         //raid 正常
    PT_DEV_RAID_DEGRED,         //raid 降级
    PT_DEV_RAID_REBUILDING,     //raid 重建
    PT_DEV_RAID_BROKEN,         //raid 损坏
    PT_DEV_RAID_NO_RAID,        //raid 没有建立
    PT_DEV_RAID_UNKOWN          //NO USE STAUS NOW
}PT_RAIDSTATUS_E;


typedef enum _tagPT_SYSCOLOR_E
{
    PT_SYSCOLOR_PAL,       //PAL制式
    PT_SYSCOLOR_NTSC443,   //NTSC4.43制式
    PT_SYSCOLOR_NTSC358,   //NTSC3.58制式
}PT_SYSCOLOR_E; 


typedef enum _tagPT_STANDARD_E
{
    PT_STANDARD_H264,    //H.264
    PT_STANDARD_MPG4,    // MPG4
}PT_STANDARD_E;


typedef enum _tagPT_LOGSIZE_E
{
    PT_LOGSIZ_32M,      //32M
    PT_LOGSIZ_64M,      //64M
    PT_LOGSIZ_128M,     //128M
    PT_LOGSIZ_256M,     //256M
    PT_LOGSIZ_512M,     //512M
}PT_LOGSIZE_E;


typedef struct _tagPT_SYSINFO
{
    HB_U64        serial_num;           //主板序列号
    HB_U8         rec_port;             //录像通道数4;8;16
    HB_U8         rec_format;           //录像分辨率CIF;D1
    HB_U8         rec_colorsystem;      //录像制式Ntsc;Pal
    HB_U8         rec_standard;         //录像压缩算法H264;MPG4
    PT_TIME_S     sys_time;             //系统最后访问磁盘时间
    HB_U8         log_size;
    HB_U8         esata_enable;         //esata设备位置使能
    HB_U8         sys_hd_num;           //当前系统支持的最大硬盘数
    HB_U8         reserve1[5];          //保留
}PT_SYSINFO_S;


typedef struct _tagPT_RAIDDEVINFO
{
    HB_U8     Name[64];         //型号
    HB_U64    dev_capabilty;    //容量
} PT_RAIDDEVINFO_S;


typedef enum _tagPT_Raid_Level_E
{
    PT_RAID_LEVEL_NULL,    //未组成raid模式
    PT_RAID_LEVEL_0,       /*RAID 0*/
    PT_RAID_LEVEL_1,       /*RAID 1*/
    PT_RAID_LEVEL_2,       /*RAID 2*/
    PT_RAID_LEVEL_3,       /*RAID 3*/
    PT_RAID_LEVEL_4,       /*RAID 4*/
    PT_RAID_LEVEL_5,       /*RAID 5*/
    PT_RAID_LEVEL_10       /*RAID 10*/
}PT_Raid_Level_E;


typedef struct _tagPT_RAIDINFO
{
    PT_RAIDSTATUS_E       raid_status;          //设备raid状态
    PT_Raid_Level_E       raid_level;           //设置raid模式的级别
    HB_U32                raid_dev_table;       //每个raid组上的设备存在位置情况
    PT_RAIDDEVINFO_S      raid_dev_info[10];    //每个磁盘的型号和容量
}PT_RAIDINFO_S;


typedef struct _tagPT_DEVICEINFO
{
    HB_U32 dev_num;
    PT_DEVICETYPE_E      dev_type;              //设备类型（默认硬盘）
    HB_U32               removable;             //设备是否可移动设置（默认否）
    HB_U32               backup;                //设备是否备份设置（默认否）
    PT_DEVSTATUS_E       dev_status;            //设备状态
    HB_U32               is_raid_dev;           //设备是否raid 装置(默认否)
    PT_RAIDINFO_S        raid_info;             //当前设备raid装置的详细信息
    HB_U32               active;                //设备工作状态（休眠或者活动）
    HB_U32               device_capabilty;      //设备容量(MB)
    HB_U32               mfs_fs_active;         //设备文件系统是否格式化
    HB_U32               mfs_capability;        //文件系统可用容量（格式化后的容量MB）
    HB_U32               mfs_free;              //当前可用容量(MB)
    PT_MFSDEV_HANDLE     device_handle;         //设备操作句柄
    PT_SYSINFO_S         device_sys_info;       //磁盘上录像相关的系统信息
}PT_DEVICEINFO_S;


typedef enum _tagPT_COVERMODE_E
{
    PT_COVERMODE_ALM,       //报警覆盖
    PT_COVERMODE_CYCLE,     //循环覆盖
}PT_COVERMODE_E;


typedef struct _tagPT_DISKINFO
{
    PT_COVERMODE_E     cycle_overlay;    //循环覆盖方式
    HB_U32             dev_table;
    HB_U32             backup_table;
    PT_DEVICEINFO_S    deviceinfo[MAX_DEV_MFS];
}PT_DISKINFO_S; //磁盘信息结构体地址===


typedef struct _tagPT_PRESETPOLL
{
    HB_U32           Preset[MAX_PRESET_API]; //每个预置点1-255之间
    PT_ENABLE_E      PresetPoll;             //多预置点轮巡开启或关闭表示
    HB_U32           presettime;             //多预置点轮巡时间(1s~99s)
}PT_PRESETPOLL_S; //获取/设置云台多预置点轮巡轨迹结构体地址===


typedef struct _tagPT_NETUPGRADE
{
    HB_U8     *data;     //升级文件缓冲指针
    HB_U32    size;      //升级文件大小
}PT_NETUPGRADE_S;//网络升级时升级配置文件指针===

#if 0
typedef struct
{
    HB_U32                audioin_no;                   //音频输入数
    HB_U32                videoin_no;                   //视频输入数
    HB_U32                sensorin_no;                  //报警输入数
    HB_U32                sensorout_no;                 //报警输出数
    HB_U32                spot_support;                 //SPOT支持
    HB_U32                cvbs_support;                 //CVBS支持
    HB_U32                vga_support;                  //VGA支持
    HB_U32                hdmi_support;                 //HDMI支持
    HB_U32                color_system;                 //0-PAL, 1-NTSC
    PT_RESOLUTION_E       max_res;                      //最大视频分辨率
    HB_U32                max_hd;                       //最大支持硬盘个数
    HB_CHAR               host_type[MAX_STRING];      //主机类型 如7004T
    HB_U32                modelno;                      //主机类型 如7T04
    HB_CHAR               serialnumber[MAX_STRING];   //主板序列号
    HB_CHAR               fbversion[MAX_STRING];      //前面板版本号
}PT_IOCONFIG_S; //系统基本配置的结构体指针===
#else
typedef struct _tagPT_IOCONFIG
{
    HB_U32          audioin_no;               //音频输入数
    HB_U32          videoin_no;               //视频输入数
    HB_U32          sensorin_no;              //报警输入数
    HB_U32          sensorout_no;             //报警输出数
    HB_U32          spot_support;             //SPOT输出支持
    HB_U32          cvbs_support;             //CVBS支持
    HB_U32          vga_support;              //VGA支持
    HB_U32          hdmi_support;             //HDMI输出支持
    HB_U32          color_system;             //0-PAL, 1-NTSC
    PT_RESOLUTION_E max_res;                  // 最大视频分辨率
    HB_U32          max_hd;                   // 最大支持磁盘个数
    HB_CHAR         host_type[MAX_STRING];    //主机类型  如7004T
    HB_U32          modelno;                  //主机类型号如7T04
    HB_CHAR         serialnumber[MAX_STRING]; //主板序列号
    HB_CHAR         fbversion[MAX_STRING];    //前面板版本号
    HB_CHAR         pri_res_support[PT_MAX_RESNUM];//0-不支持 1-支持      主码流支持的分辨率
    HB_CHAR         sec_res_support[PT_MAX_RESNUM];//0-不支持 1-支持     主码流支持的分辨率
    HB_U32          lang_ver; //语言版本  0：中文；1：英文
    HB_U32          logo_ver; //logo版本 0：汉邦；1：中性
}PT_IOCONFIG_S, *PPT_IOCONFIG_S;
#endif

typedef enum _tagPT_FRAMETYPE
{
    PT_FRAMETYPE_P,     //P帧
    PT_FRAMETYPE_I,     //I帧
    PT_FRAMETYPE_AUDIO, //音频帧
}PT_FRAMETYPE_E;


typedef struct _tagPT_FRAMEHEADINFO
{
    HB_U32              flag;           //MSHEAD_FLAG
    HB_U32              mshsize;        //媒体头信息, MAX size=511
    HB_U32              msdsize;        //媒体数据流大小, Max size=512K-1
    HB_U32              algorithm;      //媒体编码标准ISO_...
    PT_FRAMETYPE_E      type;           
    HB_U32              width;          //如为视频表示宽度（单位16像素）， 如为音频表示采样位宽（单位bit）
    HB_U32              height;         //如为视频表示高度（单位16像素）， 如为音频表示采样率（单位K【1000】）
    HB_U32              serial_no;      //0~511循环计数，用于标准的帧连续判断，当间隔两帧序号不连续时，表示中间帧丢失。
    HB_U32              time_msec;      //当前帧时间（单位10毫秒）
    HB_U32              time_sec;       //当前帧时间（单位秒）表示从1970年1月1日0时0分0秒算起至今的UTC时间所经过的秒数
    HB_U32              fcount;         //用于码流的帧计数
    PT_TIME_S           time;           //帧具体时间
}PT_FRAMEHEADINFO_S;  //获取单帧视频数据的帧头信息===


typedef enum _tagPT_WEPTYPE_E
{
    PT_WEPTYPE_UNABLE,     //unable
    PT_WEPTYPE_64B,        //64bit
    PT_WEPTYPE_128B,       //128bit
    PT_WEPTYPE_152B,       //152bit
}PT_WEPTYPE_E;


typedef struct _tagPT_WIFICONFIG
{
    HB_U8            ssid[50];           //SSID号
    HB_U8            wirelessIP[16];     //无线ip
    HB_U32           wpa_set;            //wpa安全类型设置
    PT_WEPTYPE_E     wep_type;
    HB_U8            psw[65];
}PT_WIFICONFIG_S; //获取/设置的无线网络配置的结构体指针===


typedef struct _tagPT_RECENABLE
{
    PT_RECTYPE_E    type;       //录像类型
    PT_ENABLE_E     enable;     //录像使能
}PT_RECENABLE_S; //设置/获取指定类型录像结构体指针===


typedef struct _tagPT_UARTPARAM
{
    HB_U32            baudrate;           //云台波特率
    PT_ENABLE_E       enable;             //是否使用
    HB_U32            func;               //0-no,1-ptz,2-keyboard,3-transparent uart
    HB_U32            databits;           //数据位(7,8)
    HB_U32            stopbits;           //停止位(1,2)
    HB_U32            parity;             //校验位(0-NONE,1-ODD,2-EVEN,3-SPACE)
    HB_U32            flow_control;       //流控(0-无,1-Xon/Xoff,2-硬件)
}PT_UARTPARAM_S;  //获取/设置的主机串口参数配置指针===


typedef struct _tagpt_msg_buf
{
    long        type;             //消息类型 必须>0
    HB_S32      buffer[4];     //消息类型
} PT_MSG_BUF, *PPT_MSG_BUF;


typedef enum _tagPT_NETKEYCMD_E
{
    NETKEY_CMD_GUI_LOGIN,              //登录
    NETKEY_CMD_GUI_DN,                 //主机号 1
    NETKEY_CMD_GUI_STOP,               //STOP 2
    NETKEY_CMD_GUI_RETURN,             //返回 3
    NETKEY_CMD_GUI_ENTER,              //确认 4
    NETKEY_CMD_GUI_UP,                 //上 5
    NETKEY_CMD_GUI_DOWN,               //下 6
    NETKEY_CMD_GUI_LEFT,               //左 7
    NETKEY_CMD_GUI_RIGHT,              //右 8
    NETKEY_CMD_GUI_INFO,               //信息 9
    NETKEY_CMD_GUI_RECORD,             //录像 10
    NETKEY_CMD_GUI_PLAYBACK,           //回放 11
    NETKEY_CMD_GUI_SETUP,              //设置 12
    NETKEY_CMD_GUI_BACKUP,             //备份 13
    NETKEY_CMD_GUI_NEAR,               //摄像头近 14
    NETKEY_CMD_GUI_FAR,                //摄像头远 15
    NETKEY_CMD_GUI_ZOOMIN,             //摄像头变焦近(ZOOM+) 16
    NETKEY_CMD_GUI_ZOOMOUT,            //摄像头变焦远(ZOOM-) 17
    NETKEY_CMD_GUI_APER_INC,           //摄像头光圈+ 18
    NETKEY_CMD_GUI_APER_DEC,           //摄像头光圈- 19
    NETKEY_CMD_GUI_PAGEUP,             //上页 20
    NETKEY_CMD_GUI_PAGEDOWN,           //下页 21
    NETKEY_CMD_GUI_PRESET_SET,         //摄像头预置 22
    NETKEY_CMD_GUI_PRESET_GET,         //摄像头调用 23
    NETKEY_CMD_GUI_CN,                 //中文 24
    NETKEY_CMD_GUI_AUTO,               //自动 25
    NETKEY_CMD_GUI_MUTE,               //静音 26
    NETKEY_CMD_GUI_F1,                 //F1 27
    NETKEY_CMD_GUI_F2,                 //F2 28
    NETKEY_CMD_GUI_REFRESH,            //REAL GUI USE 110 29
    NETKEY_CMD_GUI_IGEFORMAT,          //画面格式100 30
    NETKEY_CMD_GUI_IGESWITCH,          //画面轮换 31
    NETKEY_CMD_GUI_SHUTDOWN,           //电源关机申请 32
    NETKEY_CMD_GUI_MOUSESTATUS,        //鼠标 33
    NETKEY_CMD_GUI_VIDEOPARAM,         //视频参数 34
    NETKEY_CMD_GUI_DIGIT,              //数字(0,1,2,3,4,5,6,7,8,9) 35
    NETKEY_CMD_GUI_CHAR,               //字符(A,B,C,...,X,Y,Z,*,#) 36
    NETKEY_CMD_GUI_F1VGA2TV,           //vga与电视切换 37
    NETKEY_CMD_GUI_STEP,               //帧进 38
    NETKEY_CMD_GUI_PLAY,               //播放 39
    NETKEY_CMD_GUI_FASTF,              //快进 40
    NETKEY_CMD_GUI_FASTB,              //快退 41
    NETKEY_CMD_GUI_REFRESHTIME,        //REAL GUI USE 42
    NETKEY_CMD_GUI_PWDRST,             //密码复位 43
}PT_NETKEYCMD_E;




typedef struct _tagPT_NETKEY
{
    PT_NETKEYCMD_E      cmd;
    HB_U32              keycode;
}PT_NETKEY_S; //设置的网络键盘参数配置指针===


typedef struct _tagPT_ACCOUNT
{
    HB_U8      user[MAX_STRING];
    HB_U8      pwd[MAX_STRING];
    HB_U8      grp_name[MAX_STRING];      //分组名
    HB_U32     local_authority;           //本地用户使用权限
    HB_U32     local_channel;             //本地设置通道权限
    HB_U32     remote_authority;          //远程用户使用权限
    HB_U32     remote_channel;            //远程设置通道权限
    HB_U32     bind_ipaddr;               //远程绑定IP
    HB_U8      bind_macaddr[8];           //远程绑定MAC
}PT_ACCOUNT_S;


typedef struct _tagPT_GROUPACCOUNT
{
    HB_U8       name[MAX_STRING];      //分组名
    HB_U32      local_authority;       //本地用户使用权限
    HB_U32      local_channel;         //本地设置通道权限
    HB_U32      remote_authority;
    HB_U32      remote_channel;
}PT_GROUPACCOUNT_S;


typedef struct _tagPT_ACCOUNT_CONFIG
{
    HB_U8                   count;                             //用户数量
    HB_U8                   grp_count;                         //用户组数量
    HB_U16                  list_enable;                       //登录时是否显示用户列表
    PT_ACCOUNT_S            cur_user;                          //本地当前登录用户
    PT_ACCOUNT_S            accounts[PT_MAX_ACCOUNT];          //用户列表
    PT_GROUPACCOUNT_S       grp_accounts[PT_GRP_ACCOUNT];      //用户组列表
} PT_ACCOUNT_CONFIG_S; //获取/设置的用户参数配置指针===


typedef struct _tagPT_MASKRECPARAM
{
    HB_U16                 enalmmax;                    // 1- senor or move alarm to chang one real window
    HB_U16                 almoutbuzzer;                //报警送蜂鸣器
    PT_TMSCHEDULE_S        schedule;                    //布防时间设置
    PT_ALMLINKPLAN_S       plan;                        //报警联动预案
    PT_AREA_S              coverarea[MAX_MASK];         //遮挡区域
}PT_MASKRECPARAM_S; //获取/设置的遮挡报警联动参数配置指针===


typedef struct _tagPT_BACKUPREAD
{
    HB_U32     open_bk_handle;
    HB_U32     size;
    HB_CHAR    *data;//output
}PT_BACKUPREAD_S;

#ifndef _PTZ_LIST
#define _PTZ_LIST
typedef struct _tagPT_PTZLIST
{
    HB_CHAR                 name[16];
    //ptptz_control        func; 【这个地方有问题,先注释掉】
} PT_PTZLIST_S, *PPT_PTZLIST_S; //云台类型列表结构体指针===
#endif

typedef enum _tagPT_SYSNETAPI_NOTIFY_E
{
    PT_NOTIFY_UPDATE,
    PT_NOTIFY_UPGRADEPOS,
    PT_NOTIFY_VIDEOSYS,
    PT_NOTIFY_ALARMINOPEN,      //延时布防
    PT_NOTIFY_ALARMINCLOSE,     //撤防
}PT_SYSNETAPI_NOTIFY_E;


typedef enum _tagPT_UPDATE_STATUS_E
{
    PT_UPDATE_START,                  //开始升级
    PT_UPDATE_SUCCESS,                //升级成功
    PT_UPDATE_ERROR_CHECKFILE,        //升级文件校验错误
    PT_UPDATE_ERROR_UPGRADE,          //升级文件替换错误
}PT_UPDATE_STATUS_E;

typedef struct  _tagPT_SYS_STATUS
{
    PT_PTZPARAM_S        pt_ptz;
    PT_PTZCTRL_S         ptz_ctrl;
    PT_SYSCOLOR_S        syscolor;
    PT_SYSTIME_S         systime;
    PT_ENCSTATUS_S       enc_status;
    PT_NETCONFIG_S       net;
    PT_VERSION_S         version;
    PT_STREAMENCPARAM_S  enc_info;
    PT_MASKPARAM_S       mask;
    PT_MOTIONRECPARAM_S  motion;
    PT_ALARMINRECPARAM_S alarmin;
    PT_TMSCHEDULE_S      time;
    PT_RECFILESEG_S      fileseg;
    PT_OSDPARAM_S        osd;
    PT_PLANCONFIG_S      plan;
    HB_CHAR              mfs_info[128];
    PT_UARTPARAM_S       uart;
    PT_MASKRECPARAM_S    maskrecp;
    HB_U32               alarmout_state;
    HB_U8                currectype;//当前录像类型
    HB_CHAR              support_talk_type[128];
    HB_CHAR              current_talk_type[32];
    HB_U32               device_id;
    PT_PRESETPOLL_S      preset;
    PT_RECCOVERMODE_S    cover;
}PT_SYS_STATUS;
typedef struct _tagPT_RecInfo_S
{
	PT_TIME_S	begin_time;           //查询开始时间
	PT_TIME_S	end_time;             //结束时间
}PT_RecInfo_S; //打开的备份录像文件结构体指针===

#define MAX_OSD_CHAR_PER_LINE	44
#define MAX_FONT_HEIGHT 32
#define MAX_FONT_WIDTH 16
#ifndef _OSD_INFO
#define _OSD_INFO
typedef	struct  _tagOSD_INFO
{
	HB_U16	x;				// 10  bits (x>>2) 4-aligned
	HB_U16	y;				// 10 bits
	HB_U8	yuvf[3];		// 24 bits
	HB_U8	yuvb[3];		// 24 bits
	HB_U8	transparencef;	// 4  bits
	HB_U8	transparenceb;	// 4  bits
	HB_U16	width;			// 8  bits (width>>3) 8-aligned
	HB_U16	height;			// 10  bits ()
	HB_U16  fontwidth;		// 5 (>>2)
	HB_U16	fontheight;		// 5 (>>2)
	HB_U16	osd_format_string[MAX_OSD_CHAR_PER_LINE];	// width/(font_width)
	HB_U16	o_size;					// osd data size
	HB_U8	osd_data[MAX_OSD_CHAR_PER_LINE*MAX_FONT_HEIGHT*MAX_FONT_WIDTH/8];		// osd data
}OSD_INFO;
#endif

#if 0
#ifndef _VIDEO_PARAM
#define _VIDEO_PARAM

typedef	struct
{
	HB_S32	algorithm;
	HB_S32	version;
	HB_S32	frame_type;
	HB_S32	e_flag;
	HB_S32	e_key;
	HB_S32	e_text;
	struct {
		short	year;
		short	month;
		short	day;
		short	hour;
		short	minute;
		short	second;
		short	milli;	
		short	week;
	}ets;
	long	dts;
	long	frame_num;
	HB_S32	width;
	HB_S32	height;
	HB_S32	osd_flag;
	HB_S32	osd_lines;
	OSD_INFO	*osd;	// or OSD_INFO[MAX_OSD_LINE]
	HB_S32	v_size;
	HB_S32	size;
}VIDEO_PARAM;
#endif
#endif
//add by shilei 10.10.21
typedef struct _tagPT_SERVERINFO
{
	  HB_U32   Serverip;
	  HB_U16   Serverport;
	  HB_U16   Videoport;
	  HB_U16   playbackport;
	  HB_U16   talkport;
	  HB_U8    SerialId[32];
	  HB_U8    password[32];
}PT_SERVERINFO_S; 


typedef struct _tagPT_SYSNETAPI_REQIPCWORKPARAM
{
	HB_U8  cbStreamType;      //码流类型 0-主流1-子流 2-第三码流
	HB_U8  cbReserve[3];			//保留
}PT_SYSNETAPI_REQIPCWORKPARAM;



typedef struct _tagPT_SYSNETAPI_SCHEDTIME_IPC
{
  	HB_U8	cbStartHour;  	    //开始小时 0-23
	HB_U8	cbStartMin;  		//开始分钟 0-59
	HB_U8	cbStopHour; 		//结束小时  0-23
	HB_U8	cbStopMin;  		//结束分钟  0-59
}PT_SYSNETAPI_SCHEDTIME_IPC; 


typedef struct _tagPT_SYSNETAPI_ICRTIME
{
HB_U16 	wLightRange;		//ICR亮度切换临界值
HB_U16 	wEnable;            // 0--亮度值有效  1--时间段有效
PT_SYSNETAPI_SCHEDTIME_IPC stSchedTime[2];
}PT_SYSNETAPI_ICRTIME;

typedef 	struct _tagPT_SYSNETAPI_SHUUTERVAL
{
	HB_U32  dwShutterIndex; //当前快门时间索引值,表示基于dwShutterVal中的位置，例如
	//dwShutterIndex = 2，
	//则当前快门时间为dwShutterVal[2];
	HB_U32	 dwShutterVal[32];	//获取快门时间的支持参数列表,当dwShutterVal[1]=0,
	//表示是一个取值范围，如
	//dwShutterVal[0]= 4096,则表示取值范围为：1/[1,4096*2],当dwShutterVal[1] != 0
	//时，
	//表示有多个具体的索引值，比如：dwShutterVal[0]= 2048，dwShutterVal[1]=4096
	//，当dwShutterVal[x]=0则表示数据共有x个。
} PT_SYSNETAPI_SHUUTERVAL;

typedef 	struct _tagPT_SYSNETAPI_SCENEVAL
{
	HB_U32 dwSceneIndex;	//当前镜头索引值，表示基于cbSceneVal中的位置，例如dwSceneIndex = 2，
	//则当前镜头为：cbSceneVal[2] = "JCD661 lens"，当cbSceneVal[x] ="\0"表示总共有
	//x个数据项；
	HB_U8	cbSceneVal[8][32];	//该机型支持的镜头种类,//0 - Full Maual lens,1 - DC
	//Iris lens, //2 - JCD661 lens,3 - Ricom NL3XZD lens,4 - Tamron 18X lens，
} PT_SYSNETAPI_SCENEVAL;

typedef 	struct _tagPT_SYSNETAPI_RESOLUTION
{
	HB_U32	dwResoluIndex;	//当前分辨率索引值，表示基于dwResolution中的位置，例如dwResoluIndex= 2，
	//则当前分辨率为dwResolution[2]中所指定的分辨率
	HB_U32	dwResolution[16];	//该机型支持的分辨率，用DWORD来表示支持的分辨率，例如：
	//dwResolution[0]=0x07800438，高两字节（0x0780=1920）、低两字节（0x0438=1080）；
}PT_SYSNETAPI_RESOLUTION;

typedef struct _tagPT_SYSNETAPI_AGCVAL
{
	HB_U32 dwAgcIndex;     //当前AGC的索引值，表示基于cbAgcVal中的位置，例如
	//cbAgcVal =2，则表示AGC
	//值为cbAgcVal[2]中的值；
	HB_U8	cbAgcVal[32]; //AGC（自动增益）的支持参数列表,当cbAgcVal[1]= 0时表示
	//cbAgcVal[0]中存储的是
	//一个取值范围，如cbAgcVal[0]= 128,则表示取值范围为：[1,128],当cbAgcVal[1]!=0
	//时，则表示cbAgcVal数组中存储的是具体的值，例如 cbAgcVal[0]= 32，//cbAgcVal[1]=64等，当cbAgcVal [x] =0表示总共有x个数据项。
} PT_SYSNETAPI_AGCVAL;

typedef struct _tagPT_SYSNETAPI_FRAMERATE
{
	HB_U8	cbMinFrameRate;	//该机型支持的最小编码帧率值;
	HB_U8	cbMaxFrameRate;	//该机型支持的最大编码帧率值;
	HB_U8	cbCurFrameRate;	//该机型设置的当前编码帧率值;
	HB_U8   cbreserve;		//保留
}PT_SYSNETAPI_FRAMERATE;


//SYSNETAPI_CMD_SET_IPCWORKPARAM
//SYSNETAPI_CMD_GET_IPCWORKPARAM
typedef struct _tagPT_SYSNETAPI_REIPCWORKPARAM
{
	HB_U32  dwLength;		  //结构体长度
	HB_U8  	cbStreamEnable;   //是否开启当前码流
	HB_U8   cbStreamType;     //码流类型 PT_STREAMTYPE_E  
	HB_U8  	cbAudioEnable;    //音频使能 0-不支持 1-无音频 ,2-有音频
	HB_U8  	cbAntiFlicker;    //抗闪烁设置 0-60HZ   1-50HZ
	PT_SYSNETAPI_FRAMERATE  stFrameRate;	//编码帧率设置;
	PT_SYSNETAPI_SHUUTERVAL stShutterVal;	//快门相关参数获取
	PT_SYSNETAPI_SCENEVAL	stSceneVal;	    //镜头相关参数获取
	PT_SYSNETAPI_RESOLUTION	stResolution;	//解析度相关
	PT_SYSNETAPI_AGCVAL		stAgcVal;		//Agc相关
	HB_U32	dwBitRateVal;		//视频码率 0-100K 1-128K，2-256K，3-512K，4-1M，5-1.5M，6-2M，7-3M, 8-4M
							//9-5M，10-6M，11-7M，12-8M, 13-9M，14-10M，15-11 M，16-12M
	//其他：码率值（kbps）有效范围 32~2^32,大于等于32，以K为单位；
	HB_U8	cbFoucusSpeedVal;	//光学变焦速度值，0：不支持
	HB_U8	cbDigitalFoucusVal; //数字变焦值，0：不支持
	HB_U8	cbImageTurnVal;	    //当前图像翻转设置 //1-不翻转,2-水平翻转 3-垂直翻转, 4-水平&垂直,0-不支持
	HB_U8	cbBlackWhiteCtrlVal; //当前黑白模式设置 //1- Off, 2- On, 3-Auto, 0-不支持
	HB_U8	cbIRISCtrl;		 //Iris control mode 光圈控制模式设置，1-Off,2-Basic, 3-Advanced,0-不支持
	HB_U8	cbAutoFoucusVal;	//是否支持自动对焦，//0-不支持,1-支持
	HB_U8 	cbAWBVal;		//白平衡场景模式设置，1-auto_wide, 2-auto_normal, 3-sunny, 4-shadow, 5-indoor,
	//6-lamp, 7-FL1, 8-FL2,0-不支持
	HB_U8 	cbA3Ctrl;      //3A控制0-off; 1-Auto Exposure; 2-Auto White Balance; 3-both, (Auto Focus no support)
	PT_SYSNETAPI_ICRTIME stICRTime; //ircut(滤光片切换模式设置)仅在模式4时才设置获取该值
	HB_U8	cbFNRSuppVal;	        //当前帧降噪设置，1-开,2-关,0-不支持
	HB_U8	cbStreamKindVal;	    //当前码流类型，1-定码流,2-变码流
	HB_U8	cbVideoOutKindVal;	    //vout视频输出设置：0-disable, 1-CVBS, 2-HDMI,3-YPbPr等等
	HB_U8	cbWDRVal;		        //该机型是否支持宽动态设置,0-不支持,1-支持
	HB_U8   cbColorMode;            //色彩风格设置 0-TV   1--PC
	HB_U8   cbSharpNess;		    //锐度设置，取值范围为：[1,255]
	HB_U8	cbPlatformType;	        //平台类别
	HB_U8	cbReserve[17];		    //保留
}PT_SYSNETAPI_REIPCWORKPARAM;

 typedef struct _tagPT_ZTECONFIG
{
    HB_CHAR http_server_ip[32];              //接入服务器IP
    HB_U16  http_server_port;                //接入服务器端口
    HB_CHAR pu_id[52];                       //设备身份ID
    HB_CHAR pu_pwd[80];                      //设备密码
    HB_CHAR pu_name[100];                    //设备名
    HB_U16  pu_enable_heartbeat;             //是否心跳
    HB_U16  pu_heartbeat_period;             //心跳间隔
}PT_ZTECONFIG;//平台配置

#define ID_LEN 10
typedef struct _tagPT_HX_CONFPARA
{
    HB_CHAR     host_ip[16];          //主机IP
    HB_S32      ipc_port;
    HB_S32      video_port;		      //视频连接端口
	HB_S32      audio_port;			  //呼叫连接端口
	HB_S32      msg_port;             //消息端口
	HB_S32      update_port;          //升级端口
	HB_S32      web_port;             //Web访问端口
    HB_S32      max_client;           //最大客户端数量
    HB_S32      init_client;          //初始化监听模块中线程数量
    
    HB_CHAR     access_ip[16];           //接入服务器IP
    HB_S32      reg_port;                //注册端口
    HB_S32      storereg_port;           //存储注册端口
    HB_CHAR     device_id[ID_LEN];
}PT_HX_CONFPARA_S;

 typedef struct _tagPT_HXCONFIG
{
  HB_U32     Serverip;
  HB_U16     Serverport;
  HB_U16     Videoport;
  HB_U16     playbackport;
  HB_U16     talkport;
  HB_U8      SerialId[32];
  HB_U8      password[32];
  HB_U16     max_link;
}PT_HXCONFIG;

typedef enum _tagPT_TYPE
{
    HN_PT = 1,     //HOST NETWORK
    CY_PT, 
    HXHT_PT, 
    ZTE_PT,
    HW_PT,
    HD_PT,
    BELL_PT,
    RCJW_PT,
    DS_PT,
    ONVIF_PT, //onvif 平台
    GB28181_PT,//国标平台
    PSIA_PT //psia平台
} PT_TYPE;

typedef struct _tagPT_FORMATINFO
{ 
	HB_U16 pt_dev_num; //要格式化的磁盘号
	HB_U16 type;       //格式化的磁盘类型
}PT_FORMATINFO_S, *PPT_FORMATINFO_S; 
typedef struct _tagPT_RES_LIST
{
	HB_U32	dwResoluIndex;	//当前分辨率索引值，表示基于dwResolution中的位置，例如dwResoluIndex= 2，
	//则当前分辨率为dwResolution[2]中所指定的分辨率
	HB_U32	dwResolution[16];	//该机型支持的分辨率，用DWORD来表示支持的分辨率，例如：
	//dwResolution[0]=0x07800438，高两字节（0x0780=1920）、低两字节（0x0438=1080）；
	PT_STREAMTYPE_E  streamtype;
}PT_RES_LIST, *PPT_RES_LIST;

//onvif 协议参数 SYSNETAPI_CMD_GET_PTCONFIG
typedef struct _tagPT_ONVIF_INFO
{
    HB_S32  enable;                    //使能 -1-不支持 0-off, 1-on
    HB_U16  protocol_port;             //协议端口，现在汉邦的IPC默认为8888
    HB_U16  video_port;                //音视频端口，现在汉邦的IPC默认为554
}PT_ONVIF_INFO_OBJ, *PT_ONVIFM_INFO_HANDLE;

//GB28181 协议参数 SYSNETAPI_CMD_GET_PTCONFIG

//////////////////////////////////////////////////////////////////////////////
// GB28181设备配置部分结构体
//////////////////////////////////////////////////////////////////////////////
typedef struct _tagPT_GB28181_DEVICE_INFO
{
    HB_CHAR    device_id[32];             //设备ID
    HB_S32     device_port;               //设备命令端口
    HB_CHAR    device_domain_name[64];    //设备域名
    HB_CHAR    device_pwd[32];            //设备注册密码    默认值为12345678
    HB_S32     device_expires;            //注册过期时间 单位为秒   默认值为3600
    HB_S32     device_alarmin_num;        //设备报警输入数量，范围1-8 只读
    HB_CHAR     device_alarmin_id[8][32];         //设备报警ID
}PT_GB28181_DEVICE_INFO_OBJ, *PT_GB28181_DEVICE_INFO_HANDLE;

//////////////////////////////////////////////////////////////////////////////
// GB28181的sip服务器结构体定义
//////////////////////////////////////////////////////////////////////////////
typedef struct _tagPT_GB28181_SIP_SERVER_INFO
{
    HB_CHAR    sip_svr_ip[32];            //sip服务器IP
    HB_CHAR    sip_svr_id[32];            //sip服务器ID
    HB_S32     sip_svr_port;              //sip服务器端口号   默认值为5060
    HB_CHAR    sip_svr_domain_name[64];   //sip服务器域名
}PT_GB28181_SIP_SERVER_INFO_OBJ, *PT_GB28181_SIP_SERVER_INFO_HANDLE;

//////////////////////////////////////////////////////////////////////////////
// GB28181的流媒体服务器结构体定义
//////////////////////////////////////////////////////////////////////////////
typedef struct _tagPT_GB28181_SMS_SERVER_INFO
{
    HB_CHAR   sms_svr_ip[32];            //sms流媒体服务器接收IP
    HB_S32    sms_svr_port;              //sms流媒体服务器接收端口  默认值为6000
}PT_GB28181_SMS_SERVER_INFO_OBJ, *PT_GB28181_SMS_SERVER_INFO_HANDLE;

//////////////////////////////////////////////////////////////////////////////
// GB28181协议参数
//////////////////////////////////////////////////////////////////////////////
typedef struct _tagPT_GB28181_INFO
{
    HB_S32                        enable;           //使能 -1-不支持 0-off, 1-on
    PT_GB28181_DEVICE_INFO_OBJ       dev_info;         //GB28181设备配置信息
    PT_GB28181_SMS_SERVER_INFO_OBJ   sms_server_info;  //GB28181流媒体服务器信息
    PT_GB28181_SIP_SERVER_INFO_OBJ   sip_server_info;  //GB28181sip服务器信息
}PT_GB28181_INFO_OBJ, *PT_GB28181_INFO_HANDLE;


//
//////////////////////////////////////////////////////////////////////////////
// PSIA协议参数   SYSNETAPI_CMD_GET_PTCONFIG
//////////////////////////////////////////////////////////////////////////////
typedef struct _tagPT_PSIA_INFO
{
    HB_S32  enable;                    //使能 -1-不支持 0-off, 1-on
    HB_U16  protocol_port;             //协议端口，现在汉邦的IPC默认为8888
    HB_U16  video_port;                //音视频端口，现在汉邦的IPC默认为554
}PT_PSIA_INFO_OBJ, *PT_PSIA_INFO_HANDLE;


///////////////////////////////////////////////////////////////////////////////////
//摄像机参数：
//2013.11.20，添加宽动态
//
//
  //SYSNETAPI_CMD_GET_IPCWORKPARAM
  //SYSNETAPI_CMD_SET_IPCWORKPARAM
#if 0
typedef struct _tagPT_IPCWORKPARAM
{
	PT_STREAMTYPE_E  streamtype;
	HB_U8 wdr_val;//宽动态设置, 1-开 2-关, 0-不支持
}PT_IPCWORKPARAM_OBJ, *PT_IPCWORKPARAM_HANDLE;

#endif


/////////////////////////////////////////////////////////////////////////////////////////
////端口映射
///////////////////////////////////////////////////////////////////////////////////////////
typedef   struct 
{ 
    HB_U32   nvrip;    //内网设备ip地址(路由连接的设备的ip) 
    HB_U16   iport;    //内网端口 
    HB_U16   eport;    //外网端口 
    HB_U16   proto;    //0-TCP,1-UDP 
    HB_U16   type;    //0-sdk服务端口,1-http端口,2-升级端口，3-telnet端口， 
    //4-rtsp端口，5-https端口，6-tftp 端口 
}pt_portmap_s; 

typedef    struct 
{ 
    HB_U32   iaddr;  //路由设备内网ip地址(路由ip) 
    HB_U32   eaddr;  //路由设备外网ip地址(路由拨号等获取的ip) 
    pt_portmap_s    portmap[32];    //服务端口表或映射端口表 
    HB_CHAR   reserve_dev[4];        //保留 
}pt_devinfo_s; 

typedef    struct _tagIPC_PORTMAP    
{ 
    HB_S32    dev_num;   //出口路由设备个数，0表示没有做端口映射，但服务端口仍会在dev[0]中填充 
    pt_devinfo_s  dev[8];  //索引下的详细信息，从0开始 
    HB_CHAR   reserve[8];      //保留 
}PT_IPC_PORTMAP;





 typedef enum  _tagPT_FORMATTYPE_E
{ 
    SYSNETAPI_FORMAT_ERR = 0,  //格式化错误
    SYSNETAPI_DISK_BUSY,       //磁盘正在被使用
     SYSNETAPI_DISK_INFORMAT,  //磁盘正在被格式化
    SYSNETAPI_DISK_NOEXIST,    //要格式化的磁盘不存在
    SYSNETAPI_DISK_LOST,       //格式化中途错误
    SYSNETAPI_DISK_FORMATEND,  //格式化结束
}PT_FORMATTYPE_E; 

typedef struct _tagFLATFORM_F
{
	HB_U32 server_ip;
	HB_U32 internet_ip;
	HB_U32 max_link;
	HB_U16 nPort;
	HB_U16 videoport;
	HB_U16 talkport;
	HB_U16 cmdport;
	HB_U16 vodport;
	HB_U8  tran_mode:4;   //码流类型
	HB_U8  ftp_mode:1;    //是否选择ftp中心存储
}FLATFORM_F;

typedef struct _tagFLATFORM
{
	HB_U8 pu_id[32];
	HB_U8 pu_password[20];
}FLATFORM_S;

#ifdef __cplusplus
extern "C"{
#endif
HB_S32 sysnetapi_open(HB_S32 flag);
HB_S32 sysnetapi_start(HB_S32 handle,HB_S32 prior);
HB_S32 sysnetapi_close(HB_S32 handle);
HB_S32 sysnetapi_write_ao(HB_CHAR *pdata,HB_U32 size,HB_S32 type);
//end add
HB_S32 sysnetapi_ioctrl(HB_S32 ihandle, HB_S32 cmd, HB_S32 channel, HB_VOID* param,HB_S32 size_of_param);
typedef HB_S32 (*PPLAYBACKSTREAM)(HB_S32 idx, HB_CHAR* data, HB_U32 size, HB_VOID* paramin);
HB_S32 sysnetapi_get_frameheadinfo(HB_CHAR  *data, HB_U32 size, PT_FRAMEHEADINFO_S *frameheadinfo);//add by lu 10.09.10
HB_S32 sysnetapi_print_videoinfo(HB_CHAR *data, HB_U32 size);

#ifdef __cplusplus
}
#endif
#endif

