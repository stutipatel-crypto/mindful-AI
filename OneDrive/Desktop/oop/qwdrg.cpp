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
        cout << "Product ID: " << productID << endl;
        cout << "Total Bill: " << bill << endl;
    }
};
int main()
{
    Product obj;
    cout << "Enter Product ID: ";
    cin >> obj.productID;
    cout << "Enter Price per Unit: ";
    cin >> obj.price;
    cout << "Enter Quantity: ";
    cin >> obj.quantity;
    obj.calculateBill();
    return 0;
}