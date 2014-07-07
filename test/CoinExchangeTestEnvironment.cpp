/
//  CoinExchangeTestEnvironment.cpp
//  mycoin
//
//  Created by lx on 13-12-21.
//  Copyright (c) 2013年 lx. All rights reserved.
//

#include "CoinExchangeTestEnvironment.h"

void CoinExchangeTestEnvironment::SetUp()
{
    srand((unsigned)time(0));
    std::cout << "CoinExchange Environment SetUP" << std::endl;
}

void CoinExchangeTestEnvironment::TearDown()
{
        std::cout << "CoinExchange Environment TearDown" << std::endl;
}