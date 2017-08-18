#ifndef _MEM_APP_H_
#define _MEM_APP_H_

#include <stdlib.h>
#include <string.h>

#define TRY     __try(&except)
#define EXCEPT  __except
#define ENDTRY  __endtry(&except)

#define __ALLOC_COUNT				8
#define _MAX_BLIST_ITEM				32
#define XMEM_NEWX(mem,size)			xmem_allocz(mem,size)
#define XMEM_FREE(mem, pdata)		xmem_free(mem, pdata)
#define OFFSET(type, member)		(int)(&((type *)0)->member)

//#pragma once //the same use as #ifndef #define #endif for avoid reinclude head file ,but concern about compiler ,so may be no use
typedef struct mem_block_s
{
    int index;
    struct mem_block_s  *next;
} mem_block_t;

typedef struct dlist_s
{
    struct dlist_s  *next;
    struct dlist_s  *prev;
} dlist_t;

typedef struct big_block_s
{
    dlist_t         list;
    mem_block_t     block;
} big_block_t;

typedef struct xml_mem_s
{
	int _mem_size_log;
    mem_block_t *block_list;
    mem_block_t *mem_blist[_MAX_BLIST_ITEM];
    dlist_t big_block_list;
    struct except_s *except;
} mem_t;

void xmem_init(mem_t *mem, struct except_s *except,int size_log);//size_log:1<<size_log;
void *xmem_alloc(mem_t *mem, unsigned size);
void *xmem_allocz(mem_t *mem, unsigned size);
void xmem_free(mem_t *mem, void *ptr);
void *xmem_realloc(mem_t *mem, void *ptr, unsigned size);
void *xmem_resize(mem_t *mem, void *ptr, unsigned size);
void xmem_free_all(mem_t *mem);

#endif
