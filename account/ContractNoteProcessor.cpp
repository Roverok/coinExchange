//
//  ContractNoteAccounter.cpp
//  mycoin
//
//  Created by lx on 14-1-9.
//  Copyright (c) 2014年 lx. All rights reserved.
//
#include "account_message.h"
#include <soci/soci.h>
#include "ContractNoteAccounter.h"
#include "Account.h"
#include "BizAccount.h"
#include "AccountSuiteFactory.h"

void ContractNoteProcessor::account(ContractNote &note){
    do{
        
        money_t money = note.price*note.quality;
        money_t fee = money* 5 /1000;

        const string & platform = "platform";
        ResiVoucher voucher (switcher);
        //买方借记资产，贷记资产往来
        if(voucher.account_multi(note.buyer, BizAccount::getDeposit(note.code), BizAccount::getExchange(note.code),note.quality))
            break;
        //买方借记资金往来，贷记押金
        if(voucher.account_multi(note.buyer, ACCOUNT_EXCHANGE, ACCOUNT_SUBSCRIPTION,money))
            break;
        //买方 借记手续费（成交价*数量*比例） 贷记 deposit，如果没钱了，那么借记手续费，贷记应付费用
        if(voucher.account_multi(note.buyer, ACCOUNT_FEE_TRANSACTION, /*deposit_balance >= money or payable*/ACCOUNT_DEPOSIT,  fee))
            break;
        
        //卖方 借记exchange，贷记forsale
        if(voucher.account_multi(note.seller, BizAccount::getExchange(note.code), BizAccount::getForsale(note.code),note.quality))
            break;
        //卖方成交后 借记deposit，贷记资金往来
        if(voucher.account_multi(note.seller, ACCOUNT_DEPOSIT, ACCOUNT_EXCHANGE,money))
            break;
        //卖方手续费 借记手续费（成交价*数量*比例） 贷记 deposit
        if(voucher.account_multi(note.seller, ACCOUNT_FEE_TRANSACTION, /*seller_deposit_balance >= money or payable*/ACCOUNT_DEPOSIT , fee))
            break;
        
        //平台 借计cash 贷记收入 描述　交易号
        if(voucher.account_multi(platform, ACCOUNT_CASH, ACCOUNT_INCOME_TRANSACTION, fee))
            break;
        
        //平台 买方收入　借计cash 贷记收入 描述　交易号
        if(voucher.account_multi(platform, ACCOUNT_CASH, ACCOUNT_INCOME_TRANSACTION, fee))
            break;
        
        //平台 返还卖方 借记退款 refund，贷记cash
        if(voucher.account_multi(platform, ACCOUNT_REFUND,ACCOUNT_CASH, fee))
            break;
        //卖方手续费 借记deposit，贷记退回费用或手续费
        if(voucher.account_multi(note.seller, ACCOUNT_DEPOSIT, ACCOUNT_FEE_TRANSACTION, fee))
            break;
        
        //平台 返还买方 借记退款 refund，贷记cash
        if(voucher.account_multi(platform, ACCOUNT_REFUND,ACCOUNT_CASH, fee))
            break;
        //买方 借记deposit，贷记退回费用或手续费
        if(voucher.account_multi(note.buyer, ACCOUNT_DEPOSIT, ACCOUNT_FEE_TRANSACTION, fee))
            break;
        voucher.submit();
      
    }while(false);
    
}

