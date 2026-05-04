#include <iostream>
using namespace std;

class Product
{
public:
    string productID;
    int price;
    int quantity;

    void calculateBill()
    {
        int bill = price * quantity;
        cout << productID << " " << bill;
    }
};

int main()
{
    Product obj;

    cin >> obj.productID >> obj.price >> obj.quantity;

    obj.calculateBill();

    return 0;
}