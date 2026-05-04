#include <iostream>
using namespace std;

class CollegeCourse
{
public:
    string courseID;
    char grade;
    int credits;
    int gradePoints;
    float honorPoints;

    void set_CourseId(string CID)
    {
        courseID = CID;
    }
    void set_Grade(char g)
    {
        grade = toupper(g);
    }
    void set_Credit(int cr)
    {
        credits = cr;
    }
    int calculateGradePoints(char g)
    {
        g = toupper(g);

        if(g=='A') return 10;
        else if(g=='B') return 9;
        else if(g=='C') return 8;
        else if(g=='D') return 7;
        else if(g=='E') return 6;
        else return 5;
    }
    float calculateHonorPoints(int gp, int cr)
    {
        return gp * cr;
    }
    void display()
    {
        gradePoints = calculateGradePoints(grade);
        honorPoints = calculateHonorPoints(gradePoints, credits);

        cout << gradePoints << " " << honorPoints;
    }
};
int main()
{
    CollegeCourse obj;
    string id;
    char g;
    int cr;

    cin >> id >> g >> cr;

    obj.set_CourseId(id);
    obj.set_Grade(g);
    obj.set_Credit(cr);

    obj.display();

    return 0;
}