#include <iostream>
using namespace std;

class Student
{
public:
    int Roll;
    void setRoll()
    {
        
        cout << " Enter Roll : " << Roll << endl;
        cin>> Roll;
    }
};
class Test : public Student
{

    int m1, m2, m3, m4, m5;

public:
    void setMarks(int a, int b, int c, int d, int e)
    {
        m1 = a;
        m2 = b;
        m3 = c;
        m4 = d;
        m5 = e;
    }
};

class Result : public Test
{
public:
    void Display()
    {
        int total = m1 + m2 + m3 + m4 + m5;
        float average = total / 5.0;

        cout << "total marks: " << total << endl;
        cout << "average marks: " << average << endl;
    }
};

int main()
{
    Result obj;

    obj.setRoll();
    obj.setMarks(80, 75, 90, 85, 70);

    obj.Display();

    return 0;
}