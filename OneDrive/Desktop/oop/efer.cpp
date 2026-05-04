#include <iostream>
using namespace std;
class Point
{
    int x, y;
public:
    Point(int a, int b)
    {
        x = a;
        y = b;
    }
    // Copy constructor
    Point(const Point &p)
    {
        x = p.x;
        y = p.y;
        cout << "Copy Constructor Invoked" << endl;
    }
    void display()
    {
        cout << "X = " << x << " Y = " << y << endl;
    }
};
void show(Point p) // object passed by value
{
    p.display();
}
int main()
{
    Point p1(4, 9);
    show(p1);  // copy constructor called
    return 0;
}