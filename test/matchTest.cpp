//
//  matchTest.cpp
//  mycoin
//
//  Created by lx on 13-12-21.
//  Copyright (c) 2013年 lx. All rights reserved.
//

#include "matchTest.h"
#include "../quote.h"
#include "readerwriterqueue.h"

extern int matchQuote(SecurityQuote * quote, ReaderWriterQueue<ContractNote > *notes);
template<typename QuoteMultiMap1, typename QuoteMultiMap2>
security_price_t matchQueue(SecurityQuote *quote, QuoteMultiMap1* selfQueue, QuoteMultiMap2 *peerQueue,ReaderWriterQueue<ContractNote > *notes, MatchStrategy &strategy, BalanceStrategy<QuoteMultiMap1, QuoteMultiMap2> &balance);
template<typename QuoteMultiMap>
void withdrawQuote(SecurityQuote *quote, QuoteMultiMap *queue,ReaderWriterQueue<ContractNote > *notes);
QuoteProcessor & getQuoteProcessor(SecurityQuote *quote);

void matchQuote(SecurityQuote * quote, ReaderWriterQueue<ContractNote > *notes);
namespace {
    
    // The fixture for testing class .
    //class MatchTest :public ::testing::TestWithParam<int>
    //测试内容，股价优先，时间优先，不同类型的quote，撤销单，市价，限价
    

    class MatchTest : public ::testing::Test {
       
    protected:
        // You can remove any or all of the following functions if its body
        // is empty.
        
        MatchTest() {
            // You can do set-up work for each test here.
        }
        
        virtual ~MatchTest() {
            // You can do clean-up work that doesn't throw exceptions here.
        }
        
        /*
         SetUpTestCase() 方法在第一个TestCase之前执行
         */
        static void SetUpTestCase() {
            shared_resource_ = new ;
        }
        /*
         TearDownTestCase() 方法在最后一个TestCase之后执行
         */
        static void TearDownTestCase() {
            delete shared_resource_;
            shared_resource_ = NULL;
        }
        // Some expensive resource shared by all tests.
        static T* shared_resource_;
        
        
        // If the constructor and destructor are not enough for setting up
        // and cleaning up each test, you can define the following methods:
        //SetUp()方法在每个TestCase之前执行
        virtual void SetUp() {
            // Code here will be called immediately after the constructor (right
            // before each test).

            time(&quote.occurTime);
            quote.code = 1;//2
            quote.billId = (long)random();//hash
            quote.billType =  (security_bill_t)random()%4; // BUY_IN_LIMIT_PRICE, SELL_OUT_LIMIT_PRICE,
            
            quote.quality = random() %10;
            if(quote.billType == BUY_IN_LIMIT_PRICE || quote.billType == SELL_OUT_LIMIT_PRICE ){
                quote.price = 5000 + random()% 2000;
            }else{
                quote.guaranty = quote.quality * 6000; //BUY_IN_MARKET_PRICE,SELL_OUT_MARKET_PRICE,
            }
            

        }
        
        //TearDown()方法在每个TestCase之后执行
        virtual void TearDown() {
            // Code here will be called immediately after each test (right
            // before the destructor).
            
        }
        
        // Objects declared here can be used by all tests in the test case.
        ReaderWriterQueue<ContractNote > notes(1024);
        SecurityQuote quote;
    };

    TEST_F(MatchTest, withdrawQuote) {
        //撤销单
        //撤销买单，撤销卖单-简单，空单时
        //　有单时
        //　单已全部成交
        //　单成交部分
        //　单完全没成交
        //限价单
        //市价单
    }
}  // namespace
