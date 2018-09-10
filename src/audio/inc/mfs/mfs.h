/************* 文件命名方式 *******************************************
  MFS全称: Media File System
  主索引文件：mfsindex.idx(最大128M)
  辅助索引文件：mfsalidx.idx(固定8M)
  日志文件：mfslog.log(固定32M)
  录像数据文件：mfsxxxxx.dat, xxxxx=(00001~16383)(固定128M)
*************************************************************************/

/***************文件存储结构**********************
    1、主索引文件
    _______________________________________________
    |_______文件头信息区（512字节）______|
    |__当前录像状态信息区（512字节）__|
    |_____文件索引信息区（256K字节）____|
    |_____录像索引信息区（8KxN字节）____|

    2、辅索引文件
    _______________________________________________
    |_______文件头信息区（512字节）______|
    |__当前录像状态信息区（512字节）__|
    |_____文件索引信息区（256K字节）____|
  
    3、数据文件
    _______________________________________________
    |______录像索引信息区（8K字节）_____|
    |_____I 帧索引信息区（24K字节）_______|
    |__________数据区（128M-32K字节）_______|

    4、日志文件
    ________________________________________________
    |___日志日期索引信息区（16 K字节）_|
    |_____日志数据区（32M -16K字节）_______|
****************************************************/

#ifndef MFS_H
#define MFS_H
#include <pthread.h>
//#include "common.h"
#include "mfs/mfscommon.h"
#include <sys/ioctl.h>



//支持设备数
#define MFS_DEV_MAX               4

#define MFS_BAD_HANDLE            -1//0xff//无效句柄
#define MFS_PREREC_SIZE           MFS16M//预录空间(8~128M)

//录像属性
#define MFS_REC_TYPE_MANUAL   1 
#define MFS_REC_TYPE_SCHEDULE 2 
#define MFS_REC_TYPE_MOTION   4 
#define MFS_REC_TYPE_ALARM    8 
#define MFS_REC_TYPE_ALL      0xff 
#define MFS_REC_TYPE_UNKNOWN  0

//录像帧属性
#define MFS_FRAME_TYPE_I        1
#define MFS_FRAME_TYPE_P        2
#define MFS_FRAME_TYPE_B        4
#define MFS_FRAME_TYPE_A        8
#define MFS_FRAME_TYPE_ALL      0x0f
#define MFS_FRAME_TYPE_UNKNOWN  0

//放像速率
typedef enum {
 MFS_READ_NORMAL     =    0,
 MFS_READ_FORWARD    =    0x10,//关键帧进(不作为放像使用)
 MFS_READ_FORWARD_1X =    0x11,//关键帧读出
 MFS_READ_FORWARD_2X =    0x12,// 2倍间隔关键帧读出
 MFS_READ_FORWARD_3X =    0x13,// 3倍
 MFS_READ_FORWARD_4X =    0x14,// 4倍
 MFS_READ_FORWARD_5X =    0x15,// 5倍
  
 MFS_READ_BACKWARD   =    0x20,//关键帧退(不作为放像使用)
 MFS_READ_BACKWARD_1X=    0x21,//关键帧退
 MFS_READ_BACKWARD_2X=    0x22,// 2倍间隔关键帧退
 MFS_READ_BACKWARD_3X=    0x23,// 3倍
 MFS_READ_BACKWARD_4X=    0x24,// 4倍
 MFS_READ_BACKWARD_5X=    0x25,// 5倍
  
 MFS_READ_SEEK       =    0x40//读seek
}MFS_READ_SPEED;


#define MFS_REC_CH_MAX          32//录像通道数
#define MFS_REC_CACHE_SIZE      MFS128K//录像缓冲区

#define MFS_DEV_SLEEP_TIME      300// seconds//设备休眠时间

#define MFS_BACKUP_MAX          1//同时备份操作数


//usb检索时的全通道标示
#define MFS_USB_GET_ALL_CH        ALL_CHANNEL
#define MFS_REC_GET_ALL_CH        ALL_CHANNEL

/*****************************MFS 回调消息定义*****************************
  类型为unsigned int，第0~3字节依次定义如下：
  |_INFONO_|_INFOTYPE_|_COMPID_|_0x00_|
  COMPID = COMP_MFS ,模块ID 定义在common.h 中
***********************************************************************************************/

#define MFS_MSG_BASE                (COMP_MFS<<16)//文件系统信息头(高8位留给表示)

/******************************设备类回调信息************************/
#define MFS_MSG_DEV                 (MFS_MSG_BASE+0x0100)//设备的异常信息
#define MFS_MSG_DEV_WRITE_FAILED    (MFS_MSG_DEV+0x01)//当前设备写异常，返回设备号及LBA号等信息
                                                      //mfsCallback(MFS_MSG_DEV_WRITE_FAILED, dev_num, lba);  
#define MFS_MSG_DEV_READ_FAILED     (MFS_MSG_DEV+0x02)//当前设备读异常，返回设备号及LBA号等信息
                                                      //mfsCallback(MFS_MSG_DEV_READ_FAILED, dev_num, lba);  
