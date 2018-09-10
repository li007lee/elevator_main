////////////////////////////////////////////////////////////////////////////////
// 版权所有，2009-2012，北京汉邦高科数字技术有限公司。
// 该文件是未公开的，包含了汉邦高科机密和专利内容。
////////////////////////////////////////////////////////////////////////////////
//文件名：ipc_protocol.h
//作者:   孙威
//版本:   1.0
//日期:   2013.1.6
//功能描述:
//        IPC协议头文件
//历史记录:
////////////////////////////////////////////////////////////////////////////////
#ifndef _IPC_PROTOCOL_H
#define _IPC_PROTOCOL_H

#pragma pack(1)

#define NET_SDVR_IPCCONFIG_EX_GET       (0xBE)
#define NET_SDVR_IPCCONFIG_EX_SET       (0xBF)

//////////////////////////////////////////////////////////////////////////////
//IPC主命令分类命令
//////////////////////////////////////////////////////////////////////////////
typedef enum _tagIPC_PRI_CMD_TYPE
{
    IPC_VIDEO_CMD = 0,      //IPC音视频命令
    IPC_NET_CMD,            //IPC网络命令
    IPC_STORE_CMD,          //IPC存储命令
    IPC_ALARM_CMD,          //IPC报警命令
    IPC_MANAGE_CMD,         //IPC管理命令
    IPC_SERIAL_CMD,         //IPC串口命令
    IPC_PRI_CMD_MAX
}IPC_PRI_CMD_TYPE_E;

//////////////////////////////////////////////////////////////////////////////
//音视频命令
//////////////////////////////////////////////////////////////////////////////
typedef enum _tagIPC_VIDEO_CMD_TYPE
{
    IPC_IMAGE_PARAM = 0,      //IPC图像参数
    IPC_VIDEO_PARAM,          //IPC视频参数
    IPC_VIDEO_ENCODE,         //IPC视频编码参数
    IPC_PICTURE_SNAP,         //IPC图像抓拍参数
    IPC_OSD_OVERLAY,          //IPC字符叠加参数
    IPC_MASK,                 //IPC遮挡参数
    IPC_ADVANCE_PARAM,        //IPC高级参数
    IPC_AUDIO_IN_PARAM,       //IPC音频输入参数
    IPC_AUDIO_OUT_PARAM,      //IPC音频输出参数 
    IPC_VIDEO_CMD_MAX
}IPC_VIDEO_CMD_TYPE_E;

//////////////////////////////////////////////////////////////////////////////
//网络命令
//////////////////////////////////////////////////////////////////////////////
typedef enum _tagIPC_NET_CMD_TYPE
{
    IPC_IP_PARAM = 0,           //IPC 有线网络参数
    IPC_PPPOE,                  //IPC PPPOE参数
    IPC_E_MAIL,                 //IPC E_MAIL参数
    IPC_FTP,                    //IPC FTP参数
    IPC_PLATFORM,               //IPC 平台参数
    IPC_NAS,                    //IPC NAS
    IPC_AUTO_REGIST,            //IPC 自动注册
    IPC_UPNP,                   //IPC uPNP
    IPC_WIRELESS_NETWORK,       //IPC 无线网络
    IPC_NET_CMD_MAX
}IPC_NET_CMD_TYPE_E;

//////////////////////////////////////////////////////////////////////////////
//存储命令
//////////////////////////////////////////////////////////////////////////////
typedef enum _tagIPC_STORE_CMD_TYPE
{
    IPC_TIME_RECORD = 0,    //IPC定时录像参数
    IPC_RECORD_MODE,        //IPC录像存储方式
    IPC_DISK_CFG,           //IPC存储设备状态
    IPC_STORE_CMD_MAX       //存储类命令最大值
}IPC_STORE_CMD_TYPE_E;

//////////////////////////////////////////////////////////////////////////////
//报警命令
//////////////////////////////////////////////////////////////////////////////
typedef enum _tagIPC_ALARM_CMD_TYPE
{
    IPC_MOTION = 0,     //IPC移动侦测参数
    IPC_ALARMIN,        //IPC报警输入参数
    IPC_ALARMOUT,       //IPC报警输出参数
    IPC_NET_BUG,        //IPC网络故障报警参数
    IPC_STORE_BUG,      //IPC存储故障报警参数
    IPC_ALARM_CMD_MAX   //报警类命令最大值
}IPC_ALARM_CMD_TYPE_E;

//////////////////////////////////////////////////////////////////////////////
//管理命令
//////////////////////////////////////////////////////////////////////////////
typedef enum _tagIPC_MANAGE_CMD_TYPE
{
    IPC_DEVICE_INFO = 0,    //IPC设备信息
    IPC_AUTO_MAINTAINING,   //IPC自动维护参数
    IPC_ABILITY,            //IPC页面加载能力集
    IPC_DOME_ABILITY,       //球机页面加载
    IPC_MANAGE_CMD_MAX      //设备管理类命令最大值
} IPC_MANAGE_CMD_TYPE_E;

//////////////////////////////////////////////////////////////////////////////
//串口命令
//////////////////////////////////////////////////////////////////////////////
typedef enum _tagIPC_SERIAL_CMD_TYPE
{
    IPC_SERIAL_INFO = 0,    //IPC设备信息
    IPC_SERIAL_CMD_MAX      //串口类命令最大值
} IPC_SERIAL_CMD_TYPE_E;

//////////////////////////////////////////////////////////////////////////////
//系统时间
//////////////////////////////////////////////////////////////////////////////
typedef struct _tagIPC_SYS_TIME
{
    HB_U16 year;    //年  保留
    HB_U8  month;   //月  保留
    HB_U8  day;     //日  保留
    HB_U8  week;    //星期
    HB_U8  hour;    //小时
    HB_U8  min;     //分钟
    HB_U8  sec;     //秒
}IPC_SYS_TIME_OBJ, *IPC_SYS_TIME_HANDLE;

//////////////////////////////////////////////////////////////////////////////
//时间段
//////////////////////////////////////////////////////////////////////////////
typedef struct _tagIPC_TIME_PERIOD
{
    HB_U8 start_hour;     //开始小时
    HB_U8 start_min;      //开始分钟
    HB_U8 end_hour;       //结束小时
    HB_U8 end_min;        //结束分钟
}IPC_TIME_PERIOD_OBJ, *IPC_TIME_PERIOD_HANDLE;
//////////////////////////////////////////////////////////////////////////////
//一天内的四个时间段
//////////////////////////////////////////////////////////////////////////////
typedef struct _tagIPC_TIME_ITEM
{
    HB_U8               select[4];  //0-no     1-yes
    IPC_TIME_PERIOD_OBJ period[4];  //时间段
}IPC_TIME_ITEM_OBJ, *IPC_TIME_ITEM_HANDLE;
//////////////////////////////////////////////////////////////////////////////
//一周时间段
//////////////////////////////////////////////////////////////////////////////
typedef struct _tagIPC_TIME_SCHEDULE
{
    HB_S32             status;    //0-no, 1-yes
    IPC_TIME_ITEM_OBJ  item[8];   // 0-7: everyday, monday...sunday
}IPC_TIME_SCHEDULE_OBJ, *IPC_TIME_SCHEDULE_HANDLE;

//////////////////////////////////////////////////////////////////////////////
//图像参数
//////////////////////////////////////////////////////////////////////////////
typedef struct _tagIMAGE_PARAM_ITEM
{
    IPC_TIME_PERIOD_OBJ  time;               //时间段
    HB_S16               bright_value;       //亮度
    HB_S16               contrast_value;     //对比度
    HB_S16               saturation_value;   //饱和度
    HB_S16               hue_value;          //灰度
    HB_S16               sharpness;          //锐度
    HB_S16               reserve;            //保留
}IMAGE_PARAM_ITEM_OBJ, *IMAGE_PARAM_ITEM_HANDLE;

