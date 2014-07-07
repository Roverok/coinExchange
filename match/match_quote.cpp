//
//  QuoteMatchProcessor.cpp
//  mycoin
//
//  Created by lx on 14-1-6.
//  Copyright (c) 2014年 lx. All rights reserved.
//
#include "match_quote.h"
#include <algorithm>
#include <vector>
#include <map>
#include <functional>

#include "../quote.h"
#include "MatchStrategy.h"
#include "lost.h"

#include "QuoteQueue.h"

using namespace std;


int matchQuote(SecurityQuote &quote){
    do{
        if(quote.status != STATUS_INQUEUE)
            break;
        QuoteQueue& quoteQueue = Singleton<QuoteQueue>::instance();
        SellQuoteMultiMap * sellQueue = quoteQueue.getSellQuoteQueue(quote->code);
        BuyQuoteMultiMap * buyQueue = quoteQueue.getBuyQuoteQueue(quote->code);
        if(sellQueue == NULL || buyQueue == NULL)
            return break;
        
        security_price_t price = 0;
        switch (quote.billType) {
            case BUY_IN_LIMIT_PRICE:
                price = matchQueue(quote,*buyQueue, *sellQueue, matchTopDown);
            case BUY_IN_MARKET_PRICE:
                price = matchQueue(quote,*buyQueue, *sellQueue, matchBottomUp);
            case SELL_OUT_LIMIT_PRICE:
                price = matchQueue(quote,*buyQueue, *sellQueue, marketPriceBuyIn );
            case SELL_OUT_MARKET_PRICE:
                price = matchQueue(quote,*buyQueue, *sellQueue, marketPriceSellOut);
            default:
                return STATUS_REJECTED;
        }
        //结束后如果要把quote转为限价订单
        //guanrity　数量得从订单和那个来保证了
        /* 转topone
         BuyQuoteMultiMap* buyQueue, SellQuoteMultiMap *sellQueue){
         SelfQuoteQueue *selfQueue = IdentifyQuoteQueue<SelfQuoteQueue, PeerQuoteQueue>::getSelfQueue(buyQueue, sellQueue);
         quote->price = selfQueue->begin()->price ;
         return quote;
         还得通知客户端才好
         
         */
        //这里只是撤销
        

        if(quote.quality > 0){
            SecurityQuote * quoteReserved = postmatch(&quote, buyQueue, sellQueue);
            if(quoteReserved != NULL){
                SelfQuoteQueue &selfQueue = identify.getSelfQueue(buyQueue, sellQueue);
                selfQueue.insert(make_pair(quote.price,quote));
                quote.status = STATUS_PROCESSING;
            }
        }
        quote.status = STATUS_PROCESSED;
        return quote.status;
    }while(false);
    
    return STATUS_REJECTED;
}

struct isQuoteFinished : public std::unary_function<SecurityQuote, bool> {
    bool operator()(const SecurityQuote & x) const {
        return x.quality <= 0;
    }
};


template<typename SelfQuoteQueue, typename PeerQuoteQueue, typename MatchStrategy>
security_price_t QuoteMatchProcessor::matchQueue(SecurityQuote &quote, SelfQuoteQueue& selfQueue, PeerQuoteQueue  &peerQueue, MatchStrategy &matchStrategy){

    security_price_t lastPrice =0;
    typename PeerQuoteQueue::iterator iter;
    for(iter = peerQueue.begin(); iter != peerQueue.end(); iter++){
        security_quality_t quality = matchStrategy(quote, iter->second);
        if(quality >0 ){
            ContractNote note;
            note.code = quote.code;
            note.sourceBillId = quote.header.billId;
            note.peerBillId = iter->second.header.billId;
            memcpy(&note.buyer, quote.client , sizeof(quote.client));
            memcpy(&note.seller, iter->second.client , sizeof(iter->second.client));
            
            note.quality = quality;
            note.price = iter->second.price;
            
            notes_push_back(note);
            
            lastPrice = note.price;
            
            //对方数量＝＝０时，生成quote完成单
            if(iter->second.quality == 0){
                finishQuote(&iter->second);
            }
        }else{
            break;
        }
    }
    
    map_erase_if(peerQueue,
                 compose1(isQuoteFinished(),select2nd<map<security_price_t, SecurityQuote>::value_type>()));
    return lastPrice;
}

template<typename SelfQuoteQueue, typename PeerQuoteQueue>
static int withdraw(WithdrawQuote &quote, SelfQuoteQueue &selfQueue,  PeerQuoteQueue & peerQueue){
    
    for(typename SelfQuoteQueue::iterator iter = selfQueue.begin(); iter!=selfQueue.end(); iter++){
        if(quote.refBillId == iter->second.header.billId){
            finishQuote(&iter->second); //原单完成
            selfQueue.erase(iter);
            break;
        }
    }
    quote.status = STATUS_PROCESSED;
    return quote.status;
}


int matchWithdraw(WithdrawQuote &quote){
    do{
        QuoteQueue& quoteQueue = Singleton<QuoteQueue>::instance();
        SellQuoteMultiMap * sellQueue = quoteQueue.getSellQuoteQueue(quote->code);
        BuyQuoteMultiMap * buyQueue = quoteQueue.getBuyQuoteQueue(quote->code);
        if(sellQueue == NULL || buyQueue == NULL)
            return break;
        
        switch (quote.billType) {
            case BUY_WITHDRAW:
                return withdraw(quote, *buyQueue, *sellQueue);
            case SELL_WITHDRAW:
                return withdraw(quote, *sellQueue, *buyQueue);
            default:
                break;
        }
    }while(false);
    
    return STATUS_REJECTED;
    
}