#define MFS_MSG_DEV_DISK_FULL       (MFS_MSG_DEV+0x03)//磁盘已经满
#define MFS_MSG_DEV_DISK_NONE       (MFS_MSG_DEV+0x04)//无磁盘
#define MFS_MSG_DEV_DISK_NO_FORMAT  (MFS_MSG_DEV+0x05)//磁盘未格式化
                                                      //mfsCallback(MFS_MSG_DEV_DISK_NO_FORMAT, dev_num, null);  
#define MFS_MSG_DEV_DISK_UNLOCAL    (MFS_MSG_DEV+0x06)//磁盘非本机格式化的硬盘
                                                      //mfsCallback(MFS_MSG_DEV_DISK_UNLOCAL, dev_num, null);  
#define MFS_MSG_DEV_POSITION_CHANGE (MFS_MSG_DEV+0x07)//磁盘个数或者位置更改
#define MFS_MSG_DEV_DISK_CH_CHANGE  (MFS_MSG_DEV+0x08)//接入磁盘上录像路数和本机不匹配
                                                      //mfsCallback(MFS_MSG_DEV_DISK_CH_CHANGE, dev_num, dev_ch_num);  
#define MFS_MSG_DEV_DISK_PEOGRESS   (MFS_MSG_DEV+0x09)//磁盘格式化进度(返回已经完成百分比)
                                                          //mfsCallback(MFS_MSG_DEV_DISK_PEOGRESS, percent,  0);  
#define MFS_MSG_DEV_REC_STANDARD_ERR (MFS_MSG_DEV+0x0a)//接入磁盘上录像编码格式和本机不匹配，返回设备号及设备上的编码标准号
                                                      //mfsCallback(MFS_MSG_DEV_REC_STANDARD_ERR, dev_num, disk_rec_standard);  

/******************************文件操作类回调信息******************/
#define MFS_MSG_PFILE               (MFS_MSG_BASE+0x0200)//文件操作类异常信息
#define MFS_MSG_PFILE_ALREADY_OPEN  (MFS_MSG_PFILE+0x01)//当前对应通道已经打开了操作指针，
#define MFS_MSG_PFILE_REC_CLOSED    (MFS_MSG_PFILE+0x02)//所有通道录像指针被关闭
                                                         //callback 返回当前已经打开的操作指针
#define MFS_MSG_PFILE_HANDLE_INVALID (MFS_MSG_PFILE+0x03)//当前通道的录像句柄失效，需要重新open
                                                        //mfsCallback(MFS_MSG_PFILE_HANDLE_INVALID, ch, 0); 
#define MFS_MSG_PFILE_INDEX_ERR     (MFS_MSG_PFILE+0x04)// 当前设备主索引表损坏
                                                        //mfsCallback(MFS_MSG_PFILE_INDEX_ERR, dev, 0)

                                                         
/******************************备份操作类回调信息******************/
#define MFS_MSG_BACKUP               (MFS_MSG_BASE+0x0300)//备份操作类异常信息

#define MFS_MSG_BACKUP_REC_BEING     (MFS_MSG_BACKUP+0x01)//要备份的数据段已在备份盘上     

/******************************CD 备份操作类回调信息******************/
#define MFS_MSG_BACKUP_CD            (MFS_MSG_BASE+0x10)
#define MFS_MSG_BACKUP_CD_BLANK      (MFS_MSG_BACKUP_CD+0x1)//光盘擦除完毕
#define MFS_MSG_BACKUP_CD_START      (MFS_MSG_BACKUP_CD+0x2)//备份操作启动
#define MFS_MSG_BACKUP_CD_FINISHED   (MFS_MSG_BACKUP_CD+0x3)//备份操作完成
#define MFS_MSG_BACKUP_CD_ERROR      (MFS_MSG_BACKUP_CD+0x4)//要光盘不可用
#define MFS_MSG_BACKUP_CD_PEOGRESS   (MFS_MSG_BACKUP_CD+0x5)//光盘刻录进度(返回已经完成百分比)
                                                          //mfsCallback(MFS_MFS_BACKUP_CD_PEOGRESS, percent,  0);  

/******************************USB 备份操作类回调信息******************/
#define MFS_MSG_BACKUP_USB           (MFS_MSG_BASE+0x020)//备份操作类异常信息
#define MFS_MSG_BACKUP_USB_ATTACH    (MFS_MSG_BACKUP_USB+0x1)//usb 接入
#define MFS_MSG_BACKUP_USB_DITACH    (MFS_MSG_BACKUP_USB+0x2)//usb 拔出
#define MFS_MSG_BACKUP_USB_START     (MFS_MSG_BACKUP_USB+0x3)//备份操作启动
#define MFS_MSG_BACKUP_USB_FINISHED  (MFS_MSG_BACKUP_USB+0x4)//备份操作完成
#define MFS_MSG_BACKUP_USB_ERROR     (MFS_MSG_BACKUP_USB+0x5)//USB加载失败，不可用
#define MFS_MSG_BACKUP_USB_MOUNT     (MFS_MSG_BACKUP_USB+0x6)//USB正在加载
#define MFS_MSG_BACKUP_USB_PEOGRESS  (MFS_MSG_BACKUP_USB+0x7)//USB备份进度(返回已经完成百分比，剩余文件数)
                                                          //mfsCallback(MFS_MSG_BACKUP_USB_PEOGRESS, percent,  left_num);  
