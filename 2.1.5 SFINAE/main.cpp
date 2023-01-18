#include <fast_io.h>
#include <type_traits>
//declval函数
//用于在非求值上下文中构造对象，从而能够获取类对象的一些特征。

struct Point{};
struct Line : Point{int number;};

template<typename T, typename U = T&&> 
U declval_(int);

template<typename T>
T declval_(long);

template<typename T> struct declval_protector
{static constexpr bool value = false;};

template<typename T>
auto declval() -> decltype(declval_<T>(0)){
    static_assert(declval_protector<T>::value," declval应该只在decltype/sizeof等非求值上下文中使用!");
    return declval_<T>(0); // 避免编译器警告
}

using Void_t = decltype(declval<void>);
   
using Point_ref_t = decltype(declval<Point>);

Void_t foo(Void_t);
Point_ref_t foo2(Point_ref_t);

int main()
{    
   

    
    return 0;
}

