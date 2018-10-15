/*
 * my_iptable.c
 *
 *  Created on: 2014年11月28日
 *      Author: root
 */
#include "my_include.h"
#include "md5gen.h"
#include "xml_app.h"
#include "hf_plant_api.h"
#include "tcp_opt.h"
#include "common.h"

#include "upload_pic.h"

pthread_mutex_t mutex_send_pic = PTHREAD_MUTEX_INITIALIZER;

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


static int read_pic(char *pSavePicBuf, int iSavePicBufSize)
{
	FILE *fp = NULL;
	int total_len = 0;

	printf("%s\n",ALARM_PHOTO_PATH);
	fp=fopen(ALARM_PHOTO_PATH,"rb");
	total_len=fread(pSavePicBuf, 1, iSavePicBufSize, fp);
	fclose(fp);
	fp = NULL;

	return total_len; //返回总大小
}

HB_S32 upload_picture_xml_cb(xmlDoc *doc, void *param, HB_CHAR *tags, HB_CHAR *values)
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
			dev_info.upload_pic_success_flag = 1;
			sensor_info.alarm_pic_upload_count++;
		}
		else if ((atoi(values) == -401) || (atoi(values) == -403))
		{
			//重新获取令牌
			elevator_get_token(NULL);
		}
		else
		{
			dev_info.upload_pic_success_flag = 0;
		}
	}

	return 1;
}


static HB_S32 elevator_upload_pic(char *pPicBase64, unsigned long long get_pic_time)
{
	HB_S32 ret = 0;
	HB_S32 sockfd = -1;

	ret = create_socket_connect_domain(&sockfd, PT_ADDR_IP, PT_PORT, 5);
	if(ret != HB_SUCCESS)
	{
		TRACE_ERR("\n########  (get IP token)The HB_BOX connect HbServer failed !!!\n");
		return HB_FAILURE;
	}

	struct timeval tv;
	HB_U64 lluTimeNow;
	HB_CHAR url[512] = {0};
	HB_CHAR cSendRecvString[104800] = {0};
	HB_CHAR cBodyBuf[102400] = {0};
	HB_CHAR cSign[64] = {0};
	xmlDoc *doc;
	HB_CHAR *point = NULL;

	gettimeofday(&tv, NULL);
	//由于DVR的NTP校时时会把北京时间校为UTC时间，所以要取格林威治时间需要在此时间上减去8小时的秒数，28800000为8小时的毫秒数
	lluTimeNow = (HB_U64)tv.tv_sec*1000 + tv.tv_usec/1000 - 28800000;//取毫秒值
	snprintf(cBodyBuf, sizeof(cBodyBuf), \
		"<?xml version=\"1.0\" encoding=\"utf-8\"?>\r\n\r\n<root>\r\n<access_token>%s</access_token>\r\n<stamp>%llu</stamp>\r\n<datas>\r\n<sn>%s</sn>\r\n<acquisitionTime>%llu</acquisitionTime>\r\n<fileStr>%s</fileStr>\r\n<fileExt>.jpg</fileExt>\r\n<attribute></attribute>\r\n</datas>\r\n</root>\r\n", \
		dev_info.access_token, lluTimeNow, dev_info.mac, get_pic_time, pPicBase64);
	//计算MD5值
	calculate_md5(cSign, cBodyBuf);
	//拼接发送字符串
	snprintf(url, sizeof(url), "/OPEN_UNION/4QAEAAABAB4/IOT_upload_img/?app_id=OPEN_BASE_APP&sign=%s", cSign);
	snprintf(cSendRecvString, sizeof(cSendRecvString), "POST %s HTTP/1.1\r\nHost:%s:8088\r\ncontent-type: text/plain; charset=utf-8\r\nContent-Length: %d\r\nConnection:keep-alive\r\n\r\n%s",
			url, PT_ADDR_IP, strlen(cBodyBuf), cBodyBuf);

	if(send_data(&sockfd, cSendRecvString, strlen(cSendRecvString), 10, 0) < 0)
	{
	   return -1;
	}
	printf("\n###### api_get_token() send: %s\n",cSendRecvString);
//	printf("\n###### api_get_token() url: %s\n", url);
	memset(cSendRecvString, 0, sizeof(cSendRecvString));
	if(recv_data(&sockfd ,cSendRecvString, sizeof(cSendRecvString), 10) < 0)
	{
		printf("%s:%d:recv from http server failed!\n", __FILE__, __LINE__);
		return -1;
	}
	printf("\n######## api_get_token() recv: %s\n",cSendRecvString);
	if((point = strstr(cSendRecvString,"<?xml")) != NULL)
	{
		doc = File2MemxmlParseToDoc(point, &sockfd, upload_picture_xml_cb);
		xmlFreeDoc(doc);
	}
	close(sockfd);
	sockfd = -1;

    return HB_SUCCESS;
}

