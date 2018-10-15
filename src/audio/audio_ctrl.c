/*
 * audio_ctrl.c
 *
 *  Created on: 2018年9月5日
 *      Author: lijian
 */


#include "my_include.h"
#include "md5gen.h"
#include "xml_app.h"
#include "hf_plant_api.h"
#include "tcp_opt.h"
#include "common.h"
#include "audio_ctrl.h"
#include "simclist.h"


list_t listAudioList;
pthread_mutex_t lockAudioListMutexLock = PTHREAD_MUTEX_INITIALIZER;//音频链表锁
pthread_mutex_t mutex_send_audio = PTHREAD_MUTEX_INITIALIZER;//音频上传锁
//=============================================================//
//音频上传
//=============================================================//
static char * base64_encode( const char * bindata, char * base64, int binlength)
{
    int i, j;
    unsigned char current;
    const char * base64char = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

    for ( i = 0, j = 0 ; i < binlength ; i += 3 )
    {
        current = (bindata[i] >> 2) ;
        current &= (unsigned char)0x3F;
        base64[j++] = base64char[(int)current];

        current = ( (unsigned char)(bindata[i] << 4 ) ) & ( (unsigned char)0x30 ) ;
        if ( i + 1 >= binlength )
        {
            base64[j++] = base64char[(int)current];
            base64[j++] = '=';
            base64[j++] = '=';
            break;
        }
        current |= ( (unsigned char)(bindata[i+1] >> 4) ) & ( (unsigned char) 0x0F );
        base64[j++] = base64char[(int)current];

        current = ( (unsigned char)(bindata[i+1] << 2) ) & ( (unsigned char)0x3C ) ;
        if ( i + 2 >= binlength )
        {
            base64[j++] = base64char[(int)current];
            base64[j++] = '=';
            break;
        }
        current |= ( (unsigned char)(bindata[i+2] >> 6) ) & ( (unsigned char) 0x03 );
        base64[j++] = base64char[(int)current];

        current = ( (unsigned char)bindata[i+2] ) & ( (unsigned char)0x3F ) ;
        base64[j++] = base64char[(int)current];
    }
    base64[j] = '\0';
    return base64;
}

static HB_S32 get_audio_file(HB_CHAR *pAudioFileName, HB_CHAR *pSaveAudioBuf, HB_S32 iSaveAudioBufSize)
{
	FILE *pAudioFp = NULL;
	HB_S32 iTotalLen = 0;//获取到的文件长度

	printf("%s\n",pAudioFileName);
	pAudioFp=fopen(pAudioFileName,"rb");
	if (NULL == pAudioFp)
	{
		TRACE_ERR("Open %s failed!\n", pAudioFileName);
		return -1;
	}
	iTotalLen=fread(pSaveAudioBuf, 1, iSaveAudioBufSize, pAudioFp);
	fclose(pAudioFp);
	pAudioFp = NULL;

	return iTotalLen; //返回总大小
}

HB_S32 upload_audio_xml_cb(xmlDoc *doc, void *param, HB_CHAR *tags, HB_CHAR *values)
{
    printf("%s:tags:%s\t\t\t\tvalues:%s\n",__FUNCTION__, tags, values);
    if(doc == NULL || param == NULL || tags == NULL || values == NULL)
    {
    	assert(0);
    	return 0;
    }

	if(strstr(tags, "code") != NULL)
	{
		if(atoi(values) == 0)
		{
			//上传成功
			dev_info.iUploadAudioSuccessFlag = 1;
		}
		else if ((atoi(values) == -401) || (atoi(values) == -403))
		{
			//重新获取令牌
			elevator_get_token(NULL);
		}
		else
		{
			dev_info.iUploadAudioSuccessFlag = 0;
		}
	}

	return 1;
}

