#include <iostream>
using namespace std;
class StudentMarks
{
    string name;
    int marks;
public:
    StudentMarks(string n, int m)   // Parameterized Constructor
    {
        name = n;
        marks = m;
    }
    void display()
    {
        cout << "Name: " << name << endl;
        cout << "Marks: " << marks << endl;
    }
};
int main()
{
    StudentMarks s1("Rahul", 85);
    s1.display();

    return 0;
}