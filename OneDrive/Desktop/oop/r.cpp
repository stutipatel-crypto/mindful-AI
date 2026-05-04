#include <iostream>
using namespace std;

void swapValues(int &a, int &b)
{
    int temp;
    temp = a;
    a = b;
    b = temp;
}

int main()
{
    int a, b;

    cout << "Enter first number: ";
    cin >> a;
    cout << "Enter second number: ";
    cin >> b;

    cout << "\nBefore swapping:" << endl;
    cout << "a = " << a << ", b = " << b << endl;

    swapValues(a, b);

    cout << "\nAfter swapping:" << endl;
    cout << "a = " << a << ", b = " << b << endl;
    return 0;
}
