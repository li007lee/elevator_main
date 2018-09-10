/*
 * udp_opt.h
 *
 *  Created on: 2017年3月27日
 *      Author: root
 */

#ifndef SERVER_UDP_OPT_H_
#define SERVER_UDP_OPT_H_

#include "udp_opt.h"

typedef struct _LOCAL_UDP_SERVER_INFO
{
	int iSockFd; //udp服务套接字
	int sockaddr_in_len;//struct sockaddr_in结构体的长度（addr len）
	struct sockaddr_in addr;//内部使用，无需关心

	pthread_mutex_t mutexLock;	//通信锁
}LOCAL_UDP_SERVER_INFO;

typedef struct _UDP_CLIENT_INFO
{
	int sockaddr_in_len;//struct sockaddr_in结构体的长度（addr len）
	struct sockaddr_in addr;//内部使用，无需关心
	char arrcClientIp[16];	//客户端ip
	int iClientPort;	//客户端端口

	UDP_HEADER stRecvHeader;	//通信头
	char arrcRecvBuf[RECV_BUF_LEN];
}UDP_CLIENT_INFO, *UDP_CLIENT_INFO_HANDLE;


/****************************************
 * Function: 用于设置udp通讯服务端的参数
 * @param stUdpServerInfo: [OUT]用于存储udp服务器信息的结构体，函数内会对其初始化
 * @param pServerIp: [IN]udp服务端的ip地址
 * @param iServerPort: [IN]服务端的udp监听端口
 *
 * @return : 成功返回0， 失败返回-1
 ****************************************/
int create_socket_and_set_server(LOCAL_UDP_SERVER_INFO *stUdpServerInfo, int iServerPort);


/****************************************
 * Function: 用于设置udp通讯服务端的参数
 * @param stUdpServerInfo: [IN]udp服务器信息的结构体
 * @param pUdpClient [IN]udp客户端信息结构体
 * @param pData: [IN]需要发送的数据
 * @param iDataLen: [IN]需要发送的数据长度
 * @param timeout: [IN]发送超时
 *
 * @return : 成功返回发送的字节数，失败返回负数
 ****************************************/
int server_send_udp_data(LOCAL_UDP_SERVER_INFO *stUdpServerInfo, UDP_CLIENT_INFO_HANDLE pUdpClient, char *pSendData, short iDataLen, int timeout);

/****************************************
 * Function: 用于设置udp通讯服务端的参数
 * @param stUdpServerInfo: [IN]udp服务器信息的结构体
 *
 * @return : 成功返回udp客户端结构体指针，失败返回NULL
 ****************************************/
UDP_CLIENT_INFO_HANDLE server_recv_udp_data(LOCAL_UDP_SERVER_INFO *stUdpServerInfo);

/****************************************
 * Function: 用于设置udp通讯服务端的参数
 * @param stUdpServerInfo: [IN]服务器信息的结构体
 *
 * @return : 无
 ****************************************/
void server_close_udp(LOCAL_UDP_SERVER_INFO *stUdpServerInfo);


#endif /* UDP_OPT_H_ */
