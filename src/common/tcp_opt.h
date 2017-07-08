/*
 * tcp_opt.h
 *
 *  Created on: 2017年3月28日
 *      Author: root
 */

#ifndef TCP_OPT_H_
#define TCP_OPT_H_

#include "my_include.h"

//通过域名解析出相应的ip，超过timeout秒解析不出来，则返回失败-1，成功返回值大于0
int from_domain_to_ip(char *srv_ip, char *srv_domain, int timeout);
//tcp网络连接(域名)
int create_socket_connect_domain(int *psockfd, char *domain, int domain_port, int timeout);
//tcp网络连接(ip)
int create_socket_connect_ipaddr(int *psockfd, char *ipaddr, int port, int timeout);
//tcp网络数据发送
int send_data(int *psockfd, void *send_buf, int data_len, int timeout_s, int timeout_ms);
//tcp网络数据接收
int recv_data(int *psockfd, void *recv_buf, int recv_buf_len, int timeout);
//server模式监听端口
int setup_listen_socket(unsigned short port, int non_blocking_flag);
//设置网络文件描述符为阻塞模式
int make_socket_blocking(int sock);
//增大网络发送缓冲区的大小
unsigned int increase_send_buffer_to(int socket, unsigned int requested_size);
//增大网络接收缓冲区的大小
unsigned int increase_receive_buffer_to(int socket, unsigned int requested_size);
//检测端口是否被占用
int check_port(int port);
int get_dev_ip(char *eth, char *ipaddr);
//获取主机IP
char *get_host_ip(void);
//获取服务器端的UDP端口
int get_udp_server_port(void);
//设置报式套接字
int setup_datagram_socket(unsigned short port, int make_non_blocking);
//通过域名解析出相应的ip，超过timeout秒解析不出来，则返回失败-1，成功返回值大于0
int from_domain_to_ip(char *srv_ip, char *srv_domain, int timeout);
//关闭tcp网络套接字
int close_sockfd(int *sockfd);

#endif /* defined(__MapPort__thread_depend__) */
