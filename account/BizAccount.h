//
//  BizAccount.h
//  mycoin
//
//  Created by lx on 13-12-28.
//  Copyright (c) 2013年 lx. All rights reserved.
//

#ifndef __mycoin__BizAccount__
#define __mycoin__BizAccount__
#include <string>
#include "Account.h"

using namespace std;
class BizAccount{
public:
    static const char* getDeposit(int code){
        switch (code) {
            case 0:
                return ACCOUNT_DEPOSIT;
                break;
            case 1:
                return ACCOUNT_BTC_DEPOSIT;
            case 2:
                return ACCOUNT_LTC_DEPOSIT;
            default:
                return "";
        }
    }
    
    static const char* getExchange(int code){
        switch (code) {
            case 00:
                return ACCOUNT_EXCHANGE;
                break;
            case 1:
                return ACCOUNT_BTC_EXCHANGE;
            case 2:
                return ACCOUNT_LTC_EXCHANGE;
            default:
                return "";
        }
    }
    
    static const char* getForsale(int code){
        switch (code) {
            case 0:
                return "";
                break;
            case 1:
                return ACCOUNT_BTC_FORSALE;
            case 2:
                return ACCOUNT_LTC_FORSALE;
            default:
                return "";
        }
    }
};

#endif /* defined(__mycoin__BizAccount__) */
