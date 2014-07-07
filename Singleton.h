//
//  Singleton.h
//  mycoin
//
//  Created by lx on 14-1-6.
//  Copyright (c) 2014年 lx. All rights reserved.
//

#ifndef mycoin_Singleton_h
#define mycoin_Singleton_h

template<typename InnerSingleton, int sub=0 >
class Singleton{
private:
    static InnerSingleton *_instance;
    Singleton(){}
public:
    ~Singleton(){
        delete _instance;
        _instance = 0;
    }
    
    static InnerSingleton&  instance(){
        if(_instance == 0)
            _instance = new InnerSingleton();
        return *_instance;
    }
    
    static void  setInstance(InnerSingleton* single){
        if(single != NULL){
            if(_instance != NULL){
                delete _instance;
            }
            _instance = single;
        }
};

#endif
