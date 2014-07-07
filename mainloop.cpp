//
//  aroundMatch.cpp
//  mycoin-account
//
//  Created by lx on 13-12-25.
//  Copyright (c) 2013年 lx. All rights reserved.
//

#include <stdio.h>
#include <unistd.h>
#include <uv.h>
#include <iostream>
#include <istream>
#include <ostream>
#include <string>

#include "quote.h"
#include "aroundMatch.h"
#include "readerwriterqueue.h"
#include "account/Account.h"
#include "RoutineQuotation.h"

#include <hiredis/hiredis.h>
#include <hiredis/async.h>
#include <hiredis/adapters/libuv.h>
#include "Singleton.h"
#include "RedisPublisher.h"
#include "message/message_extend.h"

#include "WithdrawProcessor.h"
#include "QuoteProcessor.h"
#include "MessageProcessor.h"
#include "AccountExchangeProcessor.h"
#include "ContractNoteProcessor.h"

#include "queue/queue_quote.h"
#include "account/account_message.h"
#include "notify/notify.h"

using namespace std;
using namespace moodycamel;
static uv_loop_t *loop;

uv_buf_t alloc_message_buffer(uv_handle_t* handle, size_t suggested_size) {
    size_t len = suggested_size > 0 ? suggested_size : sizeof(message_t);
    char* base = (char *)malloc(len);
    return uv_buf_init(base, len);
}


void on_client_close(uv_handle_t* handle){
    free(handle);
}

void on_message_received(uv_stream_t* stream,ssize_t nread, uv_buf_t buf){
    do{
        if(nread < 0)
            break;
        assert(nread == buf.len);
        
        message_t msg;
        if(UNKOWN_MESSAGE == message_convert(buf.base, buf.len, &msg){
            break;
        }
        //消息分类， quote类 withdraw，quote，不同用户并行，可用异步。同一用户前一quote，withdraw次序得保证。方法1 withdraw检查refkey，如果不存在，则设定该key，给出status，该key设一个withraw key， 好让后到得quote找到，然后简单抛弃，留待以后处理。quote 检查key，如果存在，则是重复quote 或是withdraw所设。找到该withdraw key，设置该withdraw staus finished。这些动作使用lua做最好。方法2 withdraw插入后到match，先跑一遍，如果没找到，有可能是withdraw quote 跑到了前面，那么插入到一个队列。 每次quote到时，都检查一次。 方法2 在match中检查比较耗时。采用方法1
           //异步插入，检查 在callback中出错
           //exchange类， 不同用户基本上不会冲突，可在主线程运行，
           //在contractnote note可并行，异步
           //redis 的集群可按user来设置 ，note 进行记帐时候，会涉及到多个机器，多个机器之间怎么保证同步
        
           //关键是连接mongodb，couchdb等外部资源的客户端，要有好的异步设计。才能在应用上提高吞吐
           //node.js js 有好的异步设计，vert.x呢？
           //node.js 对外部资源的异步使用封装得怎样？vert.x呢？
           //eventbus内部使用无锁队列，使用event bus，回调函数插入event(成功或失败)到event bus，
           //应用程序只需要处理event bus
           //event switch类要预先定制好多个callback事件，尤其是web应用相关的
           //web服务器采用的fastcgi接口如果异步实现，效率能提高多少
           
           ReaderWriterQueue<message_t> * main_msg_queue = (ReaderWriterQueue<message_t> *)stream->data;
        main_msg_queue->enqueue(msg);
    }while(0);
    free((void *)buf.base);
    uv_close((uv_handle_t*) stream, on_client_close);
}


void on_client_connection(uv_stream_t *server, int status) {
    if (status == -1) {
        return;
    }
    
    uv_tcp_t *client = (uv_tcp_t*) malloc(sizeof(uv_tcp_t));
    uv_tcp_init(loop, client);

    client->data = server->data;
    if (uv_accept(server, (uv_stream_t*) client) == 0) {
        uv_read_start((uv_stream_t*) client, alloc_message_buffer, on_message_received);
    }else {
        uv_close((uv_handle_t*) client, on_client_close);
    }
}


void routine_quote_cb(uv_timer_t *handle, int){
    publisher.publish(Singleton<RoutineQuotation>::instance());
}

template<> MessageProcessorMap * Singleton<MessageProcessorMap, 1>::_instance = NULL;
           
int mainloop(int timeout, const string & host, int port, int port2
                    ,const string & publish_host, int publish_port
                    ,ReaderWriterQueue<message_t> * main_match_msg_queue
                    ,ReaderWriterQueue<message_t> * main_io_msg_queue
                    ,ReaderWriterQueue<message_t> * match_msg_queue
                    ,ReaderWriterQueue<message_t> * io_msg_quque){
    
    loop = uv_loop_new();

    uv_tcp_t server;
    uv_tcp_init(loop, &server);
    server->data = (void *)main_io_msg_queue;
    
    struct sockaddr_in bind_addr = uv_ip4_addr(host.c_str(), port);
    uv_tcp_bind(&server, bind_addr);
    int r = uv_listen((uv_stream_t*) &server, 128, on_client_connection);
    if (r) {
        fprintf(stderr, "Listen error %s\n", uv_err_name(uv_last_error(loop)));
        return 1;
    }
    
    RedisPublisher  publisher;
    publisher.connect("localhost", 6379);
    redisLibuvAttach(publisher.getContext(),loop);

    uv_timer_t timer_req;
    uv_timer_init(loop, &timer_req);
    uv_timer_start(&timer_req, routine_quote_cb, timeout, timeout);
    
    int len = 2;
    ReaderWriterQueue<message_t> * inqueue[len];
    inqueue[0] = main_match_msg_queue;
    inqueue[1] = main_io_msg_queue;
    message_t msg;
    list<message_t> out_msg_list;
    extern bool g_run;
    while(g_run){
        for(int i=0; i++; i<len){
            if(inqueue[i].try_dequeue(msg)){
                switch(msg.quote.status){
                    case STATUS_NEW:
                        if(msg.quote.msg_type == ){
                            
                        }else{
                            
                        }
                        io_msg_quque.enqueue(msg);
                        break;
                    case STATUS_ACCEPTED:
                        match_msg_quque.enqueue(msg);
                        break;
                    case STATUS_PROCESSED:
                        io_msg_quque.enqueue(msg);
                        break;
                    case STATUS_FINISHED:
                        Singleton<RoutineQuation>::instance().update(&msg);
                        publisher.update(&msg);
                        break;
                    default:
                        break;
            }
        }
        
        uv_run(loop, UV_RUN_NOWAIT);
    }

    return 0;
}