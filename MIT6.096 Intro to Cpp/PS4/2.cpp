#include <iostream>
template <typename T>
T min(const T& x, const T& y){
    return x<=y?x:y;
}

int main(){
    std::cout<<min('a','b')<<std::endl;
    std::cout<<min(21,31)<<std::endl;
    return 0;
}