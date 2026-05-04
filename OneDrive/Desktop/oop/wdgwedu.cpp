#include <iostream>
using namespace std;

void student(string name, string dept="CSE"){
    cout<<name<<" "<<dept<<endl;
}

int main(){
    student("stuti");
    student("Riya","IT");
}