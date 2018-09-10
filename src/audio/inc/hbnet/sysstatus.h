#ifndef _SYSSTATUS_H_
#define _SYSSTATUS_H_

#include "common/ipc_common.h"

#define MAX_CH 				16 		// for max channel num


#define MAX_HD 				12 		//8 tyh 2008-03-17 for max disk num
#define MAX_AM 				4 		// for max alarm out num
#define MAX_ALARMIN 		2		// for max alarm in num
#define MAX_MPEG_SIZE 		0x40000	// tyh 2008-01-08 0x20000
#define MAX_G722_SIZE 		120

#define MAX_G722HX_SIZE 	240 // 最大接收缓冲区
#define MAX_G722PACK_SIZE 	320
#define MAX_PTZ_PRESET		1
#define AUDIO   			1U
#define VIDEO_P 			2U
#define VIDEO_I 			3U

#define FD1_ENCODE 			0x40000000
#define HD1_ENCODE 			0x20000000
#define CIF_ENCODE 			0x00000000

#define ACCOUNTNUM 			16


typedef struct _tagPORTPRESET
{
	HB_U16	Preset[MAX_CH];
    HB_U16	PresetPoll;		//多预置点轮巡开启或关闭表示
    HB_U32	presettime;		//多预置点轮巡时间
}PORTPRESET_OBJ, *PORTPRESET_HANDLE;
//PortPreset,*pPortPreset;


//日期,时间

typedef struct _tagSYSTM
{
	HB_U32	date;  		//year|month|day _ _ | _ | _
	HB_U32	time;  		//|week |hour|min|sec
	HB_U32	reserve; 	//
}SYSTM_OBJ, *SYSTM_HANDLE;
//SysTm, *pSysTm;


typedef struct _tagTMPERIOD
{
	HB_U16	starttm;   //hout|min
	HB_U16	endtm;
}TMPERIOD_OBJ, *TMPERIOD_HANDLE;
//TMPeriod, *pTMPeriod;

typedef struct _tagTMITEM
{
	HB_U32			bselect;    //0-no   1-yes
	TMPERIOD_OBJ	period[2];
}TMITEM_OBJ, *TMITEM_HANDLE;
//TMItem, *pTMItem;


//time schedule


typedef struct _tagTMSCHEDULE
{
	HB_U32 		bstatus;  //0-off, 1-on
	TMITEM_OBJ 	item[8]; // 0-7: everyday, monday...sunday
}TMSCHEDULE_OBJ, *TMSCHEDULE_HANDLE;

//TMSchedule, *pTMSchedule;


//record param

typedef struct _tagRECORD_PARAM
{
	HB_U8	resolution;  	// 0-1080p, 1-720p, 2-d1    //modify by kl 090916
	HB_U8	videoquality;	// 1~6: high~low
	HB_U8	framerate;   	// framerate 1-25(PAL), 1-30(NTSC)
	HB_U8	audiorecord; 	// audio record 0-off, 1-on
	HB_U32	maxbitrate; 	// x kbit
	HB_U32	streamtype; 	// reserve for temp use
	HB_U8	vinframe;    	//vin frame rate
}RECORD_PARAM_OBJ, *RECORD_PARAM_HANDLE;
//Record_Param, *pRecord_Param;

/*
manual record param
*/

typedef struct _tagMANUAL_PARAM
{
	RECORD_PARAM_OBJ	recordparam;
	HB_U32 				reserve;     // reserve for temp use
}MANUAL_PARAM_OBJ, *MANUAL_PARAM_HANDLE;


//time record param

typedef struct _tagTIME_PARAM
{
	RECORD_PARAM_OBJ	recordparam;
	TMSCHEDULE_OBJ		schedule;
	HB_U32				reserve;     // use
}TIME_PARAM_OBJ, *TIME_PARAM_HANDLE;
//Time_Param, *pTime_Param;

