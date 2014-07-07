//
//  Publisher.h
//  mycoin
//
//  Created by lx on 14-1-8.
//  Copyright (c) 2014年 lx. All rights reserved.
//

#ifndef __mycoin__Publisher__
#define __mycoin__Publisher__
#include "quote.h"

class Publisher{
public:
    virtual void publish(const security_code_t code, security_price_t price, security_quality_t quality, security_price_t topBuyPrice[], security_quality_t topBuyQty[], int size1, security_price_t topSellPrice[], security_quality_t topSellQty[], int size2 )=0;
    virtual void publish(SecurityQuote &quote)=0;
    void publish(RoutineQuotation &routine){
        routine.publish()
    }
    void publish(message_t* msg){
        if(msg.quote.status != STATUS_FINISHED)
            return;
        switch(msg.quote.msg_type){
            case SecurityQuote:
                Singleton<RoutineQuation>::instance().update(quote);
                Singleton<Publisher>::instance().publish(quote);
            case AccountExchange:
                Singleton<Publisher>::instance().publish(note);
                break;
            case WithdrawQuote:
                Singleton<Publisher>::instance().publish(quote);
                break;
            case  CONTRACT_NOTE:
                Singleton<RoutineQuation>::instance().update(note);
                Singleton<Publisher>::instance().publish(note);
                break;
            default:
                break;
        }
    }
};

#endif /* defined(__mycoin__Publisher__) */
