#include <iostream>
using namespace std;

int main() {
    int n;
    cout << "Enter size: ";
    cin >> n;

    int *arr = new int[n];

    cout << "Enter elements:\n";
    for(int i=0;i<n;i++)
        cin >> arr[i];

    cout << "Array elements:\n";
    for(int i=0;i<n;i++)
        cout << arr[i] << " ";

    delete[] arr;
    return 0;
}