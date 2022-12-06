#include <fast_io.h>

//函数重载机制
/*
    函数重载机制涉及三个阶段：
    名称查找，模板函数处理，重载决议
    前两个阶段得到函数的候选集，最后一个阶段从候选集中选出最合适的版本
*/


//考虑如下代码，采用哪个重载版本的feed?
namespace animal{
    struct Cat{};
    void feed(Cat* foo, int );
};

struct CatLike{CatLike(animal::Cat*);};
void feed(CatLike);

template<typename T>
void feed(T* obj, double);

template<>
void feed(animal::Cat* obj, double d); // 全特化版本

int main()
{
    animal::Cat cat;
    feed(&cat, 1);
}
