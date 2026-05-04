#include<iostream>
using namespace std;
int cube(int n)
{
    return n*n*n;

}
int main()
{
    int n=3;
    int result=cube(n);
    cout<<"cube"<<result;
    return 0;
}
