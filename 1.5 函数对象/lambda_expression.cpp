#include <fast_io.h>
/*
    C++11起提供了lambda表达式，它是C++语言本身的特性。
    它可以简化程序员定义函数对象，而无需定义对应的函数对象类，如下是lambda表达式的语法：

    [捕获]{形参列表} -> 后置返回类型 {函数体}
*/

constexpr auto add = [](auto a, auto b){
    return a + b;
};

int main()
{
    println("1+2=",add(1,2));
    return 0;
}