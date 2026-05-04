#include <iostream>
using namespace std;

class Product
{
    int id;
    string name;
    float price;

public:
    // Default constructor
    Product()
    {
        id = 0;
        name = "Default";
        price = 0;
        cout << "Default Constructor Called" << endl;
    }

    // Parameterized constructor
    Product(int i, string n, float p)
    {
        id = i;
        name = n;
        price = p;
        cout << "Parameterized Constructor Called" << endl;
    }

    // Copy constructor
    Product(const Product &p)
    {
        id = p.id;
        name = p.name;
        price = p.price;
        cout << "Copy Constructor Called" << endl;
    }
    void display()
    {
        cout << "ID: " << id << endl;
        cout << "Name: " << name << endl;
        cout << "Price: " << price << endl;
        cout << endl;
    }
};

int main()
{
    Product p1;                 // Default constructor
    Product p2(101, "Laptop", 50000); // Parameterized constructor
    Product p3 = p2;            // Copy constructor

    p1.display();
    p2.display();
    p3.display();

    return 0;
}