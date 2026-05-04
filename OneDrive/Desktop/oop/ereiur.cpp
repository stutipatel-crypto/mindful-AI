#include <iostream>
using namespace std;

class Payroll {
private:
    int basic;
public:
    Payroll(int b){ basic=b; }

    inline int hra(){ return basic*20/100; }
    inline int da(){ return basic*10/100; }

    friend void audit(Payroll);
};

void audit(Payroll p){
    cout<<"Total salary = "<<p.basic+p.hra()+p.da()<<endl;
}

int main(){
    Payroll p(20000);
    audit(p);
}