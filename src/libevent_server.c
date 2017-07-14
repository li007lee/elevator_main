/*
 * libevent_server.c
 *
 *  Created on: 2016-10-8
 *      Author: li007lee
 */

#include "my_include.h"
#include "event.h"
#include "event2/listener.h"

#include "./common/common.h"
#include "upload_pic.h"

#define LIBEVENT_LISTEN_PORT 25555

// 异常事件回调函数
static void cmd_task_event_cb(struct bufferevent *bev, short events, void *args)
{
	if (events & BEV_EVENT_EOF)//对端关闭
	{
		TRACE_ERR("\n####### RTSP CMD channel normal closed!\n");
	}
	else if (events & BEV_EVENT_ERROR)//错误时间
	{
		TRACE_ERR("\n######RTSP CMD channel connect error !\n");
	}
	else if (events & BEV_EVENT_TIMEOUT)//超时事件
	{
		TRACE_ERR("\n######RTSP CMD channel  timeout !\n");
	}

	bufferevent_free(bev);
	return;
}


// 读取回调函数
static void cmd_task_read_cb(struct bufferevent *buf_bev, void *arg)
{
//	char arrc_MsgType[32] = {0};
	char arrcCommand[32] = {0};
	char dataBuf[512] = {0};

	struct evbuffer *src = bufferevent_get_input(buf_bev);//获取输入缓冲区
	int len = evbuffer_get_length(src);//获取输入缓冲区中数据的长度，也就是可以读取的长度。
	if(evbuffer_remove(src, dataBuf, len))
	{
		printf("recv_datas=[%s]\n", dataBuf);
		if (strstr(dataBuf, "Command") == NULL)
		{
			printf("Error data!\n");
			bufferevent_free(buf_bev);
			return ;
		}
	}

	analysis_json(dataBuf, "Command", arrcCommand, sizeof(arrcCommand));
	//MsgType=Alarm&Number=0
//	sscanf(dataBuf, "MsgType=%[^&]&Number=%s", arrc_MsgType, arrc_Value);
	if (strncmp(arrcCommand, "Alarm", strlen("Alarm")) == 0) //报警消息
	{
		char arrcAlarmNum[2] = {0};
		analysis_json(dataBuf, "Number", arrcAlarmNum, sizeof(arrcAlarmNum));
		switch(atoi(arrcAlarmNum))
		{
			case 0: //手动报警
			{
				pthread_t thread_SendSignal = 0;
				pthread_t thread_UploadPicId = 0;
				pthread_create(&thread_SendSignal, NULL, thread_send_signal_to_http, NULL);
				pthread_create(&thread_UploadPicId, NULL, thread_upload_picture, NULL);

				usleep(500*1000);//等待线程创建
				bufferevent_free(buf_bev);
				break;
			}
			default:
				break;
		}
	}
	else if (strncmp(arrcCommand, "GetSensorInfo", strlen("GetSensorInfo")) == 0) //报警消息
	{
		bufferevent_write(buf_bev, &sensor_info, sizeof(sensor_info));
//		bufferevent_free(buf_bev);
	}
	else if (strncmp(arrcCommand, "SetElevatorCode", strlen("GetSensorInfo")) == 0)
	{
		//设置了电梯编号，需要重新获取令牌
		pthread_attr_t attr;
		pthread_t get_token_pthread_id;
		pthread_attr_init(&attr);
		pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);
		pthread_create(&get_token_pthread_id, &attr, elevator_get_token, NULL);
		pthread_attr_destroy(&attr);
		usleep(200*1000);
	}

	return;
}

static void accept_client_connect_cb(struct evconnlistener *listener, evutil_socket_t i_AcceptSockfd,
	    struct sockaddr *p_ClientAddr, int slen, void *arg)
{
	struct timeval tv_w;

#if 1
	//打印对端ip
	struct sockaddr_in *p_PeerAddr = (struct sockaddr_in *)p_ClientAddr;
	char arrch_PeerIp[16] = {0};
	inet_ntop(AF_INET, &(p_PeerAddr->sin_addr), arrch_PeerIp, sizeof(arrch_PeerIp));
	printf("\nAccept a new connect ! sockfd=%d accept ip=%s : %d\n", \
					i_AcceptSockfd,arrch_PeerIp, ntohs(p_PeerAddr->sin_port));
#endif

	//获取base，其实就是取到main函数中的cmd_base
    struct event_base *base = evconnlistener_get_base(listener);
    // 为新的连接分配并设置 bufferevent,设置BEV_OPT_CLOSE_ON_FREE宏后，当连接断开时也会通知客户端关闭套接字
    struct bufferevent *accept_sockfd_bev = bufferevent_socket_new(base, i_AcceptSockfd, BEV_OPT_CLOSE_ON_FREE);

	tv_w.tv_sec  = 5;//5秒超时时间
	tv_w.tv_usec = 0;
	bufferevent_set_timeouts(accept_sockfd_bev, &tv_w, NULL);
    bufferevent_setcb(accept_sockfd_bev, cmd_task_read_cb, NULL, cmd_task_event_cb, (void*)NULL);
    bufferevent_enable(accept_sockfd_bev, EV_READ|EV_WRITE);
    //bufferevent_enable(accept_sockfd_bev, EV_READ|EV_WRITE);
    return;
}

void start_listening()
{
	struct event_base *cmd_base;
	struct evconnlistener *listener;
	struct sockaddr_in  listen_addr;

	bzero(&listen_addr, sizeof(listen_addr));
	listen_addr.sin_family = AF_INET;
	listen_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	listen_addr.sin_port = htons(LIBEVENT_LISTEN_PORT);

	cmd_base = event_base_new();
	if (!cmd_base)
	{
		perror("cmd_base event_base_new()");
		return ;
	}
	listener = evconnlistener_new_bind(cmd_base, accept_client_connect_cb, NULL,
		    LEV_OPT_CLOSE_ON_FREE|LEV_OPT_CLOSE_ON_EXEC|LEV_OPT_REUSEABLE,
		    1000, (struct sockaddr*)&listen_addr, sizeof(struct sockaddr_in));

	event_base_dispatch(cmd_base);
	printf("\n########## main func exit. base end error!!!\n");
	evconnlistener_free(listener);
	event_base_free(cmd_base);

    return ;
}
