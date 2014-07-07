//
//  DatabaseAccount.cpp
//  mycoin
//
//  Created by lx on 13-12-15.
//  Copyright (c) 2013年 lx. All rights reserved.
//

#include "DatabaseAccount.h"

bool DatabaseVoucher::account(time_t occurTime, AccountSuite& suit, const string& debitCode, const string& creditCode,  money_t  money){
    /*
    //debit
    sql << "insert into " <<  detail_table << "(occur_time, debit, credit, owner) values( ?, ?, 0,?)", use(occurTime), use(money), use(owner);
    
    //balance_type 　时间
    sql << "update "  << table << " set occur_time=:occur_time, balance =banalce + " <<money << " where balance_type=" << 0 <<" and owner=:owner ", use(occurTime, "occur_time"),  use(owner, "owner");
    
    //credit
    sql << "insert into " <<  detail_table << "(occur_time, debit, credit, owner) values( ?, 0, ?,?)", use(occurTime),  use(money),use(owner);
    //balance_type 　时间
    sql << "update "  << table << " set occur_time=:occur_time, balance =banalce - " <<money << " where balance_type=" <<0 <<" and owner=:owner ", use(occurTime, "occur_time"),  use(owner, "owner");
     */
    return true;
}


    /*
Account AccountDAOSqlite::get(int id){
    session sql(sqlite3, "mycoin.sqlite");
    int count;
    sql << "select count(*) from invoices", into(count);

    int id = 7;
    sql << "select name from person where id = :id", use(id, "id");

    ofstream file("my_log.txt");
    sql.set_log_stream(&file);


const int BATCH_SIZE = 25;
std::vector<int> ids;
for (int i = 0; i != BATCH_SIZE; ++i)
{
    ids.push_back(i);
}

statement st = (sql.prepare <<
                "insert into numbers(value) values(:val)",
                use(ids));
for (int i = 0; i != 4; ++i)
{
    st.execute(true);
}
}
     */




