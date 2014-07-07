//
//  RedisAccount.cpp
//  mycoin
//
//  Created by lx on 14-1-11.
//  Copyright (c) 2014年 lx. All rights reserved.
//
/*
 使用nosql，在灾难恢复方面及其难处理。数据不一致，看起来可行的办法还是在源头保存事件，进行事件重演
 */
#include "RedisVoucher.h"
typdef struct account_context{
    EventSwitcher *switcher;
    Event event;
}account_context_t;

static void account_start(redisAsyncContext *c, void *r, void *privdata){
    account_context_t context = (account_context_t *) privdata;
    redisReply *reply = r;
    if (reply == NULL) {
        context->event.status = STATUS_ERROR;
    }else{
        switch(reply->type){
            case REDIS_REPLY_STRING:
                break;
            case REDIS_REPLY_ARRAY:
                for (j = 0; j < reply->elements; j++) {
                    printf("%u) %s\n", j, reply->element[j]->str);
                }
                break;
            case REDIS_REPLY_INTEGER:
                break;
            case REDIS_REPLY_NIL:
                break;
            case REDIS_REPLY_STATUS:
                break;
            case REDIS_REPLY_ERROR:
                break;
        }
        event.status = STATUS_ACCOUNTED;
    }
    typedef struct redisReply {
        int type; /* REDIS_REPLY_* */
        long long integer; /* The integer when type is REDIS_REPLY_INTEGER */
        int len; /* Length of string */
        char *str; /* Used for both REDIS_REPLY_ERROR and REDIS_REPLY_STRING */
        size_t elements; /* number of elements, for REDIS_REPLY_ARRAY */
        struct redisReply **element; /* elements vector for REDIS_REPLY_ARRAY */
    } redisReply;
    context->switcher->push(event);
}

static void account_cb(redisAsyncContext *c, void *r, void *privdata){
    account_context_t context = (account_context_t *) privdata;
    redisReply *reply = r;
    if (reply == NULL) {
        context->event.status = STATUS_ERROR;
    }else{
        switch(reply->type){
            case REDIS_REPLY_STRING:
                break;
            case REDIS_REPLY_ARRAY:
                for (j = 0; j < reply->elements; j++) {
                    printf("%u) %s\n", j, reply->element[j]->str);
                }
                break;
            case REDIS_REPLY_INTEGER:
                break;
            case REDIS_REPLY_NIL:
                break;
            case REDIS_REPLY_STATUS:
                break;
            case REDIS_REPLY_ERROR:
                break;
        }
        event.status = STATUS_ACCOUNTED;
    }
    typedef struct redisReply {
        int type; /* REDIS_REPLY_* */
        long long integer; /* The integer when type is REDIS_REPLY_INTEGER */
        int len; /* Length of string */
        char *str; /* Used for both REDIS_REPLY_ERROR and REDIS_REPLY_STRING */
        size_t elements; /* number of elements, for REDIS_REPLY_ARRAY */
        struct redisReply **element; /* elements vector for REDIS_REPLY_ARRAY */
    } redisReply;
    context->switcher->push(event);
}

bool RedisVoucher::account(const string& suit, const string& debitCode, const string& creditCode,  money_t  money){
    
    const string key = suite +
    redisAsyncCommand(context, NULL, NULL, "MULTI");
    redisAsyncCommand(context, NULL, NULL, "WATCH %b");

    //debit
    redisAsyncCommand(context, account_start, NULL, "HMSET %b debit %b"
                      ,json, strlen(json),debitCode, strlen(debitCode));
    /*
    
    sql << "insert into " <<  detail_table << "(occur_time, debit, credit, owner) values( ?, ?, 0,?)", use(occurTime), use(money), use(owner);
    
    //balance_type 　时间
    sql << "update "  << table << " set occur_time=:occur_time, balance =banalce + " <<money << " where balance_type=" << 0 <<" and owner=:owner ", use(occurTime, "occur_time"),  use(owner, "owner");
    
    //credit
    sql << "insert into " <<  detail_table << "(occur_time, debit, credit, owner) values( ?, 0, ?,?)", use(occurTime),  use(money),use(owner);
    //balance_type 　时间
    sql << "update "  << table << " set occur_time=:occur_time, balance =banalce - " <<money << " where balance_type=" <<0 <<" and owner=:owner ", use(occurTime, "occur_time"),  use(owner, "owner");
    */
    redisAsyncCommand(context, NULL, NULL, "EXEC");
    return true;
    
}



