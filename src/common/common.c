/*
 * common.c
 *
 *  Created on: 2017年7月13日
 *      Author: root
 */

#include "my_include.h"

#include "common.h"
#include "cJSON.h"

/****************************************
 * Function: 解析json串
 * @param pSrcJson: [IN]原始json串
 * @param pKey: [IN] 需要查找的key
 * @param pValue: [OUT] 存储找到的key的结果
 * @param iValueSize: [IN] pValue的大小
 *
 * @return : 成功返回0
 ****************************************/
int analysis_json(char *pSrcJson, char *pKey, char *pValue, int iValueSize)
{
	cJSON *p_json = cJSON_Parse(pSrcJson);
	if(NULL == p_json)
	{
		return -1;
	}
	cJSON *p_sub = cJSON_GetObjectItem(p_json, pKey);
	if(NULL == p_sub)
	{
		cJSON_Delete(p_json);
		return -1;
	}
	strncpy(pValue, p_sub->valuestring, iValueSize);

	cJSON_Delete(p_json);
	return 0;
}
