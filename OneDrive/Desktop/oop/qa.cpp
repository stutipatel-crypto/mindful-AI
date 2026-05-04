#include <iostream>
using namespace std;

class Sports; // forward declaration

class Student {
private:
    int academicScore;

public:
    void setAcademic(int a) {
        academicScore = a;
    }

    friend void performance(Student s, Sports sp);
};

class Sports {
private:
    int sportsScore;

public:
    void setSports(int s) {
        sportsScore = s;
    }

    friend void performance(Student s, Sports sp);
};

// friend function
void performance(Student s, Sports sp) {
    int total = s.academicScore + sp.sportsScore;
    float average = total / 2.0;

    cout << "Academic Score: " << s.academicScore << endl;
    cout << "Sports Score: " << sp.sportsScore << endl;
    cout << "Overall Performance Index (Average): " << average << endl;
}

int main() {
    Student st;
    Sports sp;

    st.setAcademic(80);
    sp.setSports(90);

    performance(st, sp);

    return 0;
}