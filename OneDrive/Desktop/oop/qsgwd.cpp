#include <iostream>
using namespace std;

void display(int x)
{
    cout << "display(int): " << x << endl;
}

void display(double x)
{
    cout << "display(double): " << x << endl;
}

int main()
{
    display(10);    // integer literal
    display(10.5);  // double literal
    display('A');   // character literal

    return 0;
}