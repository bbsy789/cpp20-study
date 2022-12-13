#include <fast_io.h>
//declval函数
//用于在非求值上下文中构造对象，从而能够获取类对象的一些特征。
template<typename T>
T declval();

template<typename T, typename U>
U&& declval();

int main()
{
    println("decltype(declval(void)) = "),decltype(declval<void>,"\n","decltype(declval(Point))");
    return 0;
}