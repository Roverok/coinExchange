//
//  CoinExchangeTestEnvironment.h
//  mycoin
//
//  Created by lx on 13-12-21.
//  Copyright (c) 2013年 lx. All rights reserved.
//

#ifndef __mycoin__CoinExchangeTestEnvironment__
#define __mycoin__CoinExchangeTestEnvironment__

#include <iostream>
//全局事件
class CoinExchangeTestEnvironment : public testing::Environment
{
public:
    /*
     SetUp()方法在所有案例执行前执行
     */
    virtual void SetUp();
    /*
     TearDown()方法在所有案例执行后执行
     */
    virtual void TearDown();
    
};

#endif /* defined(__mycoin__CoinExchangeTestEnvironment__) */
