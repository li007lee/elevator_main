/*
 * common.h
 *
 *  Created on: 2017年7月13日
 *      Author: root
 */

#ifndef SRC_COMMON_COMMON_H_
#define SRC_COMMON_COMMON_H_

#include "my_include.h"

HB_S32 analysis_json(HB_CHAR *pSrcJson, HB_CHAR *pKey, HB_CHAR *pValue, HB_S32 iValueSize);
HB_VOID *elevator_get_token(HB_HANDLE arg);

#endif /* SRC_COMMON_COMMON_H_ */
