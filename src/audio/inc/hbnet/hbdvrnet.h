#ifndef _HB_DVR_NET_H
#define _HB_DVR_NET_H

#include "../common/ipc_common.h"

#ifdef __cpluscplus
#define HB_NET_DVR_API extern
#else
#define HB_NET_DVR_API
#endif

#ifdef __cplusplus

extern "C"
{
#endif

#define __stdcall 
#define CALLBACK

//命令通道回调
typedef HB_VOID (CALLBACK *fcmddatacallback_hb)(HB_U16 cmd, HB_CHAR * cmd_buf,
        HB_S32 cmd_len, HB_S32 result);

//报警回调
typedef HB_VOID (CALLBACK *falarmdatacallbank_hb)(HB_S32 ch, HB_S32 type,
        HB_S32 clear, HB_VOID * paramin);

//实时视频回调
//idx - 通道数 data - 数据指针 size - 数据大小 flag - 0 主码流 1 子码流 param - 扩展结构体指针，暂不用
typedef HB_VOID (CALLBACK *frealdatacallback_hb)(HB_S32 idx, HB_CHAR * data,
        HB_U32 size, HB_S32 flag, HB_VOID * paramin);

//历史视频回调
//idx - 通道数 data - 数据指针 size - 数据大小 param - 扩展结构体指针，暂不用
typedef HB_VOID (CALLBACK *fplaydatacallback_hb)(HB_S32 idx, HB_CHAR * data,
        HB_U32 size, HB_VOID * paramin);

//对讲回调
typedef HB_VOID (CALLBACK *fopentalkcallback_hb)(HB_CHAR * pdata, HB_U32 len,
        HB_S32 type, HB_VOID * paramin);


#define  NAME_LEN                  32
#define  PASSWORD_LEN              16
#define	 SERIALNO_LEN	           48
#define  MAX_CHANNUM	           16

#define  NET_SDVR_LOGIN			   0x00	   //网络登陆主机
#define  NET_SDVR_LOGOUT		   0x01	   //注销网络用户
#define  NET_SDVR_REAL_PLAY		   0x02	   //实时图像
#define  NET_SDVR_REAL_STOP		   0x03
#define  NET_SDVR_VOICE_START	   0X1B	   //对讲操作 
#define  NET_SDVR_VOICE_STOP	   0X1C
#define  NETCOM_VOD_RECFILE_REQ    0x49    //历史视频回放
#define  NETCOM_VOD_RECFILE_REQ_EX 0x4a
#define  NETCOM_VOD_RECFILE_CON    0x4d
#define  NETCOM_VOD_RECFILE_END    0x4f
#define  NET_SDVR_SHAKEHAND		   0xFF	   //握手协议
#define  NET_SDVR_IPCCONFIG_SET    0x86
#define  NET_SDVR_AUDIO_START      0xE0
#define  NET_SDVR_AUDIO_STOP       0xE1
#define  NET_SDVR_GET_ALL    0xE3
#define NET_SDVR_PTZTYPE_GET 0x79 			//获取云台协议
//ep2rom
#define  I2C_RDWR                  0x0707

#if defined(A5S)
#define EEPROM_PAGE0 0x50
#endif
//帧头标志。
#define STREAM_IPC_HEADER_FLAG              0xFF620068

//struct i2c_msg
//{
//    HB_U16 addr;
//    HB_U16 flags;	 //0:write 1:read
//    HB_U16 len;	 //addr and data all len
//    HB_U8 *buf;
//};
//struct i2c_rdwr_ioctl_data
//{
//    struct i2c_msg *msgs;
//    HB_S32 nmsgs;
//    // nmsgs,signal count //
//};
#if 0
typedef enum _tagLOGIN_RET_VALUE_E
{
    HB_SDVR_IPERR      = -101, /** IP address error */
    HB_SDVR_MACERR     = -102, /** MAC address error */
    HB_SDVR_PSWERR     = -103, /** password error */
    HB_SDVR_USERERR    = -104, /**	user name error*/
    HB_SDVR_USERISFULL = -105 /** SDVR user is full*/
} LOGIN_RET_VALUE_E;
#endif
#pragma pack(1)

//ipc命令头
typedef struct _tagHB_PACKAGE_HEADER
{
    /** Async head 'SDVR' */
    HB_U32 async_head;
    /** Use ID */
    HB_U32 user_id;
    /** Command */
    HB_U16 cmd;
    /** Send Data Len */
    HB_U16 len;
    /** Return result 0-faild/1-success */
    HB_U16 result;
    /** Reserve value */
    HB_U16 reserve;
} HB_PACKAGE_HEADER_OBJ, *HB_PACKAGE_HEADER_HANDLE;

//ipc注册命令体
typedef struct _tagHB_SDVR_LOGIN_USER
{
    /** user name */
    HB_CHAR user_name[NAME_LEN];
    /** user's password MD5 encrypt*/
    HB_CHAR user_password[PASSWORD_LEN];
    /** user name's effective length */
    HB_U32 name_len;
    /** password's effective length (md5 encrypt after return length)*/
    HB_U32 password_len;
} HB_SDVR_LOGIN_USER_OBJ, *HB_SDVR_LOGIN_USER_HANDLE;

//Real time image structure (send)
typedef struct _tagIPC_REALPLAY
{
    HB_CHAR byChannel;				//通道号
    HB_CHAR byLinkMode;				// 0-主码流 1-子码流
    HB_CHAR byMultiCast;			//保留
    HB_CHAR sMultiCastIP[16];		//保留
    HB_U16 wPort;				//保留
} IPC_REALPLAY_OBJ, *IPC_REALPLAY_HANDLE;

//Stop real play
typedef struct _tagIPC_REALPLAY_STOP
{
    HB_CHAR byChannel;			//通道号
    HB_CHAR byLinkMode;			//位：0-主码流 1-子码流
    HB_U16 wPort;			    //本地端口
} IPC_REALPLAY_STOP_OBJ, *IPC_REALPLAY_STOP_HANDLE;

// 时间信息（占用4字节，设计要求可按32位比较大小来决定时间的先后）
typedef struct _tagIPC_FIELD_TIME
{
    unsigned second :6;  // 秒: 0~59
    unsigned minute :6;  // 分: 0~59
    unsigned hour :5;    // 时: 0~23
    unsigned day :5;     // 日: 1~31
    unsigned month :4;   // 月: 1~12
    unsigned year :6;    // 年: 2000~2063
} IPC_FIELD_TIME_OBJ, *IPC_FIELD_TIME_HANDLE;

typedef union _tagIPC_TIME
{
    HB_U32 longtime;
    IPC_FIELD_TIME_OBJ fieldtime;
} IPC_TIME_U;

typedef struct _tagIPC_VOD_EX
{
    HB_U8 Channel;            //通道号 0 1 2 3[0, n-1], n:通道数
    HB_U8 dwType;            	//点播类型
    IPC_TIME_U dwtime_start;    	//点播开始时间
    IPC_TIME_U dwtime_end;    		//点播结束时间，时间跨度一天之内
    HB_U8 btRes1;				//保留
    HB_U8 btRes2;				//保留
} IPC_VOD_EX_OBJ, *IPC_VOD_EX_HANDLE;	            	//时间段点播结构体

typedef struct _tagIPC_IPCCONFIG
{
    HB_CHAR bVideoOut;		//视频输出
    HB_CHAR bTemperature;	//温度探测
    HB_CHAR bVoltage;		//电压探测
    HB_CHAR bSubStream;		//子码流
    HB_U32 rserve1;		//保留
    HB_U32 rserve2;		//保留
} IPC_IPCCONFIG_OBJ, *IPC_IPCCONFIG_HANDLE;

typedef struct _tagPT_T
{
    HB_U16 year; 	//年 如2009
    HB_U16 month; 	//月 1-12
    HB_U8 day; 	//日 1-31
    HB_U8 hour; 	//小时 0-23
    HB_U8 minute; 	//分钟 0-59
    HB_U8 second; 	//秒 0-59
    HB_U32 msec;		//毫秒
} PT_T_OBJ, *PT_T_HANDLE;

typedef enum _tagPT_REC
{
    PT_REC_TYPE_UNKNOW = 0, PT_REC_TYPE_MANUAL = 1,   //手动录像
    PT_REC_TYPE_SCHEDULE = 2,   //定时录像
    PT_REC_TYPE_MOTION = 4,   //移动录像
    PT_REC_TYPE_ALARM = 8,   //报警录像
    PT_REC_TYPE_ALL = 0xff //所有
} PT_REC_E;

typedef struct _tagPT_SEG
{
    PT_T_OBJ time; //打开录像日期
    PT_REC_E type; //打开录像类型
    HB_U32 openrec_handle; //打开录像句柄(output)
} PT_SEG_OBJ, *PT_SEG_HANDLE;

typedef struct _tagHB_SDVR_DEVICEINFO
{
    HB_CHAR sSerialNumber[SERIALNO_LEN];         //保留
    HB_CHAR byAlarmInPortNum;                    //DVR报警输入个数
    HB_CHAR byAlarmOutPortNum;                   //DVR报警输出个数
    HB_CHAR byDiskNum;                           //DVR 硬盘个数
    HB_CHAR byDVRType; //DVR类型, 1:DVR 2:ATM DVR 3:DVS  （建议使用HB_SDVR_GetDeviceType）
    HB_CHAR byChanNum;							//DVR 通道个数
    HB_CHAR byStartChan;						//保留
    HB_CHAR sDvrName[NAME_LEN];				//主机名
    HB_CHAR sChanName[MAX_CHANNUM][NAME_LEN];  //通道名称
} HB_SDVR_DEVICEINFO_OBJ, *HB_SDVR_DEVICEINFO_HANDLE;

typedef struct _tagIPC_ALARM
{
    HB_U8 alarmin_status[128];    	//探头报警0-无报警   1-有报警
    //NVR：登陆时返回的结构体中有本地报警输入个数（n），或者使用命令0xc9获取本地报警输入个数（n） 
    //数组前面的n个为本地探头，对应本地探头号, 之后依序往下对应各通道报警输入状态 
    HB_U8 vlost_status[128];    	//视频丢失0-无报警   1-有报警
    HB_U8 motion_status[128];    	//移动报警0-无报警   1-有报警
    HB_U8 hide_status[128];    	//遮挡报警0-无报警   1-有报警
    HB_U8 disk_status[16];   		//硬盘错误0-无报警   1-有报警
} IPC_ALARM_OBJ, *IPC_ALARM_HANDLE;   		//*LPSTRUCT_SDVR_ALARM;

typedef struct _tagIPC_USER_M
{
    HB_U32 locate_level;
    HB_U32 remote_level;
    HB_U32 bind_ip;
    HB_U8  bind_mac[8];
    HB_U8  user[16];
    HB_U8  password[16];
} IPC_USER_M_OBJ, *IPC_USER_M_HANDLE;

//码流帧头。
//sizeof(STREAM_HEADER) == 16
typedef struct _tagSTREAM_IPC_HEADER
{
    //帧头标志，必须是STREAM_HEADER_FLAG。
    HB_U32 nHeaderFlag;

    //帧头的大小，以字节为单位，取值范围[sizeof(STREAM_HEADER), 65535]。
    // nHeaderSize = sizeof(STREAM_HEADER)
    // + IsStreamVideoFrame() ? STREAM_VIDEO_HEADER.nVideoHeaderSize : 0
    // + STREAM_SEGMENT_HEADER[0].nSegmentSize + ... 
    // + STREAM_SEGMENT_HEADER[nSegmentCount-1].nSegmentSize;
    HB_U32 nHeaderSize :16;

    //帧类型，使用STREAM_FRAME_*。
    //当帧类型是STREAM_FRAME_VIDEO_*时，STREAM_HEADER结构体随后是STREAM_VIDEO_HEADER。
    HB_U32 nFrameType :3;

    //音频或视频编码算法。
    //当nFrameType==STREAM_FRAME_AUDIO时，使用STREAM_ALGORITHM_AUDIO_*。
    //当nFrameType==STREAM_ALGORITHM_VIDEO_*时，使用STREAM_ALGORITHM_VIDEO_*。
    HB_U32 nAlgorithm :5;

    //STREAM_SEGMENT_HEADER结构体的数量，取值范围[0, 255]。
    //当nSegmentCount==0时，表示没有STREAM_SEGMENT_HEADER。
    //一般的，只当nFrameType == STREAM_FRAME_VIDEO_I时，才设置nSegmentCount。
    HB_U32 nSegmentCount :8;

    //需要校验的编码数据的大小，取值范围[0, 255]。
    //一般只校验编码数据的前、后部分字节。
    //当nCheckedDataSize==0时，不校验编码数据。
    //建议：至少校验前后各16个字节的编码数据。
    HB_U32 nCheckedEncodeDataSize :8;

    //校验和，不能等于0。
    //包括STREAM_VIDEO_HEADER、STREAM_HEADER_SEGMENT[0 : n-1]和编码数据的前、后
    //部分字节。
    HB_U32 nChecksum :24;

    //编码数据的大小，以字节为单位，取值范围[0, 16777215]。
    HB_U32 nEncodeDataSize :24;

    //保留。
    HB_U32 nReserved :8;

} STREAM_IPC_HEADER_OBJ, *STREAM_IPC_HEADER_HANDLE;

#pragma pack()

//平台初始化
HB_S32 hb_ipc_init(HB_S32 platform);
//平台注册
//HB_S32 hb_ipc_login(HB_VOID);
HB_S32 hb_ipc_login(HB_CHAR *usrname, HB_CHAR *password, HB_CHAR *server_ip, HB_U32 server_port);
//平台退出
HB_S32 hb_ipc_logout(HB_VOID);

//设置实时视频回调
HB_S32 hb_ipc_setrealdatacb(HB_S32 realhandle, HB_VOID *pcbRealDataCallBack,
        HB_S32 dusrdata);
//关闭实时视频回调
HB_S32 hb_ipc_stoprealdatacb(HB_VOID);
//打开某通道实时视频
HB_S32 hb_ipc_openvideo(HB_S32 channel, HB_S32 stream_mode);
//关闭某通道实时视频
HB_S32 hb_ipc_closevideo(HB_S32 channel, HB_S32 stream_mode);

//设置实时视频子码流回调
HB_S32 hb_ipc_setsubrealdatacb(HB_S32 realhandle, HB_VOID *pcbRealDataCallBack,
        HB_S32 dusrdata);
//关闭实时视频子码流回调
HB_S32 hb_ipc_stopsubrealdatacb(HB_VOID);
//打开某通道实时视频字码流
HB_S32 hb_ipc_opensubvideo(HB_S32 channel, HB_S32 stream_mode);
//关闭某通道实时视频字码流
HB_S32 hb_ipc_closesubvideo(HB_S32 channel, HB_S32 stream_mode);

//设置历史视频回调
HB_S32 hb_ipc_setplaydatacb(HB_S32 realhandle, HB_VOID *pcbplaydatacallback,
        HB_S32 dusrdata);
//关闭历史视频回调
HB_S32 hb_ipc_stopplaydatacb(HB_VOID);
//打开某段时间历史视频
HB_S32 hb_ipc_openvod(HB_U32 * open_handle, HB_S32 channel,
        IPC_VOD_EX_OBJ param, HB_S32 size_of_param);
//关闭某段时间历史视频
HB_S32 hb_ipc_closevod(HB_S32 channel, HB_VOID *pparam, HB_S32 size_of_param);

//打开对讲回调
HB_S32 hb_ipc_opentalkcb(HB_VOID * cbopentalkcallback, HB_S32 size_of_param);
//关闭对讲回调
HB_S32 hb_ipc_stoptalkcb(HB_VOID);
//向IPC写入对讲数据
HB_S32 hb_write_ao(HB_CHAR *pdata, HB_U32 size, HB_S32 type);

//注册命令回调
HB_S32 hb_ipc_opencmdcb(HB_VOID * pcbcmddatacallback, HB_S32 size_of_param);
//关闭命令回调
HB_S32 hb_ipc_stopcmdcb(HB_VOID);

//向IPC发送一条命令
HB_S32 hb_ipc_senddata(unsigned cmd, HB_CHAR *pcmdbuf, HB_U16 cmdlen,
        HB_U32 reserve);

//读取 ep2rom 
HB_S32 get_i2cdata(HB_S32 addr, HB_U16 addr_addr, HB_U16 r_num,
        HB_CHAR *ptemp_buff);
HB_S32 write_eeprom(HB_S32 addr, HB_S32 addr_addr, HB_U16 w_num,
        HB_CHAR *ptemp_buf);

//写入ep2rom
HB_S32 per_w(HB_U8 page, HB_U8 addr, HB_U16 num, HB_CHAR *ptemp_buff);
HB_S32 hb_get_ptzlist(HB_VOID *pparam);
HB_S32 hb_get_usrinfolist(HB_VOID *pparam);

#ifdef __cplusplus
}
#endif
#endif

