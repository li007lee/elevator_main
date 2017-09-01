/*
 * tcp_opt.c
 *
 *  Created on: 2017年3月28日
 *      Author: root
 */
#include "my_include.h"

#include "tcp_opt.h"

#define IP_VERTICAL 		6
#define IP_HORIZONTAL 	16
#define LISTEN_BACKLOG_SIZE (100)

typedef struct _tagDOMAIN_PARSE_ARG
{
	char domain[256];
	int pipe_fd;
}DOMAIN_PARSE_ARG_OBJ, *DOMAIN_PARSE_ARG_HANDLE;


static void *parse_domain_task(void *param)
{
	int ret = 0;
    struct addrinfo hints;
    struct addrinfo *res, *cur;
    struct sockaddr_in *addr;
    char srv_ip[16] = {0};
    char ipbuf[16] = {0};
    DOMAIN_PARSE_ARG_HANDLE parse_arg = (DOMAIN_PARSE_ARG_HANDLE)param;

    memset(&hints, 0, sizeof(struct addrinfo));
    hints.ai_family = AF_INET; /* Allow IPv4 */
    hints.ai_flags = AI_PASSIVE; /* For wildcard IP address */
    hints.ai_protocol = 0; /* Any protocol */
    hints.ai_socktype = SOCK_STREAM;

    printf("\n######  begin parse domain:[%s]\n", parse_arg->domain);

    ret = getaddrinfo(parse_arg->domain, NULL,&hints,&res);
    if (ret < 0)
    {
        perror("#####  parse err getaddrinfo");
        return NULL;
    }

    for (cur = res; cur != NULL; cur = cur->ai_next)
    {
        addr = (struct sockaddr_in *)cur->ai_addr;
        sprintf(srv_ip, "%s", inet_ntop(AF_INET, &addr->sin_addr, ipbuf, 16));
        ret = write(parse_arg->pipe_fd, srv_ip, strlen(srv_ip));
        break;
    }

    freeaddrinfo(res);
    return NULL;
}

//通过域名解析出相应的ip，超过timeout秒解析不出来，则返回失败-1，成功返回值大于0
int from_domain_to_ip(char *srv_ip, char *srv_domain, int timeout)
{
	int ret = 0;
	int fd[2] = {0};
	char recv_buf[32] = {0};
	DOMAIN_PARSE_ARG_OBJ domain_arg;
	memset(&domain_arg, 0, sizeof(DOMAIN_PARSE_ARG_OBJ));
	struct timeval tval;
	fd_set rset;

	ret = pipe(fd);
    FD_ZERO(&rset);
    FD_SET(fd[0],&rset);
    tval.tv_sec = timeout;
    tval.tv_usec = 0;

    domain_arg.pipe_fd = fd[1];
    memcpy(domain_arg.domain, srv_domain, strlen(srv_domain));
	pthread_attr_t attr;
	pthread_t parse_domain_pthread_id;
	ret = pthread_attr_init(&attr);
	ret = pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);
	ret = pthread_create(&parse_domain_pthread_id, &attr, parse_domain_task, (void *)(&domain_arg));
	pthread_attr_destroy(&attr);
	ret = select(fd[0] + 1, &rset, NULL, NULL, &tval);
    if (0 == ret) // timeout
    {
    	close(fd[0]);
    	close(fd[1]);
        printf("#############time_out!\n");
        return -1;
    }
    else if (ret < 0)
    {
    	close(fd[0]);
    	close(fd[1]);
        printf("#############select error !!\n");
        return -1;
    }
    else
    {
        if (FD_ISSET(fd[0], &rset))
        {
            ret = read(fd[0], recv_buf, sizeof(recv_buf));
            TRACE_DBG("\n############parse domain [%s] to ip [%s]\n", srv_domain, recv_buf);
            strcpy(srv_ip, recv_buf);
        }
    	close(fd[0]);
    	close(fd[1]);
    }
    return 0;
}

