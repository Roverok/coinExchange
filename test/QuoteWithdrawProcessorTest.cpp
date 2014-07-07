//
//  QuoteWithDrawProcessor.cpp
//  mycoin
//
//  Created by lx on 13-12-22.
//  Copyright (c) 2013年 lx. All rights reserved.
//

#include "QuoteWithDrawProcessorTest.h"
#include <typeinfo>

namespace {
    inline security_price_t process(SecurityQuote *quote, BuyQuoteMultiMap* buyQueue, SellQuoteMultiMap *sellQueue){
        
        SelfQuoteQueue *selfQueue = identify.getSelfQueue(buyQueue, sellQueue);
        for(typename SelfQuoteQueue::iterator iter = selfQueue->begin(); iter!=selfQueue->end(); iter++){
            if(quote->billId == iter->second.billId){
                finishQuote(quote);
                break;
            }
        }
        return 0;
    }
    
    class QuoteProcessorTest : public ::testing::Test {
        
    protected:
        // You can remove any or all of the following functions if its body
        // is empty.
        
        QuoteProcessorTest() {
            // You can do set-up work for each test here.
        }
        
        virtual ~QuoteProcessorTest() {
            // You can do clean-up work that doesn't throw exceptions here.
        }
        
        /*
         SetUpTestCase() 方法在第一个TestCase之前执行
         */
        static void SetUpTestCase() {
            code = random();
            QuoteQueue& quoteQueue = QuoteQueue::getInstance();
            sellQueue = &quoteQueue.getSellQuoteQueue(code);
            buyQueue = &quoteQueue.getBuyQuoteQueue(code);

            QuoteProcessorFactory& factory = QuoteProcessorFactory::getInstance();
            buyInLimitPriceProcessor = &factory.getQuoteProcessor(BUY_IN_LIMIT_PRICE);
            sellOutLimitPriceProcessor = &factory.getQuoteProcessor(SELL_OUT_LIMIT_PRICE);
            buyInMarketPriceProcessor = factory.getQuoteProcessor(BUY_IN_MARKET_PRICE);
            sellOutMarketPriceProcessor = factory.getQuoteProcessor(SELL_OUT_MARKET_PRICE);
            buyQuoteWithdrawProcessor = factory.getQuoteProcessor(BUY_WITHDRAW);
            sellQuoteWithdrawProcessor = factory.getQuoteProcessor(SELL_WITHDRAW);
  
        }
        /*
         TearDownTestCase() 方法在最后一个TestCase之后执行
         */
        static void TearDownTestCase() {
            QuoteQueue& quoteQueue = QuoteQueue::getInstance();
            quoteQueue.clearQueue();

        }

        
        
        // If the constructor and destructor are not enough for setting up
        // and cleaning up each test, you can define the following methods:
        //SetUp()方法在每个TestCase之前执行
        virtual void SetUp() {
            // Code here will be called immediately after the constructor (right
            // before each test).
            
        }
        
        //TearDown()方法在每个TestCase之后执行
        virtual void TearDown() {
            // Code here will be called immediately after each test (right
            // before the destructor).
            
            buyQueue.clear();
            sellQueue.clear();
            
        }
        
        // Objects declared here can be used by all tests in the test case.
        SellQuoteMultiMap * sellQueue;
        BuyQuoteMultiMap * buyQueue;
        security_code_t code;
        
        QuoteProcessor* buyInLimitPriceProcessor;
        QuoteProcessor* sellOutLimitPriceProcessor;
        QuoteProcessor* buyInMarketPriceProcessor;
        QuoteProcessor* sellOutMarketPriceProcessor;
        QuoteProcessor* buyQuoteWithdrawProcessor;
        QuoteProcessor* sellQuoteWithdrawProcessor;

    };

    
    TEST_F(QuoteProcessorTest, withdrawBuy) {
        
        SecurityQuote quote;
        quote.billId = random();
        quote.code = code;
        quote.billType = BUY_IN_LIMIT_PRICE;
        
        buyInLimitPriceProcessor.process(&quote, buyQueue, sellQueue);
        
        SecurityQuote quote2;
        quote2.billId = random();
        quote2.code = code;
        quote2.refBillId = quote.billId;
        quote2.billType = BUY_WITHDRAW;
        
        buyWithdrawProcessor.process(&quote, buyQueue, sellQueue );
        
        int count = 0;
        for (QuoteProcessor::iterator iter =buyWithdrawProcessor.notes_begin(); iter!= buyWithdrawProcessor.notes_end(); iter++) {
            if(iter.sourceBillId == quote.billId || iter.sourceBillId == quote2.billId){
                count++;
            }
        }
        
        ASSERT_EQ(count, 2);
        //同时判断是否finished单，即其余参数为０
        
        count = 0;
        for (BuyQuoteMuiltiMap::iterator iter = buyQueue.begin(); iter!= buyQueue.end(); iter++) {
            if(iter.billId == quote2.refBillId){
                count = 1;
                break;
            }
        }
        
        ASSERT_EQ(count, 0);
    }
    
    TEST_F(QuoteProcessorTest, withdrawSell) {
        
        SecurityQuote quote;
        quote.billId = random();
        quote.code = code;
        quote.billType = SELL_OUT_LIMIT_PRICE;
        
        buyInLimitPriceProcessor.process(&quote, buyQueue, sellQueue);
        
        SecurityQuote quote2;
        quote2.billId = random();
        quote2.code = code;
        quote2.refBillId = quote.billId;
        quote2.billType = BUY_WITHDRAW;
        
        buyWithdrawProcessor.process(&quote, buyQueue, sellQueue );
        
        int count = 0;
        for (QuoteProcessor::iterator iter =buyWithdrawProcessor.notes_begin(); iter!= buyWithdrawProcessor.notes_end(); iter++) {
            if(iter.sourceBillId == quote.billId || iter.sourceBillId == quote2.billId){
                count++;
            }
        }
        
        ASSERT_EQ(count, 2);
        //同时判断是否finished单，即其余参数为０
        
        count = 0;
        for (BuyQuoteMuiltiMap::iterator iter = buyQueue.begin(); iter!= buyQueue.end(); iter++) {
            if(iter.billId == quote2.refBillId){
                count = 1;
                break;
            }
        }
        
        ASSERT_EQ(count, 0);
    }

    
}  // namespace