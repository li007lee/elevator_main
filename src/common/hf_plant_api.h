/*
 * hf_plant_api.h
 *
 *  Created on: 2015年1月5日
 *      Author: root
 */

#ifndef HF_PLANT_API_H_
#define HF_PLANT_API_H_


typedef enum {
	TOKEN = 1,
	UPLOAD_PIC
} OPT_TYPE;


HB_S32 api_get_token(HB_S32 *sockfd, HB_CHAR *buff, HB_S32 size);
//计算MD5
int Calculate_MD5(char *desc, const char *src);
//获取MAC
int get_sys_mac(char *sn, int sn_size);
//获取序列号，mac后8位
int get_sys_sn(char *sn, int sn_size);

#endif /* HF_PLANT_API_H_ */
