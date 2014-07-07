//
//  quote.h
//  mycoin
//
//  Created by lx on 13-12-9.
//  Copyright (c) 2013年 lx. All rights reserved.
//

#ifndef mycoin_quote_h
#define mycoin_quote_h

#include <time.h>
#include "message.h"

#ifdef __cplusplus
extern "C"{
#endif


typedef unsigned long long security_code_t;
typedef unsigned int security_price_t;
typedef unsigned int security_quality_t;
typedef unsigned int security_billId_t;

    
#ifdef __cplusplus
}
#endif



//交割单
/* java
class DeliveryOrder{
    int billId;
    int sourceBillId;
    time_t occrTime;
    class Item{
        int price;
        int quliaty;
        time_t occrTime;
    }
    public getItem();
};
 */
#endif