typedef struct _tagMOTION_PARAM
{
	RECORD_PARAM_OBJ	recordparam;
	TMSCHEDULE_OBJ 		schedule;
	HB_U32 				motionblock[18]; 	//32 line 20*18
	HB_U32 				sensitivity;      	// 1-5 low~height
	HB_U32 				alarmout;        	//one bit stand for an alarm output
	HB_U16 				alarmtrig;    		// 1-mv detect 2-videolost detect
	HB_U16 				audioalm;
	HB_U32 				reserve;     		// USE
}MOTION_PARAM_OBJ, *MOTION_PARAM_HANDLE;


typedef struct _tagALARM_PARAM
{
	RECORD_PARAM_OBJ 	recordparam;
	TMSCHEDULE_OBJ 		schedule;
	HB_U32 				recordport;   	//one bit stand for a record port
	HB_U32 				alarmout;    	//one bit stand for an alarm output
	HB_U16 				alarmtrig;   	// 1-detect alarm in 2-not detect alarm in
	HB_U16 				audioalm;
	HB_U32 				enpreset;
	HB_U8 				alm2preset[MAX_CH];
	HB_U32 				reserve;     	// use
	HB_U8 				alarm_in_type; 	// 0：常开,1：常闭
}ALARM_PARAM_OBJ, *ALARM_PARAM_HANDLE;


//PTZ set
typedef struct _tagPTZ_SET
{
	HB_U8	type;
	HB_U8	baudrate;
	HB_U16	addr;
	HB_U32	reserve;//speed
}PTZ_SET_OBJ, *PTZ_SET_HANDLE;
//PTZ_Set, *pPTZ_Set;

typedef struct _tagPOS_AREA
{
	HB_U16	left;
	HB_U16 	top;
	HB_U16 	width;
	HB_U16 	height;
}POS_AREA_OBJ, *POS_AREA_HANDLE;
//Pos_Area, *pPos_Area;

typedef struct _tagVIDEO_PARAM
{
	HB_U16	starttime;
	HB_U16	endtime;
	HB_U32	vparam; //视频参数bright/contrast/saturation/hue
}VIDEO_PARAM_OBJ, *VIDEO_PARAM_HANDLE;

typedef struct _tagCH_SET
{
	HB_U8 				title[32]; 		// 标题
	HB_U32 				vlostalm; 		//视频丢失(bit0-bit31) 0-normal, 1-lost
	HB_U32 				vlostalmout; 	//视频丢失报警输出
	HB_U8 				envlostalm; 	// 视频丢失报警
	HB_U8 				enmask;
	HB_U16 				masknum;  		//mask area num
	POS_AREA_OBJ		maskarea[4];
	VIDEO_PARAM_OBJ 	videoparam[2];
	HB_U32 				defaultvparam; 	//默认视频参数
	HB_U32 				curvparam;  	//视频参数bright/contrast/saturation/hue
	PORTPRESET_OBJ		portpreset;
	HB_U32 				reserve;
}CH_SET_OBJ, *CH_SET_HANDLE;

typedef struct _tagCH_PARAM
{
	RECORD_PARAM_OBJ 	recordparam;
	RECORD_PARAM_OBJ 	netparam;
	MANUAL_PARAM_OBJ	manual;
	TIME_PARAM_OBJ   	time;
	MOTION_PARAM_OBJ 	motion;
//  Alarm_Param  alarm;		// del by WZ		2009.03.05
	PTZ_SET_OBJ      	ptzset;
	CH_SET_OBJ       	chset;
}CH_PARAM_OBJ, *CH_PARAM_HANDLE;


//ip set

typedef struct _tagIP_SET
{
	HB_U8 		host_id[32];
	HB_U32 		dhcp_on;
	HB_U32 		ip_addr;
	HB_U32 		mask_addr;
	HB_U32 		gateway;
	HB_U32 		dns;
	HB_U32 		backip_addr;
	HB_U32 		backmask_addr;
	HB_U32 		backgateway;
	HB_U32 		backdns;
	HB_U8 		macaddr[8];
	HB_U16 		listenPort;
	HB_U16 		httpPort;
	HB_U32  	multicast; // 1-multibroadcast
	HB_U32 		net_interface; //网络接口 1-10MBase-T 2-10MBase-T全双工 3-100MBase-TX 4-100M全双工 5-10M/100M自适应
	HB_U32 		reserve;
}IP_SET_OBJ, *IP_SET_HANDLE;