#define MFS_MSG_BACKUP_USB_ABORT     (MFS_MSG_BACKUP_USB+0x8)//备份操作异常终止

/******************************操作类回调信息************************/
#define MFS_MSG_OPERAT                (MFS_MSG_BASE+0x0400)//操作类信息(bit16~23 留给表示信息类型)
#define MFS_MSG_OPERAT_REQUEST_IFRAME (MFS_MSG_OPERAT+0x01)//当前录像通道请求I帧写入，返回通道号             
                                                            //mfsCallback(MFS_MSG_OPERAT_REQUEST_IFRAME, ch, null);  
#define MFS_MSG_OPERAT_DEV_READY      (MFS_MSG_OPERAT+0x02)//休眠硬盘准备完成  
#define MFS_MSG_OPERAT_DEV_WAKENING   (MFS_MSG_OPERAT+0x03)//休眠硬盘正在唤醒





/*****************************MFS错误号定义*****************************
  类型为int，错误代码必须是负数，所以最高位置1，第0~3字节依次定义如下：
  |_ERRORNO_|_RESERVE_|_COMPID_|_0x80_|
  COMPID = COMP_MFS ,模块ID 定义在common.h 中
***********************************************************************************************/
/************************************************************************************************/
#define MFS_OK                          0U//系统正常

/**********************************设备错误号************************/
#define MFS_ERR_DEV                     COMP_ERROR_START//设备的异常信息
#define MFS_ERR_DEV_WRITE               (MFS_ERR_DEV + 1)//设备写异常
#define MFS_ERR_DEV_READ                (MFS_ERR_DEV + 2)//设备读异常
#define MFS_ERR_DEV_NOT_FORAMT          (MFS_ERR_DEV + 3)//设备未格式化  
#define MFS_ERR_DEV_FULL                (MFS_ERR_DEV + 4)//设备空间满  
#define MFS_ERR_DEV_FORMAT_FAILED       (MFS_ERR_DEV + 5)//设备格式化失败
#define MFS_ERR_DEV_LOSS                (MFS_ERR_DEV + 6)//设备异常丢失
#define MFS_ERR_DEV_BREAK               (MFS_ERR_DEV + 7)//设备所有操作被终止
#define MFS_ERR_DEV_INVALID             (MFS_ERR_DEV + 8)//设备无效
#define MFS_ERR_DEV_INIT_FAILED         (MFS_ERR_DEV + 9)//设备初始化失败
#define MFS_ERR_DEV_NOT_INIT            (MFS_ERR_DEV +10)

/**********************************通用错误号******************/
#define MFS_ERR_COMMON                 (COMP_ERROR_START+30)
#define MFS_ERR_SYS_LOGIC              (MFS_ERR_COMMON + 1)//文件系统未初始化
#define MFS_ERR_BACKUP_FAILED          (MFS_ERR_COMMON + 2)//备份失败
#define MFS_ERR_NOT_INIT               (MFS_ERR_COMMON + 3)//文件系统未初始化
#define MFS_ERR_HANDLENOCMD            (MFS_ERR_COMMON + 4)//无此命令

#define MFS_ERR_HANDLE_INVALID         (COMMON_ERROR_HANDLEINVAL)//句柄异常
#define MFS_ERR_HANDLE_OPEND           (COMMON_ERROR_HANDLEOPEND)//句柄已打开
#define MFS_ERR_NOT_SUPPORTED          (COMMON_ERROR_NOCMD)//不支持
#define MFS_ERR_BAD_PARAMETER          (COMMON_ERROR_PARAM)//错误参数
#define MFS_ERR_OUT_OF_MEMORY          (COMMON_ERROR_NOMEM)//内存满

#define MFS_ERRNO(error) ERRNO(error, COMP_MFS)//产生模块错误号


/*****************************MFS命令定义*****************************
  类型为int，错误代码必须是负数，所以最高位置1，第0~3字节依次定义如下：
  |_CMDNO_|_RESERVE_|_COMPID_|_0x00_|
  CMD域中0~31为公共命令，32~255可由模块自定义
  控制命令采用枚举定义，格式为COMP_CMD_XXX，全部大写，各模块按此标准定义
  COMPID = COMP_MFS ,模块ID 定义在common.h 中
***********************************************************************************************/
typedef enum
{
	MFS_CMD_GETVERSION = COMMON_CMD_GETVERSION, // 获取mfs版本号param 输出版本字符串指针
	MFS_CMD_SETOVERLAY = CMDNO(32, COMP_MFS), // 设置硬盘循环覆盖
                      //param 为unsgined int ;  param > 0 循环覆盖；param == 0 不覆盖
	MFS_CMD_SETBACKUPDIR, //设置USB 备份时建立文件夹的名字，需要在USB接入前调用
                        //param 输入文件夹的名字符串指针
                        //(若为NULL ,设置默认HB_BACKUP；strlen( param) <=64;否则截断处理;)
	MFS_CMD_SET_PLAYER_PATH,//设置播放器路径名;param 输入放器路径名字符串指针
	MFS_CMD_GET_USBVOLUME,//获得usb卷标;param 输出usb卷标路径名，字符串指针
	MFS_CMD_GET_REC_DATE//获得录像数据日期，获得64年的所有日期情况
                      //ch: 通道号(ch == MFS_REC_GET_ALL_CH 时，不区分通道)
                      //param 输入缓冲区指针，size_of_param = (3<<10)
} MFS_CMD;

