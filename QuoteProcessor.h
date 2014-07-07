//
//  QuoteAccount.h
//  mycoin
//
//  Created by lx on 13-12-28.
//  Copyright (c) 2013年 lx. All rights reserved.
//

#ifndef __mycoin__QuoteProcessor__
#define __mycoin__QuoteProcessor__

#include "../quote.h"
#include "MessageProcessor.h"
#include "message/message_extend.h"

class QuoteProcessor:public MessageProcessor{

protected:
    typedef int (*)(WithdrawQuote&) account_func_t;
    typedef int (*)(WithdrawQuote&) prepare_func_t;
    typedef int (*)(WithdrawQuote&) match_func_t;
    prepare_func_t prepare;
    account_func_t accout;
    match_func_t match;
    
public:
    QuoteProcessor(message_type msg_type, MessageProcessorMap* processorMap
                      , prepare_func_t prepare
                      , match_func_t match
                      , account_func_t accout
                      ): MessageProcessor(msg_type,processorMap){
        this.account = accont;
        this.prepare = prepare;
        this.match = match;
    }

    virtual int execute(message_t *msg, EventSwitcher &switcher){
        return execute(*((SecurityQuote*)&msg), switchers);
    }
    //象这样几个状态缠在一起，针对不同状态做不同处理，可使用策略模式。不过策略模式增加了一个类，把一个类的责任切成两个，内聚性岂不降低？可否使用模板，宏，lumba表达式等来处理，使得不同的处理放在不同的成员函数，同时成员函数来声明自己能处理的状态，而swtich变成根据状态，自动寻找成员函数。比如template<header.status, header.billtype>即可区分开不同的成员函数
    int QuoteAccount::execute(SecurityQuote &quote,EventSwitcher &switcher){
        switch (quote.status) {
            case STATUS_NEW:
                return check(quote, switcher);
            case STATUS_ACCEPTED:
                return  match(quote, switcher);
            case STATUS_PROCESSED:
                return account(quote, switcher);
            default:
                return STATUS_REJECTED;
        }
    }
};


#endif /* defined(__mycoin__QuoteProcessor__) */
