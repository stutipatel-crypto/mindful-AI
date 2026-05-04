#include <iostream>
using namespace std;
class Book {
public:
    string title;
    float price;
};
int main() {
    int n;
    cin >> n;
    Book *b = new Book[n];
    for(int i=0;i<n;i++) {
        cout << "Enter title and price:\n";
        cin >> b[i].title >> b[i].price;
    }
    cout << "\nBooks:\n";
    for(int i=0;i<n;i++)
        cout << b[i].title << " " << b[i].price << endl;
    delete[] b;
}