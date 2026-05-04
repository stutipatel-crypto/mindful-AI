#include <iostream>
using namespace std;
class rectangle
{
public:
    int length,breath;

void setdata(int l, int b)
    {
        length = l;
       breath = b;
    }
    int area()
    {
        return length*breath;
    }
    int parameter()
    {
        return 2*(length+breath);
    }
};
int main()
{
    rectangle p1;
    p1.setdata(4, 9);
    cout << "area: " << p1.area() << endl;
    cout << "parameter: " << p1.parameter() << endl;
    return 0;
}