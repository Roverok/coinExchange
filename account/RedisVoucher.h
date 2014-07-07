//
//  RedisAccount.h
//  mycoin
//
//  Created by lx on 14-1-11.
//  Copyright (c) 2014年 lx. All rights reserved.
//

#ifndef __mycoin__RedisAccount__
#define __mycoin__RedisAccount__

//
//  DatabaseAccount.h
//  mycoin
//
//  Created by lx on 13-12-15.
//  Copyright (c) 2013年 lx. All rights reserved.
//

#ifndef __mycoin__DatabaseAccount__
#define __mycoin__DatabaseAccount__
#include <string>
#include "Account.h"

using namespace std;
class RedisVoucher:public AccountVoucher{
private:
    EventSwitcher &switcher;
    map<string, Account> accountMap;
    
public:
    RedisVoucher(EventSwitcher &switcher):switcher(switcher){}
    Account& getAccount(const string& code);
    bool account( AccountSuite& suit, const string& debitCode, const string& creditCode,  money_t  money);
    bool account( AccountSuite& suit, const string& debitCode, const string& creditCode,  money_t  money);
    void submit();
};





#endif /* defined(__mycoin__RedisAccount__) */
