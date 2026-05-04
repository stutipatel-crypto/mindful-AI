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
    operator int() {
        return a;
    }
};
int main()
{
    set d1(5);
    d1.display();
    int x = d1; // Implicit conversion from set to int
    cout << "Value of x: " << x << endl; // Output the value of
    return 0;
}