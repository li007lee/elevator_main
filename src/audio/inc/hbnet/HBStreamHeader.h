////////////////////////////////////////////////////////////////////////////////
// 版权所有，2009-2011，北京汉邦高科数字技术有限公司。
// 该文件是未公开的，包含了汉邦高科机密和专利内容。
////////////////////////////////////////////////////////////////////////////////
// 文件名：HBStreamHeader.h
// 作者：deng feng
// 版本：1.0
// 日期：2011-04-20
// 描述：定义汉邦高科结构化的、可扩展的音视频帧头。
// 历史记录：
////////////////////////////////////////////////////////////////////////////////
#ifndef HB_STREAM_HEADER_H
#define HB_STREAM_HEADER_H

#ifdef __cplusplus
extern "C" {
#endif


//帧头的内存存储结构。
// +----------------------------+
// |         STREAM_HEADER      |
// +----------------------------+
// |    STREAM_VIDEO_HEADER     |
// +----------------------------+
// |  STREAM_SEGMENT_HEADER[0]  |
// +----------------------------+
// |          ......            |
// +----------------------------+
// | STREAM_SEGMENT_HEADER[n-1] |
// +----------------------------+
// |                            |
// |  Audio Data or Video Data  |
// |                            |
// +----------------------------+
//一个典型的音频帧包括：STREAM_HEADER和Audio Data。
//一个典型的视频I帧包括：STREAM_HEADER、STREAM_VIDEO_HEADER、若干STREAM_SEGMENT_HEADER和Video Data。
//一个典型的视频P帧包括：STREAM_HEADER、STREAM_VIDEO_HEADER和Video Data。


//帧头标志。
#define STREAM_HEADER_FLAG              0xFF620068


//帧类型。
#define STREAM_FRAME_AUDIO              0           //音频帧
#define STREAM_FRAME_VIDEO_I            1           //视频I帧
#define STREAM_FRAME_VIDEO_P            2           //视频P帧
#define STREAM_FRAME_VIDEO_B            3           //视频B帧


//音频编码算法。
#define STREAM_ALGORITHM_AUDIO_PCM8_16  0           //16-bit PCM只保留高8位
#define STREAM_ALGORITHM_AUDIO_G711A    1           //G.711 Alaw
#define STREAM_ALGORITHM_AUDIO_G722     2           //G.722
#define STREAM_ALGORITHM_AUDIO_G726     3           //G.726


//视频编码算法。
#define STREAM_ALGORITHM_VIDEO_H264_HISILICON   0   //Hisilicon H.264
#define STREAM_ALGORITHM_VIDEO_H264_AMBARELLA   1   //Ambarella H.264
#define STREAM_ALGORITHM_VIDEO_H264_TECHWELL    2   //Techwell H.264


//码流帧头。
//sizeof(STREAM_HEADER) == 16
typedef struct STREAM_HEADER
{
    //帧头标志，必须是STREAM_HEADER_FLAG。
    unsigned int                nHeaderFlag;

    //帧头的大小，以字节为单位，取值范围[sizeof(STREAM_HEADER), 65535]。
    // nHeaderSize = sizeof(STREAM_HEADER)
    // + IsStreamVideoFrame() ? STREAM_VIDEO_HEADER.nVideoHeaderSize : 0
    // + STREAM_SEGMENT_HEADER[0].nSegmentSize + ... 
    // + STREAM_SEGMENT_HEADER[nSegmentCount-1].nSegmentSize;
    unsigned int                nHeaderSize : 16;

    //帧类型，使用STREAM_FRAME_*。
    //当帧类型是STREAM_FRAME_VIDEO_*时，STREAM_HEADER结构体随后是STREAM_VIDEO_HEADER。
    unsigned int                nFrameType : 3;

    //音频或视频编码算法。
    //当nFrameType==STREAM_FRAME_AUDIO时，使用STREAM_ALGORITHM_AUDIO_*。
    //当nFrameType==STREAM_ALGORITHM_VIDEO_*时，使用STREAM_ALGORITHM_VIDEO_*。
    unsigned int                nAlgorithm : 5;

    //STREAM_SEGMENT_HEADER结构体的数量，取值范围[0, 255]。
    //当nSegmentCount==0时，表示没有STREAM_SEGMENT_HEADER。
    //一般的，只当nFrameType == STREAM_FRAME_VIDEO_I时，才设置nSegmentCount。
    unsigned int                nSegmentCount : 8;

    //需要校验的编码数据的大小，取值范围[0, 255]。
    //一般只校验编码数据的前、后部分字节。
    //当nCheckedDataSize==0时，不校验编码数据。
    //建议：至少校验前后各16个字节的编码数据。
    unsigned int                nCheckedEncodeDataSize : 8;

    //校验和，不能等于0。
    //包括STREAM_VIDEO_HEADER、STREAM_HEADER_SEGMENT[0 : n-1]和编码数据的前、后
    //部分字节。
    unsigned int                nChecksum : 24;

    //编码数据的大小，以字节为单位，取值范围[0, 16777215]。
    unsigned int                nEncodeDataSize : 24;

    //保留。
    unsigned int                nReserved : 8;

} STREAM_HEADER, *PSTREAM_HEADER;



//视频帧头信息。
//sizeof(STREAM_VIDEO_HEADER) == 24
typedef struct STREAM_VIDEO_HEADER
{
    //视频帧头的大小，以字节为单位，取值范围[sizeof(STREAM_VIDEO_HEADER), 255]。
    unsigned int                nVideoHeaderSize : 8;

    //视频帧绝对时间的毫秒值，取值范围[0, 999]。
    //可以通过_ftime64或_ftime64_s函数来获取nTimeStampLow、nTimeStampHight
    //和nTimeStampMillisecond。
    //若不使用nTimeStampHight和nTimeStampMillisecond，可以通过time或_time32函数
    //来获取nTimeStampLow。
    unsigned int                nTimeStampMillisecond : 10;

    //图像宽度，以4像素为单位，取值范围[0, 16383]。
    //实际图像宽度= nWidth * 4。
    unsigned int                nWidth : 14;

    //图像高度，以4像素为单位，取值范围[0, 8191]。
    //实际图像高度= nHeight * 4。
    unsigned int                nHeight : 13;

    //视频帧率，以赫兹（Hz）为单位，取值范围[1, 127]。
    unsigned int                nFrateRate : 7;

    //保留。
    unsigned int                nReserved : 12;

    //帧序号。
    //帧序号是逐渐递增的，用于判断视频帧的连续性。
    unsigned int                nIndex;

    //视频帧相对时间，以毫秒（millisecond）为单位。
    //播放时，用于控制2帧之间的时间间隔。
    unsigned int                nTickCount;

    //视频帧绝对时间，以秒（second）为单位。
    //nTimeStampLow为64位整数的低32位，nTimeStampHight为64位整数的高32位。
    //以世界时间（UTC）时间计算，从公元1970-01-01 00:00:00起经过的秒数。
    //nTimeStampLow最大表示到公元2038-01-19 03:14:07, UTC。
    //nTimeStampLow和nTimeStampHight共同最大表示到公元3000-12-31 23:59:59, UTC。
    unsigned int                nTimeStampLow;
    int                         nTimeStampHight;

} STREAM_VIDEO_HEADER, *PSTREAM_VIDEO_HEADER;


//段类型。
#define STREAM_SEGMENT_OSD_STRING   0               //自定义字符串
#define STREAM_SEGMENT_OSD_TIME     1               //时间信息
#define STREAM_SEGMENT_MOSAIC       2               //马赛克


//OSD字体。
#define STREAM_FONT_DEFAULT         0               //缺省字体
#define STREAM_FONT_POINT_16        1               //16点阵字体
#define STREAM_FONT_POINT_24        2               //24点阵字体
#define STREAM_FONT_POINT_32        3               //32点阵字体
#define STREAM_FONT_SYSTEM_12       4               //12号System字体
#define STREAM_FONT_SYSTEM          5               //System字体（自适应大小）
#define STREAM_FONT_SONGTI          6               //宋体（自适应大小）


//OSD背景模式。
#define STREAM_OSD_BK_OPAQUE        0               //不透明，背景色为黑色
#define STREAM_OSD_BK_TRANSPARENT   1               //透明


//时间格式。
//可以自定义多种格式。
#define STREAM_TIME_FORMAT_DEFAULT  0   //yyyy-MM-dd HH:mm:ss ==> %04d-%02d-%02d %02d:%02d:%02d
#define STREAM_TIME_FORMAT_1        1   //yyyy-MM-dd HH:mm:ss.mmm ==> %04d-%02d-%02d %02d:%02d:%02d.%03d
#define STREAM_TIME_FORMAT_2        2   //MM/dd/yyyy HH:mm:ss ==> %02d/%02d/%04d %02d:%02d:%02d
#define STREAM_TIME_FORMAT_3        3   //dddd, MMMM d, yyyy, HH:mm:ss ==> %s, %s %d, %04d, %02d:%02d:%02d
#define STREAM_TIME_FORMAT_4        4   //M/d/yy h:mm:ss tt ==> %d/%d/%02d %d:%02d:%02d %s
#define STREAM_TIME_FORMAT_5        5   //yyyy年M月d日 HH时mm分ss秒 ==> %04d年%d月%d日 %02d时%02d分%02d秒
#define STREAM_TIME_FORMAT_6        6   //yyyy年M月d日 星期 HH时mm分ss秒 ==> %04d年%d月%d日 星期%s %02d时%02d分%02d秒
#define STREAM_TIME_FORMAT_7        7   //yyyy年M月d日 tt h:mm:ss ==> 04d年%d月%d日 %s %d:%02d:%02d
#define STREAM_TIME_FORMAT_8        8   //其他自定义格式


//马赛克填充模式。
#define STREAM_MOSAIC_FILL_BLACK        0           //填充黑色
#define STREAM_MOSAIC_FILL_BACKGROUND   1           //填充背景色


//段信息。
//sizeof(STREAM_SEGMENT_HEADER) == 16
typedef struct STREAM_SEGMENT_HEADER
{
    //段大小，以字节为单位，取值范围[sizeof(STREAM_SEGMENT_HEADER), 2047]。
    //包括联合体u中扩展内容的长度。
    //当扩展数据为字符串时，包括结束符'\0'。
    unsigned int                nSegmentSize : 11;

    //段类型，指定联合体u中有效的成员。
    //当段类型是STREAM_SEGMENT_OSD_STRING时，u.OsdString有效。
    //当段类型是STREAM_SEGMENT_OSD_TIME时，u.OsdTime有效。
    //当段类型是STREAM_SEGMENT_MOSAIC时，u.Mosaic有效。
    unsigned int                nSegmentType : 5;

    //保留。
    unsigned int                nReverved : 16;

    union SEGMENT_TYPE
    {
        //自定义字符串。
        struct OSD_STRING
        {
            unsigned short      x;                  //x坐标，以像素为单位
            unsigned short      y;                  //y坐标，以像素为单位
            unsigned char       nReserved;          //保留
            unsigned char       nBlue;              //蓝色分量
            unsigned char       nGreen;             //绿色分量
            unsigned char       nRed;               //红色分量
            unsigned char       nFontType;          //字体，使用STREAM_FONT_*
            unsigned char       bBkMode;            //背景模式，使用STREAM_OSD_BK_*
            char                str[1];             //自定义字符串，必须以'\0'结束
        } OsdString;

        //时间信息。
        //使用STREAM_VIDEO_HEADER结构体中的nTimeStampLow、nTimeStampHight和
        //nTimeStampMillisecond作为时间信息。
        struct OSD_TIME
        {
            unsigned short      x;                  //x坐标，以像素为单位
            unsigned short      y;                  //y坐标，以像素为单位
            unsigned char       nReserved;          //保留
            unsigned char       nBlue;              //蓝色分量
            unsigned char       nGreen;             //绿色分量
            unsigned char       nRed;               //红色分量
            unsigned char       nFontType;          //字体，使用STREAM_FONT_*
            unsigned char       bBkMode;            //背景模式，使用STREAM_OSD_BK_*
            unsigned char       nFormat;            //时间格式，使用STREAM_TIME_FORMAT_*
        } OsdTime;

        //马赛克。
        struct MOSAIC
        {
            unsigned short      x;                  //x坐标，以像素为单位
            unsigned short      y;                  //y坐标，以像素为单位
            unsigned short      nWidth;             //马赛克的宽度
            unsigned short      nHeight;            //马赛克的高度
            unsigned char       nFillMode;          //填充模式，使用STREAM_MOSAIC_FILL_*
        } Mosaic;
    } u;

} STREAM_SEGMENT_HEADER, *PSTREAM_SEGMENT_HEADER;


////////////////////////////////////////////////////////////////////////////////
// 函数名：Stream_IsHeaderFlag
// 描述：判断是否是帧头标志。
// 参数：
//  [in]pBufferHeader - 缓冲区地址，不能为NULL。
// 返回值：
//  返回0不是合法的帧头标志，返回非0是合法的帧头标志。
// 说明：
//  pBufferHeader的有效长度不小于4字节。
////////////////////////////////////////////////////////////////////////////////
/*
static int Stream_IsHeaderFlag( const void* pBufferHeader )
{
    return (STREAM_HEADER_FLAG == *((const unsigned int*)pBufferHeader));
}
*/

////////////////////////////////////////////////////////////////////////////////
// 函数名：Stream_IsVideoFrame
// 描述：判断是否是视频帧。
// 参数：
//  [in]pStreamHeader - STREAM_HEADER结构体地址，不能为NULL。
// 返回值：
//  返回0不是视频帧，返回非0是视频帧。
// 说明：
////////////////////////////////////////////////////////////////////////////////
static inline int Stream_IsVideoFrame( const STREAM_HEADER* pStreamHeader )
{
    return (STREAM_FRAME_VIDEO_P == pStreamHeader->nFrameType
        || STREAM_FRAME_VIDEO_I == pStreamHeader->nFrameType
        || STREAM_FRAME_VIDEO_B == pStreamHeader->nFrameType);
}


////////////////////////////////////////////////////////////////////////////////
// 函数名：Stream_IsAudioFrame
// 描述：判断是否是音频帧。
// 参数：
//  [in]pStreamHeader - STREAM_HEADER结构体地址，不能为NULL。
// 返回值：
//  返回0不是音频帧，返回非0是音频帧。
// 说明：
////////////////////////////////////////////////////////////////////////////////
/*
static int Stream_IsAudioFrame( const STREAM_HEADER* pStreamHeader )
{
    return (STREAM_FRAME_AUDIO == pStreamHeader->nFrameType);
}
*/

////////////////////////////////////////////////////////////////////////////////
// 函数名：Stream_GetVideoHeaderAddress
// 描述：获取视频帧头的地址。
// 参数：
//  [in]pStreamHeader - STREAM_HEADER结构体地址，不能为NULL。
// 返回值：
//  返回视频帧头的地址。
// 说明：
//  该帧必须是合法的视频帧。
////////////////////////////////////////////////////////////////////////////////
/*
static PSTREAM_VIDEO_HEADER Stream_GetVideoHeaderAddress( 
    const STREAM_HEADER* pStreamHeader )
{
    return (PSTREAM_VIDEO_HEADER)((char*)pStreamHeader + sizeof(STREAM_HEADER));
}
*/

////////////////////////////////////////////////////////////////////////////////
// 函数名：Stream_GetSegmentHeaderAddress
// 描述：获取段信息的地址。
// 参数：
//  [in]pStreamHeader - STREAM_HEADER结构体地址，不能为NULL。
//  [in]nIndex - 段序号，应该小于STREAM_HEADER.nSegmentCount。
// 返回值：
//  返回段信息的地址。
// 说明：
////////////////////////////////////////////////////////////////////////////////
/*
static PSTREAM_SEGMENT_HEADER Stream_GetSegmentHeaderAddress( 
    const STREAM_HEADER* pStreamHeader, unsigned int nIndex )
{
    if ( nIndex < pStreamHeader->nSegmentCount )
    {
        PSTREAM_SEGMENT_HEADER pSegment;
        char* pAddress;
        unsigned int i;

        if ( Stream_IsVideoFrame( pStreamHeader ) )
        {
            PSTREAM_VIDEO_HEADER pVideoHeader = Stream_GetVideoHeaderAddress( 
                pStreamHeader );
            pAddress = (char*)pVideoHeader + pVideoHeader->nVideoHeaderSize;
        }
        else
        {
            pAddress = (char*)pStreamHeader + sizeof(STREAM_HEADER);
        }

        for ( i = 0; i <= nIndex; ++i )
        {
            pSegment  = (PSTREAM_SEGMENT_HEADER)pAddress;
            pAddress += pSegment->nSegmentSize;     //下一段的首地址
        }

        return pSegment;
    }

    return 0;
}
*/
////////////////////////////////////////////////////////////////////////////////
// 函数名：Stream_GetEncodeDataAddress
// 描述：获取编码数据的地址。
// 参数：
//  [in]pStreamHeader - STREAM_HEADER结构体地址，不能为NULL。
// 返回值：
//  返回编码数据的地址。
// 说明：
////////////////////////////////////////////////////////////////////////////////
/*
static void* Stream_GetEncodeDataAddress( const STREAM_HEADER* pStreamHeader )
{
    return (void*)((char*)pStreamHeader + pStreamHeader->nHeaderSize);
}
*/

////////////////////////////////////////////////////////////////////////////////
// 函数名：Stream_GenerateChecksum
// 描述：产生一帧数据的校验和。
// 参数：
//  [in]pStreamHeader - STREAM_HEADER结构体地址，不能为NULL。
//  [in]pDataBuffer - 编码数据的地址，不能为NULL。
//  [in]nEncodeDataSize - 编码数据的长度，以字节为单位。
// 返回值：
//  返回0失败，返回非0值是合法的校验和。
// 说明：
//  校验和是一个24位的无符号整数。
////////////////////////////////////////////////////////////////////////////////
static inline  unsigned int Stream_GenerateChecksum( const STREAM_HEADER* pStreamHeader, 
    const void* pDataBuffer, unsigned int nEncodeDataSize )
{
    const unsigned char* pValue;
    unsigned int nLength, i, nChecksum;

    if ( pStreamHeader->nEncodeDataSize != nEncodeDataSize )
    {
        return 0;
    }

    //从0开始累加校验和。
    //该校验和的算法复杂性很低，只能较低强度验证数据的正确性。
    nChecksum = 0;

    //计算STREAM_VIDEO_HEADER和STREAM_HEADER_SEGMENT[0 : n-1]的校验和。
    if ( pStreamHeader->nHeaderSize > sizeof(STREAM_HEADER) )
    {
        pValue = (const unsigned char*)pStreamHeader + sizeof(STREAM_HEADER);
        nLength = pStreamHeader->nHeaderSize - sizeof(STREAM_HEADER);
        for ( i = 0; i < nLength; ++i )
        {
            nChecksum += pValue[i];
        }
    }

    //计算编码数据的校验和。
    nLength = pStreamHeader->nCheckedEncodeDataSize;
    if ( nLength * 2 <= nEncodeDataSize )
    {
        //前一部分。
        pValue = (const unsigned char*)pDataBuffer;
        for ( i = 0; i < nLength; ++i )
        {
            nChecksum += pValue[i];
        }

        //后一部分。
        pValue = (const unsigned char*)pDataBuffer + (nEncodeDataSize - nLength);
        for ( i = 0; i < nLength; ++i )
        {
            nChecksum += pValue[i];
        }
    }

    nChecksum &= 0x00FFFFFF;                        //校验和低24位有效
    nChecksum |= 0x00800000;                        //保证校验和不为0

    return nChecksum;
}


////////////////////////////////////////////////////////////////////////////////
// 函数名：Stream_IsValidFrame
// 描述：判断是否是完整的帧。
// 参数：
//  [in]pBuffer - 缓冲区地址，不能为NULL。
//  [in]nBufferSize - 缓冲区的长度，以字节为单位。
// 返回值：
//  返回0是非法的帧，返回非0是合法的帧。
// 说明：
////////////////////////////////////////////////////////////////////////////////
/*
static int Stream_IsValidFrame( const void* pBuffer, unsigned int nBufferSize )
{
    const STREAM_HEADER* pStreamHeader = (const STREAM_HEADER*)pBuffer;
    return ( Stream_IsHeaderFlag( pBuffer )
        && pStreamHeader->nHeaderSize + pStreamHeader->nEncodeDataSize <= nBufferSize
        && (Stream_IsVideoFrame( pStreamHeader ) || Stream_IsAudioFrame( pStreamHeader ))
        && pStreamHeader->nEncodeDataSize > 0       //必须有编码数据
        && 0 != pStreamHeader->nChecksum            //不能为0
        && Stream_GenerateChecksum( pStreamHeader, 
            Stream_GetEncodeDataAddress( pStreamHeader ), 
            pStreamHeader->nEncodeDataSize ) == pStreamHeader->nChecksum );
}
*/

#ifdef __cplusplus
}
#endif

#endif  // HB_STREAM_HEADER_H
