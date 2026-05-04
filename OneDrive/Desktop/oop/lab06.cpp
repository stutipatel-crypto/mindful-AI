#include <iostream>
using namespace std;
class Array
{
    int *arr;
    int size;
public:
    Array(int n)
    {
        size = n;
        arr = new int[size];
        cout << "Memory allocated\n";
    }
    void input()
    {
        cout << "Enter elements:\n";
        for(int i = 0; i < size; i++)
            cin >> arr[i];
    }
    void display()
    {
        cout << "Array elements:\n";
        for(int i = 0; i < size; i++)
            cout << arr[i] << " ";
    }
    ~Array()
    {
        delete[] arr;
        cout << "\nMemory deallocated";
    }
};
int main()
{
    int n;
    cout << "Enter size: ";
    cin >> n;
    Array a(n);  
    a.input();
    a.display();
    return 0;    
}