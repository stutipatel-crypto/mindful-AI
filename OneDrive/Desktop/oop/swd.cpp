#include <iostream>
using namespace std;
class BankAccount
{
    int accNo;
    string name;
    float balance;
public:
    BankAccount(int a, string n, float b)
    {
        accNo = a;
        name = n;
        balance = b;
    }
    void display()
    {
        cout << "Account Number: " << accNo << endl;
        cout << "Account Holder: " << name << endl;
        cout << "Balance: " << balance << endl;
    }
};
int main()
{
    BankAccount b1(101, "stuti", 5000);
    b1.display();
    return 0;
}