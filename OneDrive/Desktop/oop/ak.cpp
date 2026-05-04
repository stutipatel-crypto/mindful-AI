#include <iostream>
using namespace std;

class Car
{
    string brand;
    int year;
public:
    Car()   // Default Constructor
    {
        brand = "Toyota";
        year = 2020;
    }
    void display()
    {
        cout << "Brand: " << brand << endl;
        cout << "Year: " << year << endl;
    }
};
int main()
{
    Car c1;
    c1.display();
    return 0;
}