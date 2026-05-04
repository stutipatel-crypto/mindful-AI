#include <iostream>
using namespace std;

class Complex
{
private:
    float real, imag;

public:
    // Constructor
    Complex(float r = 0, float i = 0)
    {
        real = r;
        imag = i;
    }

    // Friend Function Declaration
    friend Complex operator + (Complex, Complex);

    // Display Function
    void display()
    {
        cout << real << " + " << imag << "i" << endl;
    }
};
// Friend Function Definition
Complex operator + (Complex c1, Complex c2)
{
    Complex temp;
    temp.real = c1.real + c2.real;
    temp.imag = c1.imag + c2.imag;
    return temp;
}
int main()
{
    Complex c1(3, 4), c2(2, 5);
    Complex c3;

    c3 = c1 + c2;

    cout << "Result: ";
    c3.display();

    return 0;
}