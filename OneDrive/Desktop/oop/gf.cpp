#include <iostream>
namespace first_space {
 void func() {
 std::cout << "Inside first_space" << std::endl;
 }
}
using namespace first_space;
int main() {
 func();
 return 0;
}