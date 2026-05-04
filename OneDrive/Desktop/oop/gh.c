#include <iostream>
using namespace std;

enum Day { Monday = 1, Tuesday, Wednesday, Thursday, Friday, Saturday, Sunday };

int main() {
    int choice;

    cout << "Enter a number (1-7): ";
    cin >> choice;

    Day today = (Day)choice;

    switch (today) {
        case Monday:
            cout << "Monday";
            break;
        case Tuesday:
            cout << "Tuesday";
            break;
        case Wednesday:
            cout << "Wednesday";
            break;
        case Thursday:
            cout << "Thursday";
            break;
        case Friday:
            cout << "Friday";
            break;
        case Saturday:
            cout << "Saturday";
            break;
        case Sunday:
            cout << "Sunday";
            break;
        default:
            cout << "Invalid choice";
    }

    return 0;
}
