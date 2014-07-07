//
//  LevelOfQuoteTest.cpp
//  mycoin
//
//  Created by lx on 13-12-22.
//  Copyright (c) 2013年 lx. All rights reserved.
//

#include "LevelOfQuoteTestQueue.h"


namespace {
    
    TEST(LevelOfQuoteQueueTest, matchQuoteSucceess) {
        LevelOfQuoteQueue levelQueue;
        
        security_billId_t billId = -1;
        security_price_t price = -1;
        ASSERT_EQ(0, levelQueue.level(billId, price));
        
        security_billId_t billId = -1;
        security_price_t price = -1;
        ASSERT_EQ(0,matchQuote(&quote, &notes));
        
        security_billId_t billId = -1;
        security_price_t price = 2;
        ASSERT_EQ(1,matchQuote(&quote, &notes));
        
        security_billId_t billId = -1;
        security_price_t price = 2;
        ASSERT_EQ(1,matchQuote(&quote, &notes));
        
        security_billId_t billId = -1;
        security_price_t price = -1;
        ASSERT_EQ(2,matchQuote(&quote, &notes));
        
        security_billId_t billId = 0;
        security_price_t price = -1;
        ASSERT_EQ(0,matchQuote(&quote, &notes));
    }
    
}  // namespace