//pppoe set

typedef struct _tagPPPOE_SET
{
	HB_U8 	user[32];
	HB_U8 	pwd[32];
	HB_U32 	curstate;
	HB_U16  	autoconnect;
	HB_U16  	savepwd;
	HB_U32  	ip, mask, gateway;
	HB_U32  	dns, dns1;
	HB_U32  	server;
}PPPOE_SET_OBJ , *PPPOE_SET_HANDLE;

/*
ddns set
*/
typedef struct _tagDDNS_SET
{
	HB_U8 	server[32];
	HB_U8 	user[32];
	HB_U8 	pwd[32];
	HB_U8 	dn[256];
	HB_U16 	curstate;
	HB_U16 	autologin;
	HB_U32 	ip;
	HB_U16 	curserver;
}DDNS_SET_OBJ, *DDNS_SET_HANDLE;
//Ddns_Set, *pDdns_Set;
//one account

typedef struct _tagACCOUNT
{
	HB_U8 	user[32];
	HB_U8 	password[32];
	HB_U32 	level; 				// 用户权限
	HB_U32 	ctrlch;
	HB_U32 	remote_level; 		//remote user level
	HB_U32 	remote_ctrlch; 		//
	HB_U32 	bind_ipaddr; 		//0 stands for not bind
	HB_U8 	bind_macaddr[8];  	// null stand for not bind
} ACCOUNT_OBJ, *ACCOUNT_HANDLE;

typedef struct _tagACCOUNTS
{
	HB_U8 		powerpwd[8];
	HB_U8 		updatepwd[8];
	HB_U8 		usercount;
	HB_U8 		userliston; 	// 登陆时是否显示用户列表
	HB_U32 		count;
	HB_U32		md5_key;		// add by WZ 	2009.02.17
	ACCOUNT_OBJ curuser;
	ACCOUNT_OBJ account[ACCOUNTNUM];
} ACCOUNTS_OBJ, *ACCOUNTS_HANDLE;


//uart set

typedef struct _tagUART_INFO
{
	HB_U8 	useuart;    //0-off, 1-on
	HB_U8 	uartid;     //uartname id  0-no 1-ptz 2-keyboard 3-transparent uart
	HB_U16 	addr;
	HB_U16 	uartmode; 	//0 - full duplex 1-semi duplex
}UART_INFO_OBJ, *UART_INFO_HANDLE;
//Uart_Info, *pUart_Info;

typedef struct _tagUARTS_SET
{
	HB_U8 			deviceid[3];  	//device id for forward board lock
	HB_U8 			keylock;    	//0-off  1-on
	UART_INFO_OBJ 	uartdevice[3];  //0-232 1-485
	HB_U32 			reserve;
}UARTS_SET_OBJ, *UARTS_SET_HANDLE;
//
typedef struct _tagDISK_INFO
{
	HB_U32 	ch;
	HB_U32 	dev;
	HB_U32 	diskcapacity, diskfree;
	HB_U32 	reserve;
}DISK_INFO_OBJ, *DISK_INFO_HANDLE;

typedef struct _tagDISK_CFG
{
	HB_U32 			disknum;
	HB_U32 			diskctrlnum;
	HB_U32 			nDiskCapacity, nDiskFree ;
	DISK_INFO_OBJ 	diskinfo[MAX_HD];
}DISK_CFG_OBJ, *DISK_CFG_HANDLE;

typedef struct _tagPLAY_STAT
{
	HB_U32 	status; // 0-normal 1-pause 2-frame step 3-fast forward 4-fast backward   5-slow forward 6-slow backward
	HB_U32 	fast_stat; // 0 1 2 3  *
	HB_U32 	reserve;
}PLAY_STAT_OBJ, *PLAY_STAT_HANDLE;

