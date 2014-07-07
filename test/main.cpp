//
//  test.cpp
//  mycoin
//
//  Created by lx on 13-12-21.
//  Copyright (c) 2013年 lx. All rights reserved.
//

#include "test.h"
#include "gtest/gtest.h"

int main(int argc, char **argv) {

    ::testing::AddGlobalTestEnvironment(new CoinExchangeTestEnvironment);
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
