//
//  message_extend.h
//  mycoin
//
//  Created by lx on 14-1-8.
//  Copyright (c) 2014年 lx. All rights reserved.
//

#ifndef mycoin_message_extend_h
#define mycoin_message_extend_h
#include "message.h"

#ifdef __cplusplus
extern "C" {
#endif
    enum message_type_t identify_message(void *_buffer, int start_offset);
    
    typedef union message_u{
        SecurityQuote quote;
        WithdrawQuote withdraw;
        ContractNote note;
        AccountExchangeNote note;
    }message_t;
    // 宏要能把 类型 置换掉 #define message.msg_type message.quote.msg_type
    enum message_type_t message_convert( char *buf, size_t len, message_t * msg);
#ifdef __cplusplus
}
#endif
#endif