typedef struct _tagSPLIT_CFG
{
	HB_U8 	format; 			// 0-0ff, 1-1, 4-2x2, 9-3x3, 16-4x4
	HB_U8 	source; 			// 0-live, 1-pb
	HB_U8 	pipon; 				// 0-off, 1-右下, 2-左下, 3-右上, 4-左上
	HB_U8 	pipsrc; 			// 0~MAXCH-live, other-pb
	HB_U8 	splitidx[36]; 		// 多画面时，每个位置显示的图像通道
}SPLIT_CFG_OBJ, *SPLIT_CFG_HANDLE;

typedef struct _tagCUR_STATUS
{
	HB_U8 	version[16];
	HB_U8 	datever[16];
	HB_U8 	boardsn[24];
	HB_U8 	version_mcu[8];
	HB_U32 	dspversion; 		//DSP版本号，高16是主版本，低16位是次版本
	HB_U32 	currec;    			//对应通道是否录像
	HB_U32 	curmanrec;
	HB_U32 	curtmrec;
	HB_U32 	curmvrec;
	HB_U32 	curalmrec;
	HB_U32 	imagepoll; 			//轮巡控制
	HB_U32 	videostauts; 		//是否有视频输入
	HB_U32 	audioalarm; 		// 声音报警_(是否有报警)|_|_|_(1:senor 2:move 3:video lost 4:password err)
	HB_U8 	colorsystem; 		// 0-PAL, 1-NTSC4.43 2-NTSC3.58
	HB_U8 	language; 			// 0-Chinese, other-English
	HB_U8 	covermode; 			//0-自动覆盖, other-手动删除
	HB_U8 	rcdtypeshow; 		// 1 show record type
	HB_U16 	loginlock; 			// 1 auto login lock 低8为表示是否启用，高8为表示时间
	HB_U8 	sysmode; 			// 0-16Cif 1-8HD1
	HB_U8 	mvrcdtime; 			// move alarm record time
	HB_U8 	almrcdtime; 		// senor alarm record time
	HB_U8 	bmute; 				// 0-Not mute, other-Mute
	HB_U8 	listenaudio; 		//当前音频通道
	HB_U8 	talkaudio;			//语音对讲
	HB_U8 	boardled;			// bit0-alarm bit1-lock, bit2-network
	HB_U8 	upgradestatus; 		//升级状态
	HB_U8 	vgacvbs;			// 1-vga 0-cvbs
	HB_U8 	avmic; 				// 1-av 0-mic

  /**********Start by zhuhz*************/
	HB_U32 	privencstatus; 		// 每一位对应一路编码器是否工作
	HB_U32 	secvencstatus; 		// 每一位对应一路编码器是否工作
	HB_U32 	privideoiframe;
	HB_U32 	secvideoiframe;
	HB_U32 	drivercmd; 			// 磁盘操作，删除最老文件/切换磁盘等
	HB_CHAR currectype[MAX_CH];

  /***********End by zhuhz*************/

	HB_U8	avmicout;			// 0-监听 1-对讲 sch
	HB_U8 	temperature;		// 1 show DVR board temperature
	HB_U32 	alarmstatus; 		//报警状态 每一位代表一路探头是否报警，供巡航使用
	HB_U32 	softversion;		//8216 中文 8116 英文
	HB_U32 	reserve2;
}CUR_STATUS_OBJ, *CUR_STATUS_HANDLE;

typedef struct _tagDEVICE_INFO
{
	HB_U8 	alarminportnum;		//DVR报警输入个数
	HB_U8 	alarmoutportnum;	//DVR报警输出个数
	HB_U8 	rs232num;			//DVR 232串口个数
	HB_U8 	rs485num;			//DVR 485串口个数
	HB_U8 	networkportnum;		//网络口个数
	HB_U8 	dvrtype;			//DVR类型, 1:DVR 2:ATM DVR 3:DVS ......
	HB_U8 	decordchans;		//DVR 解码路数
	HB_U8 	vganum;				//VGA口的个数
	HB_U16 	usbnum;				//USB口的个数
	HB_U16 	netinterface; 		//网络接口 1-10MBase-T 2-10MBase-T全双工 3-100MBase-TX 4-100M全双工 5-10M/100M自适应-
}DEVICE_INFO_OBJ, *DEVICE_INFO_HANDLE;

