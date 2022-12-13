#include <fast_io.h>
//定义一个简单的函数对象，它是一个结构体，重载了()运算符。

struct plus{
    int operator() (int x, int y)
    {
        return x + y;
    }
};

//然后将这个函数对象实例化
int main()
{
    print("2+3=",plus{}(2,3));
    return 0;
}



