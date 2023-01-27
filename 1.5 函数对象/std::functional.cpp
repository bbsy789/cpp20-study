#include <functional>
#include <fast_io.h>
enum class Op {ADD, MUL};
std::function<int(int,int)> OperationFactory(Op op){
    switch(op){
        case Op::ADD: return [](int a,int b){return a + b;};
        case Op::MUL: return std::multiplies<int>{};
    }
}

int main()
{
    println("2+3=",OperationFactory(Op::ADD)(2,3)."\n");
    println("2*3=",OperationFactory(Op::MUL)(2,3),"\n");
    return 0;
}