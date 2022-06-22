#include <iostream>
#include "geometry.h"
int main(){
    std::cout<<"Please enter lower-left and upper-right position of a rectangle:";
    int llx, lly, urx, ury;
    std::cin>>llx>>lly>>urx>>ury;
    Rectangle rect(llx, lly, urx, ury);
    std::cout<<"Please enter positions for three vertices of a triangle:";
    int x1, y1, x2, y2, x3, y3;
    std::cin>>x1>>y1>>x2>>y2>>x3>>y3;
    Triangle tria(Point(x1,y1), Point(x2,y2), Point(x3,y3));
    printAttributes(&rect);
    printAttributes(&tria);
    return 0;
}