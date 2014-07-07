//
//  QuoteProcessorSetTest.cpp
//  mycoin
//
//  Created by lx on 13-12-22.
//  Copyright (c) 2013年 lx. All rights reserved.
//

#include "IdentifyQuoteQueueTest.h"
#include <typeinfo>

namespace {
    TEST(IdentifyQuoteQueue, SelfBuy) {
        BuyQuoteMultiMap buyQueue;
        SellQuoteMultiMap  sellQueue;
        
        IdentifyQuoteQueue<BuyQuoteMultiMap,SellQuoteMultiMap> identify1;
        ASSERT_EQ(&buyQueue, identify1.getSelfQueue(&buyQueue, &sellQueue));
        ASSERT_EQ(&sellQueue, identify1.getPeerQueue(&buyQueue, &sellQueue));
        
    }
    
    TEST(IdentifyQuoteQueue, SelfSell) {
        BuyQuoteMultiMap buyQueue;
        SellQuoteMultiMap  sellQueue;
        
        
        IdentifyQuoteQueue<SellQuoteMultiMap,BuyQuoteMultiMap> identify2;
        ASSERT_EQ(&sellQueue, identify2.getSelfQueue(&buyQueue, &sellQueue));
        ASSERT_EQ(&buyQueue, identify2.getPeerQueue(&buyQueue, &sellQueue));
        
    }
    
}  // namespace