static HB_S32 elevator_upload_audio(char *pAudioBase64, HB_U64 lluAudioRecordTime)
{
	HB_S32 ret = 0;
	HB_S32 sockfd = -1;
	static HB_CHAR cElevatorServerIp[16] = {0};

	if (strlen(cElevatorServerIp) == 0)
	{
	   if(from_domain_to_ip(cElevatorServerIp, PT_ADDR_IP, 5) < 0)
	    {
		   memset(cElevatorServerIp, 0, sizeof(cElevatorServerIp));
	    	return HB_FAILURE;
	    }
//		ret = create_socket_connect_domain(&sockfd, PT_ADDR_IP, PT_PORT, 5);
//		if(ret != HB_SUCCESS)
//		{
//			TRACE_ERR("\n########  (get IP token)The HB_BOX connect HbServer failed !!!\n");
//			return HB_FAILURE;
//		}
	}

	printf("#######################3connect to server ip [%s]:[%d]\n", cElevatorServerIp, PT_PORT);
	ret = create_socket_connect_ipaddr(&sockfd, cElevatorServerIp, PT_PORT, 5);
	if(ret != HB_SUCCESS)
	{
		memset(cElevatorServerIp, 0, sizeof(cElevatorServerIp));
		TRACE_ERR("\n########  (get IP token)The HB_BOX connect HbServer failed !!!\n");
		return HB_FAILURE;
	}

	struct timeval tv;
	HB_U64 lluTimeNow; //音频文件上传时间
	HB_CHAR url[512] = {0};
	HB_CHAR cSendRecvString[AUDIO_MAX_SIZE*2] = {0};
	HB_CHAR cBodyBuf[AUDIO_MAX_SIZE*2] = {0};
	HB_CHAR cSign[64] = {0};
	xmlDoc *doc;
	HB_CHAR *point = NULL;

	gettimeofday(&tv, NULL);
	//由于DVR的NTP校时时会把北京时间校为UTC时间，所以要取格林威治时间需要在此时间上减去8小时的秒数，28800000为8小时的毫秒数
	lluTimeNow = (HB_U64)tv.tv_sec*1000 + tv.tv_usec/1000 - 28800000;//取毫秒值
	snprintf(cBodyBuf, sizeof(cBodyBuf), \
		"<?xml version=\"1.0\" encoding=\"utf-8\"?>\r\n\r\n<root>\r\n<access_token>%s</access_token>\r\n<stamp>%llu</stamp>\r\n<datas>\r\n<sn>%s</sn>\r\n<acquisitionTime>%llu</acquisitionTime>\r\n<fileStr>%s</fileStr>\r\n<fileExt>.g711a</fileExt>\r\n<attribute></attribute>\r\n</datas>\r\n</root>\r\n", \
		dev_info.access_token, lluTimeNow, dev_info.mac, lluAudioRecordTime, pAudioBase64);
	//计算MD5值
	calculate_md5(cSign, cBodyBuf);
	//拼接发送字符串
	snprintf(url, sizeof(url), "/OPEN_UNION/4QAEAAABAB4/IOT_upload_audio/?app_id=OPEN_BASE_APP&sign=%s", cSign);
	snprintf(cSendRecvString, sizeof(cSendRecvString), "POST %s HTTP/1.1\r\nHost:%s:8088\r\ncontent-type: text/plain; charset=utf-8\r\nContent-Length: %d\r\nConnection:keep-alive\r\n\r\n%s",
			url, PT_ADDR_IP, strlen(cBodyBuf), cBodyBuf);

	if(send_data(&sockfd, cSendRecvString, strlen(cSendRecvString), 10, 0) < 0)
	{
	   return -1;
	}
//	printf("\n###### api_get_token() send: %s\n",cSendRecvString);
	printf("\n###### api_get_token() url: %s\n", url);
	memset(cSendRecvString, 0, sizeof(cSendRecvString));
	if(recv_data(&sockfd ,cSendRecvString, sizeof(cSendRecvString), 10) < 0)
	{
		printf("%s:%d:recv from http server failed!\n", __FILE__, __LINE__);
		return -1;
	}
	printf("\n######## api_get_token() recv: %s\n",cSendRecvString);
	if((point = strstr(cSendRecvString,"<?xml")) != NULL)
	{
		doc = File2MemxmlParseToDoc(point, &sockfd, upload_audio_xml_cb);
		xmlFreeDoc(doc);
	}
	close(sockfd);
	sockfd = -1;

    return HB_SUCCESS;
}

