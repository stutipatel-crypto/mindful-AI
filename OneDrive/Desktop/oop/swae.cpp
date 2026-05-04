#include <iostream>
using namespace std;
class Employee
{
    int id;
    string name;
    float salary;
public:
    Employee(int i, string n, float s)
    {
        id = i;
        name = n;
        salary = s;
    }
    void display()
    {
        cout << "ID: " << id << endl;
        cout << "Name: " << name << endl;
        cout << "Salary: " << salary << endl;
    }
};
int main()
{
    Employee e1(101, "stuti", 50000);
    e1.display();

    return 0;
}