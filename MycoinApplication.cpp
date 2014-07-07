//
//  MycoinApplication.cpp
//  mycoin-account
//
//  Created by lx on 13-12-25.
//  Copyright (c) 2013年 lx. All rights reserved.
//
#include <stdio.h>
#include <unistd.h>

#include <iostream>
#include <istream>
#include <ostream>
#include <string>
#include <Poco/Util/ServerApplication.h>
#include <uv.h>
#include "MycoinApplication.h"
#include "aroundMatch.h"
#include "thread_fn.h"
using namespace Poco;
using namespace Poco::Util;
using namespace std;

bool g_run = true;

int main(int argc, char** argv)
{
    MycoinApplication app;
    app.init(argc,argv);
    return app.run(argc, argv);
}


int mainloop(int timeout, const string & host, int port, int port2
             ,const string & publish_host, int publish_port
             ,ReaderWriterQueue<message_t> *main_msg_queue
             ,ReaderWriterQueue<message_t> *main_msg_queue2
             ,ReaderWriterQueue<message_t> * match_msg_queue
             ,ReaderWriterQueue<message_t> * io_msg_quque);

int MycoinApplication::main( const std::vector < std::string > & args){

    //loadConfiguration();
    LayeredConfiguration& conf = config();
    const string& host = "localhost"; //conf.getString("host");
    int port = 5000; //conf.getInt("quote_port");
    int port2 = 5001; //conf.getInt("fund_port");
   
    const string& publish_host = "localhost";//conf.getString("publish_host");
    int publish_port = 11211; //conf.getInt("publish_port");
    
    int timeout = 2000;//conf.getInt("quote");
    int quote_queue_length = 1024; //conf.getInt("quote_queue_length");
    int note_queue_length = 1024;//conf.getInt("note_queue_length");
    
    using namespace moodycamel;
#define CONTRANCT_NOTE_QUEUE_LENGTH 1024

    ReaderWriterQueue<message_t> main_msg_queue(quote_queue_length);
    ReaderWriterQueue<message_t> main_msg_queue2(quote_queue_length);
    ReaderWriterQueue<message_t> io_msg_quque(note_queue_length);
    ReaderWriterQueue<message_t> match_msg_queue(quote_queue_length);
    
    struct thread_context_t matchContext;
    matchContext.msgs = &match_msg_queue;
    matchContext.outs = &main_msg_queue;
    uv_thread_t match_id;
    uv_thread_create(&match_id, match_fn, &matchContext);
    uv_thread_join(&match_id);
    
    struct thread_context_t ioContext;
    ioContext.msgs = &io_msg_quque;
    ioContext.outs = &main_msg_queue2;
    uv_thread_t io_id;
    uv_thread_create(&io_id, io_fn, io_msg_quque, main_msg_queue);
    uv_thread_join(&io_id);
    

    return mainloop(timeout, host,  port, port2,  publish_host, publish_port, &notes, &main_msg_queue, &main_msg_queue2, &match_msg_queue, &io_msg_quque);
}

//routine quotation 日常行情
/*
 能否应用map reduce概念，可否嵌入lua，lua是否有足够数据结构来支撑
 */
//如果运行中多个事件，发生了关联，那么创建event source的snapshot救困难了。完成的事件之间的联系会生成一个图，
//当第一个事件产生的图不再生长时，也就是产生了相隔离的图之后，才能创建snapshot。恢复时，应把这些事件通通排除。
//但是排除这些事件之后，能否重演事件 CQRS？？无法保证的情况下，必须是整个系统snapshot，而不只是eventsource
//整个系统的snapshot必由多部分组成，多部分如何确保同步/同一? 是不是各部分都得模拟一个eventsource
//在一个不是24小时交易的系统中，可以每次启动做snapshot，那么也能做到从snapshot重演

