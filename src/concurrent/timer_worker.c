/**
 * @file timer_worker.c
 * @Synopsis  
 * @author alan lin
 * @version 
 * @date 2017-10-23
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
#include <libobject/utils/dbg/debug.h>
#include <libobject/utils/config/config.h>
#include <libobject/utils/timeval/timeval.h>
#include <libobject/concurrent/worker.h>
#include <libobject/concurrent/producer.h>

Worker *timer_worker(allocator_t *allocator,
                     int fd, int ev_events,
                     struct timeval *ev_tv, void *ev_callback,
                     void *ev_arg, void *work_callback)
{
    Producer *producer = global_get_default_producer();
    Worker *worker = NULL;

    sleep(1);

    worker = OBJECT_NEW(allocator, Worker, NULL);

    if (ev_arg == NULL) {
        ev_arg = worker;
    }

    worker->assign(worker, fd, ev_events, ev_tv, ev_callback, ev_arg, work_callback);
    worker->enroll(worker, producer);

    return worker;
}

int timer_worker_destroy(Worker *worker)
{
    return object_destroy(worker);
}

static void
test_timeout_cb(int fd, short event, void *arg)
{
    Worker *worker = (Worker *)arg;
    struct timeval newtime, difference;
    double elapsed;
    static struct timeval lasttime;

    gettimeofday(&newtime, NULL);
    timeval_sub(&newtime, &lasttime, &difference);

    elapsed  = difference.tv_sec + (difference.tv_usec / 1.0e6);
    lasttime = newtime;

    dbg_str(DBG_SUC,"timeout_cb called at %d: %.3f seconds elapsed.",
            (int)newtime.tv_sec, elapsed);
    dbg_str(DBG_DETAIL,"arg addr:%p", arg);
    worker->work_callback(NULL);

    return;
}

static void test_work_callback(void *task)
{
    dbg_str(DBG_SUC,"process timer task");
}

#if 1
void test_obj_timer_worker()
{
    allocator_t *allocator = allocator_get_default_alloc();
    Worker *worker;
    struct timeval ev_tv;

    ev_tv.tv_sec  = 2;
    ev_tv.tv_usec = 0;

    worker = timer_worker(allocator, -1, EV_READ | EV_PERSIST,
                          &ev_tv, test_timeout_cb, NULL,
                          test_work_callback);
    pause();
    timer_worker_destroy(worker);
}

#else
void test_obj_timer_worker()
{
    Producer *producer     = global_get_default_producer();
    allocator_t *allocator = allocator_get_default_alloc();
    Worker *worker;
    struct timeval ev_tv;

    ev_tv.tv_sec  = 2;
    ev_tv.tv_usec = 0;

    sleep(1);

    worker = OBJECT_NEW(allocator, Worker, NULL);
    dbg_str(DBG_DETAIL,"worker addr:%p", worker);
    worker->assign(worker, -1, EV_READ | EV_PERSIST,
                   ev_tv, test_timeout_cb, worker, test_work_callback);
    worker->enroll(worker, producer);

    pause();
    object_destroy(worker);
}

#endif
