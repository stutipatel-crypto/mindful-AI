#include <iostream>
using namespace std;
int main() {
    int r, c;
    cin >> r >> c;
    int **mat = new int*[r];
    for(int i=0;i<r;i++)
        mat[i] = new int[c];
    cout << "Enter matrix:\n";
    for(int i=0;i<r;i++)
        for(int j=0;j<c;j++)
            cin >> mat[i][j];
    cout << "Matrix:\n";
    for(int i=0;i<r;i++) {
        for(int j=0;j<c;j++)
            cout << mat[i][j] << " ";
        cout << endl;
    }
    for(int i=0;i<r;i++)
        delete[] mat[i];
    delete[] mat;
}
