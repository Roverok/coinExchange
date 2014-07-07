//
//  MatchStrategy.h
//  mycoin
//
//  Created by lx on 13-12-21.
//  Copyright (c) 2013年 lx. All rights reserved.
//

#ifndef __mycoin__MatchStrategy__
#define __mycoin__MatchStrategy__
#include "../quote.h"
#include "LevelOfQuoteQueue.h"


/*
 非类型形参
 　　　　2.1 、非类型模板形参：模板的非类型形参也就是内置类型形参，如template<class T, int a> class B{};其中int a就是非类型的模板形参。
 
 　　　　2.2、 非类型形参在模板定义的内部是常量值，也就是说非类型形参在模板的内部是常量。
 
 　　　　2.3、 非类型模板的形参只能是整型，指针和引用，像double，String, String **这样的类型是不允许的。但是double &，double *，对象的引用或指针是正确的。
 
 　　　　2.4、 调用非类型模板形参的实参必须是一个常量表达式，即他必须能在编译时计算出结果。
 
 　　　　2.5 、注意：任何局部对象，局部变量，局部对象的地址，局部变量的地址都不是一个常量表达式，都不能用作非类型模板形参的实参。全局指针类型，全局变量，全局对象也不是一个常量表达式，不能用作非类型模板形参的实参。
 
 　　　　2.6、 全局变量的地址或引用，全局对象的地址或引用const类型变量是常量表达式，可以用作非类型模板形参的实参。
 
 　　　　2.7 、sizeof表达式的结果是一个常量表达式，也能用作非类型模板形参的实参。
 
 　　　　2.8 、当模板的形参是整型时调用该模板时的实参必须是整型的，且在编译期间是常量，比如template <class T, int a> class A{};如果有int b，这时A<int, b> m;将出错，因为b不是常量，如果const int b，这时A<int, b> m;就是正确的，因为这时b是常量。
 
 　　　　2.9 、非类型形参一般不应用于函数模板中，比如有函数模板template<class T, int a> void h(T b){}，若使用h(2)调用会出现无法为非类型形参a推演出参数的错误，对这种模板函数可以用显示模板实参来解决，如用h<int, 3>(2)这样就把非类型形参a设置为整数3。显示模板实参在后面介绍。
 
 　　　　2.10、 非类型模板形参的形参和实参间所允许的转换
 　　　　　　1、允许从数组到指针，从函数到指针的转换。如：template <int *a> class A{}; int b[1]; A<b> m;即数组到指针的转换
 　　　　　　2、const修饰符的转换。如：template<const int *a> class A{}; int b; A<&b> m;   即从int *到const int *的转换。
 　　　　　　3、提升转换。如：template<int a> class A{}; const short b=2; A<b> m; 即从short到int 的提升转换
 　　　　　　4、整值转换。如：template<unsigned int a> class A{};   A<3> m; 即从int 到unsigned int的转换。
 　　　　　　5、常规转换。
 
 1、可以为类模板的类型形参提供默认值，但不能为函数模板的类型形参提供默认值。函数模板和类模板都可以为模板的非类型形参提供默认值。
 
 　　2、类模板的类型形参默认值形式为：template<class T1, class T2=int> class A{};为第二个模板类型形参T2提供int型的默认值。
 
 　　3、类模板类型形参默认值和函数的默认参数一样，如果有多个类型形参则从第一个形参设定了默认值之后的所有模板形参都要设定默认值，比如template<class T1=int, class T2>class A{};就是错误的，因为T1给出了默认值，而T2没有设定。
 
 　　4、在类模板的外部定义类中的成员时template 后的形参表应省略默认的形参类型。比如template<class  T1, class T2=int> class A{public: void h();}; 定义方法为template<class T1,class T2> void A<T1,T2>::h(){}。
 

 */
inline security_quality_t matchTopDown(SecurityQuote &quote, SecurityQuote & peer);
inline security_quality_t matchBottomUp(SecurityQuote &quote, SecurityQuote & peer);

inline security_quality_t marketPriceBuyIn(SecurityQuote &quote, SecurityQuote & peer);
inline security_quality_t marketPriceSellOut(SecurityQuote &quote, SecurityQuote & peer);

#endif /* defined(__mycoin__MatchStrategy__) */