typedef struct _tagOSD_PARAM
{
	HB_U8 	osdformat; 			//0:XXXX-XX-XX年月日 1:XX-XX-XXXX月日年 2:XXXX年XX月XX日3:XX月XX日XXXX年
	HB_U8 	osdattrib; 			// 1-透明闪烁2-透明不闪烁3-闪烁不透明4-不透明不闪烁
	HB_U8 	showrlchanname;
	HB_U8 	rlchpos;			// 0-左上1－左下2－右上3－右下
	HB_U8 	showrldate;
	HB_U8 	rldatepos;			// 0-左上1－左下2－右上3－右下
	HB_U8 	showrlweek;

	HB_U8 	showpbchanname;
	HB_U8 	pbchpos;			// 0-左上1－左下2－右上3－右下
	HB_U8 	showpbdate;
	HB_U8 	pbdatepos;			// 0-左上1－左下2－右上3－右下
	HB_U8 	showpbweek;
	HB_U16 	x_pbchpos;
	HB_U16 	y_pbchpos;
	HB_U16 	x_pbdatepos;
	HB_U16 	y_pbdatepos;
	HB_U32 	osd_contrast;
}OSD_PARAM_OBJ, *OSD_PARAM_HANDLE;

typedef struct _tagALMOUT_INFO
{
	HB_U8			alarmout; //alarmout status
	HB_U8			enalmmax; // 1-senor or move alarm to chang one real window
	HB_U8			almoutosd; //almout to screen
	HB_U16			almoutsec; // 报警输出时间
	HB_U32			almoutbuzzer; // 报警送蜂鸣器
	TMSCHEDULE_OBJ	schedule[MAX_AM];
	//TMSchedule	schedule[MAX_AM];
}ALMOUT_INFO_OBJ, *ALMOUT_INFO_HANDLE;


typedef struct _tagBACKUP_INFO
{
	HB_U8	nport;
	HB_U16	year;
	HB_U8	month;
	HB_U8	day;
	HB_U8	bgn_hour;
	HB_U8	bgn_minute;
	HB_U8	end_hour;
	HB_U8	end_minute;
} BACKUP_INFO_OBJ, *BACKUP_INFO_HANDLE;//备份时使用

//sch 2008-03-23
typedef struct _tagMATRIX_SET
{
	HB_U8 	inch[MAX_CH];
	HB_U8 	outch[MAX_CH];
	HB_U16 	MatrixPoll;
	HB_U32 	MatrixPolltime;
	HB_U16 	MatrixPollch;
}MATRIX_SET_OBJ, *MATRIX_SET_HANDLE;

//sch 2008-09-05
 typedef struct _tagREGSERVERINFO
{
	 HB_U32 regserverip;
	 HB_U16 regserverport;
	 HB_U16 regpertime;
}REGSERVERINFO_OBJ, *REGSERVERINFO_HANDLE;

//kl 2009-4-1
typedef struct _tagAV_ENCODE_FORMAT
{
	HB_S32				main_encode_type;
	HB_S32				main_width;
	HB_S32				main_height;
	HB_S32				main_framerate;

	HB_S32				secondary_encode_type;
	HB_S32				secondary_width;
	HB_S32				secondary_height;
	HB_S32				secondary_framerate;

	HB_S32				third_encode_type;
	HB_S32				third_width;
	HB_S32				third_height;
	HB_S32				third_framerate;

	HB_S32				specify_preview;
	HB_S32				preview_width;
	HB_S32				preview_height;
	HB_S32				preview_framerate;


	//   for A3 ONLY, not useful for A2  start
	HB_S32				framerate_flag;			// encode format flags, set when framerate is valid
	unsigned long		main_encode_interval;
	unsigned long		secondary_encode_interval;
	HB_S32				encode_interval_flag;	// encode format flags, set when framerate is valid
	//	for A3 ONLY, not useful for A2  end
}AV_ENCODE_FORMAT_OBJ, *AV_ENCODE_FORMAT_HANDLE;

