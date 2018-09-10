/*
 * uart.c
 *
 *  Created on: 2018年9月7日
 *      Author: lijian
 */

#include "uart.h"

HB_S32 open_uart(char *pPath, speed_t speed)
{
	printf("Open serial...\n");
	HB_S32 iUartFd = open(pPath, O_RDWR);
	if (iUartFd < 0)
	{
		perror("Open serial");
		return -1;
	}
	else
	{
		printf("Serial open succeed! %d\n", iUartFd);
	}

	struct termios options;

	if ((tcgetattr(iUartFd, &options)) < 0)
	{
		close(iUartFd);
		iUartFd = -1;
		printf("error in tcgetattrn\n");
		return -2;
	}

	options.c_cflag |= ( CLOCAL | CREAD);
	options.c_cflag &= ~CSIZE;
	options.c_cflag &= ~CRTSCTS;
	options.c_cflag |= CS8;
	options.c_cflag &= ~CSTOPB;
	options.c_iflag &= ~(BRKINT | ICRNL | INPCK | ISTRIP | IXON);
	//options.c_iflag |= IGNPAR;
	options.c_oflag = 0;
	options.c_lflag = 0;

	options.c_cc[VMIN] = 0;
	options.c_cc[VTIME] = 10;

	tcflush(iUartFd, TCIOFLUSH);
	cfsetispeed(&options, speed);
	cfsetospeed(&options, speed);

	//printf("Set speed succeed: %d\n", name_arr[i]);

	tcsetattr(iUartFd, TCSANOW, &options);

	return iUartFd;
}

HB_VOID close_uart(HB_S32 *pUartFd)
{
	if (*pUartFd > 0)
	{
		close(*pUartFd);
		*pUartFd = -1;
		printf("Close serial succeed!\n");
	}
}

HB_S32 send_to_uart(HB_S32 iUartFd, HB_U8 *pData, HB_S32 iDataLen)
{
	HB_S32 iWriteLen = 0;
	HB_S32 i;

	iWriteLen = write(iUartFd, pData,iDataLen);
	if (iWriteLen < 0)
	{
		perror("write()");
		return -1;
	}

	printf("=========write_len = %d, send data = ", iWriteLen);
	for (i = 0; i < iDataLen; i++)
	{
		printf("%X ", pData[i]);
	}

	putchar('\n');

	return iWriteLen;
}

HB_S32 read_from_uart(HB_S32 iUartFd, HB_U8 *pData, HB_S32 iDataSize)
{
	int i;
	HB_S32 iLen = 0;
	fd_set stReadFds;
	struct timeval stTimeOut = {60, 0};

	FD_ZERO(&stReadFds);
	FD_SET(iUartFd, &stReadFds);

	select(iUartFd + 1, &stReadFds, NULL, NULL, &stTimeOut);
	if (FD_ISSET(iUartFd, &stReadFds) > 0)
	{
		iLen = read(iUartFd, pData, iDataSize);
		if (iLen > 0)
		{
			printf("read_len = %d, read_data=", iLen);
			for (i = 0; i < iLen; i++)
			{
				printf("%X ", pData[i]);
			}
			putchar('\n');
		}
	}

	return iLen;
}

HB_VOID *thread_send_to_uart(HB_HANDLE hArg)
{
	HB_S32 *pUartFd = (HB_S32 *)hArg;
	HB_U8 cSendData[8] = {0x01, 0x04, 0x00, 0x00, 0x00, 0x02, 0x71, 0xcb};
	for(;;)
	{
		send_to_uart(*pUartFd, cSendData, 8);
		sleep(27);
	}
	pthread_exit(NULL);
}

HB_VOID *thread_read_uart(HB_HANDLE hArg)
{
	HB_U8 cRecvData[32] = {0};
	HB_S32 iReadDataLen = 0;
	HB_S16 sWd = 0;//溫度值
	HB_S16 sSd = 0;//湿度值

	memset(&glWSDInfo, 0, sizeof(WSD_INFO_OBJ));

	for (;;)
	{
		HB_S32 iUartFd = open_uart("/dev/ttyAMA1", B19200);
		if (iUartFd < 0)
		{
			sleep(1);
			continue;
		}

		pthread_t threadSendToUartId = -1;
		pthread_create(&threadSendToUartId, NULL, thread_send_to_uart, &iUartFd);

		for(;;)
		{
			iReadDataLen = read_from_uart(iUartFd, cRecvData, sizeof(cRecvData));
			if (iReadDataLen < 0)
			{
				close_uart(&iUartFd);
				break;
			}
			if (cRecvData[0]==0x1 && cRecvData[1] == 0x4 && cRecvData[2] == 0x4)
			{
				//温湿度数据
				sWd = (cRecvData[3] << 8) + cRecvData[4];
				sSd = (cRecvData[5] << 8) + cRecvData[6];

				if ((sWd>=0x8000)&& (sWd<=0xFFFF))
				{
					//说明温度小于0
					sWd = 0xFFFF - sWd;
					snprintf(glWSDInfo.cTemperature, sizeof(glWSDInfo.cTemperature), "-%.2f", (HB_FLOAT)sWd/10);
				}
				else
				{
					snprintf(glWSDInfo.cTemperature, sizeof(glWSDInfo.cTemperature), "%.2f", (HB_FLOAT)sWd/10);
				}
				snprintf(glWSDInfo.cHumidity, sizeof(glWSDInfo.cHumidity), "%.2f", (HB_FLOAT)sSd/10);

				printf("cTemperature = %s, cHumidity = %s\n", glWSDInfo.cTemperature, glWSDInfo.cHumidity);
			}
			else
			{
				//其它数据(激光)
			}

		}
		pthread_cancel(threadSendToUartId);
		pthread_join(threadSendToUartId, NULL);

		sleep(1);
	}
	pthread_exit(NULL);
}
