#include <iostream>
using namespace std;
int n = 3;
int main() {
 int n = 7;
 cout << ::n;
 cout << n;
 return 0;
}