#if 0
//日志类型
#define MFS_LOG_MAIN_TYPE_ALL       0xff
#define MFS_LOG_SUB_TYPE_ALL        0xff

// 日志结构体
typedef struct {
  MFS_TIME            time;
  unsigned char       type; // 类型
  unsigned char       operate; // 操作码
  unsigned char       subtype; // 次类型
  char                account[17]; // 用户
  unsigned int        ip_addr; // 0-Local other-ip
  unsigned int        input; // 事件输入输出
  unsigned int        output;
  char                data[28]; // 其他信息
} MFS_LOG_DAT, *PMFS_LOG_DAT;
#else
//日志类型
#define MFS_LOG_MAIN_TYPE_ALL       ALL_CHANNEL
#define MFS_LOG_SUB_TYPE_ALL        ALL_CHANNEL

// 日志结构体
typedef struct {
	MFS_TIME time; // 记录时间
	char pri_type; // 主类型
	char sec_type; // 次类型
	char reserve[58];//保留位
} MFS_LOG_DAT, *PMFS_LOG_DAT;

#endif



typedef int   MFS_ErrorCode;

typedef int   PMFS_SYS_HANDLE;//系统操作句柄类型
typedef int   PMFS_DEV_HANDLE;//设备操作句柄类型
typedef int   PMFS_REC_HANDLE;//文件操作句柄类型

//dev_status 定义
#define MFS_DEV_NORMAL      0 
#define MFS_DEV_DISK_ERROR  1
#define MFS_DEV_FS_FAILED   2
/* Device types. */

typedef enum
{
	tmFat32_NullDevice,     /* Null device. */
	tmFat32_IdeDevice,      /* IDE hard disk. */
	tmFat32_RamDevice,      /* RAM disk */
	tmFat32_UsbDevice,      /* USB host device */
	tmFat32_FlashDevice,    /* Flash memory */
	tmFat32_SdDevice,       /* SD Card */
  tmFat32_DvdDevic	      /* DVD Rom*/
} tmFat32_DeviceType_t;

// 系统信息（占用32字节）
typedef struct {
  unsigned long long  serial_num; //主板序列号
  unsigned char       rec_port;//录像通道数4;8;16
  unsigned char       rec_format;//录像分辨率CIF;D1
  unsigned char       rec_colorsystem;//录像制式Ntsc;Pal
  unsigned char       rec_standard;//录像压缩算法H264;MPG4
  MFS_TIME            sys_time;//系统最后访问硬盘时间
  unsigned int        reserve1[4];//保留
} MFS_SYS_INFO, *PMFS_SYS_INFO;


typedef struct {
  unsigned int          dev_num;  
  tmFat32_DeviceType_t  dev_type;//设备类型(默认硬盘)
  unsigned int          removable;//设备是否可移动装置(默认否) 
  unsigned int          backup;//设备是否备份装置(默认否)
  unsigned int          dev_status;//设备状态
  unsigned int          active;//设备工作状态(休眠或者活动).  
  unsigned int          device_capabilty;//设备容量(MB)
  unsigned int          mfs_capability;//文件系统可用容量(格式化后的容量MB)
  unsigned int          mfs_free;//当前可用容量(MB)
  PMFS_DEV_HANDLE       device_handle;//设备操作句柄
  MFS_SYS_INFO          device_sys_info;//磁盘上录像相关的系统信息
}Mfs_Device_Info, *pMfs_Device_Info;

typedef struct {
  Bool                  cycle_overlay;//磁盘循环覆盖,默认true
  unsigned int          dev_table;
  unsigned int          backup_table;
  Mfs_Device_Info       deviceinfo[MFS_DEV_MAX];
}MFS_DEV_INFO_TABLE, *PMFS_DEV_INFO_TABLE;


typedef void (*mfscallback_type)(int msg, int wParam, int lParam);

/*************************************************************
* 函数介绍：初始化MFS文件系统， 注册MFS系统回调函数
* 输入参数：rec_sys_info: 文件系统初始化信息结构体
*                               callback:    回调函数
* 输出参数：无；
* 返回值  ：<0: 错误, >0成功，表示创建的句柄
*************************************************************/
PMFS_SYS_HANDLE mfs_open(MFS_SYS_INFO * rec_sys_info, mfscallback_type callback);



