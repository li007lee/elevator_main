/*
 * file_opt.h
 *
 *  Created on: 2016-9-19
 *      Author: li007lee
 */

#ifndef CONFIG_H_
#define CONFIG_H_

//从配置文件读取字符串类型数据
int GetIniKeyString(char *AppName, char *KeyName, char *ReturnValue, char *filename);
//从配置文件读取字整型数据
int GetIniKeyInt(char *AppName, char *KeyName, int DefaultValue, char *filename);
//修改字符串类型数据
int SetConfigKeyValue(char *AppName,char *KeyName,char *filename,char *Value);

#endif /* CONFIG_H_ */
