/**
 * @socket Socket.c
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
#include <libobject/utils/dbg/debug.h>
#include <libobject/event/event_base.h>
#include <libobject/utils/config/config.h>
#include <libobject/utils/timeval/timeval.h>
#include <libobject/net/socket.h>

static int __construct(Socket *socket,char *init_str)
{
    allocator_t *allocator = socket->obj.allocator;
    configurator_t * c;
    char buf[2048];

    dbg_str(EV_DETAIL,"socket construct, socket addr:%p",socket);


    return 0;
}

static int __deconstrcut(Socket *socket)
{
    dbg_str(EV_DETAIL,"socket deconstruct,socket addr:%p",socket);

    return 0;
}

static int __set(Socket *socket, char *attrib, void *value)
{
    if (strcmp(attrib, "set") == 0) {
        socket->set = value;
    } else if (strcmp(attrib, "get") == 0) {
        socket->get = value;
    }
    else if (strcmp(attrib, "construct") == 0) {
        socket->construct = value;
    } else if (strcmp(attrib, "deconstruct") == 0) {
        socket->deconstruct = value;
    } else {
        dbg_str(EV_DETAIL,"socket set, not support %s setting",attrib);
    }

    return 0;
}

static void *__get(Socket *obj, char *attrib)
{
    if (strcmp(attrib, "") == 0) {
    } else {
        dbg_str(EV_WARNNING,"socket get, \"%s\" getting attrib is not supported",attrib);
        return NULL;
    }
    return NULL;
}

static class_info_entry_t socket_class_info[] = {
    [0 ] = {ENTRY_TYPE_OBJ,"Obj","obj",NULL,sizeof(void *)},
    [1 ] = {ENTRY_TYPE_FUNC_POINTER,"","set",__set,sizeof(void *)},
    [2 ] = {ENTRY_TYPE_FUNC_POINTER,"","get",__get,sizeof(void *)},
    [3 ] = {ENTRY_TYPE_FUNC_POINTER,"","construct",__construct,sizeof(void *)},
    [4 ] = {ENTRY_TYPE_FUNC_POINTER,"","deconstruct",__deconstrcut,sizeof(void *)},
    [5 ] = {ENTRY_TYPE_END},
};
REGISTER_CLASS("Socket",socket_class_info);

void test_obj_socket()
{
    Socket *socket;
    allocator_t *allocator = allocator_get_default_alloc();
    configurator_t * c;
    char *set_str;
    cjson_t *root, *e, *s;
    char buf[2048];

    c = cfg_alloc(allocator); 
    dbg_str(EV_SUC, "configurator_t addr:%p",c);
    cfg_config(c, "/Socket", CJSON_STRING, "name", "alan socket") ;  

    socket = OBJECT_NEW(allocator, Socket,c->buf);

    object_dump(socket, "Socket", buf, 2048);
    dbg_str(EV_DETAIL,"Socket dump: %s",buf);

    object_destroy(socket);
    cfg_destroy(c);
}


