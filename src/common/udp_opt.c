/*
 * udp_opt.c
 *
 *  Created on: 2017年3月27日
 *      Author: root
 */
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <netdb.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <fcntl.h>

#include "udp_opt.h"
#include "my_include.h"

UDP_HEADER stSensorHeader; //传感器头结构体

int create_socket_and_connect_server(UDP_SERVER_INFO *stUdpServerInfo, char *pServerIp, int iServerPort)
{
	memset(stUdpServerInfo, 0, sizeof(UDP_SERVER_INFO));
    if(stUdpServerInfo->iSockFd <= 0)
    {
	    if((stUdpServerInfo->iSockFd = socket(AF_INET,SOCK_DGRAM,0)) < 0)
	    {
	    	fprintf(stderr,"Socket Error:%s\n",strerror(errno));
	        return -1;
	    }
    }

    //填充服务端的资料
	bzero(&(stUdpServerInfo->addr),sizeof(struct sockaddr_in));
	stUdpServerInfo->addr.sin_family=AF_INET;
	stUdpServerInfo->addr.sin_port=htons(iServerPort);
	stUdpServerInfo->sockaddr_in_len = sizeof(struct sockaddr_in);

	//inet_aton函数用于把字符串型的IP地址转化成网络2进制数字
    if (inet_aton(pServerIp,&(stUdpServerInfo->addr.sin_addr)) <= 0)
    {
        fprintf(stderr,"Ip error:%s\n",pServerIp);
        return -1;
    }

    //设置非阻塞
    int cur_flags = fcntl(stUdpServerInfo->iSockFd, F_GETFL, 0);
    fcntl(stUdpServerInfo->iSockFd, F_SETFL, cur_flags|O_NONBLOCK);

    //绑定网络地址和网络文件描述符
//    if(bind(stUdpServerInfo->iSockFd, (struct sockaddr*)&(stUdpServerInfo->addr), sizeof(struct sockaddr_in)) != 0)
//	{
//		close(stUdpServerInfo->iSockFd);
//		perror("bind");
//		return -1;
//    }

    return 0;
}

void set_header()
{
	memset(&stSensorHeader, 0, sizeof(UDP_HEADER));

	stSensorHeader.cCode = 0XE1;	//校验码，固定为0xE1
	stSensorHeader.cMessageType = 1;//消息类型，固定为1
	stSensorHeader.cEncode = 0; //编码类型，固定为0,UTF-8
	stSensorHeader.cEncrypt = 0;//加密方式，暂时填0
	stSensorHeader.cContextType = 9;//发送的消息的方式：0(XML) 1(JSON) 6(二进制) 9(char)
	stSensorHeader.cEndian = 1; //扩展，用于对齐
#ifdef SYSTEM_32BITS
	stSensorHeader.lSessionId = atoll(dev_info.sessionId);//会话id
#else
	stSensorHeader.lSessionId = atol(dev_info.sessionId);//会话id
#endif
	stSensorHeader.iSid = 0;//包序号
//	stSensorHeader.sDataLen = 0; //数据长度

	return;
}

/****************************************
 * Function: 用于将大端模式的值改为小端模式
 * @param num: [IN][OUT]需要转变的值的地址
 * @param type_len: [IN]需要转变的值的类型
 *
 * @return : 无
 ****************************************/
static void big_endian_to_little_endian(void *num, VAL_TYPE type_len)
{
	int i, j;
	const int bits_8 = 8;
	char tmp[16] = {0};

	switch(type_len)
	{
		case SHORT:
		{
			short src_short_num = *((short *)num);
			short dst_short_num = 0;
			//printf("src_short_num-------------------[%d]\n", src_short_num);
			for (i=0, j=type_len-1;i<type_len;i++, j--)
			{
				tmp[i] = src_short_num>>bits_8*j;
				dst_short_num += (short)(tmp[i] << i * bits_8);
			}
			*((short *)num) = dst_short_num;
		}
		break;
		case INT:
		{
			int src_int_num = *((int *)num);
			int dst_int_num = 0;
			//printf("src_int_num -------------------[%d]\n", src_int_num);
			for (i=0, j=type_len-1; i<type_len; i++, j--)
			{
				tmp[i] = src_int_num>>bits_8*j;
				dst_int_num += (int)(tmp[i] << i * bits_8);
			}
			*((int *)num) = dst_int_num;
			//printf("dst_int_num -------------------[%d]\n", *((int *)num));
		}
		break;
		case LONG:
		{
#ifdef SYSTEM_32BITS
			long long src_long_long_num = *((long long *)num);
			long long dst_long_long_num = 0;
			for (i=0, j=type_len-1; i<type_len; i++, j--)
			{
				tmp[i] = src_long_long_num>>bits_8*i;
				dst_long_long_num += ((long long)tmp[i] << (j * bits_8));
			}
			putchar('\n');
			*((long long *)num) = dst_long_long_num;
#else
			long src_long_num = *((int *)num);
			long dst_long_num = 0;
			//printf("src_long_num -------------------[%ld]\n", src_long_num);
			for (i=0, j=type_len-1; i<type_len; i++, j--)
			{
				tmp[i] = src_long_num>>bits_8*j;
				dst_long_num += (long)(tmp[i] << i * bits_8);
			}
			*((long *)num) = dst_long_num;
			//printf("dst_long_num -------------------[%ld]\n", *((long *)num));
#endif
		}
		break;
		default:
			printf("error input len [%d]\n", type_len);
			break;
	}
}


