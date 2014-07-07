//
//  QuoteProcessorSetTest.cpp
//  mycoin
//
//  Created by lx on 13-12-22.
//  Copyright (c) 2013年 lx. All rights reserved.
//

#include "LimitPriceStrategyTest.h"
#include <typeinfo>

namespace {

    
    TEST(TopLimitPriceStrategy, match) {

        TopLimitPriceStrategy strategy;
        SecurityQuote quote,cpmQuote;
        SecurityQuote peer,cpmPeer;
        security_quality_t qty;
        
        security_code_t code = random();
        quote.code = code;
        peer.code = code;
        
        quote.quality = random();
        peer.quality = random();
        
        quote.price = random();
        peer.price = random();
        memcpy(&cpmQuote, &quote);
        memcpy(&cpmpeer, &peer);
        
        qty = strategy.match(quote, peer);
        
        ASSERT_EQ(qty, cmpQuote.quality - quote.quality);
        ASSERT_EQ(qty, peer.quality - cmpPeer.quality);
        quote.quality -= qty;
        ASSERT_EQ(0, memcpm(&cmpQuote,&quote));
        peer.quality += qty;
        ASSERT_EQ(0, memcpm(&cmpPeer,&peer));
        
        if(quote.price >= peer.price){
            ASSERT_GT(qty,0);
            quote.price = peer.price -1;
            ASSERT_EQ(strategy.match(quote, peer),0);
        }else{
            ASSERT_EQ(qty,0);
            quote.price = peer.price +1;
            ASSERT_GT(strategy.match(quote, peer),0);
        }
        
        quote.quality = - random();
        qty = strategy.match(quote, peer);
        ASSERT_EQ(0, qty);
    }
    
    TEST(BottomLimitPriceStrategy, match) {
        
        BottomLimitPriceStrategy strategy;
        
        SecurityQuote quote,cpmQuote;
        SecurityQuote peer,cpmPeer;
        security_quality_t qty;
        
        security_code_t code = random();
        quote.code = code;
        peer.code = code;

        
        quote.quality = random();
        peer.quality = random();
        
        quote.price = random();
        peer.price = random();
        memcpy(&cpmQuote, &quote);
        memcpy(&cpmpeer, &peer);
        
        qty = strategy.match(quote, peer);
        
        ASSERT_EQ(qty, cmpQuote.quality - quote.quality);
        ASSERT_EQ(qty, peer.quality - cmpPeer.quality);
        quote.quality -= qty;
        ASSERT_EQ(0, memcpm(&cmpQuote,&quote));
        peer.quality += qty;
        ASSERT_EQ(0, memcpm(&cmpPeer,&peer));
        
        if(quote.price <= peer.price){
            ASSERT_GT(qty,0);
            quote.price = peer.price + 1;
            ASSERT_EQ(strategy.match(quote, peer),0);
        }else{
            ASSERT_EQ(qty,0);
            quote.price = peer.price - 1;
            ASSERT_GT(strategy.match(quote, peer),0);
        }
        
        quote.quality = - random();
        qty = strategy.match(quote, peer);
        ASSERT_EQ(0, qty);
        
    }
    
}  // namespace