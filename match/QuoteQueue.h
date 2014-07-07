//
//  QuoteQueue.h
//  mycoin
//
//  Created by lx on 13-12-22.
//  Copyright (c) 2013年 lx. All rights reserved.
//

#ifndef __mycoin__QuoteQueue__
#define __mycoin__QuoteQueue__
#include <stdlib.h>
#include <algorithm>
#include <map>
#include <functional>
#include "../quote.h"


using namespace std;

typedef multimap<security_price_t, SecurityQuote> SellQuoteMultiMap;
typedef multimap<security_price_t, SecurityQuote,  greater<int>> BuyQuoteMultiMap;

//inline 应该允许调用方设定
class QuoteQueue{


    typedef map<security_code_t, SellQuoteMultiMap > SellQueueHash;
    typedef map<security_code_t, BuyQuoteMultiMap > BuyQueueHash;
    BuyQueueHash buyQueueHash;
    SellQueueHash sellQueueHash;
    
public:

    inline SellQuoteMultiMap* getSellQuoteQueue(security_code_t code){
        return innerQueue(sellQueueHash,code);
    }
    
    inline BuyQuoteMultiMap* getBuyQuoteQueue(security_code_t code){
        return innerQueue(buyQueueHash,code);
    }
    
    
    void clearQueue(){
        buyQueueHash.clear();
        sellQueueHash.clear();
    }
private:
    template<typename QueueHash>
    inline typename QueueHash::mapped_type * innerQueue(QueueHash& queueHash, security_code_t code){
        return &queueHash[code];

    }
};

#endif /* defined(__mycoin__QuoteQueue__) */