int send_udp_data(UDP_HEADER *pHeader, UDP_SERVER_INFO *stUdpServerInfo, char *pSendData, short iDataLen, int timeout)
{
	int iRet = 0;
	int iSendLen = 0;
	fd_set  writeset;
	struct timeval wait_time;
	char arrcSendBuf[SEND_BUF_LEN] = {0};

	if(stUdpServerInfo->iSockFd < 0 || NULL == pSendData || iDataLen <= 0)
	{
		printf("####################################\n");
		return -1;
	}

	while (iDataLen > 0)
	{
		FD_ZERO(&writeset);
		FD_SET(stUdpServerInfo->iSockFd, &writeset);
		wait_time.tv_sec = timeout;
		wait_time.tv_usec = 0;
		iRet = select(FD_SETSIZE, NULL, &writeset, NULL, &wait_time);
		if (iRet < 0)
		{
			TRACE_ERR("select err=%d(%s)\n", errno, strerror(errno));
			return -2;
		}
		else if (iRet == 0)
		{
			TRACE_LOG("select timeout\n");
			return -1;
		}
		else
		{
			pHeader->sDataLen = iDataLen;
			pHeader->iSid += 1;
			memcpy(arrcSendBuf, (const char *)pHeader, SEND_BUF_LEN);
			strncpy(arrcSendBuf+UDP_HEADER_LEN, pSendData, SEND_BUF_LEN-UDP_HEADER_LEN);
			iSendLen = sendto(stUdpServerInfo->iSockFd, arrcSendBuf, UDP_HEADER_LEN+iDataLen, 0, \
						(struct sockaddr*)&stUdpServerInfo->addr, \
						(socklen_t)stUdpServerInfo->sockaddr_in_len);
			//printf("send len:[%d]\n", len);
			if (iSendLen <= 0)
			{
				if (errno == EINTR)
				{
					TRACE_ERR("send err=%d(%s), again\n", errno, strerror(errno));
					//goto RETRY;
					continue; /* just an interrupted system call */
				}
				else
				{
					TRACE_ERR("send err=%d(%s)\n", errno, strerror(errno));
					return -2;
				}
			}
			pSendData += iSendLen;
			iDataLen -= iSendLen;
		}
	}

	return iSendLen;
}

int recv_udp_data(UDP_SERVER_INFO *stUdpServerInfo, char *pRecvBuf, int iBufLen, int timeout)
{
	UDP_HEADER stRecvHeader;
    struct timeval wait_time = {0, 0};
	int iReadLen = 0;
	int ret;
	fd_set fdread;
	static char tmpRecvBuf[RECV_BUF_LEN] = {0};

	memset(tmpRecvBuf, 0, RECV_BUF_LEN);
	memset(&stRecvHeader, 0, UDP_HEADER_LEN);

	wait_time.tv_sec   = timeout;
	wait_time.tv_usec  = 0;
    if(stUdpServerInfo->iSockFd <= 0 || pRecvBuf == NULL || iBufLen <= 0)
    {
    	//assert(0);
    	TRACE_ERR("input param error!\n");
    	return -3;
    }
    FD_ZERO(&fdread);
    FD_SET(stUdpServerInfo->iSockFd, &fdread);
	ret = select(stUdpServerInfo->iSockFd + 1, &fdread, NULL, NULL, &wait_time);

    if (0 == ret)		// 超时
    {
    	TRACE_LOG("select timeout!\n");
        return -1;
    }
    else if (ret < 0)	// 出错
    {
    	TRACE_ERR("select error!\n");
        return -2;
    }
    do
    {
		iReadLen = recvfrom(stUdpServerInfo->iSockFd, tmpRecvBuf, iBufLen+UDP_HEADER_LEN, 0, \
						(struct sockaddr*)&stUdpServerInfo->addr, \
						(socklen_t*)(&stUdpServerInfo->sockaddr_in_len));
		if (0 == iReadLen)
		{
			TRACE_ERR("Recv Closed! retval= %d\n", iReadLen);
			return 0;
		}
		memcpy(&stRecvHeader, tmpRecvBuf, UDP_HEADER_LEN);

		if (stRecvHeader.cEndian == 0)//如果是大端数据，需要将lSessionId，iSid，sDataLen转换
		{
			big_endian_to_little_endian(&stRecvHeader.lSessionId, LONG);
			big_endian_to_little_endian(&stRecvHeader.iSid, INT);
			big_endian_to_little_endian(&stRecvHeader.sDataLen, SHORT);
		}

//		printf("stRecvHeader.cCode = [%X]\n", stRecvHeader.cCode);
//		printf("stRecvHeader.cMessageType = [%d]\n", stRecvHeader.cMessageType);
//		printf("stRecvHeader.cEncode = [%d]\n", stRecvHeader.cEncode);
//		printf("stRecvHeader.cEncrypt = [%d]\n", stRecvHeader.cEncrypt);
//		printf("stRecvHeader.cContextType = [%d]\n", stRecvHeader.cContextType);
//		printf("stRecvHeader.cEndian = [%d]\n", stRecvHeader.cEndian);
//		printf("stRecvHeader.lSessionId = [%lld]\n", stRecvHeader.lSessionId);
//		printf("stRecvHeader.iSid = [%d]\n", stRecvHeader.iSid);
//		printf("stRecvHeader.sDataLen=[%d]\n", stRecvHeader.sDataLen);

		strncpy(pRecvBuf, tmpRecvBuf+UDP_HEADER_LEN, iReadLen-UDP_HEADER_LEN);
        //usleep(5000);
    }while ((iReadLen < 0) && (EINTR == errno));

    return iReadLen;
}

void close_udp(UDP_SERVER_INFO *stUdpServerInfo)
{
	if (stUdpServerInfo->iSockFd > 0)
	{
		close(stUdpServerInfo->iSockFd);
		//stUdpServerInfo->iSockFd = -1;
	}
	memset(stUdpServerInfo, 0, sizeof(UDP_SERVER_INFO));
}