typedef struct _tagAV_INIT_PARAM
{
	AV_ENCODE_FORMAT_OBJ 	encode_param;
	HB_S32 					vin_mode;
	HB_U32 					vout_enable;
	HB_S32 					main_frm_rate;
	HB_S32 					sec_frm_rate;
}AV_INIT_PARAM_OBJ, *AV_INIT_PARAM_HANDLE;

typedef struct _tagACCOUNT_S
{
	HB_U8 	user[32];
	HB_U8 	password[32];
	HB_U32	locate_level;
	HB_U32	remote_level;
	HB_U32	bind_ipaddr;
	HB_U8	bind_macaddr[8];
}ACCOUNT_S_OBJ, *ACCOUNT_S_HANDLE;

typedef struct _tagUSER_MANAGEMENT
{
	HB_U32 			md5_key;
	ACCOUNT_S_OBJ	account[ACCOUNTNUM];
}USER_MANAGEMENT_OBJ, *USER_MANAGEMENT_HANDLE;

//chenjh 2009-09-10
typedef struct _tagIPCCONFIG
{
	HB_U8  bVideoOut;		//视频输出
	HB_U8  bTemperature;		//温度探测
	HB_U8  bVoltage;			//电压探测
	HB_U8  bSubStream;		//子码流
}IPCCONFIG_OBJ, *IPCCONFIG_HANDLE;

//chenjh 2009-11-2 wifi
typedef struct _tagIPCWIFI
{
	HB_CHAR	ssid[50];		//SSID号
	HB_CHAR	wirelessIP[16];	//无线ip
	HB_U16	wpa_set;		//wpa安全类型设置
	HB_U16	wep_type; 		//unable = 0, 64bit = 1, 128bit = 2, 152bit = 3
	HB_CHAR	psw[65];
}IPCWIFI_OBJ, *IPCWIFI_HANDLE;

typedef struct _tagBOOLFLAG
{
	 HB_U8 	bMask; 		//是否开启遮挡
	 HB_U8 	bEncode; 	//是否重新编码
	 HB_U8 	bVout; 		//是否对视频输出做操作
	 HB_U8 	bVideoHead; //是否加视频头
}BOOLFLAG_OBJ, *BOOLFLAG_HANDLE;

typedef struct _tagSYSSTATUS
{
	SYSTM_OBJ          	systime;
	USER_MANAGEMENT_OBJ	accounts;

	IP_SET_OBJ          ip_set;
	PPPOE_SET_OBJ    	pppoe_set;
	DDNS_SET_OBJ      	ddns_set;
	UARTS_SET_OBJ      	uarts_set;
	CH_PARAM_OBJ     	ch_param[MAX_CH];
	PLAY_STAT_OBJ   	play_stat;
	SPLIT_CFG_OBJ   	split_cfg;
	CUR_STATUS_OBJ  	cur_status;
	OSD_PARAM_OBJ 		osd_info;

	OSD_PARAM_OBJ 		osd_info_new[MAX_CH];

	ALARM_PARAM_OBJ  	alarm[MAX_ALARMIN];	// Add by WZ 	2009.03.05
	ALMOUT_INFO_OBJ  	almout_info;
	DISK_CFG_OBJ 		disk_cfg;
	REGSERVERINFO_OBJ	regserinfo;
	HB_CHAR 			SerialId[256];
	HB_U16 				BmpCapture;
	HB_U16 				BmpPort;
	HB_U32 				reserve1;

	AV_INIT_PARAM_OBJ	init_params;

	IPCCONFIG_OBJ		ipcconfig;
	IPCWIFI_OBJ			wifi;

	BOOLFLAG_OBJ		bflag;
	HB_CHAR 			color_time_zone; 	//lr 10-01-15 视频参数时间段
	HB_S32 				frmtype; 			//0 主码流 1 子码流
}SYSSTATUS_OBJ, *SYSSTATUS_HANDLE;

#define INITWATCHVIDEO 0x0201000f
#endif