/*************************************************************
* 函数介绍：启动MFS文件系统，该函数将申请句柄所需相关资源
* 输入参数：handle: MFS句柄；
*                              file_head: 录像文件头(默认为HBGK8004)
*                                a) 1-4字节为'HBGK'
*                                b) 5-8字节为产品型号:
*                                  pnx1700方案新文件系统: '8004'
*                                  dm642方案新文件系统: '8016'
* 输出参数：无；
* 返回值  ：0-成功，<0-错误代码
*************************************************************/
int mfs_start(PMFS_SYS_HANDLE handle, char * file_head);


/*************************************************************
* 函数介绍：关闭MFS文件系统，该函数将清除句柄所有数据，并释放相关资源
* 输入参数：handle: MFS句柄；
* 输出参数：无；
* 返回值  ：0-成功，<0-错误代码
*************************************************************/
int mfs_close(PMFS_SYS_HANDLE handle);


/*************************************************************
* 函数介绍：刷新MFS文件系统
* 输入参数：handle: MFS句柄；
*                               priority:文件系统刷新线程优先级
* 输出参数：无；
* 返回值  ：0-成功，<0-错误代码
*************************************************************/
int mfs_update(PMFS_SYS_HANDLE handle, int priority);




/*************************************************************
* 函数介绍：MFS配置
* 输入参数：handle: MFS句柄；
                                 cmd: 命令；
                                 channel: 通道号，此处无效
                                 param：输入参数；
                                 size_of_param: param长度，特别对于GET命令时，
                                 输出参数应先判断缓冲区是否足够
* 输出参数：param：输出参数；
* 返回值  ：0-成功，<0-错误代码
*************************************************************/
int mfs_ioctrl(PMFS_SYS_HANDLE handle, int cmd, signed int channel, int* param, int size_of_param);


/*************************************************************
* 函数介绍：查询系统中所有设备信息
* 输入参数：无；
* 输出参数：data: 输出所有设备信息结构体
* 返回值  ：0-成功，<0-错误代码
*************************************************************/
int mfs_dev_getallinfo(PMFS_DEV_INFO_TABLE data);


/*************************************************************
* 函数介绍：查询某个设备信息
* 输入参数：handle: 设备句柄；
* 输出参数：data: 输出设备信息结构体
* 返回值  ：0-成功，<0-错误代码
*************************************************************/
int mfs_dev_getinfo(PMFS_DEV_HANDLE handle, Mfs_Device_Info * data);


/*************************************************************
* 函数介绍：格式化某个存储设备(硬盘，USB)
* 输入参数：handle: 设备句柄；
* 输出参数：无；
* 返回值  ：0-成功，<0-错误代码
*************************************************************/
int mfs_dev_format(PMFS_DEV_HANDLE handle);



/*************************************************************
* 函数介绍：创建化录像句柄
* 输入参数：ch: 通道号
*                               type:    录像类型
* 输出参数：无；
* 返回值  ：<0: 错误, >0成功，表示创建的录像句柄
*************************************************************/
PMFS_REC_HANDLE mfs_record_writeopen(char ch, char type);



/*************************************************************
* 函数介绍： 写入录像数据
* 输入参数：handle: 录像句柄；
*                               frame_type: 当前写入数据的帧类型(说明: I 帧必须放在缓冲区头部写入)
*                               data:    数据缓冲区指针；
*                               size: 写入数据字节长度；
* 输出参数：无；
* 返回值  ：0-成功，<0-错误代码
*************************************************************/
int mfs_record_write(PMFS_REC_HANDLE handle, char frame_type, char *data, unsigned int size);



/*************************************************************
* 函数介绍： 关闭录像句柄，该函数将清除句柄所有数据，并释放相关资源
* 输入参数：handle: 录像句柄；
* 输出参数：无；
* 返回值  ：0-成功，<0-错误代码
*************************************************************/
int mfs_record_writeclose(PMFS_REC_HANDLE handle);



/*************************************************************
* 函数介绍：初始化放像句柄
* 输入参数：ch: 通道号
*                               date:时间
*                               type:录像类型
* 输出参数：无；
* 返回值  ：<0: 错误, >0成功，表示创建的放像句柄
*************************************************************/
PMFS_REC_HANDLE mfs_record_readopen(char ch, MFS_TIME date, char type);


/*************************************************************
* 函数介绍： 读取录像数据(会自动搜索播放时间连续的下一段或上一段录像)
* 输入参数：handle:放像句柄；
*                               speed: 读数据的帧间隔(正常放像,关键帧快进,关键帧快退)见放像速率的宏定义
*                               data:    数据缓冲区指针；
*                               size: 读出数据字节长度；
* 输出参数：time: 当前读出数据的时间
* 返回值  ：实际读出长度;
*************************************************************/
int mfs_record_read(PMFS_REC_HANDLE handle, MFS_READ_SPEED speed, char *data, unsigned int size, MFS_TIME * time);


