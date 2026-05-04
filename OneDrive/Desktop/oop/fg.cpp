#include <iostream>
using namespace std;
class Inventory {
private:
    int stock;
public:
    Inventory(int s) {
        stock = s;
    }
    // show stock
    void show() {
        cout << "Current stock: " << stock << endl;
    }
    inline void purchase(int qty) {
        if (qty <= stock) {
            stock = stock - qty;
            cout << "Purchase successful\n";
        } else {
            cout << "Not enough stock\n";
        }
    }
};
int main() {
    Inventory item(50);
    item.show();
    item.purchase(20);
    item.show();
    item.purchase(40); // will not allow negative stock
    item.show();
    return 0;
}