//////////////////////////////////////////////////////////////////////////////
//图像参数管理
//////////////////////////////////////////////////////////////////////////////
typedef struct _tagIPC_IMAGE_PARAM
{
    HB_S32               length;              //结构体长度
    HB_S32               channel_num;         //通道号
    IMAGE_PARAM_ITEM_OBJ item[3];             //0-默认 1-时间段1 2-时间段2
}IPC_IMAGE_PARAM_OBJ, *IPC_IMAGE_PARAM_HANDLE;

//////////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////////////
typedef struct _tagIPC_LENS
{
    HB_S32 lens_iris;        //光圈 -1-不支持 0-自动 1-手动       
    HB_S32 lens_index;       //当前机型支持的镜头，-1-不支持
    HB_U8  lens_val[16][32]; //获取镜头的支持列表,只能获取
}IPC_LENS_OBJ, *IPC_LENS_HANDLE;

//////////////////////////////////////////////////////////////////////////////
//AGC  电子快门
//////////////////////////////////////////////////////////////////////////////
typedef struct _tagIPC_AE
{   
    HB_S32  ae_contrl;        //AE -1-不支持 0-自动 1-手动
    HB_S32  shutter_index;    //shutter索引，-1-不支持，如shutter_index=0;
                              //快门时间为shutter_val[0]=1000;
    HB_S32  shutter_val[32];  //快门时间的支持参数列表,只能获取
    HB_S32  agc_index;        //agc索引，-1-不支持，
                              //如agc_index=0;agc值为agc_val[0] = 32;
    HB_S32  agc_val[32];      //AGC（自动增益）的支持参数列表,只能获取。
}IPC_AE_OBJ, *IPC_AE_HANDLE;

//////////////////////////////////////////////////////////////////////////////
//ICR切换的工作能力
//////////////////////////////////////////////////////////////////////////////
typedef struct _tagIPC_ICR_ABILITY
{
    HB_S32  max_value;        //切换的最大值，只能获取
    HB_S32  min_value;        //切换的最小值，只能获取
    HB_S32  cur_value;        //切换的当前值
}IPC_ICR_ABILITY_OBJ, *IPC_ICR_ABILITY_HANDLE;

//////////////////////////////////////////////////////////////////////////////
//黑白模式管理
//////////////////////////////////////////////////////////////////////////////
typedef struct _tagIPC_DAY_NIGHT
{
    HB_S32               daynight_model;               //日夜模式  -1-不支持 0-自动 1-彩色 2-黑白
    HB_S32               icr_enable;                   //使能 -1-不支持  0-亮度值有效  1-时间段有效        
    HB_S32               sensitivity;                  //灵敏度值
    IPC_ICR_ABILITY_OBJ  blackwhite_value;             //黑白切换的阀值
    IPC_ICR_ABILITY_OBJ  color_value;                  //彩色切换的阀值
    HB_S32               min_interval;                 //黑白切换与彩色切换之间的最小间隔，只能读取
    IPC_TIME_PERIOD_OBJ  time_range[2];                //时间段 
}IPC_DAY_NIGHT_OBJ, *IPC_DAY_NIGHT_HANDLE;

//////////////////////////////////////////////////////////////////////////////
//视频参数
//////////////////////////////////////////////////////////////////////////////
typedef struct _tagIPC_VIDEO_PARAM
{
    HB_S32               length;       //结构体长度
    HB_S32               channel_num;  //通道号
    IPC_AE_OBJ           ae_model;     //AE模式
    IPC_DAY_NIGHT_OBJ    daynight;     //日夜模式
    HB_S32               image_flip;   //图像翻转 -1-不支持 0-不翻转 
                                       //1-水平翻转 2-垂直翻转 3-水平&垂直
    HB_S32               image_spin;   //图像旋转 -1-不支持 0-不旋转 1-顺时针旋转90°
                                       //2-顺时针旋转180°3-顺时针旋转270°
    HB_S32               scene_model;  //白平衡场景模式 -1-不支持 0-未开启 1-自动, 2-sunny, 3-shadow, 4-indoor,……   
}IPC_VIDEO_PARAM_OBJ, *IPC_VIDEO_PARAM_HANDLE;

//////////////////////////////////////////////////////////////////////////////
//视频编码参数
//////////////////////////////////////////////////////////////////////////////
typedef struct _tagIPC_RESOLUTION_PARAM
{
    HB_S32 resolution_index;      //当前分辨率  
    HB_S32 resolution[32][2];     //-1-不支持，该机型支持的分辨率最多为32个，
                                  //只能获取,分别为32组宽高，
                                  //如resolution_index=1;resolution[1][0] = 1920;resolution[1][1] = 1080;当前分辨率为1920*1080
}IPC_RESOLUTION_PARAM_OBJ, *IPC_RESOLUTION_PARAM_HANDLE;

//////////////////////////////////////////////////////////////////////////////
//IPC帧率信息
//////////////////////////////////////////////////////////////////////////////
typedef struct _tagIPC_FRAMERATE
{
    HB_S16  min_framerate;         //该机型支持的最小编码帧率值;
    HB_S16  max_framerate;         //该机型支持的最大编码帧率值;
    HB_S16  cur_framerate;         //该机型设置的当前编码帧率值;
    HB_S16  reserve;               //保留
}IPC_FRAMERATE_OBJ, *IPC_FRAMERATE_HANDLE;


//////////////////////////////////////////////////////////////////////////////
//视频流参数
//////////////////////////////////////////////////////////////////////////////
typedef struct _tagIPC_STREAM_PARAM
{
    HB_S8                     enable;            //使能 -1-不支持 0-off, 1-on
    HB_S8                     encode_type;       //编码类型 0-H264 1-MJPEG 2-MPEG4
    HB_S8                     stream_control;    //码流控制 0-定码流 1-变码流
    HB_U8                     i_frame;           //I帧间隔  1-254
    HB_U16                    video_bitrate;     //视频码率  -1-不支持 0-128K 1-256K，2-384K,3-512K，4-1M，5-1.5M，
                                                 //6-2M，7-3M, 8-4M，9-5M，10-6M，11-7M，12-8M,13-自定义,以K为单位（128k-12M）；
    HB_S16                    audio_enable;      //音频 -1-不支持 0-off, 1-on
    IPC_RESOLUTION_PARAM_OBJ  resolution;        //分辨率
    IPC_FRAMERATE_OBJ         framerate;         //编码帧率设置 
}IPC_STREAM_PARAM_OBJ, *IPC_STREAM_PARAM_HANDLE;

//////////////////////////////////////////////////////////////////////////////
//视频编码
//////////////////////////////////////////////////////////////////////////////
typedef struct _tagIPC_VIDEO_ENCODE
{
    HB_S32                length;               //结构体长度
    HB_S32                channel_num;          //通道号 [0, n－1] n:通道数
    HB_S16                combo_index;          //当前套餐值 0-自定义 1-套餐一 2-套餐二 3-套餐三……
    HB_S16                combo_num;            //总套餐数量
    HB_S8                 combo[256];           //套餐内容 只获取
    IPC_STREAM_PARAM_OBJ  stream[4];            //0-主码流 1-子码流1 2-子码流2 3-子码流3   当套餐值为自定义时，可设置，其余情况只读
    HB_S32                reserve;              //保留
}IPC_VIDEO_ENCODE_OBJ, *IPC_VIDEO_ENCODE_HANDLE;

//////////////////////////////////////////////////////////////////////////////
//字符叠加位置
//////////////////////////////////////////////////////////////////////////////
typedef struct _tagIPC_OSD_POS
{
    HB_S32  posx;          //x坐标
    HB_S32  posy;          //y坐标
    HB_S32  reserve;       //保留
}IPC_OSD_POS_OBJ, *IPC_OSD_POS_HANDLE;