/*************************************************************
* 函数介绍： 读取一段录像数据(只播放一个文件，不能夸文件放像)
* 输入参数：handle:放像句柄；
*                               speed: 读数据的帧间隔(正常放像,关键帧快进,关键帧快退,文件内seek)见放像速率的宏定义
*                               data:    数据缓冲区指针；
*                               size: 读出数据字节长度；
*                               perent:当speed == MFS_READ_SEEK , 用此值定义定位百分比(0~99)
* 输出参数：无
* 返回值      ：实际读出长度;
*************************************************************/
int mfs_record_readseg(PMFS_REC_HANDLE handle, MFS_READ_SPEED speed, char *data, unsigned int size, UInt32 Percent);



/*************************************************************
* 函数介绍： 关闭放像句柄，该函数将清除句柄所有数据，并释放相关资源
* 输入参数：handle: 放像句柄；
* 输出参数：无；
* 返回值      ：0-成功，<0-错误代码
*************************************************************/
int mfs_record_readclose(PMFS_REC_HANDLE handle);



/*************************************************************
* 函数介绍：  查询录像日期
* 输入参数：month: 查询的年月
* 输出参数：data: 返回有录像数据的日期(data[0:30]对应的日期为1~31号)
* 返回值      ：0-成功，<0-错误代码
*************************************************************/
int mfs_record_getdate(char ch, MFS_TIME month, unsigned int *data);



/*************************************************************
* 函数介绍：查询某天的录像段信息
* 输入参数：ch: 通道号
                                 date:  查询日期
                                 type:录像类型
                                 data:输出 缓冲； 
                                 start 读取当天录像段的起始号(0开始)；
                                 limit : 想 读取的录像段数(buffer_length / sizeof(Mfs_RecSeg_Info))
* 输出参数：total_num :输出 当天符合条件的录像段总数
* 返回值      ：返回值为实际读出段数
*************************************************************/
int mfs_record_getseg(char ch, MFS_TIME date, char type, Mfs_RecSeg_Info *data, int start, int limit, int *total_num);


/*************************************************************
* 函数介绍：查询某天的录像段信息，将时间连续的录像段拼接
*                               这个函数是mfs_record_getseg 的拼接
* 输入参数：ch: 通道号
                                 date:  查询日期
                                 type:录像类型
                                 data:输出 缓冲； 
                                 start 读取当天录像段的起始号(0开始)；
                                 limit : 想 读取的录像段数(buffer_length / sizeof(Mfs_RecSeg_Info))
* 输出参数：total_num :输出 当天符合条件的录像段总数
* 返回值      ：返回值为实际读出段数
*************************************************************/
int mfs_record_getseg_link(char ch, MFS_TIME date, char type, Mfs_RecSeg_Info *data, int start, int limit, int *total_num);


/*************************************************************
* 函数介绍： 查询一天内时间段的录像段信息
* 输入参数：ch: 通道号
                                 time_bg:  开始时间time_ed: 结束时间
                                 type:录像类型
                                 data:输出 缓冲； 
                                 start 读取当天录像段的起始号(0开始)；
                                 limit : 想 读取的录像段数(buffer_length / sizeof(Mfs_RecSeg_Info))
* 输出参数：total_num :输出 当天符合条件的录像段总数
* 返回值      ：返回值为实际读出段数
*************************************************************/
int mfs_record_getsegtimelice(char ch, MFS_TIME time_bg, MFS_TIME time_ed, char type, Mfs_RecSeg_Info *data, int start, int limit, int *total_num);


/*************************************************************
* 函数介绍： 查询一天内时间段的录像段信息，将时间连续的录像段拼接
*                               这个函数是mfs_record_getsegtimelice 的拼接
* 输入参数：ch: 通道号
                                 time_bg:  开始时间time_ed: 结束时间
                                 type:录像类型
                                 data:输出 缓冲； 
                                 start 读取当天录像段的起始号(0开始)；
                                 limit : 想 读取的录像段数(buffer_length / sizeof(Mfs_RecSeg_Info))
* 输出参数：total_num :输出 当天符合条件的录像段总数
* 返回值      ：返回值为实际读出段数
*************************************************************/
int mfs_record_getsegtimelice_link(char ch, MFS_TIME time_bg, MFS_TIME time_ed, char type, Mfs_RecSeg_Info *data, int start, int limit, int *total_num);


/***********************************************************************/
/*备份功能函数(将数据刻录到光盘或者备份到U盘)*/
/*网络备份文件使用*/
/***********************************************************************/
//
/*************************************************************
* 函数介绍：打开备份句柄函数
* 输入参数：ch: 通道号
*                               date:时间
*                               type:录像类型
* 输出参数：无；
* 返回值      ：<0: 错误, >0成功，表示创建的备份句柄函数
*************************************************************/
PMFS_REC_HANDLE mfs_backup_readopen(Mfs_RecSeg_Info data);


/*************************************************************
* 函数介绍： 读取备份数据
* 输入参数：handle:备份句柄；
*                               data:    数据缓冲区指针；
*                               size: 读出数据字节长度；
* 输出参数：无；
* 返回值      ：实际读出长度;
*************************************************************/
int mfs_backup_read(PMFS_REC_HANDLE handle, char *data, int size);


