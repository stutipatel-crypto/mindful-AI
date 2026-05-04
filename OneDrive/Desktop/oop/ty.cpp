#include <iostream>
using namespace std;

int main() {
    int a = 10;
    float b;

    b = a;   // implicit typecasting (int → float)

    cout << "Value of a (int): " << a << endl;
    cout << "Value of b (float): " << b << endl;

    return 0;
}
