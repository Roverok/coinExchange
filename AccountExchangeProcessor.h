//
//  AccountExchangeProcessor.h
//  mycoin
//
//  Created by lx on 13-12-27.
//  Copyright (c) 2013年 lx. All rights reserved.
//

#ifndef __mycoin__AccountExchangeProcessor__
#define __mycoin__AccountExchangeProcessor__

#include "MessageProcessor.h"

class AccountExchangeProcessor:public MessageProcessor{
protected:
    typedef int (*)(AccountExchangeNote&) account_func_t;

    account_func_t account;
    
public:
    AccountExchangeProcessor(message_type msg_type, MessageProcessorMap* processorMap
                      , account_func_t account
                      )
        : MessageProcessor(msg_type,processorMap){
            this.account = account;
    }
    int execute(Event *msg, EventSwitcher& switcher){
        
    }
    int execute(AccountExchangeNote &quote, EventSwitcher& switcher){
        if(note.status != STATUS_NEW)
            return STATUS_REJECTED;
        switch(note.billType){
            case ACCOUNT_CHARGE:
                return charge(note,switcher);
            case ACCOUNT_WITHDRAW:
                return withdraw(note,switcher);
            default:
                return STATUS_REJECTED;
        }
    }

    int withdraw(AccountExchangeNote &note);
    int charge(AccountExchangeNote &note);
};


#endif
