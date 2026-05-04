#include <iostream>
#include <string>
using namespace std;

class Student
{
private:
    string name;
    int marks;

public:
    // Constructor
    Student(string n = "", int m = 0)
    {
        name = n;
        marks = m;
    }

    // Overload > operator (compare based on marks)
    bool operator > (Student s)
    {
        return this->marks > s.marks;
    }

    void display()
    {
        cout << name << " - " << marks << endl;
    }
};

int main()
{
    Student s[4] = {
        Student("Aman", 75),
        Student("Riya", 88),
        Student("Kunal", 65),
        Student("Sneha", 92)
    };

    int n = 4;

    // Sorting using overloaded > operator (Descending order)
    for(int i = 0; i < n-1; i++)
    {
        for(int j = 0; j < n-i-1; j++)
        {
            if(s[j] > s[j+1])
            {
                Student temp = s[j];
                s[j] = s[j+1];
                s[j+1] = temp;
            }
        }
    }

    cout << "Students sorted by marks (Ascending):\n";
    for(int i = 0; i < n; i++)
    {
        s[i].display();
    }

    return 0;
}