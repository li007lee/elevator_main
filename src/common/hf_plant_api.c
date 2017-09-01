/* ========================================================================== */
/*                                                                            */
/*   Filename.c                                                               */
/*   (c) 2012 Author                                                          */
/*                                                                            */
/*   Description                                                              */
/*                                                                            */
/* ========================================================================== */

#include "my_include.h"
#include "xml_app.h"
#include "md5gen.h"
#include "hf_plant_api.h"
#include "tcp_opt.h"
#include "udp_opt.h"
#include "file_opt.h"

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
	HB_CHAR mac_sn[32] = {0};
	HB_CHAR url_base[512] = {0};
	HB_CHAR url[512] = {0};
	HB_CHAR buf_body[1024] = {0};
	HB_CHAR desc[64];
   	xmlDoc *doc;
    HB_CHAR *point = NULL;
    if(*sockfd <= 0 || buff == NULL || size == 0)
    {
    	assert(0);
    	return -1;
    }

    strncpy(url_base, "/OPEN_UNION/4QAEAAABAB4/IOT_GetAccessToken/?app_id=OPEN_BASE_APP", sizeof(url_base));

    get_sys_mac(mac_sn,sizeof(mac_sn));

	gettimeofday(&tv,NULL);
//	time_now = (unsigned long long)tv.tv_sec*1000 + tv.tv_usec/1000;//取毫秒值
	//由于DVR的NTP校时时会把北京时间校为UTC时间，所以要取格林威治时间需要在此时间上减去8小时的秒数，28800000为8小时的毫秒数
	time_now = (unsigned long long)tv.tv_sec*1000 + tv.tv_usec/1000 - 28800000;//取毫秒值

	//获取电梯编号
//	GetIniKeyString(NULL, "elevator_code", arrcElevatorCode, ELEVATOR_CONFIG);

    snprintf(buf_body, sizeof(buf_body), \
    	"<?xml version=\"1.0\" encoding=\"utf-8\"?>\r\n\r\n<root>\r\n<access_token></access_token>\r\n<stamp>%llu</stamp>\r\n<datas>\r\n<sn>%s</sn>\r\n<elevatorId>%s</elevatorId>\r\n</datas>\r\n</root>\r\n", \
		time_now, mac_sn, elevator_properties.elevator_id);
    //计算MD5值
    Calculate_MD5(desc, buf_body);
    //拼接发送字符串
    snprintf(url, sizeof(url), "%s&sign=%s", url_base, desc);

    sprintf(buff, "POST %s HTTP/1.1\r\nHost:%s:8088\r\ncontent-type: text/plain; charset=utf-8\r\nContent-Length: %d\r\nConnection:keep-alive\r\n\r\n%s",
    		url, PT_ADDR_IP, strlen(buf_body), buf_body);

    if(send_data(sockfd, buff, strlen(buff), 5, 0) < 0)
    {
       return -1;
    }
	printf("\n###### api_get_token() send: %s\n",buff);
	memset(buff, 0, size);
    if(recv_data(sockfd ,buff, size, 10) < 0)
    {
        return -1;
    }
	printf("\n######## api_get_token() recv: %s\n",buff);
    if((point = strstr(buff,"<?xml")) != NULL)
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


//计算MD5
int Calculate_MD5(char *desc, const char *src)
{
	char buf[102400] = {0};

	snprintf(buf, sizeof(buf), "%skWbe3Nah3hjNpNdcRwlPtg", src);
	md5_packages_string(desc, buf, strlen(buf));

	return 1;
}


//mac_sn 网卡序列号, dev 网卡名
static HB_S32 get_mac_dev(HB_CHAR *mac_sn, HB_CHAR *dev)
{
    struct ifreq tmp;
    HB_S32 sock_mac;
   // HB_CHAR *tmpflag;
    //HB_CHAR mac_addr[30];
    sock_mac = socket(AF_INET, SOCK_STREAM, 0);
    if( sock_mac == -1)
    {
        perror("### create socket fail\n");
        return -1;
    }
    memset(&tmp,0,sizeof(tmp));
    strncpy(tmp.ifr_name, dev, sizeof(tmp.ifr_name)-1);
    if( (ioctl( sock_mac, SIOCGIFHWADDR, &tmp)) < 0 )
    {
    	close(sock_mac);
    	TRACE_ERR("### mac ioctl error\n");
        return -1;
    }

    close(sock_mac);
    memcpy(mac_sn, tmp.ifr_hwaddr.sa_data, 6);

    return 0;
}


//获取MAC
int get_sys_mac(char *sn, int sn_size)
{
	HB_CHAR get_mac[32] = {0};
	get_mac_dev(get_mac, ETHX);

    sprintf(sn, "%02x%02x%02x%02x%02x%02x",
            (HB_U8)get_mac[0],
            (HB_U8)get_mac[1],
            (HB_U8)get_mac[2],
            (HB_U8)get_mac[3],
            (HB_U8)get_mac[4],
            (HB_U8)get_mac[5]
            );

    return 0;
}

//获取网卡序列号
int get_sys_sn(char *sn, int sn_size)
{
	HB_CHAR get_mac[32] = {0};
	get_mac_dev(get_mac, ETHX);

    sprintf(sn, "%02x%02x%02x%02x",
            (HB_U8)get_mac[2],
            (HB_U8)get_mac[3],
            (HB_U8)get_mac[4],
            (HB_U8)get_mac[5]
            );

    return 0;
}
