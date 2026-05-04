#include<iostream>
using namespace std;
int main()
{
int total,com,his,civ,average;

cout << "enter the marks of com:";
cin >>  com;
cout << "enter the marks of his:";
cin >>  his;
cout << "enter the marks of civ:";
cin >>  civ;
total=com+his+civ;
cout << "total ="<<total<<endl;
average=total/3.0;
cout << "average ="<<average<<endl;
string result = (average>=60) ? "pass": "fail";
cout << "result ="<<result<<endl;
return 0;
}


