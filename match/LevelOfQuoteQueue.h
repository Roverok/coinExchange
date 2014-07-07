//
//  LevelOfQuote.h
//  mycoin
//
//  Created by lx on 13-12-21.
//  Copyright (c) 2013年 lx. All rights reserved.
//

#ifndef __mycoin__LevelOfQuote__
#define __mycoin__LevelOfQuote__
#include "../quote.h"
class LevelOfQuoteQueue{
private:
    int _level=0;
    security_billId_t _lastBillId = 0;
    security_price_t _lastPrice =0;
    
public:
    int level(security_billId_t billId, security_price_t peerPrice ){
        if(billId != _lastBillId){
            _level = 0;
            _lastPrice = 0;
            _lastBillId = billId;
        }
        if(peerPrice != _lastPrice){
            _lastPrice = peerPrice;
            ++_level;
        }
        return _level;
        
    }
};

#endif /* defined(__mycoin__LevelOfQuote__) */
