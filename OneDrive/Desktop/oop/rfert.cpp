#include <iostream>
using namespace std;

class Account
{
protected:
    string accountNumber;
    float balance;
public:
    void setDetails()
    {
        cout << "Enter Account Number: ";
        cin >> accountNumber;

        cout << "Enter Balance: ";
        cin >> balance;
    }
    void display()
    {
        cout << "Account Number: " << accountNumber << endl;
    }
};
class SavingsAccount : public Account
{
    float interestRate;
public:
    void calculateInterest()
    {
        cout << "Enter Interest Rate: ";
        cin >> interestRate;

        float interest = balance * interestRate / 100;

        display(); // calling parent class function
        cout << "Interest Earned: " << interest << endl;
    }
};
int main()
{
    SavingsAccount s;
    s.setDetails();
    s.calculateInterest();
}