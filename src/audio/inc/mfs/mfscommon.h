#ifndef MFSCOMMON_H
#define MFSCOMMON_H
#include "linux/types.h"


// 模块软件版本定义
typedef struct
{
	unsigned  minver : 6; //  0~63
	unsigned  secver : 6; //  0~63
	unsigned  majver : 5; //  0~31
	unsigned  day 	 : 5; // 日: 1~31
	unsigned  month  : 4; // 月: 1~12
	unsigned  year   : 6; // 年: 2000~2063
} SWVERSION, *PSWVERSION;

#define VINFO2STR(str, v) sprintf(str, "V%d.%d.%d build%04d%02d%02d\n", v.majver, v.secver, v.minver, v.year+2000, v.month, v.day)
#define ALL_CHANNEL -1 // 参数获取和设置时，用该值表示全部通道


#define COMP_MFS 16


/***************************** 错误代码定义*****************************
  类型为int，错误代码必须是负数，所以最高位置1，第0~3字节依次定义如下：
  |_ERRORNO_|_RESERVE_|_COMPID_|_0x80_|
  **  用户模块错误号从32开始定义，当返回错误时，采用ERRNO(errno, compid)形式
  **  错误代码采用枚举定义，格式为COMP_ERROR_XXX，全部大写，各模块按此标准定义
***********************************************************************/
#define ERRNO(error, id) 0x80000000|(id<<16)|(error)
#define PERROR(errno) printf("COMP_MFS: errno=%u\n", errno&0xff)

typedef enum
{
	COMMON_ERROR_HANDLEINVAL = 1, // 句柄描述字非法
	COMMON_ERROR_HANDLEOPEND,     // 句柄已打开
	COMMON_ERROR_NOCMD,           // 命令不允许
	COMMON_ERROR_PARAM,           // 参数错误
	COMMON_ERROR_NOMEM,           // 没有足够内存

	COMP_ERROR_START = 32         // 用户模块起始错误号
} COMMON_ERROR;


/***************************** 公共命令定义*****************************
  用于模块xxx_ioctrl(..., cmd, )中cmd的定义
**  CMD域中0~31为公共命令，32~255可由模块自定义
**  控制命令采用枚举定义，格式为COMP_CMD_XXX，全部大写，各模块按此标准定义
***********************************************************************/
#define CMDNO(cmd, id) (id<<16)|(cmd)

typedef enum
{
	COMMON_CMD_GETVERSION = CMDNO(0, COMP_MFS), // 获取模块版本
	COMMON_CMD_GETHEALTHY,
	COMMON_CMD_GETPID,
	COMMON_CMD_RESET,     						// 复位当前句柄
} COMMON_CMD;


#define	Null		        0
#define	False		        0
#define	True		        1


#ifdef PATH_MAX
#undef PATH_MAX
#endif
#define	PATH_MAX	1024	/* max number of bytes in pathname	*/


// Define some types

typedef char *		        Address;	/* ready for address-arithmetic */
typedef char		        Char;		/* machine-natural character */
typedef unsigned int	    Bool;
typedef char *		        String;		/* guaranteed null-terminated */
typedef char const *	    ConstString;
typedef signed char         Int8;
typedef signed short	    Int16;
typedef signed long	        Int32;
typedef int		            Int;		/* machine-natural integer */
typedef unsigned int	    UInt;		/* machine-natural unsigned integer */
typedef unsigned char	    UInt8;
typedef unsigned short	    UInt16;
typedef unsigned int	    UInt32;
typedef signed long long    Int64;
typedef unsigned long long  UInt64;
typedef UInt32              tmErrorCode_t;
typedef void *		        Pointer;	/* pointer to anonymous object */
typedef UInt32              tmosalTaskHandle_t, *ptmosalTaskHandle_t;
typedef UInt32              tmInstance_t;
typedef UInt32              tmosalSemHandle_t;
typedef	void *	            Dir;

#define U64HICASTU32(a)    ((a)>>32)
#define U64LOCASTU32(a)    ((a) & 0xFFFFFFFF)

//#define UCLIPI(a,b)         ((a)>0? ((a) > (b)? b : a) : 0)
//#define UCLIPI(a,b)         MFS_CLIP(a,0,b);
#define IMIN(a,b)           (((a)>(b))? (b) : (a))
#define UGTR(a,b)           (((a)>(b))? 1 : 0)
#define IGTR(a,b)           (((a)>(b))? 1 : 0)
#define ILEQ(a,b)           (((a)<=(b))? 1 : 0)
#define INEQ(a,b)           (((a)!=(b))? 1 : 0)
//#define MIN(a,b)            ((a)<(b)?(a):(b))
//#define MAX(a,b)		((a)>(b)?(a):(b))


// 时间信息（占用4字节，设计要求可按32位比较大小来决定时间的先后）
typedef struct
{
	unsigned            second : 6; // 秒: 0~59
	unsigned            minute : 6; // 分: 0~59
	unsigned            hour   : 5; // 时: 0~23
	unsigned            day    : 5; // 日: 1~31
	unsigned            month  : 4; // 月: 1~12
	unsigned            year   : 6; // 年: 2000~2063
}MFS_Field_Time;

typedef union
{
    unsigned int  longtime;
    MFS_Field_Time fieldtime;
}MFS_TIME, *PMFS_TIME;

#define MFS_CLIP(a,b,c)    (((a)<(b))?(b):(((a)>(c))?(c):(a)))

#define MFS_MUX(a,b,c)      (((a) != 0)? (b):(c))

typedef struct
{
	MFS_TIME      begin_time, end_time;
	unsigned int  lengh;
	char          ch;
	char          type;
}Mfs_RecSeg_Info, *PMfs_RecSeg_Info;


extern void * mfs_malloc(int len);

extern void mfs_free(void * ptr);

//年份为公元纪年
extern void mfs_gettime(UInt32* year, UInt32* month, UInt32* day, UInt32* hour, UInt32* minute, UInt32* second);


/*************************************************************
* 函数介绍：: 文件系统取写盘开始帧时间和结束帧时间
* 输入参数：ch 当前录像通道号；
*                               data --写盘缓冲区帧的首地址；  
*                               size--缓冲区的长度
* 输出参数： tarttime--开始帧的时间;
 *                               endtime--结束帧的时间;
 *                                changetimeindex--系统时间是否改变标志(False:没有 True:有)
* 返回值  ：0--成功 <0: 错误
*************************************************************/
extern int mfsGetFrameTime(unsigned char ch, char *data, unsigned int  size, PMFS_TIME starttime, PMFS_TIME endtime, Bool *changetimeindex, unsigned int  *changelen);

void mfs_RecInfo2FileName(char* pFileName, Mfs_RecSeg_Info Rec_info);

unsigned int mfs_FileName2RecInfo(PMfs_RecSeg_Info pRec_info, char* pFileName);

#endif

