#include <iostream>
#include <cmath>
using namespace std;

class Point {
private:
    int x,y;
public:
    Point(int a,int b){ x=a; y=b; }

    inline float origin(){
        return sqrt(x*x+y*y);
    }

    friend float distance(Point,Point);
};

float distance(Point a, Point b){
    return sqrt(pow(a.x-b.x,2)+pow(a.y-b.y,2));
}

int main(){
    Point p1(3,4), p2(6,8);
    cout<<p1.origin()<<endl;
    cout<<distance(p1,p2)<<endl;
}