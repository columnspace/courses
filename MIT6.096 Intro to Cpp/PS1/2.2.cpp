#include <iostream>
void helloNTimes(int n){
    for (int i = 0; i<n; i++){
        std::cout<<"Hello, World!"<<std::endl;
    }
}

int main(){
    int n;
    std::cout<<"Enter n:";
    std::cin>>n;
    helloNTimes(n);
    return 0;
}