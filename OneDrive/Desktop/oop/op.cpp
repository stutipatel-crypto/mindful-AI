#include <iostream>
using namespace std;
int main()
{
    int n;

    // Read input
    cout << "Enter a number: ";
    cin >> n;

    // for loop from 1 to n
    for (int i = 1; i <= n; i++)
    {
        // Stop the loop if number is divisible by 7
        if (i % 7 == 0)
        {
            break;
        }
        // Skip numbers divisible by 3
        if (i % 3 == 0)
        {
            continue;
        }
        // Print the number
        cout << i ;
    }
    return 0;
}
