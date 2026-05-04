#include <iostream>
using namespace std;

class Cuboid
{
protected:
    int length, width, height;

public:
    void display()
    {
        cout << "Length: " << length << endl;
        cout << "Width: " << width << endl;
        cout << "Height: " << height << endl;
    }
};

class CuboidVol : public Cuboid
{
public:
    void read_input()
    {
        cout << "Enter the value of length: ";
        cin >> length;
        cout << "Enter the value of width: ";
        cin >> width;
        cout << "Enter the value of height: ";
        cin >> height;
    }
    void display()
    {
        cout << "Volume of Cuboid = " << length * width * height << endl;
    }
};
int main()
{
    CuboidVol obj;

    obj.read_input();
    obj.display();

    return 0;
}