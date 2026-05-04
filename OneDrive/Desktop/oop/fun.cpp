#include<iostream>
using namespace std;
void checkevenodd(int a)
{
    if(a%2==0)
    cout<<"even";
    else
    cout<<"odd";
}
int main()
{
    int a=4;
    checkevenodd(a);
    return 0;
}
