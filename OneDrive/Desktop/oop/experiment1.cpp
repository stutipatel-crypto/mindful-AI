//qustion 1
#include <iostream>
namespace Room1 {
 void greet() {
 std::cout << "Hello from Room 1!" << std::endl;
 }
}
namespace Room2 {
 void greet() {
 std::cout << "Hello from Room 2!" << std::endl;
 }
}
int main() {
 Room1::greet();
 Room2::greet();
 return 0;
}