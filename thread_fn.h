//
//  thread_fn.h
//  mycoin
//
//  Created by lx on 14-1-9.
//  Copyright (c) 2014年 lx. All rights reserved.
//

#ifndef mycoin_thread_fn_h
#define mycoin_thread_fn_h
/*
#ifdef __cplusplus
extern "C"{
#endif
*/
struct thread_context_t{
    ReaderWriterQueue<message_t> * msgs;
    ReaderWriterQueue<message_t> * outs;
};

void match_fn(void *);

void io_fn(void *);

/*
#ifdef __cplusplus
}
#endif
*/

#endif
