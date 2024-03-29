#include <cmath>
#include <vector>
#include <fast_io.h>
//C++17新特性 模板类型推导
//Class Template Argument Deduction，缩写为CTAD
/*
    进一步减少冗余代码的重要特性。当我们使用标准库里提供的模板函数时，
    或许不知道它就是个模板函数，但使用起来就和普通函数一样自然。
*/

int foo = std::max(1,2); // #1,省略模板参数的指明,因为两个参数类型一致。
double bar = std::max<double>(1, 2.9); // #2,指明模板参数，因为两个参数类型不一致，编译器不知道该使用哪一个类型。
/*
    然而在我们使用模板类时，都必须指明模板类的模板参数后才能使用。
*/
std::vector<int> foo2{1,2,3,4};
std::pair<int, double> bar2{1, 2.0};
/*
    初始化一个序对类型时，我们明显可以通过构造传递的两个值的类型得到pair<int，double>,
    但是在C++17之前，尽管编译器知道这些类型，仍需显式指明模板类的模板参数。标准库也
    发现了这一点，提供了一些辅助模板来解决这个问题
*/
auto bar3 = std::make_pair(1,2.9);
/*
    make_pair是一个模板函数，可以自动推导出函数的两个参数类型。
    从而构造出最终的序对类型，对程序员来说，每写一个模板类都需要考虑封装一个辅助函数来构造
    这个类型的对象，这是一件重复的，繁琐的事情，还得考虑到转发引用和完美转发的问题。
*/
/*
    C++17起引入的这个CTAD特性就是为了解决模板类需要显式指明模板参数的问题。
    而且这个特性不是很复杂，我们可以像使用普通类一样使用模板类，就像模板函数与普通函数表现的一致性。
    在C++17中，std::pair{1,2.9}与std::pair<int,double>{1,2.9}等价。
    通过改写前面的代码可以看到明显的区别，改写后的代码更精简。
*/
std::vector foo3{1,2,3,4};
std::pair bar4{1,2.9};

template<typename T,typename U>
struct Pair{
    Pair()
    {
        println("Pair construct!");
    }
    Pair(T t,U u)
    {
        println("Pair construct! t = ",t," u = ",u,"\n");
    }
    // ...
};
Pair foo5{1,2};//编译器能自动推导出Pair<int,int>

// template<typename T,typename U>
// struct Pair2{
//     template<typename A, typename B>
//     Pair2(A&&, B&&);
// };

// Pair2 foo5{1,2}; //编译错误

// 这个例子和前面稍微不同，构造函数与模板类的模板参数不一致，编译器会认为T与U、A与B是不同的类型。
// 因此无法通过构造函数得知最终的模板类参数。这时可以通过添加推导规则来解决这个问题
template<typename T ,typename U>
struct Pair3{
    template<typename A,typename B>
    Pair3(A&&, B&&);

};
template<typename T,typename U>
Pair3(T,U) -> Pair3<T,U>;

// 在做模板参数推导时，推导规则拥有很高的优先级，编译器会优先考虑推到规则，之后才考虑通过构造函数来推导。
// 上述规则相当于告诉编译器，当通过诸如Pair(T,U)的方式构造程序时，自行推导出模板类Pair<T,U>。
// 因此Pair{1，2}会得到正确的Pair<int,int>类型。
// 确定模板类后斌不会影响构造函数的决议过程，就和程序员显式指定模板参数一样。
// 在这个例子中会通过转发引用版本的构造函数进一步构造。

/*
    推到规则和函数声明的返回类型后置写法很相似，需要注意的是推导规则前面没有auto，通过这一点来区分两者。
    CTAD特性与推导规则是非侵入式的，为已有的模板类添加推导规则并不会破坏已有的显式指明的代码，
    这也是为何标准库在引入特性后不会破坏用户代码的原因。
    模板函数的模板参数可以在程序员使用时自动对类型进行推导，从而实例化进行调用。而在C++17之前，使用模板类
    需要显式指明模板参数，而在C++17之后提供的CTAD特性可以简化这一点，同时提供自定义推导规则以帮助编译器推导正确的类型。
*/

int main()
{
    return 0;
}