//////////////////////////////////////////////////////////////////////////////
//自定义OSD信息
//////////////////////////////////////////////////////////////////////////////
typedef struct _tagIPC_OSD_USERDEF
{
    HB_S32           enable;            //使能 -1-不支持 0-关闭 1-开启
    IPC_OSD_POS_OBJ  osd_pos;           //自定义OSD坐标
    HB_CHAR          osd_strings[128];  //自定义OSD内容
    HB_S32           reserve;           //保留
}IPC_OSD_USERDEF_OBJ, *IPC_OSD_USERDEF_HANDLE;

//////////////////////////////////////////////////////////////////////////////
//OSD信息
//////////////////////////////////////////////////////////////////////////////
typedef struct _tagIPC_OSD_OVERLAY
{
    HB_S32               length;                    //结构体长度
    HB_S32               channel_num;               //通道号 [0, n－1] n:通道数 
    HB_S32               osd_enable;                //OSD使能 -1-不支持 0-off, 1-on 
    HB_S16               osd_attribute;             //OSD属性  0-不透明 1-透明
    HB_S16               osd_add_model;             //OSD叠加方式 0-前端叠加 1-后端叠加
    HB_S16               ch_name_enable;            //是否显示通道名 0-不显示 1-显示
    HB_S16               time_info_enable;          //是否显示时间  -1-不支持 0-off, 1-on 
    HB_S16               week_display;              //是否显示星期  -1-不支持 0-off, 1-on 
    HB_S16               time_format;               //时间格式   0- YYYY-MM-DD 1- DD-MM-YYYY 2- MM-DD-YYYY
    HB_S16               inverse_color;             //OSD反色 -1-不支持 0-off, 1-on
    HB_S16               color_index;               //OSD前端字体颜色  -1-不支持 
    HB_S8                color[8][16];              //OSD前端字体颜色表
    HB_CHAR              ch_name[32];               //通道名 字符内容
    IPC_OSD_POS_OBJ      ch_name_pos;               //通道名坐标 
    IPC_OSD_POS_OBJ      time_pos;                  //时码坐标 
    IPC_OSD_USERDEF_OBJ  osd_userdef[8];            //预留 尚未使用
}IPC_OSD_OVERLAY_OBJ, *IPC_OSD_OVERLAY_HANDLE;

//////////////////////////////////////////////////////////////////////////////
//视频遮挡区域
//////////////////////////////////////////////////////////////////////////////
typedef struct _tagIPC_MASK_AREA
{
    HB_S32  startx;           //遮挡区域起点X坐标 0~704
    HB_S32  starty;           //遮挡区域起点Y坐标 0~576
    HB_S32  width;            //遮挡区域宽度 0~704
    HB_S32  height;           //遮挡区域高度 0~576
}IPC_MASK_AREA_OBJ, *IPC_MASK_AREA_HANDLE;

//////////////////////////////////////////////////////////////////////////////
//视频遮挡管理
//////////////////////////////////////////////////////////////////////////////
typedef struct _tagIPC_MASK
{
    HB_S32             length;                  //结构体长度
    HB_S32             channel_num;             //通道号 [0, n－1] n:通道数
    HB_S32             mask_enable;             //遮挡块使能  -1-不支持 0-off, 1-on
    IPC_MASK_AREA_OBJ  maskarea[8];             //视频遮挡区域，最大支持遮挡8块
}IPC_MASK_OBJ, *IPC_MASK_HANDLE;

//////////////////////////////////////////////////////////////////////////////
// 音频输入参数
//////////////////////////////////////////////////////////////////////////////
typedef struct _tagIPC_AUDIO_IN_PARAM
{
    HB_S32    length;                      //结构体长度
    HB_S32    channel_num;                 //通道号 [0, n－1] n:通道数
    HB_S16    reserve;                     //保留
    HB_S16    in_volume;                   //输入音量   0-100
    HB_S32    audio_in_index;              //音频输入源 -1-不支持
    HB_U8     audio_in[8][16];             //音频输入源列表
    HB_S32    compress_format_index;       //音频压缩格式 -1-不支持
    HB_U8     compress_format[16][10];     //音频压缩格式表 
    HB_S32    bitrate_index;               //音频码率 -1-不支持
    HB_U32    bitrate[16];                 //音频码率表 
    HB_S32    samplerate_index;            //音频采样率 -1-不支持
    HB_U32    samplerate[16];              //音频采样率表
}IPC_AUDIO_IN_PARAM_OBJ, *IPC_AUDIO_IN_PARAM_HANDLE;

/////////////////////////////////////////////////////////////////////////////
// 音频输出参数
//////////////////////////////////////////////////////////////////////////////
typedef struct _tagIPC_AUDIO_OUT_PARAM
{
    HB_S32    length;                      //结构体长度
    HB_S32    channel_num;                 //通道号 [0, n－1] n:通道数  
    HB_S16    reserve;                     //保留
    HB_S16    out_volume;                  //输出音量   0-100
    HB_S32    audio_out_index;             //音频输出源 -1-不支持
    HB_U8     audio_out[8][16];            //音频输出源列表
    HB_S32    compress_format_index;       //音频压缩格式 -1-不支持
    HB_U8     compress_format[16][10];     //音频压缩格式表 
    HB_S32    bitrate_index;               //音频码率 -1-不支持
    HB_U32    bitrate[16];                 //音频码率表 
    HB_S32    samplerate_index;            //音频采样率 -1-不支持
    HB_U32    samplerate[16];              //音频采样率表        
}IPC_AUDIO_OUT_PARAM_OBJ, *IPC_AUDIO_OUT_PARAM_HANDLE;

//////////////////////////////////////////////////////////////////////////////
//图像抓拍
//////////////////////////////////////////////////////////////////////////////
typedef struct
{
    HB_S32                length;              //结构体长度
    HB_S32                channel_num;         //通道号 [0, n-1] n:通道数
    HB_S8                 snapshot_enable;     //图像抓拍使能 -1-不支持 0-off, 1-on
    HB_U8                 snapshot_type;       //抓拍类型  0-定时抓图 1-触发抓图  
    HB_U8                 pic_quality;         //图片质量  0-差 1-较差 2-一般 3-较好 4-好
    HB_U8                 snap_speed;          //抓拍速度 单位（秒/张） 1秒/张 2秒/张……
    HB_S32                snapshot_res_index;  //图像抓拍当前分辨率  
    HB_S32                snapshot_res[32][2]; //-1-不支持，该机型支持的分辨率最多为32个，
                                               //只能获取,分别为32组宽高，
                                               //如snapshot_res_index=1;snapshot_res[1][0] = 1920;snapshot_res[1][1] = 1080;当前分辨率为1920*1080
    HB_S32                pic_format_index;    //图片格式 -1-不支持 
    HB_S8                 pic_format[5][8];   //图片格式列表 
    IPC_TIME_SCHEDULE_OBJ schedule;            //抓拍时间计划
}IPC_PICTURE_SNAP_OBJ, *IPC_PICTURE_SNAP_HANDLE;

//////////////////////////////////////////////////////////////////////////////
//高级参数
//////////////////////////////////////////////////////////////////////////////
typedef struct _tagIPC_A5_ADVANCE
{
    IPC_LENS_OBJ         iris_model;  //光圈
    HB_S8    vout_type;               //模拟视频输出 -1-不支持 0-NTSC, 1-PAL
    HB_S8    anti_flicker;            //抗闪烁 -1-不支持 0- 50Hz 1- 60Hz
    HB_S8    wdr;                     //宽动态 -1-不支持 0-off, 1-on
    HB_S32   denoise_3d_val;          //3D降噪值 -1-不支持 0-255
    HB_S8    denoise_2d;              //2D降噪   -1-不支持 0-off, 1-on
    HB_S8    blc;                     //背光补偿 -1-不支持 0-off, 1-on
    HB_S8    encode_type;             //编码模式 -1-不支持 0-普通 1-低延时
    HB_S8    focus_speed;             //光学变焦速度值，-1-不支持 1-100 暂不支持
    HB_S8    digital_foucus;          //数字变焦值，-1-不支持 1-100 暂不支持
    HB_S8    auto_dropframe;          //夜间自动降帧  -1-不支持 0-off, 1-on
    HB_S8    stream_type;             //码流类型 0-无汉邦头 1-有汉邦头 暂不支持
    HB_S8    reserve[6];              //保留
}IPC_A5_ADVANCE_OBJ, *IPC_A5_ADVANCE_HANDLE;

