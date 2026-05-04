#include <iostream>

namespace very_long_namespace_name {
    void display() {
        std::cout << "Hello from namespace!" << std::endl;
    }
}

namespace vln = very_long_namespace_name;   // Namespace Alias

int main() {
    vln::display();   // using alias instead of full name
    return 0;
}