#include <iostream>
using namespace std;

class Time
{
    int hour, minute, second;

public:
    // Default constructor
    Time()
    {
        hour = minute = second = 0;
    }
    // Parameterized constructor
    Time(int h, int m, int s)
    {
        hour = h;
        minute = m;
        second = s;
    }
    void display()
    {
        cout << hour << ":" << minute << ":" << second << endl;
    }
};

int main()
{
    Time t1;          // default constructor
    Time t2(10, 30, 45); // parameterized constructor

    cout << "Default Time: ";
    t1.display();

    cout << "User Time: ";
    t2.display();

    return 0;
}