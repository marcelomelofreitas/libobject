#ifndef __OBJ_LIST_H__
#define __OBJ_LIST_H__

#include <stdio.h>
#include <libobject/utils/dbg/debug.h>
#include <libobject/core/obj.h>
#include <libobject/core/iterator.h>

typedef struct _list_s List;

struct _list_s{
	Obj obj;

	int (*construct)(List *list,char *init_str);
	int (*deconstruct)(List *list);
	int (*set)(List *list, char *attrib, void *value);
    void *(*get)(void *obj, char *attrib);

	/*virtual methods reimplement*/
    int (*push_back)(List *list,void *value);
    int (*insert_after)(List *list,Iterator *iter, void *value);
    int (*detach_front)(List *list,Iterator *iter);
    int (*free_detached)(List *list,Iterator *iter);
    int (*del)(List *list,Iterator *iter);
    void (*for_each)(List *list,void (*func)(Iterator *iter));
    void (*for_each_arg2)(List *list,void (*func)(Iterator *iter, void *arg),void *arg);
    Iterator *(*begin)(List *list);
    Iterator *(*end)(List *list);
    int (*destroy)(List *list);

#define MAX_NAME_LEN 50
    char name[MAX_NAME_LEN];
#undef MAX_NAME_LEN
	int value_size;

};

#endif