static int connect_noblock(int sockfd, struct sockaddr *addr, socklen_t salen, int nsec)
{
    int flags, n, error;
    socklen_t len;
    fd_set rset, wset;
    struct timeval tval;
    flags = fcntl(sockfd, F_GETFL, 0);
    fcntl(sockfd, F_SETFL, flags | O_NONBLOCK);

    error = 0;
    if ((n = connect(sockfd, addr, salen)) < 0)
    {
        if (errno != EINPROGRESS)
            return -1;
    }

    if (0 == n)
    {
        goto done;					// connect completed immediately
    }

    FD_ZERO(&rset);
    FD_SET(sockfd, &rset);
    wset = rset;
    tval.tv_sec = nsec;
    tval.tv_usec = 0;
    if (0 == (n = select(sockfd + 1, &rset, &wset, NULL, nsec ? &tval : NULL)))	// timeout
    {
        return -1;
    }

    if (FD_ISSET(sockfd, &rset) || FD_ISSET(sockfd, &wset))
    {
        len = sizeof(error);
        if (getsockopt(sockfd, SOL_SOCKET, SO_ERROR, &error, &len) < 0)
        {
            return -1;				// solaris pending error
        }
    }
    else
    {
    	TRACE_ERR("select error:sockfd no set!\n");
    }

done:
    if (error)
    {
        return -1;
    }

    return 0;
}

static int pt_connect(int *psockfd, char *addr, int port, int waitsec)
{
    struct sockaddr_in server_addr;
    int trueflag = 1;

	if(*psockfd <= 0 || addr == NULL || port <= 0)
	{
		assert(0);
		return 0;
	}
    setsockopt(*psockfd, SOL_SOCKET, SO_REUSEADDR, (void *)&trueflag, sizeof(trueflag));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = inet_addr(addr);
    server_addr.sin_port = htons(port);
    memset(server_addr.sin_zero, 0, 8);

    if (connect_noblock(*psockfd, (struct sockaddr *)&server_addr, sizeof(struct sockaddr_in), waitsec) < 0)
    {
    	return -1;
    }
    return 1;
}

////////////////////////////////////////////////////////////////////////////////
// 函数名：make_socket_non_blocking
// 描  述：设置网络文件描述符为非阻塞模式
// 参  数：[in] sock   网络文件描述符
// 返回值：成功返回1，出错返回0
// 说  明：
////////////////////////////////////////////////////////////////////////////////
int make_socket_non_blocking(int sock)
{

  int cur_flags = fcntl(sock, F_GETFL, 0);
  return fcntl(sock, F_SETFL, cur_flags|O_NONBLOCK) >= 0;
}

////////////////////////////////////////////////////////////////////////////////
// 函数名：setup_socket
// 描  述：设置流式套接字
// 参  数：[in] port              端口号
//         [in] make_non_blocking 是否是非阻塞模式的标识
// 返回值：成功返回网络文件描述符，出错返回ERR_GENERIC
// 说  明：
////////////////////////////////////////////////////////////////////////////////
static int setup_socket(unsigned short port, int make_non_blocking)
{
	int new_socket = -1;
    int reuse_flag = 1;
    struct sockaddr_in s;

	//创建流式网络文件描述符
    if((new_socket = socket(AF_INET, SOCK_STREAM, 0)) < 0)
	{
    	TRACE_ERR( "socket() error");
		return -1;
    }

	//防止端口被占用
    if(setsockopt(new_socket, SOL_SOCKET, SO_REUSEADDR,
		(char *)&reuse_flag, sizeof(reuse_flag)) < 0)
    {
    	close(new_socket);
    	TRACE_ERR("setsockopt() error");
		return -1;
	}

	//设置网络地址
	memset(&s, 0x00, sizeof(struct sockaddr_in));
    s.sin_family = AF_INET;
    s.sin_addr.s_addr = htonl(INADDR_ANY);
    s.sin_port = htons(port);

	//绑定网络地址和网络文件描述符
    if(bind(new_socket, (struct sockaddr*)&s, sizeof(struct sockaddr_in)) != 0)
	{
		close(new_socket);
		TRACE_ERR("bind() error in setup_stream_socket.");
		return -1;
    }

	//根据非阻塞模式标识判断是否要设置成非阻塞模式
  	if(make_non_blocking)
	{
	    if(!make_socket_non_blocking(new_socket))
		{
			close(new_socket);
			TRACE_ERR("make_socket_non_blocking() error");
			return -1;
	    }
	}

	//增大网络缓冲区的大小
	#ifdef SOCKET_INCREASE_SEND_BUFFER
	if(!increase_send_buffer_to(new_socket, SOCKET_SEND_BUFFER))
	{
		hb_fnc_log(HB_LOG_ERR, "increase_send_buffer_to() error");
		return ERR_GENERIC;
	}
	#endif

	return new_socket;
}


