//
//  test.h
//  mycoin
//
//  Created by lx on 13-12-21.
//  Copyright (c) 2013年 lx. All rights reserved.
//

#ifndef __mycoin__test__
#define __mycoin__test__

/*
 宏中的#的功能是将其后面的宏参数进行字符串化操作（Stringizing operator），简单说就是在它引用的宏变量的左右各加上一个双引号。
 #@是加单引号
 ##是拼接符号（Token-pasting operator）。
 例：
 #define paster( n ) token##n
 paster(9)展开后token##n变成token9。
 */

/*
 for (int i = 0; i < x.size(); ++i)
{
    EXPECT_EQ(x[i], y[i]) << "Vectors x and y differ at index " << i;
}
 */
/*
 布尔值检查
 Fatal assertion	Nonfatal assertion	Verifies
 ASSERT_TRUE(condition);	EXPECT_TRUE(condition);	condition is true
 ASSERT_FALSE(condition);	EXPECT_FALSE(condition);	condition is false
 
 数值型数据检查
 
 Fatal assertion	Nonfatal assertion	Verifies
 ASSERT_EQ(expected, actual);	EXPECT_EQ(expected, actual);	expected == actual
 ASSERT_NE(val1, val2);	EXPECT_NE(val1, val2);	val1 != val2
 ASSERT_LT(val1, val2);	EXPECT_LT(val1, val2);	val1 < val2
 ASSERT_LE(val1, val2);	EXPECT_LE(val1, val2);	val1 <= val2
 ASSERT_GT(val1, val2);	EXPECT_GT(val1, val2);	val1 > val2
 ASSERT_GE(val1, val2);	EXPECT_GE(val1, val2);	val1 >= val2
 
 
 字符串检查
 
 Fatal assertion	Nonfatal assertion	Verifies
 ASSERT_STREQ(expected_str, actual_str);	EXPECT_STREQ(expected_str, actual_str);	 the two C strings have the same content
 ASSERT_STRNE(str1, str2);	EXPECT_STRNE(str1, str2);	 the two C strings have different content
 ASSERT_STRCASEEQ(expected_str, actual_str);	EXPECT_STRCASEEQ(expected_str, actual_str);	 the two C strings have the same content, ignoring case
 ASSERT_STRCASENE(str1, str2);	EXPECT_STRCASENE(str1, str2);	 the two C strings have different content, ignoring case
 *STREQ*和*STRNE*同时支持char*和wchar_t*类型的，*STRCASEEQ*和*STRCASENE*却只接收char*
 
 显示返回成功或失败
 直接返回成功：SUCCEED();
 
 返回失败：
 Fatal assertion	Nonfatal assertion
 FAIL();	ADD_FAILURE();
 
 异常检查
 
 Fatal assertion	Nonfatal assertion	Verifies
 ASSERT_THROW(statement, exception_type);	EXPECT_THROW(statement, exception_type);	statement throws an exception of the given type
 ASSERT_ANY_THROW(statement);	EXPECT_ANY_THROW(statement);	statement throws an exception of any type
 ASSERT_NO_THROW(statement);	EXPECT_NO_THROW(statement);	statement doesn't throw any exception
 
 Predicate Assertions
 在使用EXPECT_TRUE或ASSERT_TRUE时，有时希望能够输出更加详细的信息，比如检查一个函数的返回值TRUE还是FALSE时，希望能够输出传入的参数是什么，以便失败后好跟踪。因此提供了如下的断言：
 Fatal assertion            Nonfatal assertion          Verifies
 ASSERT_PRED1(pred1, val1);	EXPECT_PRED1(pred1, val1);	pred1(val1) returns true
 ASSERT_PRED2(pred2, val1, val2);	EXPECT_PRED2(pred2, val1, val2);	pred2(val1, val2) returns true
 
 Google人说了，他们只提供<=5个参数的，如果需要测试更多的参数，直接告诉他们。
 bool MutuallyPrime(int m, int n)
 {
 return Foo(m , n) > 1;
 }
 
 TEST(PredicateAssertionTest, Demo)
 {
 int m = 5, n = 6;
 EXPECT_PRED2(MutuallyPrime, m, n);
 }
 当失败时，返回错误信息：
 
 error: MutuallyPrime(m, n) evaluates to false, where
 m evaluates to 5
 n evaluates to 6
 
 如果对这样的输出不满意的话，还可以自定义输出格式，通过如下：
 
 Fatal assertion	Nonfatal assertion	Verifies
 ASSERT_PRED_FORMAT1(pred_format1, val1);`	EXPECT_PRED_FORMAT1(pred_format1, val1);	pred_format1(val1) is successful
 ASSERT_PRED_FORMAT2(pred_format2, val1, val2);	EXPECT_PRED_FORMAT2(pred_format2, val1, val2);	pred_format2(val1, val2) is successful
 testing::AssertionResult AssertFoo(const char* m_expr, const char* n_expr, const char* k_expr, int m, int n, int k) {
 if (Foo(m, n) == k)
 return testing::AssertionSuccess();
 testing::Message msg;
 msg << m_expr << " 和 " << n_expr << " 的最大公约数应该是：" << Foo(m, n) << " 而不是：" << k_expr;
 return testing::AssertionFailure(msg);
 }
 
 TEST(AssertFooTest, HandleFail)
 {
 EXPECT_PRED_FORMAT3(AssertFoo, 3, 6, 2);
 }
 
 浮点型检查
 
 Fatal assertion	Nonfatal assertion	Verifies
 ASSERT_FLOAT_EQ(expected, actual);	EXPECT_FLOAT_EQ(expected, actual);	 the two float values are almost equal
 ASSERT_DOUBLE_EQ(expected, actual);	EXPECT_DOUBLE_EQ(expected, actual);	 the two double values are almost equal
 
 
 对相近的两个数比较：
 
 Fatal assertion	Nonfatal assertion	Verifies
 ASSERT_NEAR(val1, val2, abs_error);	EXPECT_NEAR(val1, val2, abs_error);	 the difference between val1 and val2 doesn't exceed the given absolute error
 
 
 同时，还可以使用：
 
 EXPECT_PRED_FORMAT2(testing::FloatLE, val1, val2);
 EXPECT_PRED_FORMAT2(testing::DoubleLE, val1, val2);
 
 类型检查
 类型检查失败时，直接导致代码编不过，难得用处就在这？看下面的例子：
 
 复制代码
 template <typename T> class FooType {
 public:
 void Bar() { testing::StaticAssertTypeEq<int, T>(); }
 };
 
 TEST(TypeAssertionTest, Demo)
 {
 FooType<bool> fooType;
 fooType.Bar();
 }
 
 死亡测试
 Fatal assertion	Nonfatal assertion	Verifies
 ASSERT_DEATH(statement, regex`);	EXPECT_DEATH(statement, regex`);	statement crashes with the given error
 ASSERT_EXIT(statement, predicate, regex`);	EXPECT_EXIT(statement, predicate, regex`);	statement exits with the given error and its exit code matches predicate
 
 
 由于有些异常只在Debug下抛出，因此还提供了*_DEBUG_DEATH，用来处理Debug和Realease下的不同。
 
 正则表达式
 在POSIX系统（Linux, Cygwin, 和 Mac）中，gtest的死亡测试中使用的是POSIX风格的正则表达式
 在Windows系统中，gtest的死亡测试中使用的是gtest自己实现的简单的正则表达式语法。 相比POSIX风格，gtest的简单正则表达式少了很多内容，比如 ("x|y"), ("(xy)"), ("[xy]") 和("x{5,7}")都不支持。
 
 下面是简单正则表达式支持的一些内容：
 matches any literal character c
 \\d	 matches any decimal digit
 \\D	 matches any character that's not a decimal digit
 \\f	 matches \f
 \\n	 matches \n
 \\r	 matches \r
 \\s	 matches any ASCII whitespace, including \n
 \\S	 matches any character that's not a whitespace
 \\t	 matches \t
 \\v	 matches \v
 \\w	 matches any letter, _, or decimal digit
 \\W	 matches any character that \\w doesn't match
 \\c	 matches any literal character c, which must be a punctuation
 .	 matches any single character except \n
 A?	 matches 0 or 1 occurrences of A
 A*	 matches 0 or many occurrences of A
 A+	 matches 1 or many occurrences of A
 ^	 matches the beginning of a string (not that of each line)
 $	 matches the end of a string (not that of each line)
 xy	 matches x followed by y
 
 
 gtest定义两个宏，用来表示当前系统支持哪套正则表达式风格：
 1. POSIX风格：GTEST_USES_POSIX_RE = 1
 2. Simple风格：GTEST_USES_SIMPLE_RE=1
 
 七、死亡测试运行方式
 1. fast方式（默认的方式）
 testing::FLAGS_gtest_death_test_style = "fast";
 2. threadsafe方式
 testing::FLAGS_gtest_death_test_style = "threadsafe";
 
 你可以在 main() 里为所有的死亡测试设置测试形式，也可以为某次测试单独设置。Google Test会在每次测试之前保存这个标记并在测试完成后恢复。如：
 TEST(MyDeathTest, TestOne) {
 testing::FLAGS_gtest_death_test_style = "threadsafe";
 // This test is run in the "threadsafe" style:
 ASSERT_DEATH(ThisShouldDie(), "");
 }
 
 TEST(MyDeathTest, TestTwo) {
 // This test is run in the "fast" style:
 ASSERT_DEATH(ThisShouldDie(), "");
 }
 
 int main(int argc, char** argv) {
 testing::InitGoogleTest(&argc, argv);
 testing::FLAGS_gtest_death_test_style = "fast";
 return RUN_ALL_TESTS();
 }

 注意事项
 1. 不要在死亡测试里释放内存。
 2. 在父进程里再次释放内存。
 3. 不要在程序中使用内存堆检查。
 */

