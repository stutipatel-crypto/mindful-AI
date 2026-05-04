#include <iostream>
using namespace std;
class Calculator
{
public:
    // Method 1: Add two integers
    int add(int a, int b)
    {
        return a + b;
    }

    // Method 2: Add three integers
    int add(int a, int b, int c)
    {
        return a + b + c;
    }
};
int main()
{
    Calculator obj;

    // Calling method with 2 arguments
    cout << "Sum of 2 numbers: " << obj.add(10, 20) << endl;

    // Calling method with 3 arguments
    cout << "Sum of 3 numbers: " << obj.add(10, 20, 30) << endl;
    return 0;
}