/*
 * sensor_opt.h
 *
 *  Created on: 2017年4月12日
 *      Author: root
 */

#ifndef SENSOR_TO_NET_SINGLE_SENSOR_OPT_H_
#define SENSOR_TO_NET_SINGLE_SENSOR_OPT_H_

struct sensor_context
{
	int dev_fd;	//陀螺仪设备的文件描述符
	float sensitivity;//敏感度调节
};


typedef struct _SENSOR_DEV_INFO
{
	int sock_fd; //连接大板数据转发服务器的套接字
	int exit_flag;

	pthread_t thread_timer_id; //定时器线程id
	pthread_t accl_thread_id; //读取加速度传感器数据线程id
	pthread_t gyro_thread_id; //读取陀螺仪传感器数据线程id

	struct sensor_context accl_ctx;
	struct sensor_context gyro_ctx;

	long int accl_x;
	long int accl_y;
	long int accl_z;
	long int gyro_x;
	long int gyro_y;
	long int gyro_z;
//	char mac[32];

	pthread_mutex_t mutex_lock_data;
}SENSOR_DEV_INFO;

typedef enum {
	ALLSENSOR = 0,
	ACCELERATED = 1,
	GYROSCOPE = 2
}DataType;


//数据发送结构体
typedef struct sensor_data
{
	char message_head[32]; //通信协议头，固定为“hb_sensor_data_to_MS”
	int i_data_type; //1为加速度数据  2为陀螺仪数据 0为加速度和陀螺仪合二为一数据
	int i_data_length; //数据长度
} SENDDATA;


extern SENSOR_DEV_INFO sensor_ctx; //定义传感器

//读取加速度数据
void *ReadAcclData(void * arg);
//读取陀螺仪数据
void *ReadGyroData(void * arg);

//发送传感器数据
int SendSensorData(long int accl_x, long int accl_y, long int accl_z, long int gyro_x, long int gyro_y, long int gyro_z);

#endif /* SENSOR_TO_NET_SINGLE_SENSOR_OPT_H_ */