/*
value-parameterized tests　参数化测试数据
 1. 告诉gtest你的参数类型
 添加一个继承自testing::TestWithParam<T>的类，，其中T就是你需要参数化的参数类型，如参数化一个int型的参数
 class IsPrimeParamTest : public::testing::TestWithParam<int>
 {
 
 };
 
 2. 使用宏TEST_P，在TEST_P宏里，用GetParam()获取当前的参数的具体值
 TEST_P(IsPrimeParamTest, HandleTrueReturn)
 {
 int n =  GetParam();
 EXPECT_TRUE(IsPrime(n));
 }
 
 
 3. 使用INSTANTIATE_TEST_CASE_P宏获取要测试的参数范围
 INSTANTIATE_TEST_CASE_P(TrueReturn, IsPrimeParamTest, testing::Values(3, 5, 11, 23, 17));
 
 第一个参数是测试案例的前缀，可以任意取。
 第二个参数是测试案例的名称，需要和之前定义的参数化的类的名称相同，如：IsPrimeParamTest
 第三个参数是可以理解为参数生成器，上面的例子使用test::Values表示使用括号内的参数。Google提供了一系列的参数生成的函数：
 Range(begin, end[, step])	 范围在begin~end之间，步长为step，不包括end
 Values(v1, v2, ..., vN)	 v1,v2到vN的值
 ValuesIn(container) and ValuesIn(begin, end)　从一个C类型的数组或是STL容器，或是迭代器中取值
 Bool()	 取false 和 true 两个值
 Combine(g1, g2, ..., gN)　将g1,g2,...gN进行排列组合，g1,g2,...gN本身是一个参数生成器，每次分别从g1,g2,..gN中各取出一个值，组合成一个元组(Tuple)作为一个参数。
 
 说明：这个功能只在提供了<tr1/tuple>头的系统中有效。gtest会自动去判断是否支持tr/tuple，如果你的系统确实支持，而gtest判断错误的话，你可以重新定义宏GTEST_HAS_TR1_TUPLE=1。
 
 ４参数化后的测试案例名
 命名规则大概为：
 prefix/test_case_name.test.name/index
 
 type-parameterized tests　类型参数化
 gtest提供了应付各种不同类型的数据时的方案，以及参数化类型的方案。
 首先定义一个继承testing::Test的模版类，：
 template <typename T>
 class FooTest : public testing::Test {
 public:
 
 typedef std::list<T> List;
 static T shared_;
 T value_;
 };

 
 接着定义需要测试到的具体数据类型，比如下面定义了需要测试char,int和unsigned int ：
 typedef testing::Types<char, int, unsigned int> MyTypes;
 TYPED_TEST_CASE(FooTest, MyTypes);
 
 使用TYPED_TEST宏写测试案例，在声明模版的数据类型时，使用TypeParam

 TYPED_TEST(FooTest, DoesBlah) {
 // Inside a test, refer to the special name TypeParam to get the type
 // parameter.  Since we are inside a derived class template, C++ requires
 // us to visit the members of FooTest via 'this'.
 TypeParam n = this->value_;
 
 // To visit static members of the fixture, add the 'TestFixture::'
 // prefix.
 n += TestFixture::shared_;
 
 // To refer to typedefs in the fixture, add the 'typename TestFixture::'
 // prefix.  The 'typename' is required to satisfy the compiler.
 typename TestFixture::List values;
 values.push_back(n);
 
 }
 
 上面的例子看上去也像是类型的参数化，但是还不够灵活，因为需要事先知道类型的列表。gtest还提供一种更加灵活的类型参数化的方式，允许你在完成测试的逻辑代码之后再去考虑需要参数化的类型列表，并且还可以重复的使用这个类型列表。例子：

 template <typename T>
 class FooTest : public testing::Test {
 
 };
 
 TYPED_TEST_CASE_P(FooTest);
 
 
使用宏TYPED_TEST_P写测试案例：
 TYPED_TEST_P(FooTest, DoesBlah) {
 // Inside a test, refer to TypeParam to get the type parameter.
 TypeParam n = 0;
 
 }
 
 TYPED_TEST_P(FooTest, HasPropertyA) {  }

 使用REGISTER_TYPED_TEST_CASE_P宏注册，第一个参数是testcase的名称，后面的参数是test的名称
 REGISTER_TYPED_TEST_CASE_P(FooTest, DoesBlah, HasPropertyA);
 
 接着指定需要的类型列表：
 
 typedef testing::Types<char, int, unsigned int> MyTypes;
 INSTANTIATE_TYPED_TEST_CASE_P(My, FooTest, MyTypes);

 */

