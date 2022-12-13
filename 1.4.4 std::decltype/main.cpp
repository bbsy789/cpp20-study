#include<assert.h>
#include<type_traits>

/*
    考虑一个典型场景，如何获取给定任意一个函数与其参数进行调用得到的返回类型？
    给定函数类型F和其
    template<typename F, typename...Args>
    using InvokeResultOfFunc = 如何实现？

*/

/*
    首先分析一下InvokeResultOfFunc的原型，这里使用C++11提供的using类型别名特性来代替以往的typedef从而提高可读性。
    using别名不仅能替代所有的typedef场景，而且更加强大，能够给模板类提供别名。
    作为模板类的别名使用时，并不会实例化别名本身，而是实例化原模板类。
    而这也是typedef做不到的地方。如果说变量储存的是值，那么别名存储的就是类型。
*/

/*
    接下来考虑模板参数F。最简单地场景是一个普通函数类型，那么当入参类型匹配时，其返回类型也就确定了。
    而一般场景考虑函数对象是，可能是一个lambda或用户自定义的函数对象。
    当入参类型不同时，其重载决议的operator()操作符也不一样，因此得到的返回类型也是不一样的。
*/
namespace test{
struct AFunctionObj{
    double operator() (char, int); //#1
    float operator() (int); //#2
}f;

/*
    在这个场景中，若使用f('a',O)将决议第一个版本，函数返回一个double类型的值，进一步需要使用decltype从值得到其类型，
    因此decltype(f('a',O))得到函数对象调用后的返回值的类型double，同理通过
*/

/*
    因此我们可以初步实现如下：
*/
// template<typename F, typename...Args>
// using InvokeResultOfFunc = decltype(F{}(Args...));
/*
    因为无法直接对类型进行调用，因此需要对F进行实例化得到函数对象F
    ，从而能够进行函数调用动作，
    同理函数调用的入参也必须是对象（值）而不是类型，
    同时需要将每个入参类型进行实例化Arg{}...,
    这样得到的是一个合法的函数调用语句，最终通过decltype操作符获得返回值的类型。
    需要注意的是实例化并不是真正在内存上构造出对象，它在编译期非求值上下文种，仅仅是用于构造合法的语句。
    似乎一切正常，然而当类模板参数不可构造时，其没有默认构造函数，或者构造函数时私有的，
    那么上述实现将不可用，因为语句F{}/Args{}...无效。
    这时候标准库的std::declval模板函数就派上用场了，它能不受以上条件的约束而构造出对象，
    只要在非求值上下文中将F{}对象写成std::declval<F>()即可，将待构造的类型显式传递给declval模板函数，
    最终的实现如下：
*/
template<typename F, typename...Args>
using InvokeResultOfFunc = 
    decltype(std::declval<F>()(std::declval<Args>()...));

using T1 = InvokeResultOfFunc<AFunctionObj, char, int>; // double
using T2 = InvokeResultOfFunc<AFunctionObj, int>; // float
}
int main()
{
    using namespace test;
    static_assert(std::is_same_v<T1,double>,"T1 == double"); // true
    static_assert(std::is_same_v<T2,float>, "T2 == float"); //true
    //static_assert(std::is_same_v<T1,float>,"T1 != float"); //false
    //static_assert(std::is_same_v<T2,double>,"T2 != double"); //false
    return 0; 
}

