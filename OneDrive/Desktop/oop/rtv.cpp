#include <iostream>
using namespace std;

class Employee {
private:
    int salary;
public:
    Employee(int s){ salary=s; }
    friend void bonus(Employee);
};

void bonus(Employee e){
    cout<<"Annual Bonus = "<<e.salary*0.10<<endl;
}

int main(){
    Employee e(50000);
    bonus(e);
}