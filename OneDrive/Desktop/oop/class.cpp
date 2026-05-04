#include <iostream>
using namespace std;

int main() {
    int number = 10;     // normal variable
    int &ref = number;  // reference variable

    cout << "Original number: " << number << endl;
    cout << "Reference value: " << ref << endl;

    ref = 25;  // changing value using reference

    cout << "After modifying through reference:" << endl;
    cout << "Number: " << number << endl;
    cout << "Reference: " << ref << endl;

    return 0;
}