////////////////////////////////////////////////////////////////////////////////
// 函数名：setup_listen_socket
// 描  述：设置服务监听套接字
// 参  数：[in] port  端口号
// 		   [in]	non_blocking_flag非阻塞表示，置为1为非阻塞，0为阻塞
// 返回值：成功返回网络文件描述符，出错返回-1
// 说  明：
////////////////////////////////////////////////////////////////////////////////
int setup_listen_socket(unsigned short port, int non_blocking_flag)
{
	//int blocking_flag = 0;//阻塞方式为0
  	int socket = -1;

	//设置网络文件描述符以及阻塞模式
    socket = setup_socket(port, non_blocking_flag);
    if(socket < 0)
	{
    	TRACE_ERR("setup_listen_socket() error  !\n");
		return -1;
	}

    //监听网络文件描述符
    if(listen(socket, LISTEN_BACKLOG_SIZE) < 0)
	{
    	TRACE_ERR("\nlisten() error in setup_listen_socket() !\n");
		return -1;
    }
    return socket;
}


////////////////////////////////////////////////////////////////////////////////
// 函数名：create_socket_connect_domain
// 描述：tcp网络连接
// 参数：
//  ［IN］psockfd - 套接字指针。
//  ［IN］domain – 要连接的域名
//    [IN] domain_port - 要连接域名的端口
//   [IN] timeout - 超时时间
// 返回值：-1失败,0成功
// 说明：
//通过域名和端口创建socket并且连接到对端，timeout秒后仍然没有连接上，则返回失败-1，成功返回0
////////////////////////////////////////////////////////////////////////////////
int create_socket_connect_domain(int *psockfd, char *domain, int domain_port, int timeout)
{
    int ret = -1;
    char ipaddr[16];
    if(*psockfd <= 0)
    {
	    if((*psockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
	    {
	        return -1;
	    }
    }
    memset(ipaddr, 0, sizeof(ipaddr));
    if(from_domain_to_ip(ipaddr, domain, timeout) < 0)
    {
    	return -1;
    }

    ret = pt_connect(psockfd, ipaddr, domain_port, timeout);
    if(ret < 0)
    {
        return -1;
    }
    else
    {
        return 0;
    }
}


////////////////////////////////////////////////////////////////////////////////
// 函数名：create_socket_connect_ipaddr
// 描述：tcp网络连接
// 参数：
//  ［IN］psockfd - 套接字指针。
//  ［IN］ipaddr – 要连接的IP地址
//    [IN] port - 要连接的端口
//   [IN] timeout - 超时时间
// 返回值：-1失败,0成功
// 说明：
//通过IP和端口创建socket并且连接到对端，timeout秒后仍然没有连接上，则返回失败
////////////////////////////////////////////////////////////////////////////////
int create_socket_connect_ipaddr(int *psockfd, char *ipaddr, int port, int timeout)
{
    int ret = -1;
    if(*psockfd <= 0)
    {
	    if((*psockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
	    {
	        return -1;
	    }
    }

    ret = pt_connect(psockfd, ipaddr, port, timeout);
    if(ret < 0)
    {
        return -1;
    }
    else
    {
        return 0;
    }
}


////////////////////////////////////////////////////////////////////////////////
// 函数名：send_data
// 描述：tcp网络数据发送
// 参数：
//  ［IN］psockfd - 套接字指针。
//  ［IN］send_buf -发送缓冲区首地址
//    [IN] data_len - 要发送的数据长度
//   [IN] timeout_s - 超时时间 -秒
//   [IN] timeout_ms - 超时时间 -微秒
// 返回值：-1超时，-2失败，0成功
// 说明：
//发送指定长度datalen的数据，如果timeout秒后还为发送，则返回超时失败-1，
//否则返回发送剩余的字节数，成功表示全部发送完成则返回0，否则失败返回非0
////////////////////////////////////////////////////////////////////////////////
int send_data(int *psockfd, void *send_buf, int data_len, int timeout_s, int timeout_ms)
{
	if(*psockfd < 0 || NULL == send_buf || data_len <= 0)
	{
		return -1;
	}

    int err = 0;
	struct timeval wait_time;
    fd_set  writeset;
    int len = 0;
	while (data_len > 0)
    {
        FD_ZERO(&writeset);
        FD_SET(*psockfd, &writeset);
        wait_time.tv_sec = timeout_s;
        wait_time.tv_usec = timeout_ms;

        err = select(FD_SETSIZE, NULL, &writeset, NULL, &wait_time);
        if (err < 0)
        {
	    	TRACE_ERR("select err=%d(%s)\n", errno, strerror(errno));
        	return -2;
        }
        else if (err == 0)
        {
        	TRACE_LOG("select timeout\n");
        	return -1;
        }
        if ((len = send(*psockfd, send_buf, data_len, 0)) <= 0)
        {
            if (errno == EINTR)
            {
            	TRACE_ERR("send err=%d(%s), again\n", errno, strerror(errno));
                continue; /* just an interrupted system call */
            }
            else
            {
            	TRACE_ERR("send err=%d(%s)\n", errno, strerror(errno));
                return -2;
            }
        }
        send_buf += len;
        data_len -= len;
    }
	return data_len;
}


////////////////////////////////////////////////////////////////////////////////
// 函数名：recv_data
// 描述：tcp网络数据接收
// 参数：
//  ［IN］psockfd - 套接字指针。
//  ［IN］send_buf -接收缓冲区首地址
//    [IN] data_len - 接收缓冲区长度
//   [IN] timeout - 超时时间
// 返回值：-1超时，-2失败，0对端close，大于0成功
// 说明：
//接收数据，接收缓冲区为recv_buf,缓冲区长度为recv_buf_len,超过timeout秒仍没接收
//到数据，则返回失败(0-超时，小于0-其他错误，大于0-成功接收)
////////////////////////////////////////////////////////////////////////////////
int recv_data(int *psockfd, void *recv_buf, int recv_buf_len, int timeout)
{
    struct timeval wait_time = {0, 0};
	int retval = 0;
	int ret;
	fd_set fdread;
	wait_time.tv_sec   = timeout;
	wait_time.tv_usec  = 0;
    if(*psockfd <= 0 || recv_buf == NULL || recv_buf_len <= 0)
    {
    	assert(0);
    	return 0;
    }
    FD_ZERO(&fdread);
    FD_SET(*psockfd, &fdread);
	ret = select(*psockfd + 1, &fdread, NULL, NULL, &wait_time);
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
        retval = recv(*psockfd, recv_buf, recv_buf_len, 0);
        if (0 == retval)
        {
        	TRACE_ERR("Recv Closed! retval= %d\n", retval);
        	return 0;
        }
        usleep(5000);
    }
    while ((retval < 0) && (EINTR == errno));
    return retval;
}


////////////////////////////////////////////////////////////////////////////////
// 函数名：make_socket_blocking
// 描  述：设置网络文件描述符为阻塞模式
// 参  数：[in] sock   网络文件描述符
// 返回值：成功返回1，出错返回0
// 说  明：
////////////////////////////////////////////////////////////////////////////////
int make_socket_blocking(int sock)
{
  int cur_flags = fcntl(sock, F_GETFL, 0);
  return fcntl(sock, F_SETFL, cur_flags&(~O_NONBLOCK)) >= 0;
}

////////////////////////////////////////////////////////////////////////////////
// 函数名：get_buffer_size
// 描  述：获取缓冲区的大小
// 参  数：[in] buf_opt_name  网络缓冲区的名称
//         [in] sock          网络文件描述符
// 返回值：成功返回缓冲区的大小，出错返回0
// 说  明：
////////////////////////////////////////////////////////////////////////////////
static unsigned int get_buffer_size(int buf_opt_name, int socket)
{
	unsigned int cur_size;
	unsigned int size_size = sizeof(cur_size);

	if(getsockopt(socket, SOL_SOCKET, buf_opt_name, (void *)&cur_size, &size_size) < 0)
	{
		//hb_fnc_log(HB_LOG_ERR, "getsockopt() error in get_buffer_size !\n" );
	    return 0;
	}

	return cur_size;
}

////////////////////////////////////////////////////////////////////////////////
// 函数名：increase_buffer_to
// 描  述：增大缓冲区的大小
// 参  数：[in] buf_opt_name   网络缓冲区的名称
//         [in] sock           网络文件描述符
//         [in] requested_size 缓冲区的大小
// 返回值：成功返回缓冲区的大小，出错返回0
// 说  明：
////////////////////////////////////////////////////////////////////////////////
static unsigned int increase_buffer_to(int buf_opt_name,
	int socket, unsigned int requested_size)
{
	//获取到当前的网络缓冲区的大小
	unsigned int cur_size = get_buffer_size(buf_opt_name, socket);

	//增加网络缓冲区到要求的大小，假如失败，增加到一个比要求的大小小的值
	while(requested_size > cur_size)
	{
		if(setsockopt(socket, SOL_SOCKET, buf_opt_name,
		   (char*)&requested_size, sizeof(requested_size)) < 0)
		{
			requested_size = (requested_size + cur_size) / 2;
	    }
		else
		{
			//成功
			break;
		}
	}

	//返回当前的网络缓冲区的大小
	return get_buffer_size(buf_opt_name, socket);
}

////////////////////////////////////////////////////////////////////////////////
// 函数名：increase_send_buffer_to
// 描  述：增大网络发送缓冲区的大小
// 参  数：[in] sock           网络文件描述符
//         [in] requested_size 缓冲区的大小
// 返回值：成功返回缓冲区的大小，出错返回0
// 说  明：
////////////////////////////////////////////////////////////////////////////////
unsigned int increase_send_buffer_to(int socket, unsigned int requested_size)
{
  return increase_buffer_to(SO_SNDBUF, socket, requested_size);
}

////////////////////////////////////////////////////////////////////////////////
// 函数名：increase_receive_buffer_to
// 描  述：增大网络接收缓冲区的大小
// 参  数：[in] sock           网络文件描述符
//         [in] requested_size 网络缓冲区的大小
// 返回值：成功返回缓冲区的大小，出错返回0
// 说  明：
////////////////////////////////////////////////////////////////////////////////
unsigned int increase_receive_buffer_to(int socket, unsigned int requested_size)
{
  return increase_buffer_to(SO_RCVBUF, socket, requested_size);
}

//返回值：0-端口未被占用，-1-端口已占用
int check_port(int port)
{
	int test_sock = -1;
	int opt = 1;
	struct sockaddr_in  listen_on_addr;
	test_sock = socket(AF_INET, SOCK_STREAM, 0);//主要是探测端口是否可用，别无所用
	setsockopt(test_sock, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

	bzero(&listen_on_addr, sizeof(listen_on_addr));
	listen_on_addr.sin_family = AF_INET;
	listen_on_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	listen_on_addr.sin_port = htons(port);

	if (0 == bind(test_sock, (struct sockaddr *) &listen_on_addr, sizeof(struct sockaddr)))//绑定成功，说明此端口没有被占用
	{
		close(test_sock);
		return 0;
	}
	close(test_sock);

	return -1;
}

//根据网卡eth获取相应到ip地址
//返回值：-1获取失败，0获取成功
int get_dev_ip(char *eth, char *ipaddr)
{
	int sock;
    struct ifreq req;
    struct  sockaddr_in my_addr;
    sock = socket(AF_INET, SOCK_DGRAM, 0);
    if (sock < 0)
    {
        return -1;
    }
    strncpy(req.ifr_name, eth, IFNAMSIZ);
    if ( ioctl(sock, SIOCGIFADDR, &req) < 0 )
    {
        close(sock);
        return -1;
    }
    memcpy(&my_addr, &req.ifr_addr, sizeof(my_addr));
    strcpy(ipaddr, inet_ntoa(my_addr.sin_addr));
    close(sock);
    return 0;
}

////////////////////////////////////////////////////////////////////////////////
// 函数名：get_host_ip
// 描  述：获取主机IP
// 参  数：无
// 返回值：成功返回主机的IP地址，出错返回NULL
// 说  明：
////////////////////////////////////////////////////////////////////////////////
char *get_host_ip(void)
{
    int  i;                 //用于计数
    int  num;               //网络接口的数目
    int  sock_fd = -1;      //网络文件描述符
    char buff[BUFSIZ];      //用来存放所有接口信息的缓冲区
    struct ifconf  conf;    //网络接口配置结构体
    struct ifreq   *ifr;    //用来配置ip地址，激活接口，配置MTU等接口信息的结构体指针
    static char ipc_ip[16]; //存储ip地址的静态数组

	//数组清零
    memset(ipc_ip, 0x00, 16);

	//获取网络文件描述符
    sock_fd = socket(PF_INET, SOCK_DGRAM, 0);
	if(sock_fd < 0)
	{
		//hb_fnc_log(HB_LOG_ERR, "socket\n");
		return NULL;
	}
    conf.ifc_len = BUFSIZ; //表示用来存放所有接口信息的缓冲区长度
    conf.ifc_buf = buff;   //表示存放接口信息的缓冲区

	//获取所有网络接口信息
    ioctl(sock_fd, SIOCGIFCONF, &conf);

    num = conf.ifc_len / sizeof(struct ifreq); //网络接口的数目
    ifr = conf.ifc_req;                        //用来保存某个接口的信息

    for(i = 0; i < num; i++)
    {
        struct sockaddr_in *sin = (struct sockaddr_in *)(&ifr->ifr_addr);

        ioctl(sock_fd, SIOCGIFFLAGS, ifr); //获取接口标识

		//判断是否是本地的非loopback的IP地址
        if(((ifr->ifr_flags & IFF_LOOPBACK) == 0) && (ifr->ifr_flags & IFF_UP))
        {
        	//保存ip地址
            strcpy(ipc_ip, inet_ntoa(sin->sin_addr));
            close(sock_fd);
            return ipc_ip;
            //hb_fnc_log(HB_LOG_INFO, "%s (%s)\n", ifr->ifr_name, inet_ntoa(sin->sin_addr));
        }
        ifr++;
    }

    return NULL;
}

////////////////////////////////////////////////////////////////////////////////
// 函数名：close_sockfd
// 描述：关闭tcp网络套接字
// 参数：
//  ［IN］psockfd - 套接字指针。
// 返回值：1
// 说明：
//关闭tcp网络套接字，并初始化为-1
////////////////////////////////////////////////////////////////////////////////
int close_sockfd(int *sockfd)
{
	if(*sockfd > 0)
	{
		close(*sockfd);
	}
	*sockfd = -1;
	return 1;
}