/*
 gtest提供的运行参数（环境变量、命令行参数或代码里指定）
 三种设置的途径：
 1. 系统环境变量
 2. 命令行参数
 3. 代码中指定FLAG
 三种途径最中后设置的那个会生效。通常情况下，比较理想的优先级为：命令行参数 > 代码中指定FLAG > 系统环境变量
 如果需要在代码中指定FLAG，可以使用testing::GTEST_FLAG这个宏来设置。比如相对于命令行参数--gtest_output，可以使用testing::GTEST_FLAG(output) = "xml:";来设置。注意到了，不需要加--gtest前缀了。同时，推荐将这句放置InitGoogleTest之前，这样就可以使得对于同样的参数，命令行参数优先级高于代码中指定。
 
 如果需要gtest的设置系统环境变量，必须注意的是：
 1. 系统环境变量全大写，比如对于--gtest_output，响应的系统环境变量为：GTEST_OUTPUT
 2. 有一个命令行参数例外，那就是--gtest_list_tests，它是不接受系统环境变量的
 
 参数列表
 了解了上面的内容，我这里就直接将所有命令行参数总结和罗列一下。如果想要获得详细的命令行说明，直接运行你的案例，输入命令行参数：/? 或 --help 或 -help
 
 1. 测试案例集合
 命令行参数	说明
 --gtest_list_tests	使用这个参数时，将不会执行里面的测试案例，而是输出一个案例的列表。
 --gtest_filter
 对执行的测试案例进行过滤，支持通配符
 
 ?    单个字符
 
 *    任意字符
 
 -    排除，如，-a 表示除了a
 :    取或，如，a:b 表示a或b
 比如下面的例子：
 
 ./foo_test 没有指定过滤条件，运行所有案例
 ./foo_test --gtest_filter=* 使用通配符*，表示运行所有案例
 ./foo_test --gtest_filter=FooTest.* 运行所有“测试案例名称(testcase_name)”为FooTest的案例
 ./foo_test --gtest_filter=*Null*:*Constructor* 运行所有“测试案例名称(testcase_name)”或“测试名称(test_name)”包含Null或Constructor的案例。
 ./foo_test --gtest_filter=-*DeathTest.* 运行所有非死亡测试案例。
 ./foo_test --gtest_filter=FooTest.*-FooTest.Bar 运行所有“测试案例名称(testcase_name)”为FooTest的案例，但是除了FooTest.Bar这个案例
 --gtest_also_run_disabled_tests
 执行案例时，同时也执行被置为无效的测试案例。关于设置测试案例无效的方法为：
 
 在测试案例名称或测试名称中添加DISABLED前缀，比如：
 
 复制代码
 // Tests that Foo does Abc.
 TEST(FooTest, DISABLED_DoesAbc) {  }
 
 class DISABLED_BarTest : public testing::Test {  };
 
 // Tests that Bar does Xyz.
 TEST_F(DISABLED_BarTest, DoesXyz) {  }
 复制代码
 --gtest_repeat=[COUNT]
 设置案例重复运行次数，非常棒的功能！比如：
 
 --gtest_repeat=1000      重复执行1000次，即使中途出现错误。
 --gtest_repeat=-1          无限次数执行。。。。
 --gtest_repeat=1000 --gtest_break_on_failure     重复执行1000次，并且在第一个错误发生时立即停止。这个功能对调试非常有用。
 --gtest_repeat=1000 --gtest_filter=FooBar     重复执行1000次测试案例名称为FooBar的案例。
 
 
 2. 测试案例输出
 
 命令行参数	说明
 --gtest_color=(yes|no|auto)	输出命令行时是否使用一些五颜六色的颜色。默认是auto。
 --gtest_print_time	输出命令行时是否打印每个测试案例的执行时间。默认是不打印的。
 --gtest_output=xml[:DIRECTORY_PATH\|:FILE_PATH]
 将测试结果输出到一个xml中。
 
 1.--gtest_output=xml:    不指定输出路径时，默认为案例当前路径。
 2.--gtest_output=xml:d:\ 指定输出到某个目录
 3.--gtest_output=xml:d:\foo.xml 指定输出到d:\foo.xml
 如果不是指定了特定的文件路径，gtest每次输出的报告不会覆盖，而会以数字后缀的方式创建。xml的输出内容后面介绍吧。
 
 
 3. 对案例的异常处理
 
 命令行参数	说明
 --gtest_break_on_failure	调试模式下，当案例失败时停止，方便调试
 --gtest_throw_on_failure	当案例失败时以C++异常的方式抛出
 --gtest_catch_exceptions
 是否捕捉异常。gtest默认是不捕捉异常的，因此假如你的测试案例抛了一个异常，很可能会弹出一个对话框，这非常的不友好，同时也阻碍了测试案例的运行。如果想不弹这个框，可以通过设置这个参数来实现。如将--gtest_catch_exceptions设置为一个非零的数。
 
 注意：这个参数只在Windows下有效。
 
 
 四、XML报告输出格式
 复制代码
 <?xml version="1.0" encoding="UTF-8"?>
 <testsuites tests="3" failures="1" errors="0" time="35" name="AllTests">
 <testsuite name="MathTest" tests="2" failures="1"* errors="0" time="15">
 <testcase name="Addition" status="run" time="7" classname="">
 <failure message="Value of: add(1, 1)  Actual: 3 Expected: 2" type=""/>
 <failure message="Value of: add(1, -1)  Actual: 1 Expected: 0" type=""/>
 </testcase>
 <testcase name="Subtraction" status="run" time="5" classname="">
 </testcase>
 </testsuite>
 <testsuite name="LogicTest" tests="1" failures="0" errors="0" time="5">
 <testcase name="NonContradiction" status="run" time="5" classname="">
 </testcase>
 </testsuite>
 </testsuites>
 */
