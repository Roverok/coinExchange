//
//  RoutineQuotation.cpp
//  mycoin
//
//  Created by lx on 13-12-24.
//  Copyright (c) 2013年 lx. All rights reserved.
//

#include "RoutineQuotation.h"
#include "../Singleton.h"

template<> RoutineQuotation *Singleton<RoutineQuotation>::_instance = 0;

int RoutineQuotation::update(ContractNote &note){
    innerMap[note.code].sum += note.price * note.qty;
    innerMap[note.code].qty += note.qty;
    
    updateTopQuote(innerMap[code].topBuys,  note.price, -note.qty);
    updateTopQuote(innerMap[code].topSells,  price, -note.qty);

}

int RoutineQuotation::update(SecurityQuote &quote){
    switch(quote.billType){
        case BUY_IN_LIMIT_PRICE:
        case BUY_IN_MARKET_PRICE:
            updateTopQuote(innerMap[code].topBuys,  price, qty);
            break;
        case SELL_OUT_LIMIT_PRICE:
        case SELL_OUT_MARKET_PRICE:
            updateTopQuote(innerMap[code].topSells,  price, qty);
            break;
        default:
            break;
    }
}


void RoutineQuotation::publish(Publisher &publisher){

    for (InnerRoutineMap::iterator iter=innerMap.begin(); iter!=innerMap.end(); iter++) {
        
        int i = 0;
        security_price_t topBuyPrice[MAX_ROUTINE_LEVEL], topSellPrice[MAX_ROUTINE_LEVEL];
        security_quality_t topBuyQty[MAX_ROUTINE_LEVEL], topSellQty[MAX_ROUTINE_LEVEL];
        SellQuoteRoutine &topSells = iter->second.topSells;
        BuyQuoteRoutine &topBuys = iter->second.topBuys;
        for (SellQuoteRoutine::iterator iter2= topSells.begin(); iter2!=topSells.end() && i < MAX_ROUTINE_LEVEL ; iter2 ++ ) {
            topSellQty[i] = iter2->second;
            topSellPrice[i] = iter2->first;
            i++;
        }
        
        int j =0;
        for (BuyQuoteRoutine::iterator iter2= topBuys.begin(); iter2!=topBuys.end() && j < MAX_ROUTINE_LEVEL ; iter2 ++ ) {
            topBuyQty[j] = iter2->second;
            topBuyPrice[j] = iter2->first;
            j++;
        }
        
        publisher.publish( iter->first, iter->second.qty >0? iter->second.sum/iter->second.qty :0, iter->second.qty, topBuyPrice, topBuyQty, j, topSellPrice, topSellQty, j);
    }
    
    reset();
}
