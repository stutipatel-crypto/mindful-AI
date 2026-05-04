#include <iostream>
using namespace std;

// Define the MathOps namespace
namespace MathOps {
    int square(int x) {
        return x * x;
    }
}
// Define the BitOps namespace
namespace BitOps {
    bool isEven(int x) {
        return (x & 1) == 0;
    }
}
int main() {
    int number;
    // Taking input from the user
    cout << "Enter an integer: ";
    cin >> number;
    // Calling square function from MathOps namespace
    int squared = MathOps::square(number);
    cout << "Square of " << number << " is " << squared << endl;
    // Calling isEven function from BitOps namespace
    bool even = BitOps::isEven(number);
    cout << number << " is " << (even ? "even" : "odd") << endl;
    return 0;
}
