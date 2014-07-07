//
//  MycoinApplication.h
//  mycoin-account
//
//  Created by lx on 13-12-25.
//  Copyright (c) 2013年 lx. All rights reserved.
//

#ifndef __mycoin_account__MycoinApplication__
#define __mycoin_account__MycoinApplication__
#include <Poco/Util/ServerApplication.h>

using namespace Poco;
using namespace Poco::Util;
using namespace std;
class MycoinApplication:public ServerApplication{
public:
    int main( const std::vector < std::string > & args);
protected:
    void handleOption(const std::string& name, const std::string& value){}
    
};

#endif /* defined(__mycoin_account__MycoinApplication__) */
