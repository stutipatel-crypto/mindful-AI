#include <iostream>
using namespace std;

class Laptop {
private:
    string brand;
    int ram, storage;
public:
    Laptop(string b="HP", int r=8, int s=512){
        brand=b; ram=r; storage=s;
    }
    void show(){
        cout<<brand<<" "<<ram<<"GB "<<storage<<"GB\n";
    }
};

int main(){
    Laptop l1;
    Laptop l2("Dell",16,1024);
    l1.show();
    l2.show();
}