#include <iostream>
using namespace std;
class Book
{
    string title, author;
    float price;
public:
    Book(string t, string a, float p)
    {
        title = t;
        author = a;
        price = p;
    }
    // Copy constructor
    Book(const Book &b)
    {
        title = b.title;
        author = b.author;
        price = b.price;
    }
    void display()
    {
        cout << "Title: " << title << endl;
        cout << "Author: " << author << endl;
        cout << "Price: " << price << endl;
    }
};
int main()
{
    Book b1("C++ Programming", "friend ", 500);
    Book b2 = b1;

    cout << "Book 1:" << endl;
    b1.display();

    cout << "Book 2:" << endl;
    b2.display();

    return 0;
}