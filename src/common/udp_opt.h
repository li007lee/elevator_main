/*
 * udp_opt.h
 *
 *  Created on: 2017年3月27日
 *      Author: root
 */

#ifndef UDP_OPT_H_
#define UDP_OPT_H_

#define SYSTEM_32BITS

typedef enum _VAL_TYPE
{
	SHORT = 2,
	INT = 4,
	LONG = 8,
}VAL_TYPE;

typedef struct _UDP_SERVER_INFO
{
	int iSockFd; //用于与udp服务端通讯的套接字
	int sockaddr_in_len;//struct sockaddr_in结构体的长度（addr len）
	int iServerPort;//用于存储udp服务端的端口
	char pServerIp[16];//用于存储udp服务端的ip地址
	struct sockaddr_in addr;//内部使用，无需关心
}UDP_SERVER_INFO;

#pragma pack(push) //保存对齐状态
#pragma pack(2)// 设定为2字节对齐
typedef struct _UDP_HEADER
{
	unsigned char cCode;	//校验码，固定为0xE1
	unsigned char cMessageType;//消息类型，固定为1
	unsigned char cEncode; //编码类型，固定为0,UTF-8
	unsigned char cEncrypt;//加密方式，暂时填0
	unsigned char cContextType;//发送的消息的方式：0(XML) 1(JSON) 6(二进制) 9(char)
	unsigned char cEndian; //大小端，0大端，1小端
#ifdef SYSTEM_32BITS
	long long lSessionId;//会话id
#else
	long lSessionId;
#endif
	unsigned int iSid;//包序号
	short sDataLen; //数据长度
}UDP_HEADER;
#pragma pack(pop)// 恢复对齐状态

#define RECV_BUF_LEN	(2048)
#define SEND_BUF_LEN	(4096)
#define UDP_HEADER_LEN	sizeof(UDP_HEADER)

/****************************************
 * Function: 用于设置udp通讯服务端的参数
 * @param stUdpServerInfo: [OUT]用于存储udp服务器信息的结构体，函数内会对其初始化
 * @param pServerIp: [IN]udp服务端的ip地址
 * @param iServerPort: [IN]服务端的udp监听端口
 *
 * @return : 成功返回0， 失败返回-1
 ****************************************/
int create_socket_and_set_server(UDP_SERVER_INFO *stUdpServerInfo, char *pServerIp, int iServerPort);

/****************************************
 * Function: 用于设置通讯头信息
 * @param pHeader: [IN]消息头的结构体
 * @param iContextType: [IN]发送的消息的方式：0(XML) 1(JSON) 6(二进制) 9(char)
 *
 * @return : 无
 ****************************************/
void set_header(UDP_HEADER *pHeader, int iContextType);

/****************************************
 * Function: 用于设置udp通讯服务端的参数
 * @param pHeader: [IN]发送包的数据头
 * @param stUdpServerInfo: [IN]udp服务器信息的结构体
 * @param pData: [IN]需要发送的数据
 * @param iDataLen: [IN]需要发送的数据长度
 * @param timeout: [IN]发送超时
 *
 * @return : 成功返回发送的字节数，失败返回负数
 ****************************************/
int send_udp_data(UDP_HEADER *pHeader, UDP_SERVER_INFO *stUdpServerInfo, char *pSendData, short iDataLen, int timeout);

/****************************************
 * Function: 用于设置udp通讯服务端的参数
 * @param stUdpServerInfo: [IN]udp服务器信息的结构体
 * @param pData: [IN]需要发送的数据
 * @param iDataLen: [IN]需要发送的数据长度
 * @param timeout: [IN]接收超时
 *
 * @return : 成功返回读取的字节数，失败返回负数（-1超时 -2select出错）
 ****************************************/
int recv_udp_data(UDP_SERVER_INFO *stUdpServerInfo, char *pRecvBuf, int iBufLen, int timeout);

/****************************************
 * Function: 用于设置udp通讯服务端的参数
 * @param stUdpServerInfo: [IN]服务器信息的结构体
 *
 * @return : 无
 ****************************************/
void close_udp(UDP_SERVER_INFO *stUdpServerInfo);


#endif /* UDP_OPT_H_ */
