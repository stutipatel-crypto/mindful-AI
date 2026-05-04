#include <iostream>
using namespace std;

class Complex {
private:
    int real, imag;
public:
    Complex(int r,int i){ real=r; imag=i; }

    friend Complex operator-(Complex, Complex);

    void show(){
        cout<<real<<" + "<<imag<<"i\n";
    }
};

Complex operator-(Complex a, Complex b){
    return Complex(a.real-b.real, a.imag-b.imag);
}

int main(){
    Complex c1(5,4), c2(2,1);
    Complex c3 = c1 - c2;
    c3.show();
}