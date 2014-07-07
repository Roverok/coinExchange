//
//  send_quote.c
//  mycoin
//
//  Created by lx on 14-1-1.
//  Copyright (c) 2014年 lx. All rights reserved.
//

#include <stdio.h>
#include <uv.h>


typedef struct _SecurityQuote{
    security_billId_t billId;
    enum security_bill_t billType;
    time_t occurTime;
    
    security_code_t code;
    security_price_t price;
    security_quality_t quality;
    security_price_t guaranty;
    security_billId_t refBillId;
    bill_status_t status;
    char client[21];
} SecurityQuote;

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
    
    SecurityQuote* quote = req->data;
    time(&quote.occurTime);

    uv_write(&write_req, req->handle, (char *)&quote, 1, write_cb);
    
    uv_shutdown(&shutdown_req, req->handle, shutdown_cb);
    
}

int send_quote(const char * host, int port, security_code_t code,security_price_t price, security_quality_t quality, security_price_t guaranty, const char *client)
{

    uv_loop_t *loop = uv_default_loop();
    
    quote.code = 1;//2
    quote.billId = (long)random();//hash
    quote.billType =  (security_bill_t)random()%4; // BUY_IN_LIMIT_PRICE, SELL_OUT_LIMIT_PRICE,
    
    quote.quality = random() %10;
    if(quote.billType == BUY_IN_LIMIT_PRICE || quote.billType == SELL_OUT_LIMIT_PRICE ){
        quote.price = 5000 + random()% 2000;
    }else{
        quote.guaranty = quote.quality * 6000; //BUY_IN_MARKET_PRICE,SELL_OUT_MARKET_PRICE,
    }

    
        SecurityQuote quote;
       
        uv_run(loop, UV_RUN_ONCE);
    }
    return 0;
}

int withdraw_quote(const char * host, int port, security_code_t code, security_billId_t refBillId, const char *client)
{
    
    uv_loop_t *loop = uv_default_loop();
    uv_tcp_t socket;
    uv_tcp_init(loop, &socket);
    uv_connect_t connect;
    SecurityQuote quote;
    connect.data = &quote;

    struct sockaddr_in dest = uv_ip4_addr(host, port);
    uv_tcp_connect(&connect, &socket, dest, on_connect);
    
    SecurityQuote quote;
    uv_run(loop, UV_RUN_ONCE);
    
    return 0;
}