typedef struct _tagIPC_HISI_ADVANCE
{
    HB_S8    anti_flicker_enable;       //抗闪烁使能  -1-不支持 0-off, 1-on
    HB_S8    anti_flicker;              //抗闪烁  0- 50Hz 1- 60Hz 2-自动 
    HB_S8    wdr;                       //宽动态  -1-不支持 0-off, 1-on 
    HB_S8    wdr_type;                  //宽动态模式选择 -1-不支持 0-线性模式, 1-宽动态模式
    HB_S8    time_domain;               //3D降噪时间域  -1-不支持 0-63
    HB_S32   space_domain;              //3D降噪空间域   -1-不支持 0-255
    HB_S8    denoise_2d;                //2D降噪   -1-不支持 0-off, 1-on
    HB_S8    defog;                     //去雾     -1-不支持 0-off, 1-on
    HB_S8    pseudo_color;              //去伪彩   -1-不支持 0-off, 1-on
    HB_U8    pseudo_color_num;          //去伪彩值 0-255
    HB_S8    encode_type;               //编码模式 0-普通 1-低延时
    HB_S8    vout_type;                 //模拟视频输出 -1-不支持 0-NTSC, 1-PAL
    HB_S8    auto_dropframe;            //夜间自动降帧  -1-不支持 0-off, 1-on 
    HB_S8    stream_type;               //码流类型 0-无汉邦头 1-有汉邦头 暂不支持 
    HB_S8    reserve[7];                //保留
}IPC_HISI_ADVANCE_OBJ, *IPC_HISI_ADVANCE_HANDLE;

typedef struct
{
    HB_S32   length;                        //结构体长度
    HB_S32   channel_num;                   //通道号 [0, n－1] n:通道数
    HB_S32   type;                          //同获取IPC加载能力集中advance_param的值一致
                                            //type = 1;是IPC_A5_ADVANCE_OBJ， type = 2;IPC_HISI_ADVANCE_OBJ
    HB_S32   size;                          //对应union cfg中结构体的大小
    union
    {
    	IPC_A5_ADVANCE_OBJ    a5_advance;   //A5高级参数
    	IPC_HISI_ADVANCE_OBJ  hisi_advance; //海思高级参数
    }cfg;
}IPC_ADVANCE_PARAM_OBJ, *IPC_ADVANCE_PARAM_HANDLE;

//////////////////////////////////////////////////////////////////////////////
//IPV4网络参数
//////////////////////////////////////////////////////////////////////////////
typedef struct _tagIPC_IPV4
{
    HB_U8   ip[4];             //ip地址 如IP为192.168.9.31,ip[0]=192 ip[1]=168 ip[2]=9 ip[3]=31;
    HB_U8   mask[4];           //子网掩码
    HB_U8   gateway[4];        //默认网关
    HB_U8   dns[4];            //首选DNS 
    HB_U8   dns_bak[4];        //备选DNS
}IPC_IPV4_OBJ, *IPC_IPV4_HANDLE;

//////////////////////////////////////////////////////////////////////////////
//IPV6网络参数
//////////////////////////////////////////////////////////////////////////////
typedef struct _tagIPC_IPV6
{
    HB_U16  ip[8];              //ip地址
    HB_U8   gateway[16];        //默认网关
    HB_U8   dns[16];            //首选DNS
    HB_U8   dns_bak[16];        //备选DNS
    HB_U32  subnet_prefix;      //子网前缀长度  
}IPC_IPV6_OBJ, *IPC_IPV6_HANDLE;

//////////////////////////////////////////////////////////////////////////////
//有线网络管理
//////////////////////////////////////////////////////////////////////////////
typedef struct _tagIPC_IP_PARAM
{
    HB_S32          length;         //结构体长度
    HB_U8           net_interface;  //网络接口 1-10MBase-T 2-10MBase-T全双工 3-100MBase-TX 4-100M全双工 5-10M/100M自适应
    HB_U8           net_model;      //网络模式 0-静态 1-DHCP
    HB_U8           mac_addr[6];    //mac地址
    IPC_IPV4_OBJ    ipv4;           //ipv4
    IPC_IPV6_OBJ    ipv6;           //ipv6
    HB_S32          listen_port;    //监听端口
    HB_S32          http_port;      //http端口
    HB_S32          multicast;      // 1-multibroadcast
}IPC_IP_PARAM_OBJ, *IPC_IP_PARAM_HANDLE;

//////////////////////////////////////////////////////////////////////////////
//PPPOE
//////////////////////////////////////////////////////////////////////////////
typedef struct _tagIPC_PPPOE
{
    HB_S32   length;         //结构体长度
    HB_S32   auto_con;       //PPPOE自动重连：0-不自动重连1-自动重连
    HB_S32   state;          //连接状态  0-断开 1-连接 
    HB_CHAR  username[32];   //用户名
    HB_CHAR  pwd[32];        //密码
    HB_S32   pppoesave;      //PPPOE信息保存: 0-不保存 1-保存
    HB_U8    ipv4[4];        //ipv4 ip地址
    HB_U8    gateway_v4[4];  //ipv4 网关 
    HB_U16   ipv6[8];        //ipv6 ip地址
    HB_U8    gateway_v6[16]; //ipv6 网关
}IPC_PPPOE_OBJ, *IPC_PPPOE_HANDLE;

//////////////////////////////////////////////////////////////////////////////
//E_MAIL
//////////////////////////////////////////////////////////////////////////////
typedef struct _tagIPC_E_MAIL
{
    HB_S32     length;                 //结构体长度 
    HB_S32     enable;                 //使能  -1-不支持 0-off, 1-on
    HB_S32     md5_auth;               //支持MD5加密 -1-不支持 0-off, 1-on 
    HB_S32     use_ipv6;               //使用IPV6发送邮件 -1-不支持 0-off, 1-on 
    HB_S32     use_ssl;                //启用SSL
    HB_S32     use_starttls;           //启用STARTTLS
    HB_S16     accessory_enable;       //附件使能
    HB_U16     port;                   //端口号
    HB_CHAR    smtp_server[128];       //服务器地址
    HB_CHAR    username[32];           //用户名
    HB_CHAR    pwd[32];                //密码
    HB_CHAR    send_person[128];       //发件人地址
    HB_CHAR    recv_person[256];       //收件人地址
    HB_S32     send_period;            //上传周期,单位(分钟)[1, 10]
    HB_S32     snap_enable;            //是否抓拍上传
    HB_CHAR    mail_topic[32];         //主题
}IPC_E_MAIL_OBJ, *IPC_E_MAIL_HANDLE; 

//////////////////////////////////////////////////////////////////////////////
//FTP
//////////////////////////////////////////////////////////////////////////////
typedef struct _tagIPC_FTP
{
    HB_S32    length;                 //结构体长度 
    HB_S16    enable;                 //使能 -1-不支持 0-off, 1-on
    HB_U16    port;                   //端口号
    HB_S8     server_address[128];    //服务器地址
    HB_S8     username[32];           //用户名
    HB_S8     pwd[32];                //密码
    HB_S8     save_path[128];         //远程存储路径
}IPC_FTP_OBJ, *IPC_FTP_HANDLE;

