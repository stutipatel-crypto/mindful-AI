#include<iostream>
using namespace std;
void add(int,int );
int main()
{
    int x,y;
    cout <<"enter the value of x and y";
    cin >>x>>y;
    add(x,y);
    return 0;
}
void add(int x, int y)
{
    int sum=x+y;
    cout<<"sum "<<sum;
    
    }

