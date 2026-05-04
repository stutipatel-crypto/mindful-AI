#include <iostream>
using namespace std;
class Cuboid
{
protected:
    int length, width, height;

public:
    void display()
    {
        cout << length << " " << width << " " << height << endl;
    }
};
class CuboidVol : public Cuboid
{
public:
    void read_input()
    {
        cin >> length >> width >> height;
    }

    void display()
    {
        cout << length * width * height << endl;
    }
};
int main()
{
    CuboidVol obj;

    obj.read_input();   // read length, width, height
    obj.display();      // display volume

    return 0;
}