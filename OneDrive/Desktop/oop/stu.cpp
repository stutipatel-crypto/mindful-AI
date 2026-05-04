#include <iostream>
using namespace std;

int main() {
    float a = 10.75;
    int b;

    b = a;   // implicit typecasting (float → int)

    cout << "Value of a : " << (int) a  << endl; //explicite conversion or type casting
    cout << "Value of b : " << b << endl;

    return 0;
}
