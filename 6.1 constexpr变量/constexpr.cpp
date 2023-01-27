//C++常量表达式

//代替宏与C语言定义的常量表达式

//Purpose
//1.让编译时计算达到类型安全
//2.一般来说，将计算移到编译时提高运行时效率
//3.支持嵌入式系统编程（尤其是ROM）
//4.直接支持元编程而非模板元编程
//5.让编译时编程与“普通编程”类似

//Implement
//1.constexpr函数可以在编译期求值，这使它无法访问本地对象，也不能对调用者的环境产生副作用。
//2.如果没有标注constexpr函数，那么编译器就需要将所有的函数体全部保留在二进制中，以便常量表达式在求值时要调用它们。
//3.早期的实现主要集中在嵌入式系统和关注性能的简单实例中。2015年起，constexpr函数才称为元编程的主要支柱。
//C++14允许在constexpr函数中使用局部变量，从而支持了循环；在此之前constexpr必须是纯函数式的。
//C++20允许将字面类型用作值模板参数类型。

//Now
//1.constexpr函数已经非常流行，它们遍布于C++14,C++17,C++20标准库
//2.相关建议也在不断产生
#include <numbers>
#include <numeric>
#include <iostream>

namespace wwj{
//2.constexpr与const的区别主要有：
//constexpr需要保证表达式在编译时可以被求值，否则会出现编译错误
//const只是表达式具有常量属性，若能在编译时求值，也可用于编译时计算上下文。

constexpr double Area(const double& R)
{
    return (R*R*std::numbers::pi_v<double>);
}
template<double R>
constexpr double Area()
{
    return (R * R * std::numbers::pi_v<double>);
}
//3.constexpr常量还可以与变量模板组合使用，例如标准库<type_traits>中定义大量常量模板以简化traits的使用
    // template<typename T>// 这是一个变量模板
    // inline constexpr bool is_intgeral_v = std::is_integral<T>::value;
    // static_assert(is_integral_v<int>);
    // static_assert(!is_integral_v<void>);
    //4.也可以定义简单的表达式计算逻辑，例如判断给定的字符是否是一个数字
    template<char c>
    constexpr bool is_digit = (c >= '0' && c <= '9');
    static_assert(! is_digit<'x'>);
    static_assert(is_digit<'6'>);
//5.模板可以特化，因此可以实现一些包含循环的逻辑
    //例如2.2.1中的斐波那契数列
    template<std::size_t N>
    constexpr std::size_t fibonacci = fibonacci<N-1> + fibonacci<N-2>;
    template<>
    constexpr std::size_t fibonacci<0> = 0;
    template<>
    constexpr std::size_t fibonacci<1> = 1;
    static_assert(fibonacci<10> == 55);
}


int main()
{
    using namespace wwj;
    //1.使用constexpr定义的常量通常可以代替使用宏定义的常量，并且能够保证类型安全
    constexpr double PI = std::numbers::pi_v<double>;
    constexpr double R_ = 2.0;
    std::cout << Area<R_>() << "\n" << Area(R_) << std::endl; // 2 * 2 * 3.14 = 12.56
    return 0;
}
