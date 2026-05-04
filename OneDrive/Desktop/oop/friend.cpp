#include<iostream>
using namespace std;
class bankaccount
{
    int x;
public:
    int balance()
    friend void display(bankaccount );
};
void bankaccount::balance(int p)
{
    x=p;
}
void display(bankaccount b)
{
    cout<<"displaying balance: "<<b.x<<endl;
}
int main()
{
    bankaccount p;
    p.balance(300);
    display(bankaccount);
    return 0;

}