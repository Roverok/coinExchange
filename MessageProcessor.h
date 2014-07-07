//
//  MessageProcessor.h
//  mycoin
//
//  Created by lx on 14-1-3.
//  Copyright (c) 2014年 lx. All rights reserved.
//

#ifndef __mycoin__MessageProcessor__
#define __mycoin__MessageProcessor__
#include <map>
#include <list>
#include "message/message_extend.h"

using namespace std;
/*
  一致回调处理方式
 一致同步异步编程模型
 一致多线程，单线程模型
 
沙漠履带车安全不，不致陷落吧
 坦克太重，可以搞点耐热陶瓷，又轻
 */
typedef enum {
    ES_RUN_DEFAULT = 0,
    ES_RUN_ONCE,
    ES_RUN_NOWAIT
} es_run_mode;

template <int size>
class EventSwitcher{
protected:
    map<event_type, EventProcessor *> processorMap;
    typedef ReaderWriterQueue<Event> EventQueue; //vector<Event> EventQueue;
    typedef vector<EventQueue&> EventQueues;
    EventQueues queue(size);
public:
    void connect(EventProcessor);
    void push(Event &event, int rank);
    void now(Event &event);
    void run(es_run_mode run_mode); //once , process all until null, for ever
};

class EventProcessor{
public:
    event_type & const ev_type;
    
    EventProcessor(message_type& ev_type):ev_type(ev_type){

    }
    virtual int execute(Event &msg, EventSwitcher& switcher)=0;
};

class MessageProcessor;

typedef map<message_type, MessageProcessor*>  MessageProcessorMap;

class MessageProcessor{
public:
    message_type & msg_type;
    
    MessageProcessor(message_type& msg_type, MessageProcessorMap* processorMap):msg_type(msg_type){
        if(processorMap != NULL)
            processorMap->insert(msg_type, this);
    }
    virtual int execute(message_t *msg, list<message_t> &)=0;
};


#endif /* defined(__mycoin__Command__) */
