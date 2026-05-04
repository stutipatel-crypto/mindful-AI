#include <iostream>
using namespace std;
enum toy { bunny, train, anabelle, voodoo, doll, basketball, yoyo };
int main()
{
    toy today;
    today = train;
    cout << "Day " << today;
    return 0;
}