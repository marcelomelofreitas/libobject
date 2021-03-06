/**
 * @file Lock.c
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
#include <libobject/core/lock.h>

static int __construct(Lock *lock,char *init_str)
{
    allocator_t *allocator = lock->obj.allocator;
    configurator_t * c;
    char buf[2048];

    dbg_str(DBG_DETAIL,"lock construct, lock addr:%p",lock);

    return 0;
}

static int __deconstrcut(Lock *lock)
{
    dbg_str(DBG_DETAIL,"lock deconstruct,lock addr:%p",lock);
    int ret;
    void *tret;

    return 0;
}

static int __set(Lock *lock, char *attrib, void *value)
{
    if (strcmp(attrib, "set") == 0) {
        lock->set = value;
    } else if (strcmp(attrib, "get") == 0) {
        lock->get = value;
    } else if (strcmp(attrib, "construct") == 0) {
        lock->construct = value;
    } else if (strcmp(attrib, "deconstruct") == 0) {
        lock->deconstruct = value;
    }
    else if (strcmp(attrib, "lock") == 0) {
        lock->lock = value;
    } else if (strcmp(attrib, "trylock") == 0) {
        lock->trylock = value;
    } else if (strcmp(attrib, "unlock") == 0) {
        lock->unlock = value;
    }
    else {
        dbg_str(DBG_DETAIL,"lock set, not support %s setting",attrib);
    }

    return 0;
}

static void *__get(Lock *obj, char *attrib)
{
    if (strcmp(attrib, "") == 0) {
    } else {
        dbg_str(DBG_WARNNING,"lock get, \"%s\" getting attrib is not supported",attrib);
        return NULL;
    }
    return NULL;
}

static class_info_entry_t lock_class_info[] = {
    [0] = {ENTRY_TYPE_OBJ,"Obj","obj",NULL,sizeof(void *)},
    [1] = {ENTRY_TYPE_FUNC_POINTER,"","set",__set,sizeof(void *)},
    [2] = {ENTRY_TYPE_FUNC_POINTER,"","get",__get,sizeof(void *)},
    [3] = {ENTRY_TYPE_FUNC_POINTER,"","construct",__construct,sizeof(void *)},
    [4] = {ENTRY_TYPE_FUNC_POINTER,"","deconstruct",__deconstrcut,sizeof(void *)},
    [5] = {ENTRY_TYPE_VFUNC_POINTER,"","lock",NULL,sizeof(void *)},
    [6] = {ENTRY_TYPE_VFUNC_POINTER,"","trylock",NULL,sizeof(void *)},
    [7] = {ENTRY_TYPE_VFUNC_POINTER,"","unlock",NULL,sizeof(void *)},
    [8] = {ENTRY_TYPE_END},
};
REGISTER_CLASS("Lock",lock_class_info);
