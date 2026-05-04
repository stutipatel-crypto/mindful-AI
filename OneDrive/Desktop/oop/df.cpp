#include <iostream>
#include <cmath>
using namespace std;
class Point
{
private:
    int x, y;
public:
    // Constructor
    Point(int a, int b)
    {
        x = a;
        y = b;
    }
    // Method to calculate distance
    double distance(Point p)
    {
        return sqrt((p.x - x) * (p.x - x) +
                    (p.y - y) * (p.y - y));
    }
};
int main()
{
    Point p1(2, 3);
    Point p2(6, 7);
    // Object-to-object interaction
    double d = p1.distance(p2);
    cout << "Distance between points: " << d << endl;
    return 0;
}