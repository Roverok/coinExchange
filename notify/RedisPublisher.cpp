//
//  RedisPublisher.cpp
//  mycoin
//
//  Created by lx on 13-12-31.
//  Copyright (c) 2013年 lx. All rights reserved.
//

#include "RedisPublisher.h"

#include <string>
using namespace std;


void RedisPublisher::connect(const char *host, int port){
        
    context = redisAsyncConnect(host, port); //6379
    if (context->err) {
    }
        
}


void RedisPublisher::publish(const security_code_t code, security_price_t price, security_quality_t quality, security_price_t topBuyPrice[], security_quality_t topBuyQty[], int size1, security_price_t topSellPrice[], security_quality_t topSellQty[], int size2 ){
    if(context == NULL)
            return;
        /*
    std::streambuf json;
    json << "{price:" << price << ",quality:" << quality  << ",topbuys:[";
    for(int i=0; i< size1; i++){
        json<<  "{price:" << topBuyPrice[i] << ", quality:" << topBuyQty[i] << "},";
    }
    json << "], topsells:[";
    for(int i=0; i< size2; i++){
        json << "{price:" << topSellPrice[i] <<", quality:" << topSellQty[i] <<"},";
    }
    json << "]}";
    
    redisAsyncCommand(context, NULL, NULL, "publish /topic/stock/%b/routation %b"
                          ,code, strlen(code)
                          ,json, strlen(json));
     */
}

void RedisPublisher::publish(SecurityQuote &quote){
    if(context == NULL)
        return;
    /*
    std::streambuf json ;
    json << "{price:" << quote.price << ",quality:" << quote.quality
        << ",guanity:" << quote->guanity << ", status:" << quote.header.status +"}";

    redisAsyncCommand(context, NULL, NULL, "publish /topic/stock/queue/%b %b"
                      ,quote.header.billId, strlen(code)
                      ,json, strlen(json));
     */
}

int RedisPublisher::publish(ContractNote &note){
// 通知买了多少, 价格，数量都在变，原来的单到底是什么单，发布价格还是
    /*
     std::streambuf json ;
     json << "{price:" << quote.price << ",quality:" << quote.quality
     << ",guanity:" << quote->guanity << ", status:" << quote.header.status +"}";
     
     redisAsyncCommand(context, NULL, NULL, "publish /topic/stock/queue/%b %b"
     ,quote.header.billId, strlen(code)
     ,json, strlen(json));
     */
}
