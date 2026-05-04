#include <iostream>
using namespace std;
class Circle;
class Rectangle {
private:
    float l, w;
public:
    Rectangle(float a,float b){ l=a; w=b; }
    friend void compare(Rectangle, Circle);
};
class Circle {
private:
    float r;
public:
    Circle(float x){ r=x; }
    friend void compare(Rectangle, Circle);
};
void compare(Rectangle rec, Circle cir) {
    float areaR = rec.l * rec.w;
    float areaC = 3.14 * cir.r * cir.r;
    if(areaR > areaC)
        cout<<"Rectangle larger\n";
    else
        cout<<"Circle larger\n";
}
int main() {
    Rectangle r(5,4);
    Circle c(3);
    compare(r,c);
}