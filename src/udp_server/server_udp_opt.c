/*
 * udp_opt.c
 *
 *  Created on: 2017年3月27日
 *      Author: root
 */
#include "my_include.h"

#include "server_udp_opt.h"


int create_socket_and_set_server(LOCAL_UDP_SERVER_INFO *stUdpServerInfo, int iServerPort)
{
	memset(stUdpServerInfo, 0, sizeof(LOCAL_UDP_SERVER_INFO));
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

    //设置非阻塞
    int cur_flags = fcntl(stUdpServerInfo->iSockFd, F_GETFL, 0);
    fcntl(stUdpServerInfo->iSockFd, F_SETFL, cur_flags|O_NONBLOCK);

    //绑定网络地址和网络文件描述符
    if(bind(stUdpServerInfo->iSockFd, (struct sockaddr*)&(stUdpServerInfo->addr), sizeof(struct sockaddr_in)) != 0)
	{
		close(stUdpServerInfo->iSockFd);
		perror("bind");
		return -1;
    }

    printf("start listen udp [8899]\n");
    return 0;
}


int server_send_udp_data(LOCAL_UDP_SERVER_INFO *stUdpServerInfo, UDP_CLIENT_INFO_HANDLE pUdpClient, char *pSendData, short iDataLen, int timeout)
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
			pUdpClient->stRecvHeader.sDataLen = iDataLen;
			memcpy(arrcSendBuf, (const char *)(&pUdpClient->stRecvHeader), SEND_BUF_LEN);
			strncpy(arrcSendBuf+UDP_HEADER_LEN, pSendData, SEND_BUF_LEN-UDP_HEADER_LEN);
			iSendLen = sendto(stUdpServerInfo->iSockFd, arrcSendBuf, UDP_HEADER_LEN+iDataLen, 0, \
						(struct sockaddr*)&pUdpClient->addr, \
						(socklen_t)pUdpClient->sockaddr_in_len);
//			printf("Datalen:[%d], SendLen = [%d]\n", pUdpClient->stRecvHeader.sDataLen, iSendLen);
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
			TRACE_LOG("\nsend to phone client Datalen:[%d], SendLen:[%d]\n[%s]\n", pUdpClient->stRecvHeader.sDataLen, iSendLen, pSendData);
			pSendData += iSendLen;
			iDataLen -= iSendLen;
		}
	}

	return iSendLen;
}

UDP_CLIENT_INFO_HANDLE server_recv_udp_data(LOCAL_UDP_SERVER_INFO *stUdpServerInfo)
{
//    struct timeval wait_time = {0, 0};
	int ret;
	fd_set fdread;
	HB_CHAR arrcRecvBuf[RECV_BUF_LEN] = {0};

//	wait_time.tv_sec   = timeout;
//	wait_time.tv_usec  = 0;
    if(stUdpServerInfo->iSockFd <= 0)
    {
    	//assert(0);
    	TRACE_ERR("input param error!\n");
    	return NULL;
    }
    FD_ZERO(&fdread);
    FD_SET(stUdpServerInfo->iSockFd, &fdread);
    ret = select(stUdpServerInfo->iSockFd + 1, &fdread, NULL, NULL, NULL);
    if (0 == ret)		// 超时
    {
    	TRACE_LOG("select timeout!\n");
        return NULL;
    }
    else if (ret < 0)	// 出错
    {
    	TRACE_ERR("select error!\n");
        return NULL;
    }
    else
    {
    	int iReadLen = 0;
    	UDP_CLIENT_INFO_HANDLE pClient = (UDP_CLIENT_INFO_HANDLE)malloc(sizeof(UDP_CLIENT_INFO));
    	if(pClient == NULL)
    	{
    		printf("malloc error!\n");
    		return NULL;
    	}
    	memset(pClient, 0, sizeof(UDP_CLIENT_INFO));
    	memset(&(pClient->stRecvHeader), 0, UDP_HEADER_LEN);
    	pClient->sockaddr_in_len = sizeof(pClient->addr);

#if 0
    	iReadLen = recvfrom(stUdpServerInfo->iSockFd, pClient->arrcRecvBuf, 1024, 0, \
						(struct sockaddr*)&(pClient->addr), \
						(socklen_t*)(&pClient->sockaddr_in_len));
#else
		iReadLen = recvfrom(stUdpServerInfo->iSockFd,  arrcRecvBuf, RECV_BUF_LEN, 0, \
						(struct sockaddr*)&pClient->addr, (socklen_t*)(&pClient->sockaddr_in_len));

		if (iReadLen < UDP_HEADER_LEN)
		{
			printf("the head is too small!\n");
			free(pClient);
			return NULL;
		}

		memcpy(&(pClient->stRecvHeader), arrcRecvBuf, UDP_HEADER_LEN);
//		printf("stRecvHeader.cCode = [%X]\n", pClient->stRecvHeader.cCode);
//		printf("stRecvHeader.cMessageType = [%d]\n", pClient->stRecvHeader.cMessageType);
//		printf("stRecvHeader.cEncode = [%d]\n", pClient->stRecvHeader.cEncode);
//		printf("stRecvHeader.cEncrypt = [%d]\n", pClient->stRecvHeader.cEncrypt);
//		printf("stRecvHeader.cContextType = [%d]\n", pClient->stRecvHeader.cContextType);
//		printf("stRecvHeader.cEndian = [%d]\n", pClient->stRecvHeader.cEndian);
//		printf("stRecvHeader.lSessionId = [%lld]\n", pClient->stRecvHeader.lSessionId);
//		printf("stRecvHeader.iSid = [%d]\n", pClient->stRecvHeader.iSid);
//		printf("stRecvHeader.sDataLen=[%d]\n", pClient->stRecvHeader.sDataLen);

		if (pClient->stRecvHeader.cCode != 0xF1)
		{
			printf("head code error!\n");
			HB_CHAR arrcReturnJson[64] = {0};
			strncpy(arrcReturnJson, "{\"code\":\"-30006\",\"msg\":\"消息头校验码有误\"}", sizeof(arrcReturnJson));
			server_send_udp_data(stUdpServerInfo, pClient, arrcReturnJson, strlen(arrcReturnJson), 2);
			free(pClient);
			return NULL;
		}
		strncpy(pClient->arrcRecvBuf, arrcRecvBuf+UDP_HEADER_LEN, pClient->stRecvHeader.sDataLen);
#endif
		//存储客户端ip
		strncpy(pClient->arrcClientIp, inet_ntoa(pClient->addr.sin_addr), sizeof(pClient->arrcClientIp));
		printf("pClient->arrcClientIp:[%s] readlen:[%d]\n", pClient->arrcClientIp, iReadLen);

		return pClient;

//		if (stRecvHeader.cEndian == 0)//如果是大端数据，需要将lSessionId，iSid，sDataLen转换
//		{
//			big_endian_to_little_endian(&stRecvHeader.lSessionId, LONG);
//			big_endian_to_little_endian(&stRecvHeader.iSid, INT);
//			big_endian_to_little_endian(&stRecvHeader.sDataLen, SHORT);
//		}
    }

    return NULL;
}

void server_close_udp(LOCAL_UDP_SERVER_INFO *stUdpServerInfo)
{
	if (stUdpServerInfo->iSockFd > 0)
	{
		close(stUdpServerInfo->iSockFd);
		//stUdpServerInfo->iSockFd = -1;
	}
	memset(stUdpServerInfo, 0, sizeof(LOCAL_UDP_SERVER_INFO));
}

