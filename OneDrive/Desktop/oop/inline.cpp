#include <iostream>
using namespace std;
class Circle {
private:
    float radius;
public:
    void setRadius(float r) {
        radius = r;
    }
    inline float area() {
        return 3.14 * radius * radius;
    }
    inline float circumference() {
        return 2 * 3.14 * radius;
    }
};
int main() {
    Circle c;
    float r;
    for(int i = 1; i <= 3; i++) {
        cout << "Enter radius: ";
        cin >> r;
        c.setRadius(r);
        cout << "Area = " << c.area() << endl;
        cout << "Circumference = " << c.circumference() << endl;
        cout << endl;
    }
  return 0;
}