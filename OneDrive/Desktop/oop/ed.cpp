#include <iostream>
using namespace std;
class Temperature {
private:
    float celsius;
public:
    // set temperature in Celsius
    void setCelsius(float c) {
        celsius = c;
    }
    inline float toFahrenheit() {
        return (celsius * 9.0 / 5.0) + 32;
    }
};
int main() {
    Temperature t;
    float c;
    cout << "Enter temperature in Celsius: ";
    cin >> c;
    t.setCelsius(c);
    cout << "Fahrenheit = " << t.toFahrenheit() << endl;
    return 0;
}