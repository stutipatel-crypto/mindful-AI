#include <iostream>
using namespace std;
int main() {
    int n;
    cin >> n;
    int *arr = new int[n];
    for(int i=0;i<n;i++)
    cin >> arr[i];
    int *newArr = new int[2*n];
    for(int i=0;i<n;i++)
        newArr[i] = arr[i];
    delete[] arr;
    cout << "Resized array:\n";
    for(int i=0;i<n;i++)
        cout << newArr[i] << " ";
    delete[] newArr;
}