static HB_VOID *thread_upload_audio(HB_HANDLE hArg)
{
	pthread_detach(pthread_self());
	AUDIO_INFO_HANDLE pAudioFile = (AUDIO_INFO_HANDLE)hArg;
	HB_S32 iUploadFailTimes = 0; //上传失败次数
	HB_S32 iAudioSize = 0;

	pthread_mutex_lock(&mutex_send_audio);
	HB_CHAR cAudioBuf[AUDIO_MAX_SIZE] = {0};
	HB_CHAR cAudioBufBase64[AUDIO_MAX_SIZE*2] = {0};

	iAudioSize = get_audio_file(pAudioFile->cAudioName, cAudioBuf, AUDIO_MAX_SIZE); //读取音频文件
	if(iAudioSize < 0)
	{
		pthread_mutex_unlock(&mutex_send_audio);
		pthread_exit(NULL);
	}

	base64_encode(cAudioBuf, cAudioBufBase64, iAudioSize);//base64编码

	while(1)
	{
		elevator_upload_audio(cAudioBufBase64, pAudioFile->lluRecordTime);//音频文件上传
		if (dev_info.iUploadAudioSuccessFlag == 0)
		{
			//上传失败
			iUploadFailTimes++;
			if (iUploadFailTimes>=MAX_ERR_TIMES)
			{
				pthread_mutex_lock(&lockAudioListMutexLock);
				//失败次数过多，删除本地文件
				HB_CHAR cCmd[256] = {0};
				snprintf(cCmd, sizeof(cCmd), "rm -rf %s", pAudioFile->cAudioName);
				system(cCmd);
				list_delete(&listAudioList, pAudioFile);
				free(pAudioFile);
				pAudioFile = NULL;
				pthread_mutex_unlock(&lockAudioListMutexLock);

				pthread_mutex_unlock(&mutex_send_audio);
				TRACE_ERR("picture upload failed!\n");
				pthread_exit(NULL);
			}
			sleep(3);
			continue;
		}
		else
		{
			pthread_mutex_lock(&lockAudioListMutexLock);
			printf("-----------------------send audio file success, delete audio file[%s]!\n", pAudioFile->cAudioName);
			//上传成功，删除本地文件
			HB_CHAR cCmd[256] = {0};
			snprintf(cCmd, sizeof(cCmd), "rm -rf %s", pAudioFile->cAudioName);
			system(cCmd);
			list_delete(&listAudioList, pAudioFile);
			free(pAudioFile);
			pAudioFile = NULL;
			pthread_mutex_unlock(&lockAudioListMutexLock);
			dev_info.iUploadAudioSuccessFlag = 0;//清除标识
			break;
		}
	}
	pthread_mutex_unlock(&mutex_send_audio);
	printf("upload audio thread exit!\n");
	pthread_exit(NULL);
}


//=============================================================//
//音频采集
//=============================================================//
HB_S32 open_audio()
{
	HB_S32 iRet = 0;
	iRet = hb_ipc_login("admin", "888888", "127.0.0.1", 8101);
	if (1 != iRet)
	{
		iRet = hb_ipc_login("admin", dev_info.sn, "127.0.0.1", 8101);
		if (1 != iRet)
		{
			printf("\n######### Login IPC FAILED!\n");
			return -1;
		}
	}

	//初始化音频链表
	list_init(&listAudioList);

	return 0;
}

static HB_VOID *hb_get_audio_frame_cb(HB_CHAR * pdata, HB_U32 len, HB_S32 type, HB_VOID *paramin)
{
	//G711A
	static HB_S32 iAudioFd = -1;
	HB_S64 llCurTime = time(NULL);//当前时间
	static HB_S64 llLastTime = 0;//上一次的时间
	static HB_U64 lluRecordTime = 0;//音频记录时间
	static HB_CHAR cAudioName[32] = {0};

	if (-1 == iAudioFd)
	{
		struct timeval tv;
		gettimeofday(&tv,NULL);
		//由于DVR的NTP校时时会把北京时间校为UTC时间，所以要取格林威治时间需要在此时间上减去8小时的秒数，28800000为8小时的毫秒数
		lluRecordTime = (HB_U64)tv.tv_sec*1000 + tv.tv_usec/1000 - 28800000;//取毫秒值

		llLastTime = llCurTime;
		memset(cAudioName, 0, sizeof(cAudioName));
		snprintf(cAudioName, sizeof(cAudioName), "%lld.g711a", llCurTime);
		iAudioFd = open(cAudioName, O_WRONLY | O_CREAT, 0777);
		if (-1 == iAudioFd)
		{
			return NULL;
		}
	}

	write(iAudioFd, pdata, len);

	if ((llCurTime - llLastTime) >= AUDIO_RECORD_TIME)
	{
		printf("+++++++++++++++record OK save audio file[%s]!\n", cAudioName);
		//每30秒存储于一个文件
		close(iAudioFd);
		iAudioFd = -1;

		AUDIO_INFO_HANDLE pAudioFile = calloc(1, sizeof(AUDIO_INFO_OBJ));
		strncpy(pAudioFile->cAudioName, cAudioName, sizeof(pAudioFile->cAudioName));
		pAudioFile->lluRecordTime = lluRecordTime;

		if (0 != pthread_mutex_trylock(&lockAudioListMutexLock))
		{
			//上锁失败，说明正在上传音频,直接插在链表尾
			list_append(&listAudioList, pAudioFile);
			printf("audio file count = %d\n", list_size(&listAudioList));
			return NULL;
		}

		while(list_size(&listAudioList) >= MAX_AUDIO_FILE_COUNT)
		{
			//如果超出了最大存储个数，尾插头删
			AUDIO_INFO_HANDLE pAudioFile = list_get_at(&listAudioList, 0);
			HB_CHAR cCmd[256] = {0};
			snprintf(cCmd, sizeof(cCmd), "rm -rf %s", pAudioFile->cAudioName);
			system(cCmd);
			list_delete_at(&listAudioList, 0);
			free(pAudioFile);
			pAudioFile = NULL;

			printf("delete audio file\n");
		}

		//插入链表尾端
		list_append(&listAudioList, pAudioFile);

		pthread_mutex_unlock(&lockAudioListMutexLock);
	}

	return NULL;
}

