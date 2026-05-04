
#include <iostream>
using namespace std;

class Device {
public:
    int batteryLevel;

    Device() {
        cout << "Device created" << endl;
        batteryLevel = 100;
    }
};

class Smartphone : virtual public Device {
public:
    Smartphone() {
        cout << "Smartphone created" << endl;
    }
};

class Tablet : virtual public Device {
public:
    Tablet() {
        cout << "Tablet created" << endl;
    }
};

class FoldablePhone : public Smartphone, public Tablet {
public:
    FoldablePhone() {
        cout << "Foldable Phone created" << endl;
    }
};

int main() {
    FoldablePhone f;

    cout << "Battery Level: " << f.batteryLevel << endl;

    return 0;
}