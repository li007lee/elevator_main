/*
 * file_opt.c
 *
 *  Created on: 2016-9-19
 *      Author: li007lee
 */

#include "my_include.h"
#include "file_opt.h"


/**********************************************************************/
/*******************************文件操作*******************************/
/**********************************************************************/
/*
 * Func:从配置文件读取字符串类型数据
 * Para:
 * 		IN AppName : 配置文件title名称，可以为空
 * 		IN KeyName : 需要查找的字段的名称
 * 		OUT ReturnValue : 存放返回值的数组
 * 		IN filename : 配置文件名称
 * 	Return: 成功返回0,失败返回-1
 */
int GetIniKeyString(char *AppName, char *KeyName, char *ReturnValue, char *filename)
{
	FILE *fp = NULL;
	char szLine[1024] = { 0 };
	char tmpstr[1024] = { 0 };
	int rtnval = 0;
	int i = 0;
	int flag = 0;
	char *tmp = NULL;

	memset(szLine, 0x0, sizeof(szLine));
	memset(tmpstr, 0x0, sizeof(tmpstr));

	if ((fp = fopen(filename, "r")) == NULL)
	{
		printf("have   no   such   file <%s>  \n", filename);
		return -1;
	}

	if (NULL == AppName)
	{
		flag = 1;
	}

	while (!feof(fp))
	{
		rtnval = fgetc(fp);
		if (rtnval == EOF)
		{
			printf("file eof!\n");
			break;
		}
		else
		{
			szLine[i++] = rtnval;
		}
		if ('\n' == rtnval)
		{
			i--;
			if ('\r' == szLine[i - 1])
				i--;
			szLine[i] = '\0';
			i = 0;
			//注释行
			if ((';' == szLine[0]) || ('#' == szLine[0]))
			{
				memset(szLine, 0x0, sizeof(szLine));
				continue;
			}
			else if (('/' == szLine[0]) && ('/' == szLine[1]))
			{
				memset(szLine, 0x0, sizeof(szLine));
				continue;
			}
			tmp = strchr(szLine, '=');
			if (1 == flag)
			{
				if ('[' == szLine[0])   //找到下一组[title]表示结束
				{
					fclose(fp);
					return -1;
				}
				else if ((tmp != NULL) && (0 == strncmp(szLine, KeyName, strlen(KeyName))))
				{
					fclose(fp);
					//找key对应变量
					memset(tmpstr, 0x0, sizeof(tmpstr));
					strcpy(tmpstr, tmp + 1);
					if (0 == strcmp(tmpstr, ""))
						return -1;
					strcpy(ReturnValue, tmpstr);

					return 0;
				}
			}
			else
			{
				sprintf(tmpstr, "[%s]", AppName);
				if (0 == strncmp(tmpstr, szLine, strlen(tmpstr)))
				{
					//找到title
					flag = 1;
				}
			}
			memset(szLine, 0x0, sizeof(szLine));
		}
	}
	fclose(fp);

	return -1;
}

/*
 * Func:从配置文件读取字整型数据
 * Para:
 * 		IN AppName : 配置文件title名称，可以为空
 * 		IN KeyName : 需要查找的字段的名称
 * 		IN DefaultValue : 如果没有配置文件中没有设定值时取用的默认值
 * 		IN filename : 配置文件名称
 * 	Return: 获取成功返回配置文件中的值，获取失败返回默认值
 */
int GetIniKeyInt(char *AppName, char *KeyName, int DefaultValue, char *filename)
{
	char value[256] = { 0 };
	int result = 0;

	//memset(value, 0x0, sizeof(value));
	result = GetIniKeyString(AppName, KeyName, value, filename);

	if (result < 0)
		return DefaultValue;   //增加默认值 FOR ZHEN 2012-10-19
	return atoi(value);
}


/*
 * Func:从配置文件修改字符串类型数据
 * Para:
 * 		IN AppName : 配置文件title名称，可以为空
 * 		IN KeyName : 需要查找的字段的名称
 * 		IN filename : 配置文件名称
 * 		IN Value : 设置的值
 * 	Return: 成功返回0,失败返回-1
 */
int SetConfigKeyValue(char *AppName,char *KeyName,char *filename,char *Value)
{
    FILE *fp=NULL;
    char Line[100];
    char Key[100];
    int FindApp=0;
    char fconfigure_content[1024] = {0};

    if(Value == NULL)
    	return -1;

    fp=fopen(filename, "r+");
    if(fp == NULL)
    {
        perror("\n\n[fconfigure.c] Open File Failed ");
        return -1;
    }

    memset(Key,0,sizeof(Key));

    strcpy(Key,KeyName);
    strcat(Key,"=");

    //不需要父节点，直接找节点名称
    if(AppName == NULL)
    {
        FindApp=1;
    }

    while(!feof(fp))
    {
        memset(Line,0,sizeof(Line));
        if(fgets(Line,sizeof(Line),fp) != NULL)
        {
            //找到大几点后，找子节点 如：TouchByte=
            if( (FindApp == 1) && (strstr(Line,Key) != NULL))
            {
                //保存所有内容
                strcat(Key,Value);
                strcat(Key,"\n");
                strcat(fconfigure_content,Key);
                continue;
            }
            strcat(fconfigure_content,Line);
        }
    }
    fclose(fp);

    //确认fconfigure_content有内容，否则有可能把touch.ini清空，导致开机不能启动
	if(strlen(fconfigure_content)>10)
	{
		//重新写入文件
		fp=fopen(filename,"w+");
		if(fp != NULL)
		{
			fwrite(fconfigure_content,strlen(fconfigure_content),1,fp);
			fclose(fp);
		}
	}


    return 0;
}


/**********************************************************************/
/******************************文件操作End******************************/
/**********************************************************************/
