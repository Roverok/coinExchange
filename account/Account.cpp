//
//  Account.cpp
//  mycoin
//
//  Created by lx on 13-12-28.
//  Copyright (c) 2013年 lx. All rights reserved.
//

#include "Account.h"


    /*
     private:
     multimap<money_t, Account*> m_debitList, m_creditList;
     struct Compare
     {
     bool operator()(const Account& s1, const Account& s2) const
     {
     return strcmp(s1, s2) < 0;
     }
     };
     
     public :
     
     
     void debit(Account* debitAccount, money_t const & money){
     m_debitList.insert(pair<money, debitAccount>);
     }
     
     void credit(Account* creditAccount, money_t const & money){
     m_creditList.insert<money,creditAccount>;
     }
     
     bool account(){
     //校验两个列表金额时候相等
     //事务处理
     return true;
     }
     */
Account& AccountSuite::getAccount(const string& code){
    map<string, Account>::iterator iter = accountMap.find(code);
    if(iter == accountMap.end()){
        //  iter = accountMap.insert(pair<string, Account>(code, DatabaseAccount(owner,code, ses)));
    }
    return iter->second;
}

