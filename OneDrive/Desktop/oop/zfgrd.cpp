#include <iostream>
using namespace std;

class Counter
{
private:
    int value;

public:
    // Constructor
    Counter(int v = 0)
    {
        value = v;
    }
    // Prefix Increment (++obj)
    Counter operator++()
    {
        ++value;        // Increment first
        return *this;   // Return updated object
    }
    // Postfix Increment (obj++)
    Counter operator++(int)
    {
        Counter temp = *this;  // Store old value
        value++;               // Increment after
        return temp;           // Return old value
    }
    void display()
    {
        cout << "Value: " << value << endl;
    }
};
int main()
{
    Counter c1(5), c2;

    cout << "Initial Value: ";
    c1.display();

    // Prefix
    c2 = ++c1;
    cout << "\nAfter Prefix (++c1):" << endl;
    cout << "c1 = ";
    c1.display();
    cout << "c2 = ";
    c2.display();

    // Postfix
    c2 = c1++;
    cout << "\nAfter Postfix (c1++):" << endl;
    cout << "c1 = ";
    c1.display();
    cout << "c2 = ";
    c2.display();

    return 0;
}