static HB_VOID *thread_get_audio_file_and_send(HB_HANDLE hArg)
{
	pthread_detach(pthread_self());

	for(;;)
	{
		sleep(AUDIO_SCAN_TIME);

		if (0 != pthread_mutex_trylock(&lockAudioListMutexLock))
		{
			usleep(1000);
			continue;
		}

		HB_S32 iAudioFileCount = list_size(&listAudioList);
		for(;iAudioFileCount;)
		{
			AUDIO_INFO_HANDLE pAudioFile = list_get_at(&listAudioList, 0);
			//在此处发送到云端
			pthread_t threadSendAudioFileId = -1;
			pthread_create(&threadSendAudioFileId, NULL, thread_upload_audio, (HB_VOID *)pAudioFile);
//			HB_CHAR cCmd[256] = {0};
//			snprintf(cCmd, sizeof(cCmd), "rm -rf %s", pAudioFile->cAudioName);
//			system(cCmd);
//
//			list_delete_at(&listAudioList, 0);
//			printf("-----------------------send audio file success, delete audio file[%s]!\n", pAudioFile->cAudioName);
//
//			free(pAudioFile);
//			pAudioFile = NULL;

			iAudioFileCount--;
		}
		pthread_mutex_unlock(&lockAudioListMutexLock);
	}

	return NULL;
}

HB_S32 read_audio()
{
	pthread_t threadSendAudioFileId = -1;
	//设置对讲的回调函数
	hb_ipc_opentalkcb(hb_get_audio_frame_cb, 1);

	pthread_create(&threadSendAudioFileId, NULL, thread_get_audio_file_and_send, NULL);

	usleep(100);//等待线程启动完毕

	return 0;
}

HB_S32 close_audio()
{
	printf("calling close audio!\n");

	hb_ipc_stoptalkcb();
	hb_ipc_logout();

	HB_S32 iAudioFileCount = list_size(&listAudioList);
	for(;iAudioFileCount;)
	{
		AUDIO_INFO_HANDLE pAudioFile = list_get_at(&listAudioList, 0);
		HB_CHAR cCmd[256] = {0};

		snprintf(cCmd, sizeof(cCmd), "rm -rf %s", pAudioFile->cAudioName);
		system(cCmd);
		pthread_mutex_lock(&lockAudioListMutexLock);
		list_delete_at(&listAudioList, 0);
		pthread_mutex_unlock(&lockAudioListMutexLock);

		printf("send audio file success, delete it[%s]!\n", pAudioFile->cAudioName);
		free(pAudioFile);
		pAudioFile = NULL;

		iAudioFileCount--;
	}

	list_destroy(&listAudioList);

	return 0;
}



HB_VOID *thread_start_audio_moudle(HB_HANDLE hArg)
{
	system("rm ./*.g711a");

	if (open_audio() < 0)
	{
		printf("open audio failed!\n");
		return NULL;
	}

	read_audio();

	pause();
	close_audio();

	return NULL;
}


