#include <iostream>
using namespace std;

class Result {
private:
    int marks;
public:
    Result(int m){ marks=m; }

    inline char grade(){
        if(marks>=75) return 'A';
        else if(marks>=50) return 'B';
        else return 'F';
    }
    friend void rank(Result,Result);
};
void rank(Result a, Result b){
    if(a.marks>b.marks)
        cout<<"Student 1 higher\n";
    else
        cout<<"Student 2 higher\n";
}
int main(){
    Result r1(80), r2(60);
    cout<<r1.grade()<<endl;
    rank(r1,r2);
}