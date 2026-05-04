#include<iostream>
using namespace std;
class set
{
    int a;
    public:
    set(){
        a=0;
    }
    set(int x)
    {
        a=x;
    }
    void display()
    {
        cout<<"set: "<<a<<endl;
    }
};
int main()
{
    set d1;
    d1=5;
    d1.display();
    return 0;
}