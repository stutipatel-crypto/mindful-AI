#include <iostream>
using namespace std;

class Fahrenheit;

class Celsius {
private:
    float c;
public:
    Celsius(float x){ c=x; }
    inline bool valid(){ return c>-273; }
    friend void convert(Celsius);
};

void convert(Celsius t){
    if(t.valid())
        cout<<(t.c*9/5)+32<<" F\n";
}

int main(){
    Celsius c(25);
    convert(c);
}