#include <iostream>
using namespace std;

void fun(int a){
    cout<<"One parameter\n";
}

void fun(int a, int b=0){
    cout<<"Two parameters\n";
}

int main(){
    fun(5); // ambiguity
}