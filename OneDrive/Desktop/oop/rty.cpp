#include <iostream>
using namespace std;
class BankAccount {
private:
    int balance;
public:
    BankAccount(int b) { balance = b; }

    void show() { cout << "Balance = " << balance << endl; }

    friend void transfer(BankAccount &a, BankAccount &b, int amt);
};
void transfer(BankAccount &a, BankAccount &b, int amt) {
    if (a.balance >= amt) {
        a.balance -= amt;
        b.balance += amt;
        cout << "Transfer done\n";
    } else {
        cout << "Insufficient balance\n";
    }
}
int main() {
    BankAccount A(1000), B(500);
    transfer(A,B,200);
    A.show();
    B.show();
}