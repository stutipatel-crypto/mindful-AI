#include <iostream>
using namespace std;
class Temperature
{
    float celsius;
public:
    Temperature()   // Default Constructor
    {
        celsius = 0;
    }

    void convert()
    {
        float fahrenheit = (celsius * 9/5) + 32;
        cout << "Temperature in Fahrenheit: " << fahrenheit << endl;
    }
};
int main()
{
    Temperature t1;
    t1.convert();

    return 0;
}