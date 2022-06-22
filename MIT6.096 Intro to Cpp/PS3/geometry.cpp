#include <cmath>
#include <iostream>
#include "geometry.h"
// Point
Point::Point(int x, int y):x(x),y(y){}

int Point::getX() const {return x;}

int Point::getY() const {return y;}

void Point::setX(const int new_x){x = new_x;}

void Point::setY(const int new_y){y = new_y;}

// PointArray
PointArray::PointArray():size(0){
    array = new Point[0];
}

PointArray::PointArray(const Point points[], const int size):size(size){
    array = new Point[size];
    for (int i=0;i<size;i++){
        array[i] = points[i];
    }
}

PointArray::PointArray(const PointArray& pv){
    size = pv.size;
    array = new Point[size];
    for (int i = 0; i<size; i++){
        array[i] = pv.array[i];
    }
}

PointArray::~PointArray(){
    delete[] array;
}

void PointArray::resize(int n){
    if (n==size){
        return;
    }
    Point* newArray = new Point[n];
    for (int i = 0; i<n && i < size; i++){
        newArray[i] = array[i];
    }
    delete []array;
    array = newArray;
    size = n;
}

void PointArray::push_back(const Point &p){
    resize(size+1);
    array[size-1] = p;
}

void PointArray::insert(const int position, const Point &p){
    resize(size+1);
    for (int i = size - 1; i > position; i--){
        array[i] = array[i-1];
    }
    array[position] = p;
}

void PointArray::remove(const int pos){
    for (int i = pos; i < size - 1; i++){
        array[i] = array[i+1];
    }
    resize(size - 1);
}

const int PointArray::getSize() const{
    return size;
}

void PointArray::clear(){
    resize(0);
}

Point *PointArray::get(const int position){
    return position >=0 && position < size ? array + position : nullptr;
}

const Point *PointArray::get(const int position) const{
    return position >=0 && position < size ? array + position : nullptr;
}

// Polygon
int Polygon::count = 0;

Polygon::Polygon(Point points[], int size): array(points, size){
    count++;
}

Polygon::Polygon(const PointArray& arr): array(arr){
    count++;
}

Polygon::~Polygon(){
    count--;
}

int Polygon::getNumPolygons() {
    return count;
}

int Polygon::getNumSides() const {
    return array.getSize();
}
const PointArray* Polygon::getPoints() const{
    return &array;
}

// Rectangle
Point constructorPoints [4];

Point * updateConstructorPoints ( const Point &p1 , const Point &p2 , const Point &p3 , const Point &p4 = Point (0 ,0)) {
    constructorPoints [0] = p1;
    constructorPoints [1] = p2;
    constructorPoints [2] = p3;
    constructorPoints [3] = p4;
    return constructorPoints ;
}

Rectangle::Rectangle(const Point& ll, const Point& ur):
    Polygon(updateConstructorPoints(ll, Point(ll.getX(), ur.getY()), ur,  Point(ur.getX(), ll.getY())),4){}

Rectangle::Rectangle(const int llx, const int lly, const int urx, const int ury):
    Polygon(updateConstructorPoints(Point(llx,lly), Point(llx, ury), Point(urx, ury),  Point(urx, lly)),4){}

double Rectangle::area() const{
    int area = ((array.get(0)->getX() - array.get(2)->getX())*(array.get(0)->getY() - array.get(2)->getY()));
    return area >= 0 ? area : -area;
}

// Triangle
Triangle::Triangle(const Point& p1, const Point& p2, const Point& p3):
    Polygon(updateConstructorPoints(p1, p2, p3),3){};

double Triangle::area() const{
    int x1 = array.get(0)->getX(); int y1 = array.get(0)->getY();
    int x2 = array.get(1)->getX(); int y2 = array.get(1)->getY();
    int x3 = array.get(2)->getX(); int y3 = array.get(2)->getY();
    double a = sqrt(1.0*(x1-x2)*(x1-x2)+(y1-y2)*(y1-y2));
    double b = sqrt(1.0*(x2-x3)*(x2-x3)+(y2-y3)*(y2-y3));
    double c = sqrt(1.0*(x1-x3)*(x1-x3)+(y1-y3)*(y1-y3));
    double s = 0.5*(a+b+c);
    return sqrt(s*(s-a)*(s-b)*(s-c));
};


void printAttributes(Polygon * p){
    std::cout<<"Area = "<< p->area() <<". The coordinates are: ";
    const PointArray* array = p->getPoints();
    for (int i = 0; i < array->getSize(); i++){
        std::cout<<"("<<array->get(i)->getX()<<", "<<array->get(i)->getY()<<") ";
    }
    std::cout<<std::endl;
}
