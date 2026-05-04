#include<iostream>
#include<string>
using namespace std;
class book
{
    string title, author;

public:
    book()
    {
        title="the sun";
        author="stuti";
    }

    void display()
    {
        cout<<"title: "<<title<<endl;
        cout<<"author: "<<author<<endl;
    }
};

int main()
{
    book b1;
    b1.display();
    return 0;
}