//////////////////////////////////////////////////////////////////////////////
//NAS
//////////////////////////////////////////////////////////////////////////////
typedef struct _tagIPC_NAS
{
    HB_S32   length;            //结构体长度
    HB_S16   enable;            //NAS使能 -1-不支持 0-off, 1-on
    HB_U16   port;              //端口号
    HB_S32   style;             //方式    
    HB_U32   server_ip;         //服务器IP
    HB_CHAR  username[32];      //用户名
    HB_CHAR  pwd[32];           //密码
    HB_CHAR  remote_path[128];  //远程存储路径
    HB_S32   reserve[3];        //保留
}IPC_NAS_OBJ, *IPC_NAS_HANDLE;

//////////////////////////////////////////////////////////////////////////////
//自动注册
//////////////////////////////////////////////////////////////////////////////
typedef struct _tagIPC_AUTO_REGIST
{
    HB_S32 length;                //结构体长度
    HB_S16 enable;                //自动注册使能 -1-不支持 0-off, 1-on
    HB_U16 port;                  //端口号
    HB_S8  server_address[64];    //服务器地址
    HB_S32 sub_device_id;         //子设备IDss
}IPC_AUTO_REGIST_OBJ,*IPC_AUTO_REGIST_HANDLE;

//////////////////////////////////////////////////////////////////////////////
//端口映射
//////////////////////////////////////////////////////////////////////////////
typedef struct _tagIPC_PORT_MAP
{
    HB_U8     port_map_enable;      //启用端口映射 0-off, 1-on
    HB_U8     port_status;          //端口映射状态 0-未生效 1-已生效
    HB_U16    proto;                //协议即TCP或者UDP 0-UDP 1-TCP
    HB_S8     servicename[32];      //服务名称
    HB_U16    iport;                //映射端口
    HB_U16    eport;                //路由器端口               
    HB_S32    reserve[3];           //保留
}IPC_PORT_MAP_OBJ, *IPC_PORT_MAP_HANDLE;

//////////////////////////////////////////////////////////////////////////////
//网关路由器地址
//////////////////////////////////////////////////////////////////////////////
typedef struct _tagIPC_UPNP_DEVICE_OBJ
{
    HB_S8  wanip[20];              //网关路由器WAN口地址
    HB_S8  lanip[4][20];           //网关路由器LAN口地址列表
    HB_U8  lanip_index;            //网关路由器LAN口地址索引
    HB_S8  reserve[7];             //保留
}IPC_UPNP_DEVICE_OBJ, *IPC_UPNP_DEVICE_HANDLE;


//////////////////////////////////////////////////////////////////////////////
//uPNP
//////////////////////////////////////////////////////////////////////////////
typedef struct _tagIPC_UPNP
{
    HB_S32              length;               //结构体长度
    HB_S8               enable;               //启用uPNP使能  0-off, 1-on
    HB_S8               operate;              //操作方式  0-添加, 1-删除, 2-编辑
    HB_U8               curr_index;           //编辑时的索引下标
    HB_U8               count;                //端口映射列表个数
    IPC_UPNP_DEVICE_OBJ routerip;             //网关路由器地址 (只读)
    IPC_PORT_MAP_OBJ    port_map[8];          //端口映射信息     
    HB_S32              reserve[3];           //保留
}IPC_UPNP_OBJ, *IPC_UPNP_HANDLE;


//////////////////////////////////////////////////////////////////////////////
//无线网络管理
//////////////////////////////////////////////////////////////////////////////
typedef struct _tagIPC_WIRELESS_NETWORK
{
    HB_S32    length;            //结构体长度
    HB_S8     enable;            //无线网络使能 -1-不支持 0-off, 1-on
    HB_U8     ssid[50];          //ssid号         
    HB_U8     channel;           //频段
    IPC_IPV4_OBJ  ipv4;              //ipv4 
    IPC_IPV6_OBJ  ipv6;              //ipv6   尚未使用
    HB_U8     mac_addr[6];       //mac地址 
    HB_U8     model;             //模式     0-11Mbps 1-54Mbps
    HB_S8     key_type;          //加密方式 0-WEP 1-WPA2 2-WPA2-TKIP 3-WPA2-AES
    HB_S32    key_chose;         //密钥选择
    HB_CHAR   key_data[4][64];   //密钥内容
    HB_CHAR   psw[64];           //密码 
}IPC_WIRELESS_NETWORK_OBJ, *IPC_WIRELESS_NETWORK_HANDLE;

//////////////////////////////////////////////////////////////////////////////
// onvif/PSIA协议参数
//////////////////////////////////////////////////////////////////////////////
typedef struct _tagIPC_PLATFORM_INFO
{
    HB_S32  enable;                    //使能 -1-不支持 0-off, 1-on
    HB_U16  protocol_port;             //协议端口，现在汉邦的IPC默认为8888
    HB_U16  video_port;                //音视频端口，现在汉邦的IPC默认为554
}IPC_PLATFORM_INFO_OBJ, *IPC_PLATFORM_INFO_HANDLE;

//////////////////////////////////////////////////////////////////////////////
// GB28181设备配置部分结构体
//////////////////////////////////////////////////////////////////////////////
typedef struct _tagIPC_GB28181_DEVICE_INFO
{
    HB_CHAR    device_id[32];             //设备ID
    HB_S32     device_port;               //设备命令端口
    HB_CHAR    device_domain_name[64];    //设备域名
    HB_CHAR    device_pwd[32];            //设备注册密码    默认值为12345678
    HB_S32     device_expires;            //注册过期时间 单位为秒   默认值为3600
    HB_S32     device_alarmin_num;        //设备报警输入量，范围1-8 
    HB_CHAR    device_alarmin_id[8][32];     //设备报警ID
}IPC_GB28181_DEVICE_INFO_OBJ, *IPC_GB28181_DEVICE_INFO_HANDLE;

//////////////////////////////////////////////////////////////////////////////
// GB28181的sip服务器结构体定义
//////////////////////////////////////////////////////////////////////////////
typedef struct _tagIPC_GB28181_SIP_SERVER_INFO
{
    HB_CHAR    sip_svr_ip[32];            //sip服务器IP
    HB_CHAR    sip_svr_id[32];            //sip服务器ID
    HB_S32     sip_svr_port;              //sip服务器端口号   默认值为5060
    HB_CHAR    sip_svr_domain_name[64];   //sip服务器域名
}IPC_GB28181_SIP_SERVER_INFO_OBJ, *IPC_GB28181_SIP_SERVER_INFO_HANDLE;

//////////////////////////////////////////////////////////////////////////////
// GB28181的流媒体服务器结构体定义
//////////////////////////////////////////////////////////////////////////////
typedef struct _tagIPC_GB28181_SMS_SERVER_INFO
{
    HB_CHAR   sms_svr_ip[32];            //sms流媒体服务器接收IP
    HB_S32    sms_svr_port;              //sms流媒体服务器接收端口  默认值为6000
}IPC_GB28181_SMS_SERVER_INFO_OBJ, *IPC_GB28181_SMS_SERVER_INFO_HANDLE;

//////////////////////////////////////////////////////////////////////////////
// GB28181协议参数
//////////////////////////////////////////////////////////////////////////////
typedef struct _tagIPC_GB28181_INFO
{
    HB_S32                            enable;           //使能 -1-不支持 0-off, 1-on
    IPC_GB28181_DEVICE_INFO_OBJ       dev_info;         //GB28181设备配置信息
    IPC_GB28181_SMS_SERVER_INFO_OBJ   sms_server_info;  //GB28181流媒体服务器信息
    IPC_GB28181_SIP_SERVER_INFO_OBJ   sip_server_info;  //GB28181sip服务器信息
}IPC_GB28181_INFO_OBJ, *IPC_GB28181_INFO_HANDLE;

