/*
 * common.c
 *
 *  Created on: 2017年7月13日
 *      Author: root
 */

#include "common.h"
#include "cJSON.h"
#include "hf_plant_api.h"
#include "xml_app.h"
#include "udp_opt.h"
#include "tcp_opt.h"

extern UDP_HEADER stSensorHeader; //传感器头结构体

/****************************************
 * Function: 解析json串
 * @param pSrcJson: [IN]原始json串
 * @param pKey: [IN] 需要查找的key
 * @param pValue: [OUT] 存储找到的key的结果
 * @param iValueSize: [IN] pValue的大小
 *
 * @return : 成功返回0
 ****************************************/
int analysis_json(char *pSrcJson, char *pKey, char *pValue, int iValueSize)
{
	cJSON *p_json = cJSON_Parse(pSrcJson);
	if (NULL == p_json)
	{
		return -1;
	}
	cJSON *p_sub = cJSON_GetObjectItem(p_json, pKey);
	if (NULL == p_sub)
	{
		cJSON_Delete(p_json);
		return -1;
	}
	strncpy(pValue, p_sub->valuestring, iValueSize);

	cJSON_Delete(p_json);
	return 0;
}



static HB_S32 fn_get_token_fun(xmlDoc *doc, void *param, HB_CHAR *tags, HB_CHAR *values)
{
    static HB_S32 ifcheck_behind = 0;
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
		    ifcheck_behind = 1;
		}
		else
		{
			dev_info.return_token = 0; //获取令牌失败
		}
	}
	if(ifcheck_behind == 1)
	{
		if(strstr(tags, "access_token") != NULL)
		{
			dev_info.return_token = 1;//获取令牌成功
		    strcpy(dev_info.access_token, values);
		    printf("recv token [%s]\n", dev_info.access_token);
		}
		else if(strstr(tags, "sessionId") != NULL)
		{
		    strcpy(dev_info.sessionId, values);
#ifdef SYSTEM_32BITS
		    stSensorHeader.lSessionId = atoll(dev_info.sessionId);//会话id
#else
		    stSensorHeader.lSessionId = atol(dev_info.sessionId);//会话id
#endif
		}
		else if (strstr(tags, "elevatorId") != NULL)
		{
			strncpy(elevator_properties.elevator_id, values, sizeof(elevator_properties.elevator_id));
		}
		else if (strstr(tags, "address") != NULL)
		{
			strncpy(elevator_properties.elevator_addr, values, sizeof(elevator_properties.elevator_addr));
		}
		else if (strstr(tags, "simId") != NULL)
		{
			strncpy(elevator_properties.elevator_sim, values, sizeof(elevator_properties.elevator_sim));
		}
	}

	return 1;
}


HB_S32 api_get_token(HB_S32 *sockfd, HB_CHAR *buff, HB_S32 size)
{
	struct timeval tv;
	unsigned long long time_now;
//	HB_CHAR arrcElevatorCode[32] = {0};
	HB_CHAR mac_sn[32] = { 0 };
	HB_CHAR url_base[512] = { 0 };
	HB_CHAR url[512] = { 0 };
	HB_CHAR buf_body[1024] = { 0 };
	HB_CHAR desc[64];
	xmlDoc *doc;
	HB_CHAR *point = NULL;
	if (*sockfd <= 0 || buff == NULL || size == 0)
	{
		assert(0);
		return -1;
	}

	strncpy(url_base, "/OPEN_UNION/4QAEAAABAB4/IOT_GetAccessToken/?app_id=OPEN_BASE_APP", sizeof(url_base));

	get_sys_mac(mac_sn, sizeof(mac_sn));

	gettimeofday(&tv, NULL);
//	time_now = (unsigned long long)tv.tv_sec*1000 + tv.tv_usec/1000;//取毫秒值
	//由于DVR的NTP校时时会把北京时间校为UTC时间，所以要取格林威治时间需要在此时间上减去8小时的秒数，28800000为8小时的毫秒数
	time_now = (unsigned long long) tv.tv_sec * 1000 + tv.tv_usec / 1000 - 28800000;	//取毫秒值

	//获取电梯编号
//	GetIniKeyString(NULL, "elevator_code", arrcElevatorCode, ELEVATOR_CONFIG);

	snprintf(buf_body, sizeof(buf_body),
					"<?xml version=\"1.0\" encoding=\"utf-8\"?>\r\n\r\n<root>\r\n<access_token></access_token>\r\n<stamp>%llu</stamp>\r\n<datas>\r\n<sn>%s</sn>\r\n<elevatorId>%s</elevatorId>\r\n</datas>\r\n</root>\r\n",
					time_now, mac_sn, elevator_properties.elevator_id);
	//计算MD5值
	calculate_md5(desc, buf_body);
	//拼接发送字符串
	snprintf(url, sizeof(url), "%s&sign=%s", url_base, desc);

	sprintf(buff,
					"POST %s HTTP/1.1\r\nHost:%s:8088\r\ncontent-type: text/plain; charset=utf-8\r\nContent-Length: %d\r\nConnection:keep-alive\r\n\r\n%s",
					url, PT_ADDR_IP, strlen(buf_body), buf_body);

	if (send_data(sockfd, buff, strlen(buff), 5, 0) < 0)
	{
		return -1;
	}
	printf("\n###### api_get_token() send: %s\n", buff);
	memset(buff, 0, size);
	if (recv_data(sockfd, buff, size, 10) < 0)
	{
		return -1;
	}
	printf("\n######## api_get_token() recv: %s\n", buff);
	if ((point = strstr(buff, "<?xml")) != NULL)
	{
		doc = File2MemxmlParseToDoc(point, &sockfd, fn_get_token_fun);
		xmlFreeDoc(doc);
	}
	else
	{
		return -1;
	}
	return 1;
}

//获取token
HB_VOID *elevator_get_token(HB_HANDLE arg)
{
	HB_S32 ret = 0;
	HB_S32 sockfd = -1;
	HB_CHAR buff[1024] = { 0 };

	while (1)
	{
		ret = create_socket_connect_domain(&sockfd, PT_ADDR_IP, PT_PORT, 5);
		if (ret != HB_SUCCESS)
		{
			TRACE_ERR("\n########  (get IP token)The HB_BOX connect HbServer failed !!!\n");
			sleep(5);
			continue;
		}

		api_get_token(&sockfd, buff, sizeof(buff));	//从服务器获取令牌
		if (dev_info.return_token != 1)
		{
			//sleep_appoint_time(connect_faile_times++);
			TRACE_ERR("\n########  The HB_BOX get token failed !!!\n");
			close(sockfd);
			sockfd = -1;
			sleep(5);
			continue;
		}
		close(sockfd);
		sockfd = -1;
		break;
	}

	return NULL;
}

