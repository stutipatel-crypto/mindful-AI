include<iostream>
using namespace std;
int main()
{
int total,com,his,civ,average,pass,fail;
cout<< "enter the marks of com";
cout<< "enter the marks of his";
cout<< "enter the marks of civ";
cin>>  com;
cin>>  his;
cin>>  civ;
total=com+his+civ;
average=com+his+civ/3;
pass/fail=60>total ? "pass" :"fail";
return 0
}

