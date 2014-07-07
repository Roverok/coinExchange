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
#include <map>
#include <soci/soci.h>
#include "Account.h"

using namespace std;
using namespace soci;

class DatabaseVoucher :public AccountingVoucher{
public:
    bool account(time_t now, AccountSuite& suit, const string& debitCode, const string& creditCode,  money_t  money);
    
};


#endif /* defined(__mycoin__DatabaseAccount__) */