#if 0
void *thread_send_signal_to_http(void *arg)
{
	pthread_detach(pthread_self());

	HB_S32 ret = 0;
	HB_S32 sockfd = -1;
	HB_CHAR send_buff[1024] = {0};

	ret = create_socket_connect_domain(&sockfd, PT_Alarm_ADDR_IP, PT_Alarm_PORT, 5);
	if(ret != HB_SUCCESS)
	{
		TRACE_ERR("\n########  (get IP token)The HB_BOX connect Server failed !!!\n");
		pthread_exit(NULL);
	}

    sprintf(send_buff, "GET /mobile/alarmFromScreen?liftId=%s HTTP/1.1\r\nHost:%s:%d\r\nConnection:keep-alive\r\nAccept:text/html,application/xhtml+xml,application/xml;q=0.9,image/webp,*/*;q=0.8\r\nUpgrade-Insecure-Requests:1\r\nUser-Agent:Mozilla/5.0\r\nAccept-Encoding:gzip,deflate,sdch\r\nAccept-Language:zh-CN,zh;q=0.8\r\n\r\n",
    		elevator_properties.elevator_id,PT_Alarm_ADDR_IP, PT_Alarm_PORT);

//    sprintf(send_buff, "GET /mobile/alarmFromScreen?liftId=%s HTTP/1.1\r\nHost:%s:%d\r\nConnection:keep-alive\r\nAccept:text/html,application/xhtml+xml,application/xml;q=0.9,image/webp,*/*;q=0.8\r\nUpgrade-Insecure-Requests:1\r\nUser-Agent:Mozilla/5.0\r\nAccept-Encoding:gzip,deflate,sdch\r\nAccept-Language:zh-CN,zh;q=0.8\r\n\r\n",
//    		dev_info.sn, PT_Alarm_ADDR_IP, PT_Alarm_PORT);

	if(send_data(&sockfd, send_buff, strlen(send_buff), 10, 0) < 0)
	{
		printf("Send to http failed!\n");
		pthread_exit(NULL);
	}
	printf("\n###### send_signal() send: %s\n",send_buff);
	memset(send_buff, 0, sizeof(send_buff));
	if(recv_data(&sockfd ,send_buff, sizeof(send_buff), 10) < 0)
	{
		printf("%s:%d:recv from http server failed!\n", __FILE__, __LINE__);
		pthread_exit(NULL);
	}
	printf("\n######## send_signal() recv: %s\n",send_buff);
	close(sockfd);
	sockfd = -1;
	pthread_exit(NULL);
}
#endif


void *thread_upload_picture(void *arg)
{
	pthread_detach(pthread_self());
	int fail_times = 0;
	int pic_size = 0;
	struct timeval tv;
	unsigned long long get_pic_time = 0;
	char arrc_PictureBuf[PIC_MAX_SIZE] = {0};
	char arrc_PictureBufBase64[PIC_MAX_SIZE*3] = {0};

	while(1)
	{
		system(GET_PICTURE);
		if (access(ALARM_PHOTO_PATH, 0) < 0)//文件不存在
		{
			fail_times++;
			if (fail_times>=MAX_ERR_TIMES)
			{
				printf("get picture failed!\n");
				pthread_exit(NULL);
			}
		}
		else
		{
			gettimeofday(&tv,NULL);
			//由于DVR的NTP校时时会把北京时间校为UTC时间，所以要取格林威治时间需要在此时间上减去8小时的秒数，28800000为8小时的毫秒数
			get_pic_time = (unsigned long long)tv.tv_sec*1000 + tv.tv_usec/1000 - 28800000;//取毫秒值
			break;
		}
	}
#if 1
	pic_size = read_pic(arrc_PictureBuf, PIC_MAX_SIZE); //读取图片
	base64_encode(arrc_PictureBuf, arrc_PictureBufBase64, pic_size);//base64编码

	while(1)
	{
		pthread_mutex_lock(&mutex_send_pic);
		elevator_upload_pic(arrc_PictureBufBase64, get_pic_time);//报警图片上传
		pthread_mutex_unlock(&mutex_send_pic);
		if (dev_info.upload_pic_success_flag == 0)
		{
			//上传失败
			fail_times++;
			if (fail_times>=MAX_ERR_TIMES)
			{
				TRACE_ERR("picture upload failed!\n");
				pthread_exit(NULL);
			}
			sleep(3);
			continue;
		}
		else
		{
			dev_info.upload_pic_success_flag = 0;//清除标识
			break;
		}
	}
#endif
	printf("upload thread exit!\n");
	pthread_exit(NULL);
}
