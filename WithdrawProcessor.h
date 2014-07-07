//
//  WithdrawProcessor.h
//  mycoin
//
//  Created by lx on 14-1-8.
//  Copyright (c) 2014年 lx. All rights reserved.
//

#ifndef __mycoin__WithdrawProcessor__
#define __mycoin__WithdrawProcessor__

#include "MessageProcessor.h"

class WithdrawProcessor:public MessageProcessor{
protected:
    typedef int (*)(WithdrawQuote&) account_func_t;
    typedef int (*)(WithdrawQuote&) match_func_t;
    
    account_func_t accout;
    match_func_t match;
    
public:
    WithdrawProcessor(message_type msg_type, MessageProcessorMap* processorMap
                      , match_func_t match
                      , account_func_t accout
                     )
    :MessageProcessor(msg_type,processorMap){
        this.account = accont;
        this.match = match;
    }
    
    virtual int execute(message_t *msg,list<message_t> &out_msg_list){
        return execute(*((WithdrawQuote*)&msg),out_msg_list);
    }
    
    int execute(WithdrawQuote &quote,list<message_t> &out_msg_list){
        switch (quote.status) {
            case STATUS_NEW:
                return quote.status = STATUS_ACCEPTED;
            case STATUS_ACCEPTED:
                return match != NULL ? match(quote, out_msg_list) : STATUS_REJECTED;
            case STATUS_PROCESSED:
                return account != NULL ? account(quote, out_msg_list) : STATUS_REJECTED;
            default:
                break;
        }

        return STATUS_REJECTED;
    }
   
};

#endif /* defined(__mycoin__WithdrawAccount__) */
