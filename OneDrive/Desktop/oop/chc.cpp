#include <iostream>
using namespace std;
struct Student {
    string name;
    int roll;
    float marks;
};
int main() {
    Student *s = new Student;
    cout << "Enter name, roll, marks:\n";
    cin >> s->name >> s->roll >> s->marks;
    cout << "\nDetails:\n";
    cout << s->name << " " << s->roll << " " << s->marks;
    delete s;
}