/*************************************************************
* 函数介绍： 关闭备份句柄，该函数将清除句柄所有数据，并释放相关资源
* 输入参数：handle: 备份句柄；
* 输出参数：无；
* 返回值      ：0-成功，<0-错误代码
*************************************************************/
int mfs_backup_readclose(PMFS_REC_HANDLE handle);

#if mfs_cd

/*********************************************************************/
/*光盘功能模块函数*/
/**/
/*********************************************************************/
//光盘备份录像任务函数
int mfs_cd_recordtask(unsigned int nPrior, unsigned int stack, Mfs_RecSeg_Info *pdata, int limit);


/*************************************************************
* 函数介绍：初始化光盘文件 放像句柄
* 输入参数：data: 要打开的光盘录像文件信息
* 输出参数：无；
* 返回值  ：<0: 错误, >0成功，表示创建的放像句柄
*************************************************************/
PMFS_REC_HANDLE mfs_cd_readopen(Mfs_RecSeg_Info data);

//
/*************************************************************
* 函数介绍：读出光盘数据(只播放一个文件，不能夸文件放像)
* 输入参数：handle:放像句柄；
*                               speed: 读数据的帧间隔(正常放像,关键帧快进,关键帧快退,文件内seek)见放像速率的宏定义
*                               data:    数据缓冲区指针；
*                               size: 读出数据字节长度；
* 输出参数：无
* 返回值      ：实际读出长度;
*************************************************************/
unsigned int mfs_cd_read(PMFS_REC_HANDLE handle, MFS_READ_SPEED speed, char *data, unsigned int size);


/*************************************************************
* 函数介绍： 关闭光盘放像句柄，该函数将清除句柄所有数据，并释放相关资源
* 输入参数：handle: 备份句柄；
* 输出参数：无；
* 返回值      ：0-成功，<0-错误代码
*************************************************************/
int mfs_cd_readclose(PMFS_REC_HANDLE handle);


/*************************************************************
* 函数介绍：光盘文件检索所有录像段
* 输入参数：rec_seg_info:输出 缓冲； 
                                 limit : 想 读取的录像段数(buffer_length / sizeof(Mfs_RecSeg_Info))
* 输出参数：total :U盘录像段总数
* 返回值      ：返回值为实际读出段数
*************************************************************/
int mfs_cd_recordgetall(Mfs_RecSeg_Info * rec_seg_info, unsigned int limit, unsigned int * total);


/*************************************************************
* 函数介绍：按条件检索光盘上录像段
* 输入参数：ch: 通道号(ch == MFS_USB_GET_ALL_CH 时，不区分通道)
                                 date:  查询日期(当data == 0时，不区分时间)
                                 rec_seg_info:输出 缓冲； 
                                 limit : 想 读取的录像段数(buffer_length / sizeof(Mfs_RecSeg_Info))
* 输出参数：total :U盘符合条件的录像段总数
* 返回值      ：返回值为实际读出段数
*************************************************************/
int mfs_cd_recordgetseg(signed char ch, MFS_TIME date, Mfs_RecSeg_Info * rec_seg_info, unsigned int limit, unsigned int * total);

//擦除光盘
int mfs_cd_clear();

//刻录模块用
unsigned int mfs_cd_getnum();
#endif


#if mfs_usb
/*********************************************************************/
/*U 盘功能模块函数*/


/*************************************************************
* 函数介绍：从硬盘上备份对应的文件段到USB 
* 输入参数：priority: 线程优先级1~99
                                  pdata: 文件段信息结构体链表
                                  limit: 文件数
* 输出参数：无；
* 返回值  ：<0: 错误, >0成功，表示创建的放像句柄
*************************************************************/
int mfs_usb_backupfiletask(int priority, Mfs_RecSeg_Info *pdata, int limit);


/*************************************************************
* 函数介绍：初始化USB 放像句柄
* 输入参数：data: 要打开的usb录像文件信息
* 输出参数：无；
* 返回值  ：<0: 错误, >0成功，表示创建的放像句柄
*************************************************************/
PMFS_REC_HANDLE mfs_usb_readopen(Mfs_RecSeg_Info data);


/*************************************************************
* 函数介绍：读出usb 上文件数据(只播放一个文件，不能夸文件放像)
* 输入参数：handle:放像句柄；
*                               speed: 读数据的帧间隔(正常放像,关键帧快进,关键帧快退,文件内seek)见放像速率的宏定义
*                               data:    数据缓冲区指针；
*                               size: 读出数据字节长度；
* 输出参数：无
* 返回值      ：实际读出长度;
*************************************************************/
unsigned int mfs_usb_read(PMFS_REC_HANDLE handle, MFS_READ_SPEED speed, char *data, unsigned int size);


/*************************************************************
* 函数介绍： 关闭USB 放像句柄，该函数将清除句柄所有数据，并释放相关资源
* 输入参数：handle: 备份句柄；
* 输出参数：无；
* 返回值      ：0-成功，<0-错误代码
*************************************************************/
int mfs_usb_readclose(PMFS_REC_HANDLE handle);


