#include <iostream>
using namespace std;

class Result {
private:
    string name;
    int marks;
    static int passMarks; // default passing marks

public:
    Result(string n, int m) {
        name = n;
        marks = m;
    }

    // inline function to calculate grade
    inline char grade() {
        if (marks >= 75) return 'A';
        else if (marks >= 60) return 'B';
        else if (marks >= passMarks) return 'C';
        else return 'F';
    }

    void show() {
        cout << name << " Marks: " << marks 
             << " Grade: " << grade() << endl;
    }
    // friend function for ranking
    friend void rankList(Result, Result);
};
// default passing marks
int Result::passMarks = 50;
// friend function definition
void rankList(Result s1, Result s2) {
    if (s1.marks > s2.marks)
        cout << s1.name << " has higher rank\n";
    else if (s2.marks > s1.marks)
        cout << s2.name << " has higher rank\n";
    else
        cout << "Both have same rank\n";
}
int main() {
    Result r1("Aman", 78);
    Result r2("Riya", 65);
    r1.show();
    r2.show();
    rankList(r1, r2);
    return 0;
}