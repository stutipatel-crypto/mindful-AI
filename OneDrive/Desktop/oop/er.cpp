#include <iostream>
using namespace std;

class Fraction {
private:
    int num, den;

public:
    // input fraction
    void input() {
        cout << "Enter numerator and denominator: ";
        cin >> num >> den;
    }

    // inline function to find GCD
    inline int gcd(int a, int b) {
        while (b != 0) {
            int t = b;
            b = a % b;
            a = t;
        }
        return a;
    }

    // inline function to simplify fraction
    inline void simplify() {
        int g = gcd(num, den);
        num = num / g;
        den = den / g;
    }

    void show() {
        cout << "Simplified fraction = " << num << "/" << den << endl;
    }
};

int main() {
    Fraction f;
    f.input();
    f.simplify();
    f.show();
    return 0;
}