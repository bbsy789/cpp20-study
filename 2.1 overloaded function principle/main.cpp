#include <fast_io.h>
#include <source_location>
//函数重载机制
/*
    函数重载机制涉及三个阶段：
    名称查找，模板函数处理，重载决议
    前两个阶段得到函数的候选集，最后一个阶段从候选集中选出最合适的版本
*/


//考虑如下代码，采用哪个重载版本的feed?
namespace animal{
    struct Cat{};
    void feed(Cat* foo, int value){
        println(std::source_location::current());
    }
};

struct CatLike{CatLike(animal::Cat* );};
void feed(CatLike c){
    println(std::source_location::current());
}

template<typename T>
void feed(T* obj, double value){
    println(std::source_location::current());
}

template<>
void feed(animal::Cat* obj, double d)
{
    println(std::source_location::current());
} // 全特化版本

int main()
{
    animal::Cat cat;
    feed(&cat, 1);
}
