#include <iostream>
using namespace std;
class Distance
{
    int feet, inches;
public:
    Distance(int f, int i)
    {
        feet = f;
        inches = i;
    }
    // Copy constructor
    Distance(const Distance &d)
    {
        feet = d.feet;
        inches = d.inches;
    }

    void display()
    {
        cout << feet << " feet " << inches << " inches" << endl;
    }
};
int main()
{
    Distance d1(5, 10);
    Distance d2 = d1;
    cout << "Distance 1: ";
    d1.display();
    cout << "Distance 2: ";
    d2.display();
    return 0;
}