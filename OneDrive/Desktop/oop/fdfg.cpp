#include <iostream>
using namespace std;
inline namespace inline_space {
 void display() {
 cout << "Inside inline namespace";
 }
}
int main() {
 display();
 return 0;
}