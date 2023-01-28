//C++17折叠表达式
//语法syntax:
//1.右折叠：(pack op ...[op init])
//2.左折叠：([init op]...op pack)
//pack是参数包
//op是运算符
//[op init / init op]是可选初值
using std::size_t;
template<size_t ...Is> // 右折叠
constexpr int rsum = (Is + ... + 0);
//(1+ (2 + (3 + (4 + (5 + 0)))))
static_assert(rsum<1,2,3,4,5> == 15);

template<size_t ...Is> // 左折叠
constexpr int lsum = (0 + ... + Is);
//(((((0 + 1) + 2) + 3) + 4)+ 5)
static_assert(lsum<1,2,3,4,5> == 15);

//因为加法具有结合律，因此左折叠与右折叠等效
//但是如减法这样不具有结合律的运算
template<size_t ...Is>
constexpr int rsub = (Is - ... - 0);
//(1 - (2 - (3 - (4 - (5 - 0)))))
//1-2+3-4+5=1+1+1=3
static_assert(rsub<1,2,3,4,5> == 3);
template<size_t ...Is>
constexpr int lsub = (0 - ... - Is);
//(((((0 - 1) - 2) - 3) - 4) - 5)
//-1-2-3-4-5=-15
static_assert(lsub<1,2,3,4,5> == -15);

int main()
{
    return 0;
}

