//
//  MatchStrategy.cpp
//  mycoin
//
//  Created by lx on 13-12-21.
//  Copyright (c) 2013年 lx. All rights reserved.
//

#ifndef __mycoin__TopLimitPriceStrategy__
#define __mycoin__TopLimitPriceStrategy__
#include "../quote.h"
#include "MatchStrategy.h"

security_quality_t matchTopDown(SecurityQuote &quote, SecurityQuote & peer){
        
    if(quote.quality <=0 || quote.price < peer.price)
        return 0;
        
    security_quality_t qty = std::min(quote.quality,  peer.quality);
    quote.quality -= qty;
    peer.quality -= qty;
    return qty;
}



//sell out
security_quality_t matchBottomUp(SecurityQuote &quote, SecurityQuote & peer){
        
    if(quote.quality <=0 || quote.price > peer.price)
            return 0;
        
    security_quality_t qty = std::min(quote.quality,  peer.quality);
    quote.quality -= qty;
    peer.quality -= qty;
    return qty;
        
}
    

#define MAX_LEVEL 5;

static LevelOfQuoteQueue levelQueue;

security_quality_t marketPriceBuyIn(SecurityQuote &quote, SecurityQuote & peer){
    if(quote.quality > 0 || MAX_LEVEL > levelQueue.level(quote.billId, peer.price) ){
            
            //结束后要把quote转为限价订单
            //guanrity 转为price，是否要生成新的quote，在postMatch中处理
            security_quality_t qty = min(quote.quality,  peer.quality);
            if(quote.guaranty < peer.price * qty){
                qty = quote.guaranty / peer.price;
            }
            
            quote.guaranty -= peer.price * qty;
            quote.quality -= qty;
            peer.quality -= qty;
            return qty;
        }else{
            return 0;
        }
    }
    

security_quality_t marketPriceSellOut(SecurityQuote &quote, SecurityQuote & peer){
    if(quote.quality > 0 || maxLevel > levelQueue.level(quote.billId, peer.price) ){
        //市价卖出
        security_quality_t qty = std::min(quote.quality,  peer.quality);
        quote.quality -= qty;
        peer.quality -= qty;
        return qty;
    }else
        return 0;
}


#endif