//////////////////////////////////////////////////////////////////////////////
// 接入平台信息
//////////////////////////////////////////////////////////////////////////////
typedef struct _tagIPC_PLATFORM
{
    HB_S32    length;                      //结构体长度 
    HB_S32    protocol_type;               //平台接入协议的选择 0-GB28181 1-onvif 2-PSIA
    union
    {
        IPC_PLATFORM_INFO_OBJ   onvif;     //onvif协议参数
        IPC_PLATFORM_INFO_OBJ   psia;      //PSIA协议参数
        IPC_GB28181_INFO_OBJ    gb28181;   //GB28181协议参数
    }platform_cfg;
}IPC_PLATFORM_OBJ, *IPC_PLATFORM_HANDLE;

//////////////////////////////////////////////////////////////////////////////
//定时录像
//////////////////////////////////////////////////////////////////////////////
typedef struct _tagIPC_TIME_RECORD
{
    HB_S32                 length;              //结构体长度 
    HB_S32                 channel_num;         //通道号   
    IPC_TIME_SCHEDULE_OBJ  schedule;            //时间计划 
    HB_S32                 reserve;             //保留
}IPC_TIME_RECORD_OBJ,*IPC_TIME_RECORD_HANDLE;

//////////////////////////////////////////////////////////////////////////////
//存储方式
//////////////////////////////////////////////////////////////////////////////
typedef struct
{
    HB_S32    length;               //结构体长度 
    HB_S32    channel_num;          //通道号
    HB_S32    cover_delete;         //存储设备满时，是否自动删除旧文件  0-满删除 1-满覆盖
    HB_S8     manual_rcd[8];        //手动录像存储方式 -1-不支持 0-未选中 1-选中，数组下标：0-SD/TF 1-FTP 2-NAS
    HB_S8     time_rcd[8];          //定时录像存储方式 -1-不支持 0-未选中 1-选中，数组下标：0-SD/TF 1-FTP 2-NAS
    HB_S8     linkage_rcd[8];       //联动录像存储方式 -1-不支持 0-未选中 1-选中，数组下标：0-SD/TF 1-FTP 2-NAS
}IPC_RECORD_MODE_OBJ,*IPC_RECORD_MODE_HANDLE;

//////////////////////////////////////////////////////////////////////////////
//存储设备状态
//////////////////////////////////////////////////////////////////////////////
typedef struct
{
    HB_S8    dev_name[16];           //设备名称
    HB_S8    status[32];             //存储卡状态
    HB_FLOAT diskcapacity;           //存储卡储容量 单位GB
    HB_FLOAT disk_free;              //存储卡储容量剩余 单位GB
    HB_FLOAT prerec_time;            //存储卡预计可录时长 单位小时
}IPC_DISK_PARAM_OBJ,*IPC_DISK_PARAM_HANDLE;

typedef struct
{   
    HB_S32             length;          //结构体长度 
    HB_S32             disknum;         //磁盘数量 
    IPC_DISK_PARAM_OBJ diskinfo[12];    //磁盘信息  
}IPC_DISK_CFG_OBJ,*IPC_DISK_CFG_HANDLE;

//////////////////////////////////////////////////////////////////////////////
//联动EMAL设置
//////////////////////////////////////////////////////////////////////////////
typedef struct _tagIPC_LINKAGE_MAIL
{
    HB_S32  e_mail;        //发送邮件 -1-不支持 0-off, 1-on
    HB_S32  delay_time;    //报警时长 5-300秒
    HB_S32  reserve;       //保留
}IPC_LINKAGE_MAIL_OBJ, *IPC_LINKAGE_MAIL_HANDLE;

//////////////////////////////////////////////////////////////////////////////
//联动报警输出设置
//////////////////////////////////////////////////////////////////////////////
typedef struct _tagIPC_LINKAGE_ALARM
{
    HB_S32 alarm_out;      //报警输出 -1-不支持 0-off, 1-on
    HB_S32 alarm;          //联动报警量 如报警量1，报警量2
    HB_S32 delay_time;     //报警延迟时间  10-300秒 暂不支持
    HB_S32 continue_time;  //报警延时时间  只读
}IPC_LINKAGE_ALARM_OBJ, *IPC_LINKAGE_ALARM_HANDLE;

//////////////////////////////////////////////////////////////////////////////
//联动录像设置
//////////////////////////////////////////////////////////////////////////////
typedef struct _tagIPC_LINKAGE_RECORD
{
    HB_S32  record;       //录像     -1-不支持 0-off, 1-on
    HB_S32  delay_time;   //录像延迟时间 10-300秒 暂不支持
    HB_S32  record_time;  //录像时间  5-300秒
    HB_S32  reserve[2];   //保留
}IPC_LINKAGE_RECORD_OBJ, *IPC_LINKAGE_RECORD_HANDLE;

//////////////////////////////////////////////////////////////////////////////
//联动云台
//////////////////////////////////////////////////////////////////////////////
typedef struct _tagIPC_LINKAGE_PTZ
{
    HB_S32  ptz;        //云台     -1-不支持 0-off, 1-on
    HB_S32  ptz_item;   //-1-不支持 0-预支点 1-点间巡航
    HB_S32  ptz_addr;   //预支点 1-16    -1-不支持 当ptz_item为0时 可用此项
    HB_S32  reserve;    //保留
}IPC_LINKAGE_PTZ_OBJ, *IPC_LINKAGE_PTZ_HANDLE;

//////////////////////////////////////////////////////////////////////////////
//联动图像抓拍
//////////////////////////////////////////////////////////////////////////////
typedef struct _tagIPC_LINKAGE_SNAP
{
    HB_S32   snapshot;      //图片抓拍 -1-不支持 0-off, 1-on
    HB_S16   delay_time;    //发送邮件延迟时间 10-300秒  暂不支持
    HB_S16   pic_num;       //抓拍张数 1-10
    HB_S32   reserve;       //保留
}IPC_LINKAGE_SNAP_OBJ, *IPC_LINKAGE_SNAP_HANDLE;

//////////////////////////////////////////////////////////////////////////////
//联动管理
//////////////////////////////////////////////////////////////////////////////
typedef struct _tagIPC_LINKAGE
{ 
//    HB_S32                 ftp;        //ftp上传  -1-不支持 0-off, 1-on
    IPC_LINKAGE_MAIL_OBJ   mail;       //联动发送邮件
    IPC_LINKAGE_SNAP_OBJ   snapshot;   //联动图片抓拍
    IPC_LINKAGE_ALARM_OBJ  alarm;      //联动报警
    IPC_LINKAGE_PTZ_OBJ    ptz;        //联动云台
    IPC_LINKAGE_RECORD_OBJ record;     //联动录像
}IPC_LINKAGE_OBJ, *IPC_LINKAGE_HANDLE;

//////////////////////////////////////////////////////////////////////////////
//移动侦测
//////////////////////////////////////////////////////////////////////////////
typedef struct _tagIPC_MOTION
{
    HB_S32                 length;             //结构体长度
    HB_S32                 channel_num;        //通道号
    HB_S32                 motion_enable;      //移动侦测使能 -1-不支持 0-off, 1-on
    HB_U32                 motion_block[18];   //移动侦测红块  18*22
    HB_S32                 sensitivity;        //灵敏度 1-5 low~height
    HB_S32                 reserved;           //去抖 1-5   low~height
    IPC_TIME_SCHEDULE_OBJ  monitor_time;       //布防时间
    IPC_LINKAGE_OBJ        linkage_out;        //联动输出
}IPC_MOTION_OBJ, *IPC_MOTION_HANDLE;

