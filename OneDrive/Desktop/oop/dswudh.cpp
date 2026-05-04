#include <iostream>
using namespace std;

void show(int a) {
    cout << "Function with one parameter\n";
}

void show(int a, int b = 0) {
    cout << "Function with two parameters\n";
}

int main() {
    show(10);   // ambiguous call
    return 0;
}