/*
 * net_to_rs485.c
 *
 *	Function: 实际为激光测距模块处理代码
 *
 *  Created on: 2018年9月17日
 *      Author: lijian
 */

#include "net_to_rs485.h"
#include "upload_pic.h"

//pthread_mutex_t mutex_sock_fd = PTHREAD_MUTEX_INITIALIZER;

//断开与串口服务器的连接
void close_serial_dev_ser(int *pFd)
{
	if (*pFd > 0)
	{
		close(*pFd);
		*pFd = -1;
	}
}

//打开与串口服务器的连接
int open_serial_dev_ser(int *pFd)
{
	struct sockaddr_in saddr;

	bzero(&saddr,sizeof(saddr));
	saddr.sin_family = AF_INET;
	saddr.sin_port = htons(SERIAL_DEV_SERVER_PORT); //服务器绑定的端口
	saddr.sin_addr.s_addr = inet_addr(SERIAL_DEV_SERVER_IP);//服务器的IP地址

	if (*pFd > 0)
	{
		close_serial_dev_ser(pFd);
	}

	*pFd = socket(AF_INET,SOCK_STREAM,0); //创建一个套接字用于连接服务器，并且这个套接字可用作对服务器操作的文件描述符。
	if (*pFd < 0)
	{
		return -1;
	}

	if (connect(*pFd,(struct sockaddr*)&saddr, sizeof(struct sockaddr_in)) < 0)//返回-1失败
	{
		//连接串口服务器失败
		TRACE_ERR("Connect to serial device server failed!\n");
		return -2;
	}

	return *pFd;
}



//发送消息到串口服务器
int send_to_serial_dev_ser(int *pFd, char *data, int len)
{
	int iSendLen = 0;
	int i;

	iSendLen = send(*pFd, data, len, 0);
	if (iSendLen < 0)
	{
		perror("send()");
		return -1;
	}

	printf("=========write_len = %d, send data = ", iSendLen);
	for (i = 0; i < len; i++)
	{
		printf("%X ", data[i]);
	}

	putchar('\n');

	return iSendLen;
}


//从串口服务器接收数据
int recv_from_serial_dev_ser(int *pFd)
{
	char tmpbuff[16] = {0};
	short len;
	fd_set rdfds;
	struct timeval timeout = {15, 0};
	int iDistance[3] = {0};
	int iCurDistance = 0;
	int iDataFlag = 0;
	int iIndex = 0;
	int iGetPicFlag = 0;

	FD_ZERO(&rdfds);
	FD_SET(*pFd, &rdfds);
	select(*pFd + 1, &rdfds, NULL, NULL, &timeout);

	for (;;)
	{
		if (FD_ISSET(*pFd, &rdfds) > 0)
		{
			memset(tmpbuff, 0, sizeof(tmpbuff));
			len = recv(*pFd, tmpbuff, sizeof(tmpbuff), 0);
			if (len > 0)
			{
				printf("############################read_len = %d, read_data=%s\n", len, tmpbuff);
				if (tmpbuff[0] == ':')
				{
					if (strstr(tmpbuff, "Er") != NULL)
					{
						//采集出错
						stDistance.iDistance = -1;
					}
					else
					{
						if (iDataFlag >= 3)
						{
							iIndex %= 3;
							if (abs(iDistance[0]-iDistance[1]) < 10 && abs(iDistance[1]-iDistance[2]) < 10)
							{
								//连续三个数值无变化，说明是静止状态，将拍照标志置位
								iGetPicFlag = 1;
							}

							iCurDistance = (HB_S32)(atof(&tmpbuff[1]) * 1000);
							if (0 == iCurDistance)
							{
								//采集有问题，词条数据丢弃
								stDistance.iDistance = -1;
								continue;
							}
							iDistance[iIndex] = iCurDistance;
							printf("distance:[%d] [%d] [%d]\n", iDistance[0], iDistance[1], iDistance[2]);
							stDistance.iDistance = iCurDistance;
							if (iGetPicFlag)
							{
								//静止状态下检测电梯是否开始运动，若由静止变为运动就进行拍照
								if (abs(iDistance[0]-iDistance[1]) > 20 || abs(iDistance[1]-iDistance[2]) > 20)
								{
									iGetPicFlag = 0;
									pthread_t threadUploadPicId = 0;
									pthread_create(&threadUploadPicId, NULL, thread_upload_picture, NULL);
//									printf("ka cha ka cha ka cha ka cha ka cha ka cha ka cha ka cha ka cha ka cha ka cha ka cha ka cha ka cha ka cha ka cha ka cha \n");
								}
							}
							iIndex++;
						}
						else
						{
							iDataFlag++;
							iDistance[iIndex] = (HB_S32)(atof(&tmpbuff[1]) * 1000);
							stDistance.iDistance = iDistance[iIndex];
							printf("distance0:[%d] [%d] [%d]\n", iDistance[0], iDistance[1], iDistance[2]);
							iIndex++;
						}
					}
				}
			}
		}
		else
		{
			break;
		}
	}

	return 0;
}


static HB_VOID *get_distance_thread_task(HB_HANDLE hArg)
{
	pthread_detach(pthread_self());

	HB_S32 *pFd = (HB_S32 *)hArg;

	for(;;)
	{
//		pthread_mutex_lock(&mutex_sock_fd);
		if (send_to_serial_dev_ser(pFd, "D", 1) < 0)
		{
			open_serial_dev_ser(pFd);
		}
//		pthread_mutex_unlock(&mutex_sock_fd);
		sleep(5);
	}

	pthread_exit(NULL);
}

HB_VOID *thread_get_distance_moudle(HB_HANDLE hArg)
{
	HB_S32 iConnectToSerialDevSerFd = -1;

	for(;;)
	{
		if (open_serial_dev_ser(&iConnectToSerialDevSerFd) < 0)
		{
			sleep(2);
			continue;
		}
		else
		{
			break;
		}
	}

	pthread_t threadGetDistanceTaskId = -1;
	pthread_create(&threadGetDistanceTaskId, NULL, get_distance_thread_task, &iConnectToSerialDevSerFd);


	for(;;)
	{
		recv_from_serial_dev_ser(&iConnectToSerialDevSerFd);
	}

	return NULL;
}
