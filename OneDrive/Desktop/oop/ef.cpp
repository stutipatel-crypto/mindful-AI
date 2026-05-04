#include <iostream>
using namespace std;
class ArrayHandler
{
private:
    int arr[5];
public:
    // Constructor to initialize array
    ArrayHandler()
    {
        for(int i = 0; i < 5; i++)
        {
            arr[i] = i + 1;  // 1, 2, 3, 4, 5
        }
    }
    // Function returning reference
    int& getElement(int index)
    {
        return arr[index];   // returning reference
    }
    // Function to display array
    void display()
    {
        for(int i = 0; i < 5; i++)
        {
            cout << arr[i] << " ";
        }
        cout << endl;
    }
};
int main()
{
    ArrayHandler obj;
    cout << "Original Array: ";
    obj.display();
    // Modify element using returned reference
    obj.getElement(2) = 100;
    cout << "Modified Array: ";
    obj.display();
    return 0;
}