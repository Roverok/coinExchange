//
//  IdentifyQuoteQueye.h
//  mycoin
//
//  Created by lx on 13-12-23.
//  Copyright (c) 2013年 lx. All rights reserved.
//

#ifndef mycoin_IdentifyQuoteQueue_h
#define mycoin_IdentifyQuoteQueue_h
#include "../quote.h"

typedef multimap<security_price_t, SecurityQuote> SellQuoteMultiMap;
typedef multimap<security_price_t, SecurityQuote,  greater<int>> BuyQuoteMultiMap;

template<typename SelfQuoteQueue, typename PeerQuoteQueue>
struct IdentifyQuoteQueue{
    
};

template<>
struct IdentifyQuoteQueue<BuyQuoteMultiMap,SellQuoteMultiMap>{
    BuyQuoteMultiMap &getSelfQueue(BuyQuoteMultiMap& buyQueue, SellQuoteMultiMap  &sellQueue){
        return buyQueue;
    }
    
    SellQuoteMultiMap &getPeerQueue(BuyQuoteMultiMap& buyQueue, SellQuoteMultiMap  &sellQueue){
        return sellQueue;
    }
};
template<>
struct IdentifyQuoteQueue<SellQuoteMultiMap,BuyQuoteMultiMap>{
    SellQuoteMultiMap &getSelfQueue(BuyQuoteMultiMap& buyQueue, SellQuoteMultiMap  &sellQueue){
        return sellQueue;
    }
    BuyQuoteMultiMap &getPeerQueue(BuyQuoteMultiMap& buyQueue, SellQuoteMultiMap& sellQueue){
        return buyQueue;
    }
};


#endif
