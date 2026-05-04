#include<iostream>
using namespace std;
class counter
{
public:
    int iteam;
    static int count;

    void setdata(int i)
    {
        iteam = i;
        count++;
    }
    void display()
    {
        cout<< count<<endl;
        cout<<iteam<<endl;
    }
};
    int counter::count;
    int main()
    {
    counter a,b;
    a.setdata(10);
    b.setdata(20);
    a.display();
    b.display();
    return 0;
    }