/*
 在C++中，为了支持RTTI提供了两个操作符：dynamic_cast和typeid。
 dynamic_cast允许运行时刻进行类型转换，从而使程序能够在一个类层次结构中安全地转化类型，与之相对应的还有一个非安全的转换操作符static_cast，
 
 typeid是C++的关键字之一，等同于sizeof这类的操作符。typeid操作符的返回结果是名为type_info的标准库类型的对象的引用（在头文件typeinfo中定义），它的表达式有两种形式。
 typeid(type) 类型ID
 typeid(expr)　运行时刻类型ID
 如果表达式的类型是类类型且至少包含有一个虚函数，则typeid操作符返回表达式的动态类型，需要在运行时计算；否则，typeid操作符返回表达式的静态类型，在编译时就可以计算。
 ISO C++标准并没有确切定义type_info，确切定义与编译器的实现相关，标准规定必需提供如下四种操作：
 t1 == t2	 如果两个对象t1和t2类型相同，则返回true；否则返回false
 t1 != t2	 如果两个对象t1和t2类型不同，则返回true；否则返回false
 t.name()	 返回类型的C-style字符串，类型名字用系统相关的方法产生
 t1.before(t2)	 返回指出t1是否出现在t2之前的bool值
 
ASSERT_EQ(typeid(*sellQueue), typeid(SellQuoteMultiMap));
 
 type_info类提供了public虚 析构函数，以使用户能够用其作为基类。它的默认构造函数和拷贝构造函数及赋值操作符都定义为private，不能定义或复制type_info类型的对象。程序中创建type_info对象的唯一方法是使用typeid操作符。type_info的name成员函数返回C-style的字符串，表示相应的类型名，这个返回的类型名与程序中使用的相应类型名并不一定一致，这具体由编译器的实现所决定的，标准只要求实现为每个类型返回唯一的字符串。
 
 当typeid操作符的操作数是不带有虚函数的类类型时，typeid操作符会指出操作数的类型，而不是底层对象的类型。
 如果typeid操作符的操作数是至少包含一个虚拟函数的类类型时，并且该表达式是一个基类的引用，则typeid操作符指出底层对象的派生类类型。而指向基类的指针不是类类型，返回基类的类型。
 
 对于多态类实例，想得到实际的类名称，需要使用到RTTI，这需要在编译的时候加上参数"/GR"
 */


#include <iostream>

#endif /* defined(__mycoin__test__) */