//////////////////////////////////////////////////////////////////////////////
//报警输入
//////////////////////////////////////////////////////////////////////////////
typedef struct _tagIPC_ALARMIN
{
    HB_S32                 length;          //结构体长度
    IPC_TIME_SCHEDULE_OBJ  monitor_time;    //布防时间 
    IPC_LINKAGE_OBJ        linkage_out;     //联动输出
    HB_U8                  alarm_in_num;    //报警输入总个数 只读
    HB_U8                  alarm_in_no;     //报警输入通道号， 0-报警输入1 1-报警输入2 2-报警输入3 3-报警输入4
    HB_U8                  alarm_in_type;   // 0：常开，1：常闭 
    HB_U8                  reserve[5];      //保留
}IPC_ALARMIN_OBJ, *IPC_ALARMIN_HANDLE;


//////////////////////////////////////////////////////////////////////////////
//报警输出管理
//////////////////////////////////////////////////////////////////////////////
typedef struct _tagIPC_ALARMOUT
{
    HB_S32                 length;         //结构体长度
    IPC_TIME_SCHEDULE_OBJ  time;           //报警输出布防时间 
    HB_U8                  alarm_out_num;  //报警输出总个数 只读
    HB_U8                  alarm_out_no;   //报警输出通道号， 0-报警输出1 1-报警输出2 2-报警输出3 3-报警输出4
    HB_U16                 alarm_time;     //报警输出时间 10-300秒  
    HB_U8                  reserve[4];     //保留
}IPC_ALARMOUT_OBJ, *IPC_ALARMOUT_HANDLE;

//////////////////////////////////////////////////////////////////////////////
//网络故障处理
//////////////////////////////////////////////////////////////////////////////
typedef struct _tagIPC_NET_BUG
{
    HB_S32  length;          //结构体长度
    HB_S32  enable;          //使能 -1-不支持 0-off, 1-on 
    HB_S16  record_enable;   //录像使能 -1-不支持 0-off, 1-on
    HB_S16  alarm_enable;    //报警使能 -1-不支持 0-off, 1-on
    HB_S16  record_time;     //录像时间  10-300秒
    HB_S16  alarmout_time;   //报警输出时间  10-300秒 
}IPC_NET_BUG_OBJ, *IPC_NET_BUG_HANDLE;

//////////////////////////////////////////////////////////////////////////////
//存储设备故障处理
//////////////////////////////////////////////////////////////////////////////
typedef struct _tagIPC_SAVE_BUG_PROCESS
{
    HB_S16  enable;          //使能 -1-不支持 0-off, 1-on
    HB_S16  e_mail;          //发送邮件  -1-不支持 0-off, 1-on  
    HB_S16  alarmout_enable; //报警输出  -1-不支持 0-off, 1-on
    HB_S16  alarmout_delay;  //报警输出延迟时间    10-300秒
}IPC_SAVE_BUG_PROCESS_OBJ, *IPC_SAVE_BUG_PROCESS_HANDLE;

//////////////////////////////////////////////////////////////////////////////
//存储介质状态
//////////////////////////////////////////////////////////////////////////////
typedef struct _tagIPC_STORE_BUG
{
    HB_S32                    length;      //结构体长度
    IPC_SAVE_BUG_PROCESS_OBJ  no_sd;       //无SD卡
    IPC_SAVE_BUG_PROCESS_OBJ  no_free_sd;  //SD卡空间不足
    IPC_SAVE_BUG_PROCESS_OBJ  error_sd;    //SD卡出错
}IPC_STORE_BUG_OBJ, *IPC_STORE_BUG_HANDLE;

//////////////////////////////////////////////////////////////////////////////
//设备信息
//////////////////////////////////////////////////////////////////////////////
typedef struct _tagIPC_DEVICE_INFO
{
    HB_S32   length;             //结构体长度
    HB_CHAR  dev_name[32];       //产品名称
    HB_CHAR  dev_type[32];       //产品型号
    HB_CHAR  soft_version[32];   //软件版本
    HB_U8    dev_no[4];          //设备编号
    HB_CHAR  reserve[2];         //保留 
}IPC_DEVICE_INFO_OBJ,*IPC_DEVICE_INFO_HANDLE;

//////////////////////////////////////////////////////////////////////////////
//自动维护（重启）
//////////////////////////////////////////////////////////////////////////////
typedef struct _tagIPC_AUTO_MAINTAINING
{
    HB_S32            length;              //结构体长度
    HB_S16            auto_reboot;         //自动重启使能 -1-不支持 0-off, 1-on
    HB_S16            style;               //自动维护方式 0-天 1-星期
    IPC_SYS_TIME_OBJ  reboot_time;         //重启时间
}IPC_AUTO_MAINTAINING_OBJ, *IPC_AUTO_MAINTAINING_HANDLE;

//////////////////////////////////////////////////////////////////////////////
//功能能力集列表
//////////////////////////////////////////////////////////////////////////////
typedef struct _tagIPC_AV_ABILITY
{
    HB_U8     image_param;    	//图像参数 0-不支持, 1-支持
    HB_U8     video_param;    	//视频参数 0-不支持, 1-支持
    HB_U8     video_encode;   	//视频编码 0-不支持, 1-支持
    HB_U8     picture_snap;   	//图像抓拍 0-不支持, 1-支持
    HB_U8     osd_overlay;    	//字符叠加 0-不支持, 1-支持 
    HB_U8     mask;           	//视频遮挡 0-不支持, 1-支持
    HB_U8     audio_in_param; 	//音频输入 0-不支持, 1-支持
    HB_U8     audio_out_param;	//音频输出 0-不支持, 1-支持
    HB_U8     advance_param;    //高级设置 0-不支持, 非0-支持
    HB_U8     reserve[3];       //保留
}IPC_AV_ABILITY_OBJ, *IPC_AV_ABILITY_HANDLE;

typedef struct _tagIPC_NET_ABILITY
{
    HB_U8    ip_param;      //有线网络 0-不支持, 1-支持
    HB_U8    pppoe;         //PPPOE 0-不支持, 1-支持
    HB_U8    e_mail;        //E_mail 0-不支持, 1-支持
    HB_U8    ftp;           //FTP 0-不支持, 1-支持
    HB_U8    platform;      //平台服务器 0-不支持, 1-支持
    HB_U8    nas;           //NAS 0-不支持, 1-支持
    HB_U8    auto_regist;   //自动注册 0-不支持, 1-支持
    HB_U8    upnp;          //UPNP 0-不支持, 1-支持
    HB_U8    wireless;      //无线网络 0-不支持, 1-支持
    HB_U8    ddns;          //DDNS 0-不支持, 1-支持
    HB_U8    reserve[2];    //保留
}IPC_NET_ABILITY_OBJ, *IPC_NET_ABILITY_HANDLE;

typedef struct _tagIPC_ALARM_ABILITY
{
    HB_U8    motion;      //移动侦测 0-不支持, 1-支持
    HB_U8    alarmin;     //报警输入 0-不支持, 1-支持
    HB_U8    alarmout;    //报警输出 0-不支持, 1-支持
    HB_U8    net_bug;     //网络故障 0-不支持, 1-支持
    HB_U8    store_bug;   //存储故障 0-不支持, 1-支持
    HB_U8    reserve[3];  //保留
}IPC_ALARM_ABILITY_OBJ, *IPC_ALARM_ABILITY_HANDLE;

typedef struct _tagIPC_ABILITY
{
    HB_S32                  length;       //结构体长度
    IPC_AV_ABILITY_OBJ      av;           //音视频
    IPC_NET_ABILITY_OBJ     net;          //网络
    IPC_ALARM_ABILITY_OBJ   alarm;        //报警
    HB_U8                   store;        //存储设置 0-不支持, 1-支持
    HB_U8                   serial;       //串口设置 0-不支持, 1-支持
    HB_U8                   manage;       //系统管理 0-不支持, 1-支持
    HB_U8                   reserve;      //保留
}IPC_ABILITY_OBJ, *IPC_ABILITY_HANDLE;

