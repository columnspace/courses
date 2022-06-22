class Point{
    int x, y;
public:
    Point(int x = 0, int y = 0);
    int getX() const;
    int getY() const;
    void setX(const int new_x);
    void setY(const int new_y);
};

class PointArray{
    Point* array;
    int size;
    void resize(int n);
public:
    PointArray();
    PointArray(const Point points[], const int size);
    PointArray(const PointArray& pv);
    ~PointArray();
    void push_back(const Point &p);
    void insert(const int position, const Point &p);
    void remove(const int pos);
    const int getSize() const;
    void clear();
    Point *get(const int position);
    const Point *get(const int position) const;
};

class Polygon{
protected:
    PointArray array;
    static int count;
public:
    Polygon(Point points[], int size);
    Polygon(const PointArray& arr);
    ~Polygon();
    virtual double area() const = 0;
    static int getNumPolygons();
    int getNumSides() const;
    const PointArray* getPoints() const;
};

class Rectangle:public Polygon{
public:
    Rectangle(const Point&, const Point&);
    Rectangle(const int, const int, const int, const int);
    double area() const;
};

class Triangle:public Polygon{
public:
    Triangle(const Point&, const Point&, const Point&);
    double area() const;
};


void printAttributes(Polygon *);