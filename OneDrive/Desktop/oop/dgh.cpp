#include <iostream>
using namespace std;

class ElectricityBill
{
public:
    string consumerID;
    int units;
    int bill;

    void calculateBill()
    {
        if(units <= 100)
            bill = units * 5;
        else if(units <= 200)
            bill = (100 * 5) + ((units - 100) * 7);
        else
            bill = (100 * 5) + (100 * 7) + ((units - 200) * 10);

        cout << "Consumer ID: " << consumerID << endl;
        cout << "Total Bill: " << bill << endl;
    }
};
int main()
{
    ElectricityBill obj;

    cout << "Enter Consumer ID: ";
    cin >> obj.consumerID;

    cout << "Enter Units Consumed: ";
    cin >> obj.units;

    obj.calculateBill();

    return 0;
}