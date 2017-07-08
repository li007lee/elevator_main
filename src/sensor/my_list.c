/*
 * my_list.c
 *
 *  Created on: 2016年8月2日
 *      Author: root
 */

#include "my_include.h"
#include "my_list.h"


/////////////////////////////////////////////////////////////////////////////////
// 函数描述：创建链表
// 入口参数：无
// 返回值：指向链表的指针
/////////////////////////////////////////////////////////////////////////////////
LIST_HANDLE list_create(HB_VOID)
{
	LIST_HANDLE plist = NULL;
	plist = (LIST_HANDLE)malloc(sizeof(LIST_OBJ));

	plist->p_end  = NULL;
	plist->p_head = NULL;
	plist->cnt	 = 0;

	return	plist;
}


/////////////////////////////////////////////////////////////////////////////////
// 函数描述：链表复位
// 入口参数：指向链表的指针
// 返回值：无
/////////////////////////////////////////////////////////////////////////////////
HB_VOID list_reset(LIST_HANDLE plist)
{
	if (NULL == plist)
	{
		return;
	}

	while(plist->cnt > 0)
	{
		list_remove_head_node(plist);
	}
	return;
}


/////////////////////////////////////////////////////////////////////////////////
// 函数描述：销毁链表
// 入口参数：指向链表的指针
// 返回值：无
/////////////////////////////////////////////////////////////////////////////////
HB_VOID list_destroy(LIST_HANDLE plist)
{
	list_reset(plist);
	free(plist);
}



/////////////////////////////////////////////////////////////////////////////////
// 函数描述：创建链表中的节点
// 入口参数：指向链表的指针
// 返回值：链表节点的指针
/////////////////////////////////////////////////////////////////////////////////
static LIST_NODE_HANDLE list_create_node(LIST_HANDLE plist)
{

	LIST_NODE_HANDLE p_node;	// 节点指针

	p_node = (LIST_NODE_HANDLE)malloc(sizeof(LIST_NODE_OBJ));

	// 创建节点信息
	p_node->p_value= (HB_CHAR*)plist->new_node();
	p_node->len	= 0;
	p_node->p_next = NULL;

	return p_node;
}


/////////////////////////////////////////////////////////////////////////////////
// 函数描述：向链表尾添加节点
// 入口参数：指向链表的指针
// 返回值：存放数据的指针
/////////////////////////////////////////////////////////////////////////////////
HB_VOID* list_add_node_to_end(LIST_HANDLE plist)
{

	LIST_NODE_HANDLE p_node;

	// 创建节点
	p_node = list_create_node(plist);
	if(p_node == NULL)
	{
		return NULL;
	}
	plist->cnt++;

	if(plist->p_head == NULL)
	{
		plist->p_head = p_node;
	}
	else
	{
		plist->p_end->p_next = p_node;
	}
	plist->p_end = p_node;

	return p_node->p_value;
}



/////////////////////////////////////////////////////////////////////////////////
// 函数描述：从链表头取出节点
// 入口参数：指向链表的指针
// 返回值：链表节点数目
/////////////////////////////////////////////////////////////////////////////////
HB_S32	list_remove_head_node(LIST_HANDLE plist)
{
	LIST_NODE_HANDLE p_node;
	switch(plist->cnt)
	{
		case 0:
			break;

		case 1:
			plist->del_node((HB_VOID*)plist->p_head->p_value);
			free(plist->p_head);
			plist->p_head = NULL;
			plist->p_end  = NULL;
			plist->cnt = 0;
			break;

		default:
			p_node = plist->p_head->p_next;
			plist->del_node((HB_VOID*)plist->p_head->p_value);
			free(plist->p_head);
			plist->p_head = p_node;
			plist->cnt--;
			break;
	}
	return plist->cnt;
}
