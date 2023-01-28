//编译时堆排序
#include <fast_io.h>
#include <array>
#include <vector>
#include <random>

using std::vector;
using std::array;

consteval vector<int> foo()
{
    vector<int> testVector{4,3,5,2,1};
    std::sort(testVector.begin(),testVector.end());
    return testVector;
}

consteval size_t fooCount()
{
    return foo().size();
}

consteval auto saveVectorToArray()
{
    array<int,fooCount()> result;
    auto _foo = foo();
    std::copy(_foo.begin(),_foo.end(),result.data());
    return result;
}

constexpr auto foo_result = saveVectorToArray();

int main()
{
    for(auto e: foo_result)
    {
        println(e,"\n");
    }
    return 0;
}