#include <iostream>
using namespace std;

float calculateEMI(float loan, float rate=10, int years=5){
    return (loan*rate*years)/100;
}

int main(){
    cout<<calculateEMI(10000)<<endl;
    cout<<calculateEMI(10000,12,3)<<endl;
}