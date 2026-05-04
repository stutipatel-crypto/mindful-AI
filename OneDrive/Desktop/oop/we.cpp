#include <iostream>
using namespace std;

class Marks {
private:
    int m1, m2, m3, m4, m5;
public:
    // function to input marks
    void input() {
        cout << "Enter 5 subject marks: ";
        cin >> m1 >> m2 >> m3 >> m4 >> m5;
    }
    // inline function to calculate total
    inline int total() {
        return m1 + m2 + m3 + m4 + m5;
    }
    inline float average() {
        return total() / 5.0;
    }
};
int main() {
    Marks s;
    s.input();
    cout << "Total = " << s.total() << endl;
    cout << "Average = " << s.average() << endl;
    return 0;
}