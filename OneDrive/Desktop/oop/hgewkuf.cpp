#include <iostream>
using namespace std;

class MovieTicket {
public:
    float cost(float price, float discount=10, float tax=5){
        price = price - price*discount/100;
        price = price + price*tax/100;
        return price;
    }
};

int main(){
    MovieTicket m;
    cout<<m.cost(200)<<endl;
}