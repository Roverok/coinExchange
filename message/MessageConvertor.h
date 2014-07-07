//
//  MessageConvertor.h
//  mycoin
//
//  Created by lx on 14-1-8.
//  Copyright (c) 2014年 lx. All rights reserved.
//

#ifndef __mycoin__MessageConvertor__
#define __mycoin__MessageConvertor__
#include "message.h"

template <typename Message>
struct message_traits {
    typedef bool (* convert_func_type)(char *, Message &) ;
    typedef bool (* identify_func_type)(MessageHeader &) ;
};

template<typename message_type>
bool convertMessage( char *buf, size_t len, message_type & msg, typename message_traits<message_type>::identify_func_type identify_func, typename message_traits<message_type>::convert_func_type convert_func){
    unsigned long Message_get_delimited_size(void *_buffer, int offset);
    MessageHeader header;
    /*
     * Tests whether a message can be completely read from the given buffer at
     * the offset. The bytes [offset..offset+length-1] are interpreted.
     *,
     * Returns 1 (true) if buffer[offset..offset+length-1] contains a complete
     * message or 0 (false) otherwise.
     */
    do{
        if( Message_can_read_delimited_from(buf, 0, MAX_MessageHeader_SIZE) == 0)
            break;
        
        /*
         * Serialize a Person-message into the given buffer at offset and return
         * new offset for optional next message.
         */
        int MessageHeader_write_delimited_to(struct MessageHeader *_MessageHeader, void *_buffer, int offset);
        
        
        MessageHeader_read_delimited_from(buf, &header, 0);
        
        if(identify_func(header)){
            //以后将统一生成message，不再把message分散到各处
            return  convert_func(buf, msg);
        }
    }while (false);
    
    return false;
    
}




#endif /* defined(__mycoin__MessageConvertor__) */
