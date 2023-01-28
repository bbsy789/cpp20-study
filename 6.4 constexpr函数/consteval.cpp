#include <numeric>
#undef min
//使用constexpr修饰仅表达一个函数是否可能被编译时求值，而使用consteval修饰则必须能编译时求值
consteval int min(std::initializer_list<int> xs)
{
    int low = std::numeric_limits<int>::max();
    for(int x: xs)
    {
        if(x < low)
        {
            low = x;
        }
    }
    return low;
}

static_assert(min({1,3,2,4}) == 1);

int main()
{
    return 0;
}