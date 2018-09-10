/*
 * audio_ctrl.h
 *
 *  Created on: 2018年9月5日
 *      Author: lijian
 */

#ifndef AUDIO_CTRL_H_
#define AUDIO_CTRL_H_

#include "./inc/sysapi/sys_api.h"
#include "./inc/hbnet/hbdvrnet.h"
#include "simclist.h"

#define AUDIO_RECORD_TIME		(30) //录音时间
#define AUDIO_SCAN_TIME		(AUDIO_RECORD_TIME-7) //录音链表扫描时间
#define MAX_AUDIO_FILE_COUNT	(20)	//最多存储音频文件的个数

typedef struct _AUDIO_INFO
{
	HB_CHAR cAudioName[128];
	HB_U64	lluRecordTime;
}AUDIO_INFO_OBJ, *AUDIO_INFO_HANDLE;

HB_S32 open_audio();
HB_S32 read_audio();
HB_S32 close_audio();



#endif /* AUDIO_CTRL_H_ */
