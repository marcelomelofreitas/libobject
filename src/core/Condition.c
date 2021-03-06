/**
 * @file Condition.c
 * @synopsis 
 * @author a1an1in@sina.com
 * @version 
 * @date 2017-10-07
 */
/* Copyright (c) 2015-2020 alan lin <a1an1in@sina.com>
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 * notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 * notice, this list of conditions and the following disclaimer in the
 * documentation and/or other materials provided with the distribution.
 * 3. The name of the author may not be used to endorse or promote products
 * derived from this software without specific prior written permission.
 * 
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 * IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
 * NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
 * THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 * 
 */
#include <stdio.h>
#include <unistd.h>
#include <libobject/utils/dbg/debug.h>
#include <libobject/event/event_base.h>
#include <libobject/utils/config/config.h>
#include <libobject/utils/timeval/timeval.h>
#include <libobject/core/condition.h>

static int __construct(Condition *condition,char *init_str)
{
    allocator_t *allocator = condition->obj.allocator;
    configurator_t * c;
    char buf[2048];

    dbg_str(DBG_DETAIL,"condition construct, condition addr:%p",condition);

    return 0;
}

static int __deconstrcut(Condition *condition)
{
    dbg_str(DBG_DETAIL,"condition deconstruct,condition addr:%p",condition);
    int ret;
    void *tret;

    return 0;
}

static int __set(Condition *condition, char *attrib, void *value)
{
    if (strcmp(attrib, "set") == 0) {
        condition->set = value;
    } else if (strcmp(attrib, "get") == 0) {
        condition->get = value;
    } else if (strcmp(attrib, "construct") == 0) {
        condition->construct = value;
    } else if (strcmp(attrib, "deconstruct") == 0) {
        condition->deconstruct = value;
    }
    else if (strcmp(attrib, "setlock") == 0) {
        condition->setlock = value;
    } else if (strcmp(attrib, "wait") == 0) {
        condition->wait = value;
    } else if (strcmp(attrib, "signal") == 0) {
        condition->signal = value;
    } else if (strcmp(attrib, "broadcast") == 0) {
        condition->broadcast = value;
    }
    else {
        dbg_str(DBG_DETAIL,"condition set, not support %s setting",attrib);
    }

    return 0;
}

static void *__get(Condition *obj, char *attrib)
{
    if (strcmp(attrib, "") == 0) {
    } else {
        dbg_str(DBG_WARNNING,"condition get, \"%s\" getting attrib is not supported",attrib);
        return NULL;
    }
    return NULL;
}

static int __setlock(Condition *condition, Lock *lock)
{
    dbg_str(DBG_DETAIL,"not support now");
}

static int __wait(Condition *condition)
{
    dbg_str(DBG_DETAIL,"not support now");
}

static int __signal(Condition *condition)
{
    dbg_str(DBG_DETAIL,"not support now");
}

static int __broadcast(Condition *condition)
{
    dbg_str(DBG_DETAIL,"not support now");
}

static class_info_entry_t condition_class_info[] = {
    [0] = {ENTRY_TYPE_OBJ,"Obj","obj",NULL,sizeof(void *)},
    [1] = {ENTRY_TYPE_FUNC_POINTER,"","set",__set,sizeof(void *)},
    [2] = {ENTRY_TYPE_FUNC_POINTER,"","get",__get,sizeof(void *)},
    [3] = {ENTRY_TYPE_FUNC_POINTER,"","construct",__construct,sizeof(void *)},
    [4] = {ENTRY_TYPE_FUNC_POINTER,"","deconstruct",__deconstrcut,sizeof(void *)},
    [5] = {ENTRY_TYPE_VFUNC_POINTER,"","setlock",__setlock,sizeof(void *)},
    [6] = {ENTRY_TYPE_VFUNC_POINTER,"","wait",__wait,sizeof(void *)},
    [7] = {ENTRY_TYPE_VFUNC_POINTER,"","signal",__signal,sizeof(void *)},
    [8] = {ENTRY_TYPE_VFUNC_POINTER,"","broadcast",__broadcast,sizeof(void *)},
    [9] = {ENTRY_TYPE_END},
};
REGISTER_CLASS("Condition",condition_class_info);

void test_obj_condition()
{
    Condition *condition;
    allocator_t *allocator = allocator_get_default_alloc();
    configurator_t * c;
    char *set_str;
    cjson_t *root, *e, *s;
    char buf[2048];

    c = cfg_alloc(allocator); 
    dbg_str(DBG_SUC, "configurator_t addr:%p",c);
    /*
     *cfg_config(c, "/Condition", CJSON_STRING, "name", "alan condition") ;  
     */

    condition = OBJECT_NEW(allocator, Condition, NULL);

    object_dump(condition, "Condition", buf, 2048);
    dbg_str(DBG_DETAIL,"Condition dump: %s",buf);

    object_destroy(condition);
    cfg_destroy(c);
}
