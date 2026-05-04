#include <iostream>
using namespace std;
class Box
{
    int length, width, height;
public:
    // Default constructor
    Box()
    {
        length = width = height = 1;
    }
    // Parameterized constructor
    Box(int l, int w, int h)
    {
        length = l;
        width = w;
        height = h;
    }

    void display()
    {
        int volume = length * width * height;
        cout << "Volume = " << volume << endl;
    }
};
int main()
{
    Box b1;           // default constructor
    Box b2(2, 3, 4);  // parameterized constructor

    cout << "Default Box: ";
    b1.display();

    cout << "Parameterized Box: ";
    b2.display();

    return 0;
}