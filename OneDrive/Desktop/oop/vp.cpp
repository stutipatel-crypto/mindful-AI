#include <iostream>
using namespace std;

int main()
{
    int a, b;
    float result;

    // Taking input
    cout << "Enter two integers: ";
    cin >> a >> b;

    // Typecasting to get decimal result
    result = (float)a / b;

    // Display result
    cout << "Division result = " << result << endl;

    return 0;
}
