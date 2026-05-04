#include <iostream>
using namespace std;

class Time {
private:
    int h,m,s;
public:
    Time(int hh,int mm,int ss=0){ h=hh; m=mm; s=ss; }

    inline void normalize(){
        if(s>=60){ m++; s-=60; }
        if(m>=60){ h++; m-=60; }
    }
    friend Time add(Time,Time);

    void show(){ cout<<h<<":"<<m<<":"<<s<<endl; }
};

Time add(Time a, Time b){
    Time t(a.h+b.h,a.m+b.m,a.s+b.s);
    t.normalize();
    return t;
}
int main(){
    Time t1(1,59,50), t2(0,10,20);
    Time t3=add(t1,t2);
    t3.show();
}