//
//  QuoteQueueTest.cpp
//  mycoin
//
//  Created by lx on 13-12-22.
//  Copyright (c) 2013年 lx. All rights reserved.
//

#include "QuoteQueueTest.h"
#include <typeinfo>

namespace {
   
    TEST(QuoteQueueTest, getQuoteQueue) {
        
        int code = random();
        
        QuoteQueue& quoteQueue = QuoteQueue::getInstance();
        SellQuoteMultiMap * sellQueue = quoteQueue.getSellQuoteQueue(code);
        ASSERT_EQ(typeid(*sellQueue), typeid(SellQuoteMultiMap));
        
        BuyQuoteMultiMap * buyQueue = quoteQueue.getBuyQuoteQueue(code);
        ASSERT_EQ(typeid(*buyQueue), typeid(BuyQuoteMultiMap));
        
        ASSERT_NE(buyQueue, sellQueue);
        
        code = random();
        
        SellQuoteMultiMap * sellQueue2 = quoteQueue.getSellQuoteQueue(code);
        BuyQuoteMultiMap * buyQueue2 = quoteQueue.getBuyQuoteQueue(code);
   
        
        ASSERT_NE(buyQueue2, sellQueue2);
        
        ASSERT_EQ(buyQueue, buyQueue2);
        ASSERT_EQ(sellQueue, sellQueue2);
        

    }
    
}  // namespace