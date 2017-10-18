/**
 * @thread Thread.c
 * @Synopsis  
 * @author alan lin
 * @version 
 * @date 2017-09-27
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
#include <libobject/core/event_thread.h>
#include <libobject/event/select_base.h>

static int __construct(Event_Thread *thread, char *init_str)
{
    allocator_t *allocator = thread->parent.obj.allocator;
    Event_Base *eb;

    dbg_str(DBG_DETAIL,"Event_Thread construct, thread addr:%p",thread);

    thread->eb = (Event_Base *)OBJECT_NEW(allocator, Select_Base, NULL);

    return 0;
}

static int __deconstrcut(Event_Thread *thread)
{
    int ret = 0;

    dbg_str(DBG_DETAIL,"Event thread deconstruct,thread addr:%p",thread);
    object_destroy(thread->eb);

    return ret;
}

static int __set(Event_Thread *thread, char *attrib, void *value)
{
    if (strcmp(attrib, "set") == 0) {
        thread->set = value;
    } else if (strcmp(attrib, "get") == 0) {
        thread->get = value;
    } else if (strcmp(attrib, "construct") == 0) {
        thread->construct = value;
    } else if (strcmp(attrib, "deconstruct") == 0) {
        thread->deconstruct = value;
    } else if (strcmp(attrib, "add_event") == 0) {
        thread->add_event = value;
    } else if (strcmp(attrib, "del_event") == 0) {
        thread->del_event = value;
    } /*inherited methods*/
    else if (strcmp(attrib, "start") == 0) {
        thread->start = value;
    } else if (strcmp(attrib, "set_start_routine") == 0) {
        thread->set_start_routine = value;
    } else if (strcmp(attrib, "set_start_arg") == 0) {
        thread->set_start_arg = value;
    } /*vitural methods*/
    else if (strcmp(attrib, "start_routine") == 0) {
        thread->start_routine = value;
    }
    else {
        dbg_str(DBG_DETAIL,"thread set, not support %s setting",attrib);
    }

    return 0;
}

static void *__get(Thread *obj, char *attrib)
{
    if (strcmp(attrib, "") == 0) {
    } else {
        dbg_str(DBG_WARNNING,"thread get, \"%s\" getting attrib is not supported",attrib);
        return NULL;
    }

    return NULL;
}

static int __add_event(Event_Thread *thread, void *event)
{
    dbg_str(DBG_DETAIL,"add event");

    if (write(thread->ctl_write, "r", 1) != 1) {
        dbg_str(DBG_ERROR,"ctl_write error");
        return -1;
    }

    return 0;
}

static int __del_event(Event_Thread *thread, void *event)
{
    dbg_str(DBG_DETAIL,"del event");
}

static class_info_entry_t event_thread_class_info[] = {
    [0 ] = {ENTRY_TYPE_OBJ, "Thread", "parent", NULL, sizeof(void *)}, 
    [1 ] = {ENTRY_TYPE_FUNC_POINTER, "", "set", __set, sizeof(void *)}, 
    [2 ] = {ENTRY_TYPE_FUNC_POINTER, "", "get", __get, sizeof(void *)}, 
    [3 ] = {ENTRY_TYPE_FUNC_POINTER, "", "construct", __construct, sizeof(void *)}, 
    [4 ] = {ENTRY_TYPE_FUNC_POINTER, "", "deconstruct", __deconstrcut, sizeof(void *)}, 
    [5 ] = {ENTRY_TYPE_FUNC_POINTER, "", "add_event", __add_event, sizeof(void *)}, 
    [6 ] = {ENTRY_TYPE_FUNC_POINTER, "", "del_event", __del_event, sizeof(void *)}, 
    [7 ] = {ENTRY_TYPE_IFUNC_POINTER, "", "start", NULL, sizeof(void *)}, 
    [8 ] = {ENTRY_TYPE_IFUNC_POINTER, "", "set_start_routine", NULL, sizeof(void *)}, 
    [9 ] = {ENTRY_TYPE_IFUNC_POINTER, "", "set_start_arg", NULL, sizeof(void *)}, 
    [10] = {ENTRY_TYPE_VFUNC_POINTER, "", "start_routine", NULL, sizeof(void *)}, 
    [11] = {ENTRY_TYPE_END}, 
};
REGISTER_CLASS("Event_Thread",event_thread_class_info);

static void test_ev_callback(int fd, short events, void *arg)
{
    char buf[255];
    int len;

    dbg_str(DBG_SUC,"hello world, event");
    if (read(fd, buf, 1) != 1) {
        dbg_str(DBG_WARNNING,"ctl_read error");
        return ;
    }
}

static void *test_func(void *arg)
{
    Event_Thread *et = (Event_Thread *)arg;
    Event_Base *eb   = et->eb;
    event_t *event   = &et->ctl_read_event;
    int fds[2]       = {0};
    char buf[2048];

    dbg_str(DBG_SUC,"test func, arg addr:%p",arg);

    if (pipe(fds)) {
        dbg_str(DBG_ERROR, "create pipe");
        return NULL;
    }

    et->ctl_read  = fds[0];
    et->ctl_write = fds[1];

    dbg_str(DBG_DETAIL,"read fd=%d, write fd=%d", et->ctl_read, et->ctl_write);

    /*
     *object_dump(eb, "Select_Base", buf, 2048);
     *dbg_str(DBG_DETAIL,"Select_Base dump: %s",buf);
     */

    event->ev_fd              = et->ctl_read;
    event->ev_events          = EV_READ | EV_PERSIST;
    event->ev_timeout.tv_sec  = 0;
    event->ev_timeout.tv_usec = 0;
    event->ev_callback        = test_ev_callback;
    event->ev_arg             = event;
    eb->add(eb, event);

    eb->loop(eb);
}

void test_obj_event_thread()
{
    Event_Thread *thread;
    allocator_t *allocator = allocator_get_default_alloc();
    char buf[2048];

    thread = OBJECT_NEW(allocator, Event_Thread, NULL);

    object_dump(thread, "Thread", buf, 2048);
    dbg_str(DBG_DETAIL,"Thread dump: %s",buf);
    thread->set_start_routine(thread, test_func);
    thread->set_start_arg(thread, thread);
    thread->start(thread);

    sleep(1);
    thread->add_event(thread, NULL);

    sleep(10);

    pause();

    object_destroy(thread);
}