//
//  account_exchange.cpp
//  mycoin
//
//  Created by lx on 14-1-9.
//  Copyright (c) 2014年 lx. All rights reserved.
//

#include "account_message.h"

static bool record(session &ses, WithdrawQuote &quote){
    do{
        ses << "insert into exchange_bill(bill_id, bill_type, occur_time, security_code,  quality, client)  values(?, ?, ?, ?, ?, ?)",
        use(quote.billId), use(quote.billType), use(quote.occurTime)
        , use(quote.code), use(quote.quality), use(quote.client);
        
    }while(false);
    
    return true;
    
}

int AccountExchangeProcessor::charge(AccountExchangeNote &note, EventSwitcher& switcher){
    do {        

        
        // 借记depoist资产，贷记资金往来
        if(RedisVoucher::account(note.client, BizAccount::getDeposit(note.code), BizAccount::getExchange(note.code),note.quality)){


    } while (false);
    
    return STATUS_REJECTED;
}

int AccountExchangeProcessor::withdraw(AccountExchangeNote &note, EventSwitcher& switcher){
    do {

        //借记资金往来，贷记deposit
        if(RedisVoucher::account(note.client, BizAccount::getExchange(note.code),BizAccount::getDeposit(note.code), note.quality)){
            tr.commit();
            note.status = STATUS_FINISHED;
        }else{
            tr.rollback();
        }
    } while (false);
    
    return STATUS_REJECTED;
}



