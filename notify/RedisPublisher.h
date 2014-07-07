//
//  RoutineQuote.h
//  mycoin
//
//  Created by lx on 13-12-31.
//  Copyright (c) 2013年 lx. All rights reserved.
//

#ifndef __mycoin__RoutineQuote__
#define __mycoin__RoutineQuote__
#include "quote.h"
#include "Publisher.h"
#include <hiredis/hiredis.h>
#include <hiredis/async.h>


class RedisPublisher:public Publisher{
private:
    redisAsyncContext *context =NULL;

public:
    void connect(const char *host, int port);
    redisAsyncContext * getContext(){
        return context;
    }
    
    void publish(SecurityQuote &quote);
    virtual void publish(const security_code_t code, security_price_t price, security_quality_t quality, security_price_t topBuyPrice[], security_quality_t topBuyQty[], int size1, security_price_t topSellPrice[], security_quality_t topSellQty[], int size2 );
    int publish (ContractNote &note);
};

#endif /* defined(__mycoin__RoutineQuote__) */
