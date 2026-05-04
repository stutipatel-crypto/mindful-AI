#include <iostream>
using namespace std;

class Employee
{
private:
    int id;
    string name;

public:
    // Constructor
    Employee(int i, string n)
    {
        id = i;
        name = n;
    }

    void display()
    {
        cout << "ID: " << id << " Name: " << name << endl;
    }
};

int main()
{
    // Two objects with same data
    Employee emp1(101, "Stuti");
    Employee emp2(101, "Stuti");

    cout << "Employee 1 Details:" << endl;
    emp1.display();

    cout << "Employee 2 Details:" << endl;
    emp2.display();

    // Showing different memory addresses (identity)
    cout << "\nMemory Address of emp1: " << &emp1 << endl;
    cout << "Memory Address of emp2: " << &emp2 << endl;

    return 0;
}