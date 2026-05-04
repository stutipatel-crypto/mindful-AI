#include <iostream>
using namespace std;

// maximum of two integers
int maximum(int a, int b)
{
    if (a > b)
        return a;
    else
        return b;
}

// maximum of two float numbers
float maximum(float a, float b)
{
    if (a > b)
        return a;
    else
        return b;
}
// maximum of three integers
int maximum(int a, int b, int c)
{
    int max = a;
    if (b > max)
        max = b;
    if (c > max)
        max = c;
    return max;
}

int main()
{
    cout << "Max of 10 and 20 = " << maximum(10, 20) << endl;        // calls int, int
    cout << "Max of 5.5 and 2.3 = " << maximum(5.5f, 2.3f) << endl;  // calls float, float
    cout << "Max of 3, 7 and 5 = " << maximum(3, 7, 5) << endl;      // calls int, int, int

    return 0;
}