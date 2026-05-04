#include <iostream>
#include <cstring>
using namespace std;
class String {
    char *str;
public:
    String(const char *s) {
        str = new char[strlen(s)+1];
        strcpy(str, s);
    }
    // Copy Constructor (Deep Copy)
    String(const String &s) {
        str = new char[strlen(s.str)+1];
        strcpy(str, s.str);
    }
    void display() {
        cout << str << endl;
    }
    ~String() {
        delete[] str;
    }
};
int main() {
    String s1("Hello");
    String s2 = s1;  // deep copy
    s1.display();
    s2.display();
}