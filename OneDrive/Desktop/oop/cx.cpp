#include <iostream>
using namespace std;
class Number
{
    int value;
public:
    Number(int v)
    {
        value = v;
    }

    // Copy Constructor
    Number(const Number &obj)
    {
        value = obj.value;
    }

    void display()
    {
        cout << "Value: " << value << endl;
    }
};
int main()
{
    Number n1(10);
    Number n2 = n1;   // Copy constructor called

    cout << "Object 1: ";
    n1.display();

    cout << "Object 2: ";
    n2.display();

    return 0;
}