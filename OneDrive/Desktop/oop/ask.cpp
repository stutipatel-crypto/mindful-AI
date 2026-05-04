#include <iostream>
using namespace std;

// square
int area(int s)
{
    return s * s;
}

// rectangle
int area(int l, int b)
{
    return l * b;
}

// circle
double area(double r)
{
    return 3.14 * r * r;
}

int main()
{
    cout << "Square area = " << area(4) << endl;
    cout << "Rectangle area = " << area(5, 3) << endl;
    cout << "Circle area = " << area(2.5) << endl;
}