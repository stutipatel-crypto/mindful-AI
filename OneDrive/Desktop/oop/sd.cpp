#include <iostream>
using namespace std;
class BankAccount
{
private:
    int accountNumber;
    double balance;   // private (hidden)

public:
    // Constructor
    BankAccount(int accNo, double bal)
    {
        accountNumber = accNo;
        balance = bal;
    }
    // Deposit money
    void deposit(double amount)
    {
        balance = balance + amount;
    }
    // Withdraw money
    void withdraw(double amount)
    {
        if(amount <= balance)
        {
            balance = balance - amount;
        }
        else
        {
            cout << "Not enough balance!" << endl;
        }
    }
    // Show balance
    void showBalance()
    {
        cout << "Balance: " << balance << endl;
    }
};
int main()
{
    BankAccount acc(101, 5000);

    acc.showBalance();   // 5000

    acc.deposit(1000);
    acc.withdraw(2000);

    acc.showBalance();   // 4000

    // acc.balance = 10000; ❌ Error (balance is private)

    return 0;
}