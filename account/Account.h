//
//  Account.h
//  mycoin
//
//  Created by lx on 13-12-13.
//  Copyright (c) 2013年 lx. All rights reserved.
//

#ifndef mycoin_Account_h
#define mycoin_Account_h
#include <time.h>
#include <string>

#define ACCOUNT_DEPOSIT ""
#define ACCOUNT_EXCHANGE ""
#define ACCOUNT_EXCHANGE ""
#define ACCOUNT_SUBSCRIPTION ""
#define ACCOUNT_BTC_EXCHANGE ""
#define ACCOUNT_BTC_FORSALE ""
#define ACCOUNT_BTC_DEPOSIT ""

#define ACCOUNT_LTC_EXCHANGE ""
#define ACCOUNT_LTC_DEPOSIT ""
#define ACCOUNT_LTC_FORSALE ""

#define ACCOUNT_FEE_TRANSACTION ""
#define ACCOUNT_CASH ""
#define ACCOUNT_INCOME_TRANSACTION ""
#define ACCOUNT_REFUND ""

typedef enum balance_type_t{REAL_TIME, WEEK, MONTH, YEAE} balance_type_t;
typedef int money_t;
using namespace std;
class Account{
protected:
    const string& code;
    const string& owner;
    time_t start_time;
    time_t end_time;
    money_t balance;
protected:
    virtual bool debit(time_t occurTime, money_t  money){return false;}
    virtual bool credit(time_t  occurTime, money_t  money){return false;}
    friend class AccountSuite;
public:
    money_t geBalance() { return balance;}
    Account(const string& owner, const string& code):code(code), owner(owner){}
};


//AccountSuite
//owner, create_time, description, start_time, end_time
class AccountSuite{
protected:
    const string& owner;
    time_t create_time;
    string description;
    time_t start_time;
    time_t end_time;
    
    AccountingVoucher& voucher;
    map<string, Account> accountMap;
    
public:
    AccountSuite(AccountingVoucher& voucher):voucher(voucher){};
    Account& getAccount(const string& code);
    AccountSuite(const string& name):owner(name){}
    
    bool account(const string& debitCode, const string& creditCode, money_t money){
        time_t now;
        time(&now);
        voucher.account( now, this, debitCode, creditCode, money);
    }
    bool account(Account& debitAccount, Account& creditAccount, money_t  money){
        return account( debitAccount.code, creditAccount.code, money);
    }
};

//记账凭证
class AccountingVoucher{
public:
    bool account(time_t now, AccountSuite& suit, const string& debitCode, const string& creditCode,  money_t  money);
    
};

#endif