//////////////////////////////////////////////////////////////////////////////
//串口信息
//////////////////////////////////////////////////////////////////////////////
typedef struct _tagIPC_SERIAL_INFO
{
    HB_S32   length;             //结构体长度 
    HB_S32   inter_type_index;   //接口类型  -1-不支持 如为不支持，以下参数均无效
    HB_S8    inter_type[8][10];  //接口类型表
    HB_S32   baud_rate;          //波特率 2400,4800,9600,19200,38400 自定义,取值范围[300，115200]。
    HB_U8    data_bit;           // 数据位5 6 7 8
    HB_U8    stop_bit;           // 停止位1 2
    HB_U8    parity;             //校验位 0-无校验 1-奇校验 2-偶校验
    HB_U8    flow_control;       // 流控 0-无 1-软件 2-硬件
    HB_S32   decoder_type;       // 云台协议值，通过NET_SDVR_PTZTYPE_GET 获取该列表
    HB_U32   decoder_address;    // 解码器地址:[0 – 255]
    HB_S32   reserve;            // 保留
}IPC_SERIAL_INFO_OBJ,*IPC_SERIAL_INFO_HANDLE;

//////////////////////////////////////////////////////////////////////////////
//视频命令结构体联合体
//////////////////////////////////////////////////////////////////////////////
typedef union _tagVIDEO_CFG
{
    IPC_IMAGE_PARAM_OBJ           image_param;    //IPC图像参数
    IPC_VIDEO_PARAM_OBJ           video_param;    //IPC视频参数
    IPC_VIDEO_ENCODE_OBJ          video_encode;   //IPC视频编码参数
    IPC_PICTURE_SNAP_OBJ          picture_snap;   //IPC图像抓拍参数
    IPC_OSD_OVERLAY_OBJ           osd_overlay;    //IPC字符叠加参数
    IPC_MASK_OBJ                  mask;           //IPC遮挡参数
    IPC_ADVANCE_PARAM_OBJ         advance_param;  //IPC高级参数
    IPC_AUDIO_IN_PARAM_OBJ        audio_in_param; //IPC音频输入参数
    IPC_AUDIO_OUT_PARAM_OBJ       audio_out_param;//IPC音频输出参数
}VIDEO_CFG_U;

//////////////////////////////////////////////////////////////////////////////
//网络命令结构体联合体
//////////////////////////////////////////////////////////////////////////////
typedef union _tagNET_CFG
{
    IPC_IP_PARAM_OBJ           ip_param;       //IPC 有线网络参数
    IPC_PPPOE_OBJ              pppoe;          //IPC PPPOE参数
    IPC_E_MAIL_OBJ             e_mail;         //IPC E_MAIL参数
    IPC_FTP_OBJ                ftp;            //IPC FTP参数
    IPC_PLATFORM_OBJ           platform;       //IPC 平台参数
    IPC_NAS_OBJ                nas;            //IPC NAS
    IPC_AUTO_REGIST_OBJ        auto_regist;    //IPC 自动注册
    IPC_UPNP_OBJ               upnp;           //IPC UPnP
    IPC_WIRELESS_NETWORK_OBJ   wireless;       //IPC 无线网络参数
}NET_CFG_U;

//////////////////////////////////////////////////////////////////////////////
//存储命令结构体联合体
//////////////////////////////////////////////////////////////////////////////
typedef union _tagSTORE_CFG
{
//    IPC_RECORD_PARAM_OBJ  record_param;
    IPC_TIME_RECORD_OBJ   time_record;      //IPC定时录像参数
    IPC_RECORD_MODE_OBJ   record_mode;      //IPC录像存储方式
    IPC_DISK_CFG_OBJ      disk_cfg;         //IPC存储设备状态
}STORE_CFG_U;

//////////////////////////////////////////////////////////////////////////////
//报警命令结构体联合体
//////////////////////////////////////////////////////////////////////////////
typedef union _tagALARM_CFG
{
    IPC_MOTION_OBJ     motion;     //IPC移动侦测参数
    IPC_ALARMIN_OBJ    alarmin;    //IPC报警输入参数
    IPC_ALARMOUT_OBJ   alarmout;   //IPC报警输出参数
    IPC_NET_BUG_OBJ    net_bug;    //IPC网络故障报警参数
    IPC_STORE_BUG_OBJ  store_bug;  //IPC存储故障报警参数
}ALARM_CFG_U;

///////////////////////////////////////////////////////////////////////////////
//IPC页面球机加载能力
///////////////////////////////////////////////////////////////////////////////
typedef struct _tagIPC_DOME_ABLITILY
{
    HB_U8     dome_enable;    	//球机使能 0-不支持, 1-支持
    HB_U8     advance_param;    //高级参数 0-不支持, 1-支持
    HB_U8     limit;   	        //限位     0-不支持, 1-支持
    HB_U8     zero_angle;   	//零方位角 0-不支持, 1-支持
    HB_U8     park;          	//守望     0-不支持, 1-支持 
    HB_U8     time_task;        //定时任务 0-不支持, 1-支持
    HB_U8     clear; 	        //清除使能 0-不支持, 1-支持
    HB_U8     reserve[32];
}IPC_DOME_ABILITY_OBJ, *IPC_DOME_ABILITY_HANDLE;

//////////////////////////////////////////////////////////////////////////////
//管理命令结构体联合体
//////////////////////////////////////////////////////////////////////////////
typedef union _tagMANAGE_CFG
{
    IPC_DEVICE_INFO_OBJ        dev_info;          //设备信息
    IPC_AUTO_MAINTAINING_OBJ   auto_maintaining;  //IPC自动维护参数
    IPC_ABILITY_OBJ            ability;           //加载能力集
    IPC_DOME_ABILITY_OBJ       dome_info;         //球机加载
}MANAGE_CFG_U;

//////////////////////////////////////////////////////////////////////////////
//串口类命令传送的数据结构体
//////////////////////////////////////////////////////////////////////////////
typedef union _tagSERIAL_CFG
{
    IPC_SERIAL_INFO_OBJ       serial_info;          //串口信息
}SERIAL_CFG_U;

//////////////////////////////////////////////////////////////////////////////
//获取请求结构体 设置应答结构体
//////////////////////////////////////////////////////////////////////////////
typedef struct _tagIPC_CMD
{
    HB_S32   cmd_pri_type;     //命令主类型，即命令所属类型 
    HB_S32   cmd_sec_type;     //命令子类型，即具体指哪条命令 
    HB_S32   channel_num;      //通道号 -1为无通道号，[0, n－1] n:通道数
}IPC_CMD_OBJ, *IPC_CMD_HANDLE;

//////////////////////////////////////////////////////////////////////////////
//获取应答结构体 设置请求结构体
//////////////////////////////////////////////////////////////////////////////
typedef struct _tagHB_IPC_CFG
{
     HB_S32  cmd_pri_type;          //命令主类型，即命令所属类型
     HB_S32  cmd_sec_type;          //命令子类型，即具体指那条命令
     HB_S32  size;                  //union ipc_cfg中对应的数据结构体大小
     union                          //union ipc_cfg为IPC命令传送数据的结构体
     {
          VIDEO_CFG_U  video_cfg;   //视频类命令传送的数据结构体
          NET_CFG_U    net_cfg;     //网络类命令传送的数据结构体
          STORE_CFG_U  store_cfg;   //存储类命令传送的数据结构体
          ALARM_CFG_U  alarm_cfg;   //报警类命令传送的数据结构体
          MANAGE_CFG_U manage_cfg;  //管理类命令传送的数据结构体
          SERIAL_CFG_U serial_cfg;  //串口类命令传送的数据结构体
    }ipc_cfg;
    HB_S32 reserve[2];              //保留
}HB_IPC_CFG_OBJ, *HB_IPC_CFG_HANDLE;

#pragma pack()
#endif
