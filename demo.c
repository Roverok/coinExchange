//
//  test.cpp
//  mycoin
//
//  Created by lx on 13-12-17.
//  Copyright (c) 2013年 lx. All rights reserved.
//
#include <stdio.h>
#include <stdlib.h>
#include <uv.h>
#include <time.h>
#include "demo.h"
#include "quote.h"

static uv_shutdown_t shutdown_req;
static uv_write_t write_req;
struct sockaddr_in dest;
static uv_loop_t *loop;

static void write_cb(uv_write_t* req, int status) {
    

}

static void close_cb(uv_handle_t* handle) {
    uv_tcp_t socket;
    uv_tcp_init(loop, &socket);
    uv_connect_t connect;
    
    uv_tcp_connect(&connect, &socket, dest, on_connect);
}

static void shutdown_cb(uv_shutdown_t* req, int status) {
    
    uv_close((uv_handle_t*)req->handle, close_cb);
}

void on_connect(uv_connect_t* req, int status){
    
    SecurityQuote quote;
    time(&quote.occurTime);
    //撤销单
    //撤销买单，撤销卖单-简单，空单时
    //　有单时
    //　单已全部成交
    //　单成交部分
    //　单完全没成交
    //限价单
    //市价单
    quote.code = 1;//2
    quote.billId = (long)random();//hash
    quote.billType =  (security_bill_t)random()%4; // BUY_IN_LIMIT_PRICE, SELL_OUT_LIMIT_PRICE,
    
    quote.quality = random() %10;
    if(quote.billType == BUY_IN_LIMIT_PRICE || quote.billType == SELL_OUT_LIMIT_PRICE ){
        quote.price = 5000 + random()% 2000;
    }else{
        quote.guaranty = quote.quality * 6000; //BUY_IN_MARKET_PRICE,SELL_OUT_MARKET_PRICE,
    }
    
    uv_write(&write_req, req->handle, (char *)&quote, 1, write_cb);
    
    uv_shutdown(&shutdown_req, req->handle, shutdown_cb);
 
}


void thread_fn(void * arg){
    srand((unsigned)time(0));
    dest = uv_ip4_addr("127.0.0.1", 7000);
    
    loop = uv_loop_new();
    uv_tcp_t socket;
    uv_tcp_init(loop, &socket);
    uv_connect_t connect;
    
    uv_tcp_connect(&connect, &socket, dest, on_connect);
    uv_run(loop, UV_RUN_DEFAULT);
}

int main() {
    
    int tracklen = 10;
    for(int i=0; i< 2; i++){
        uv_thread_t tortoise_id;
        uv_thread_create(&tortoise_id, thread_fn, &tracklen);
        uv_thread_join(&tortoise_id);
    }
    
    return 0;
}