#include<assert.h>
#include<type_traits>
struct  AFunctionObj
{
    /* data */
    double operator() (char, int);
    float operator() (int);
};

template<typename T> struct declval_protector
{static constexpr bool value = false;};
template<typename T> T&& declval(){
    static_assert(declval_protector<T>::value," declval应该只在decltype/sizeof等非求值上下文中使用!");//防呆措施
}

template<typename T>
T&& declval();

int main()
{
    //declval<AFunctionObj>();//没有在decltype/sizeof等操作符中使用
    //编译错误：
    /*
        in function `main':
        /home/wwj/cpp-study/build/<artificial>:15: undefined reference to `AFunctionObj&& declval<AFunctionObj>()'
        collect2: error: ld returned 1 exit status
    */

   //但是编译错误不明确，可以添加更友好的错误信息。
   declval<AFunctionObj>();

}
