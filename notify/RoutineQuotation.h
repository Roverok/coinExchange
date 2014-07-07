//
//  RoutineQuotation.h
//  mycoin
//
//  Created by lx on 13-12-24.
//  Copyright (c) 2013年 lx. All rights reserved.
//

#ifndef __mycoin__RoutineQuotation__
#define __mycoin__RoutineQuotation__
/*
routine quotation 日常行情
成交价　时间间隔内的平均价格
成交量　时间间隔内的合计
top行情　实时，因为未成交的top报价也会包含在内，所以包含了历史情况
*/
#include <time.h>
#include "quote.h"
#include <map>
#include "Publisher.h"

using namespace std;

#define MAX_ROUTINE_LEVEL 10

class RoutineQuotation{

private:
    typedef map<security_price_t, security_quality_t> SellQuoteRoutine;
    typedef map<security_price_t, security_quality_t,  greater<int>> BuyQuoteRoutine;

    struct InnerRoutine{
        security_price_t sum=0;
        security_quality_t  qty=0;
        SellQuoteRoutine topSells;
        BuyQuoteRoutine topBuys;
    };
    typedef map<security_code_t,struct InnerRoutine> InnerRoutineMap;

    InnerRoutineMap innerMap;
    
    static inline void fill_zero(InnerRoutine & data){
        data.sum = data.qty = 0;
    }
private:
    template<typename TopQuotes>
    inline void updateTopQuote(TopQuotes& tops, security_price_t price, security_quality_t qty ){
        typename TopQuotes::iterator iter = tops.find(price);
        if(iter != tops.end()){
            iter->second += qty;
        }else{
            tops[price] = qty;
        }
    }
    
public:
    inline void reset()  {
        for (InnerRoutineMap::iterator iter=innerMap.begin(); iter!= innerMap.end(); iter++) {
            
            iter->second.sum = iter->second.qty = 0;
        }
        //for_each(innerMap.begin(), innerMap.end(), fill_zero);
    }
    
    void publish(Publisher &publisher);
    int update(message_t *msg);
    int update(SecurityQuote &quote);
    int update(ContractNote &note);
};

#endif /* defined(__mycoin__RoutineQuotation__) */
