#include <iostream>
using namespace std;

class Student
{
    string name;
    int marks;

public:
    Student(string n, int m)
    {
        name = n;
        marks = m;
    }
    void display()
    {
        cout << "Name: " << name << "  Marks: " << marks << endl;
    }
};
int main()
{
    Student s[5] = {
        Student("shital", 80),
        Student("stuti", 75),
        Student("Neha", 90),
        Student("Priya", 85),
        Student("devyani", 70)
    };

    cout << "Student Details:" << endl;

    for(int i = 0; i < 5; i++)
    {
        s[i].display();
    }

    return 0;
}