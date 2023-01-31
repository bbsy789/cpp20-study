#include <fast_io.h>
#include <type_traits>
//C++20 非类型模板参数
//C++20之前
template <size_t N>
constexpr void f(){/*...*/}

enum class Color{/*...*/};
template<Color c>
struct C{
    /*...*/
};

//C++20之后
//模板参数使用auto占位符表达由编译器类型推导的非类型参数,以及用户定义的字面类型
//字面类型要求能够在编译器构造对象，并且所有非类型静态成员都需要是public的字面类型，它们和字符串常量，标量一样不可修改。
template Foo{};
template <auto...> 
struct ValueList{};
ValueList<'C',0,2L,nullptr,Foo{}> x; // OK
//注意非类型模板参数对于字符串的支持。
//字符串常量与其他类型不同，它们具有地址。C++语言中定义为左值。
//对于同一个字符串常量，它们的地址甚至可以不同。进行比较也不会相同。
//因此不可以简单地使用const char *来作为模板参数。
static const char hello[] = "hello";
static_assert(std::is_same_v<hello>,C<hello>>);//OK
int main()
{

    return 0;
}