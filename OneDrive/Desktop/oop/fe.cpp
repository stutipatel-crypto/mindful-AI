#include <iostream>
namespace first_space {
 void func() {
 std::cout << "Inside first_space" << std::endl;
 }
}
using first_space::func;
int main() {
 func();
 return 0;
}