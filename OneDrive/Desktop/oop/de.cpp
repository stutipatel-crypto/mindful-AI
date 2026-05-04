#include<iostream>
using namespace std;
class A
{

    int x;
public:
    A(int a)  
      {
        x = a;
        cout<<"Constructor called with value: " << x << endl;
        cout<<" x: " << x << endl;
    }
    ~A()  
    {
        cout<<"Destructor called for value: " << x << endl;
        cout<<"object with x: " << x << " is being destroyed." << endl;

    }
};
    int main()
    {
        A myObject(10);  // Create an object of class A
        A anotherObject(20);  // Create another object of class A
        return 0;
    }
