//
//  message_extend.c
//  mycoin
//
//  Created by lx on 14-1-8.
//  Copyright (c) 2014年 lx. All rights reserved.
//
#include "message_extend.h"

extern int read_raw_varint32(unsigned long *tag, void *_buffer, int offset);

enum message_type_t identify_message(void *_buffer, int start_offset){
    unsigned long size;
    
    unsigned long offset = read_raw_varint32(&size, _buffer, start_offset);
    unsigned long tag = 0;
    
    if(offset < size + offset) {
        offset = read_raw_varint32(&tag, _buffer, offset);
        tag = tag>>3;
        if(tag == 1){
            offset = read_raw_varint32(&tag, _buffer, offset);
            return tag;
        }
    }
    return UNKOWN_MESSAGE;
}


enum message_type_t message_convert( char *buf, size_t len, message_t * msg){
    unsigned long Message_get_delimited_size(void *_buffer, int offset);
    /*
     * Tests whether a message can be completely read from the given buffer at
     * the offset. The bytes [offset..offset+length-1] are interpreted.
     *,
     * Returns 1 (true) if buffer[offset..offset+length-1] contains a complete
     * message or 0 (false) otherwise.
     */
    enum message_type_t msg_type = UNKOWN_MESSAGE;
    do{
        msg_type = identify_message(buf,0);
        switch (msg_type) {
            case SECURITY_QUOTE:
                break;
            case WITHDRAW_QUOTE:
                break;
            case CONTRACT_NOTE:
                ContractNote_read_delimited_from(buf, &quote, 0)
                break;
            case ACCOUNT_EXCHANGE_NOTE:
                
                break;
            default:
                break;
        }
    }while (0);
    
    return msg_type;
}