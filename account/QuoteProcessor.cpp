//
//  account_quote.cpp
//  mycoin
//
//  Created by lx on 14-1-9.
//  Copyright (c) 2014年 lx. All rights reserved.
//

#include "account_message.h"

static bool record(session &ses, SecurityQuote &quote){
    do{
        ses << "insert into quote_bill(bill_id, bill_type, occur_time, status, security_code, price, quality, guaranty,client)  values(?, ?, ?, ?, ?, ?, ?, ?,?)",
        use(quote.billId), use(quote.billType) , use(quote.occurTime), use(quote.status)
            ,use(quote.code), use(quote.price), use(quote.quality), use(quote.guaranty)
            , use(( char*)quote->client);

        
    }while(false);
    
    return true;
    
}

int QuoteProcessor::match(SecurityQuote &quote,EventSwitcher &switcher){
    Singleton<Match>::instance().push(quote); //跨线程要明显的表示出来，不好用now
}

int QuoteProcessor::buyInPrepare(session &ses, SecurityQuote &quote){
    do {
        transaction tr(ses);
        if(!record(ses, quote))
            break;
        AccountSuite* suite = AccountSuiteFactory::instance(ses).getSuite(quote.client);
        
        //买方 借记订金，贷记现金
        if(AccountingVoucher::account(*suite, ACCOUNT_DEPOSIT, ACCOUNT_SUBSCRIPTION,quote.guaranty))
            break;
        
        tr.commit();
        quote.status = STATUS_ACCEPTED;
        return quote.status;
    } while (false);
    
    
    return STATUS_REJECTED;
}

static int sellOutPrepare(session &ses, SecurityQuote &quote){
    do{
        transaction tr(ses);
        if(!record(ses, quote))
            break;
        
        //取消 借记deposit，贷记订金subscription
        
        AccountSuite& suite = *AccountSuiteFactory::instance(ses).getSuite(quote.client);
        if(AccountingVoucher::account(suite, ACCOUNT_DEPOSIT, ACCOUNT_SUBSCRIPTION, quote.guaranty))
            break;
        tr.commit();
        quote.status = STATUS_FINISHED;
        
        return quote.status;
    }while(false);
    
    return STATUS_REJECTED;
}

int prepareQuote(SecurityQuote &quote){
    switch(quote.billType){
        case BUY_IN_LIMIT_PRICE:
        case BUY_IN_MARKET_PRICE:
            return buyInPrepare(ses, &quote);
        case SELL_OUT_LIMIT_PRICE:
        case SELL_OUT_MARKET_PRICE:
            return sellOutPrepare(ses, &quote);
        default:
            return STATUS_REJECTED;
    }
}

static int buyInAccount(session &ses, SecurityQuote &quote){
    
    do{
        transaction tr(ses);
        ses << "update quote_bill set status = " << STATUS_FINISHED<<" where id = ?" , use(quote.billId);
        
        AccountSuite& suite = *AccountSuiteFactory::instance(ses).getSuite(quote.client);
        //取消 借记金融资产，贷记可供出售金融资产
        if(AccountingVoucher::account(suite, BizAccount::getDeposit(quote.code), BizAccount::getForsale(quote.code), quote.quality))
            break;
        tr.commit();
        quote.status = STATUS_FINISHED;
        
        return quote.status;
    }while(false);
    
    return STATUS_REJECTED;
}


static int sellOutAccount(session &ses, SecurityQuote &quote){
    
    do{
        transaction tr(ses);
        
        ses << "update quote_bill set status = ? where id = ?",use((int)STATUS_FINISHED), use(quote.billId);
        
        //取消 借记deposit，贷记订金subscription
        
        AccountSuite& suite = *AccountSuiteFactory::instance(ses).getSuite(quote.client);
        if(AccountingVoucher::account(suite, ACCOUNT_DEPOSIT, ACCOUNT_SUBSCRIPTION, quote.guaranty))
            break;
        tr.commit();
        quote.status = STATUS_FINISHED;
        
        return quote.status;
    }while(false);
    
    return STATUS_REJECTED;
    
}

int accountQuote(SecurityQuote &quote){
    switch(quote.billType){
        case BUY_IN_LIMIT_PRICE:
        case BUY_IN_MARKET_PRICE:
            return buyInAccount(ses, quote);
        case SELL_OUT_LIMIT_PRICE:
        case SELL_OUT_MARKET_PRICE:
            return sellOutAccount(ses, quote);
        default:
            return STATUS_REJECTED;
    }
}