/*************************************************************
* 函数介绍：U 盘文件检索所有录像段
* 输入参数：rec_seg_info:输出 缓冲； 
                                 limit : 想 读取的录像段数(buffer_length / sizeof(Mfs_RecSeg_Info))
* 输出参数：total :U盘录像段总数
* 返回值      ：返回值为实际读出段数
*************************************************************/
int mfs_usb_recordgetall(Mfs_RecSeg_Info * rec_seg_info, unsigned int limit, unsigned int * total);



/*************************************************************
* 函数介绍：按条件检索U 盘上录像段
* 输入参数：ch: 通道号(ch == MFS_USB_GET_ALL_CH 时，不区分通道)
                                 date:  查询日期(当data == 0时，不区分时间)
                                 rec_seg_info:输出 缓冲； 
                                 limit : 想 读取的录像段数(buffer_length / sizeof(Mfs_RecSeg_Info))
* 输出参数：total :U盘符合条件的录像段总数
* 返回值      ：返回值为实际读出段数
*************************************************************/
int mfs_usb_recordgetseg(unsigned char ch, MFS_TIME date, Mfs_RecSeg_Info * rec_seg_info, unsigned int limit, unsigned int * total);



/*************************************************************
* 函数介绍：U 盘文件检索所有录像段,并分页输出
* 输入参数：rec_seg_info:输出 缓冲； 
                                 start 读取当天录像段的起始号(0开始)；
                                 limit : 想 读取的录像段数(buffer_length / sizeof(Mfs_RecSeg_Info))
* 输出参数：total :U盘录像段总数
* 返回值      ：返回值为实际读出段数
*************************************************************/
//  int mfs_usb_recordget(Mfs_RecSeg_Info *rec_seg_info, int start, int limit, int *total);
int mfs_usb_recordgetall_page(Mfs_RecSeg_Info *rec_seg_info, int start, int limit, int *total);



/*************************************************************
* 函数介绍：按条件检索U 盘上录像段,并分页输出
* 输入参数：ch: 通道号(ch == MFS_USB_GET_ALL_CH 时，不区分通道)
                                 date:  查询日期(当data == 0时，不区分时间)
                                 rec_seg_info:输出 缓冲； 
                                 start 读取当天录像段的起始号(0开始)；
                                 limit : 想 读取的录像段数(buffer_length / sizeof(Mfs_RecSeg_Info))
* 输出参数：total :U盘符合条件的录像段总数
* 返回值      ：返回值为实际读出段数
*************************************************************/
//int mfs_usb_recordgetdateseg(unsigned char ch, MFS_TIME date, Mfs_RecSeg_Info * rec_seg_info,  int start, unsigned int limit, unsigned int * total);
int mfs_usb_recordgetseg_page(unsigned char ch, MFS_TIME date, Mfs_RecSeg_Info * rec_seg_info,  int start, unsigned int limit, unsigned int * total);

#endif


/*************************************************************
* 函数介绍：文件系统通用读关闭，可以关闭所有类型的读句柄
* 输入参数：handle: 放像句柄；
* 输出参数：无；
* 返回值      ：0-成功，<0-错误代码
*************************************************************/
int mfs_readclose(PMFS_REC_HANDLE handle);




/************************************************************************/
/*日志类功能函数*/
/************************************************************************/
/*************************************************************
* 函数介绍：写日志数据
* 输入参数：data: 日志结构体(时间不用填充，文件系统自动获取当前时间)
* 输出参数：无；
* 返回值      ：0-成功，<0-错误代码
*************************************************************/
int mfs_log_write(MFS_LOG_DAT *data);


/*************************************************************
* 函数介绍：查询日志日期
* 输入参数：month: 查询的年月
* 输出参数：data: 返回有日志的日期(data[0:30]对应的日期为1~31号)
* 返回值      ：0-成功，<0-错误代码
*************************************************************/
int mfs_log_getdate(MFS_TIME month, unsigned int *data);


/*************************************************************
* 函数介绍： 查询某天的日志信息；
* 输入参数：date 日期；
                                 *data 缓冲；
                                 start 读取当天日志项的起始号(0开始)
                                 num : 想 读取的日志数(当num==0 查询当天日志条数)
* 输出参数：total_num : 输出 当天日志总数
* 返回值      ：0-成功，<0-错误代码
*************************************************************/
int mfs_log_getseg(MFS_TIME date, MFS_LOG_DAT *data, unsigned int start, unsigned int num, unsigned int *total_num);



/*************************************************************
* 函数介绍： 按照类型 查询某天的日志信息；
* 输入参数： date 日期；*data 缓冲； start 读取当天日志项的起始号(0开始)
                                  pri_type: 日志主类型( pri_type == ALL_TYPE 查询所有日志信息)
                                  sec_type:日志次类型( sec_type == ALL_TYPE 查询主类型下所有日志信息)
                                  num : 想 读取的日志数(当num==0 查询当天日志条数)
* 输出参数：total_num : 输出 当天日志总数
* 返回值      ：0-成功，<0-错误代码
*************************************************************/
int mfs_log_getsegtype(MFS_TIME date, MFS_LOG_DAT *data, signed char pri_type, signed char sec_type, unsigned int start, unsigned int num, unsigned int *total_num);

#endif

