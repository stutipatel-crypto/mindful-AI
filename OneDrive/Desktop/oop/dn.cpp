#include <iostream>
using namespace std;
int main()
{
    int n, count = 0;
    // Take input
    cout << "Enter an integer: ";
    cin >> n;
    int temp = n;   // store original value for checking odd/even
    // Count set bits using while loop and bitwise operators
    while (temp > 0)
    {
        // Check last bit
        if (temp & 1)
        {
            count++;
        }
        // Right shift the number
        temp = temp >> 1;
    }
    // Display number of set bits
    cout << "Number of set bits: " << count << endl;
    // Check odd or even using bitwise operator
    if (n & 1)
        cout << n << " is Odd" << endl;
    else
        cout << n << " is Even" << endl;
    return 0;
}
