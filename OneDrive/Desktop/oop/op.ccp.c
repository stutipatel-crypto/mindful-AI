#include <iostream>
using namespace std;

int main() {
    float a = 10.75;
    int b;

    b = (int)a;   // explicit typecasting (float → int)

    cout << "Value of a (int): " << a << endl;
    cout << "Value of b (int): " << b << endl;

    return 0;
}
