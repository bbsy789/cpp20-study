#include <type_traits>
#include <concepts>

template<typename...Ts>
struct TypeList{
    // 判断是不是一个TypeList
    struct IsTypeList{};
    // 保存列表的长度
    constexpr static std::size_t size = sizeof...(Ts);
    // TypeList的类型成员type是它自己
    using type = TypeList;
    // 尾部追加元素的元函数append
    template<typename...T>
    using append = TypeList<Ts...,T...>;
    // 头部追加元素的元函数prepend
    template<typename...T>
    using prepend = TypeList<T...,Ts...>;
    // 用于转发给其他需要类型列表的元函数to
    template< template<typename...> typename T>
    using to = T<Ts...>;
};

template<typename T>
concept TL = requires{
    typename T::IsTypeList;
    typename T::type;
}

// Fold接受一个TypeList，一个初始累计元素，一个二元函数。
// 它对列表中的每一个元素进行迭代并调用二元函数

// 假设一个初始累计元素为空，使用less二元函数对TypeList进行一次次迭代，每一次迭代都累计到累计元素上。
// Init = TypeList<> , TypeList<char,int,char,size_t> <= Less<T,int>
// 1. Init = TypeList<char>, TypeList<int,char,size_t> <= Less<T,int>
// 2. Init = TypeList<char,int>, TypeList<char,size_t> <= Less<T,int>
// 3. Init = TypeList<char,int,char>, TypeList<size_t> <= Less<T,int>
// 4. 由于继承了Return，所以 using type = Init = TypeList<char,int,char>。最终得到结果


// 实现时采用倒推的方式，先写最终的结果，然后写迭代。

template<typename T>
struct Return {using type = T;};

// 利用Return返回最终的累计元素
template<TL In, typename Init, template<typename ,typename> class Op>
struct Fold : Return<Init> {};

// 利用偏特化得到当前步的迭代元素
template<typename Acc, typename <typename,typename> class Op, // Acc是累计元素，Op是二元函数
        typename H, typename ...Ts> // H 就是当前步的迭代元素
struct Fold<TypeList<H,Ts...>,Acc,Op> : Fold<TypeList<Ts...>,typename Op<Acc,H>::type,Op>{};//继承上一步的结果，上一步的结果就是这一步的初始状态
//其中TypeList<Ts...>是上一步的第一个模板参数也就是去掉了H迭代元素的剩余列表。
//typename关键字表示这里是一个类型, Op<Acc,H>::type表示对累计元素和当前迭代元素使用Op二元函数进行操作，拿到Op二元函数的类型成员type作为结果。
//因为Fold是对TypeList每一个成员都使用一次Op，所以第三个模板参数还是Op。

// Fold_t的实现较为简单
template<TL In,typename Init,template<typename,typename> class Op>
using Fold_t = typename Fold<In,Init,Op>::type;