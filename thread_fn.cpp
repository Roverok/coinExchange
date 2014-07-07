//
//  match.c
//  mycoin
//
//  Created by lx on 13-12-27.
//  Copyright (c) 2013年 lx. All rights reserved.
//

#include <stdio.h>
#include <unistd.h>
#include <iostream>
#include <istream>
#include <ostream>
#include <string>

#include "match.h"
#include "message.h"

#include "Singleton.h"
#include "readerwriterqueue.h"
#include "WithdrawProcessor.h"
#include "QuoteProcessor.h"
#include "Singleton.h"
#include "match/match_quote.h"

using namespace std;
using namespace moodycamel;

template<> MessageProcessorMap * Singleton<MessageProcessorMap, 2>::_instance = NULL;
template<> MessageProcessorMap * Singleton<MessageProcessorMap, 3>::_instance = NULL;

void match_fn(void * arg){
    
    struct thread_context_t *context = (struct threadContext *)arg;
    ReaderWriterQueue<message_t> & msgs = *(context->msgs);
    ReaderWriterQueue<message_t> & outs = *(context->outs);
    
    MessageProcessorMap &processorMap = Singleton<MessageProcessorMap, 2>::instance();
    WithdrawProcessor withdrawer(WITHDRAW_QUOTE, &processorMap, NULL, matchWithdraw, NULL);
    QuoteProcessor quoteProcessor(SecurityQuote, &processorMap, NULL, matchQuote, NULL) ;

    
    message_t msg;
    list<message_t> out_msg_list;
    extern bool g_run;
    while(g_run){
        while(msgs.try_dequeue(msg)){
            MessageProcessorMap::iterator iter = processorMap.find(msg->quote.msg_type);
            if(iter != processorMap.end()){
                int status = iter->second->execute(msg, out_msg_list);
                if(status == STATUS_INVALID){
                    //outs.enqueue(*iter);
                }else{
                    for(list<message_t>::iterator iter = out_msg_list.begin(); iter!= out_msg_list.end(); iter++){
                        outs.enqueue(*iter);
                    }
                    out_msg_list.clear();
                    outs.enqueue(msg);
                }
            }
        }
    }
}

void io_fn(void *arg){
    
    struct thread_context_t *context = (struct threadContext *)arg;
    ReaderWriterQueue<message_t> & msgs = *(context->msgs);
    ReaderWriterQueue<message_t> & outs = *(context->outs);
    
    MessageProcessorMap &processorMap = Singleton<MessageProcessorMap, 3>::instance();
    
    QuoteProcessor(SECURITY_QUOTE, &processorMap
                   , prepareQuote, NULL, accoutQuote);
    WithdrawProcessor withdrawProcessor(WITHDRAW_QUOTE, &processorMap
                , prepareWithdraw, NULL, accoutWithdraw);
    ContractNoteProcessor noteProcessor(CONTRACT_NOTE, &processorMap
                        ,accountNote);
    AccountExchangeProcessor exchangeProcessor(ACCOUNT_EXCHANGE_NOTE, &processorMap
                        , accountExchange );
    
    message_t msg;
    list<message_t> out_msg_list;
    extern bool g_run;
    while(g_run){
        if(! msgs.try_dequeue(msg))
            continue;

        MessageProcessorMap::iterator iter = processorMap.find(msg->quote.msg_type);
        if(iter != processorMap.end()){
            int status = iter->second->execute(msg, out_msg_list);
            if(status == STATUS_INVALID){
               // outs.enqueue(*iter);
            }else{
                for(list<message_t>::iterator iter = out_msg_list.begin(); iter!= out_msg_list.end(); iter++){
                    outs.enqueue(*iter);
                }
                out_msg_list.clear();
                outs.enqueue(msg);
            }
        }
    }
}

