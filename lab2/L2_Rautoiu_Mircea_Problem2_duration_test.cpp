#include <iostream>
#include "L2_Rautoiu_Mircea_Problem2_Duration.h"

using namespace std;

int main() {
    float d1, d2, scale;
    string u1, u2;
    cout << "Enter first duration: ";
    cin >> d1;
    cout << "Enter first unit: ";
    cin >> u1;

    cout << "Enter second duration: ";
    cin >> d2;
    cin.clear();
    cout << "Enter second unit: ";
    cin >> u2;

    cout << "Enter a scaling factor: ";
    cin >> scale;

    Duration dur1(d1, u1), dur2(d2, u2);

    cout << "\n" << dur1.text() << " + " << dur2.text() << " = " << dur1.add(dur2).text() << endl;
    cout << dur1.text() << " - " << dur2.text() << " = " << dur1.subtract(dur2).text();

    cout << "\n" << dur1.text() << " * " << scale << " = ";
    dur1.scale(scale);
    cout << dur1.text();

    cout << "\n" << dur2.text() << " * " << scale << " = ";
    dur2.scale(scale);
    cout << dur2.text() << endl;

    int cmp = dur1.compare(dur2);
    if (cmp == 0)
        cout << dur1.text() << " == " << dur2.text();
    else if (cmp == -1)
        cout << dur1.text() << " < " << dur2.text();
    else if (cmp == 1)
        cout << dur1.text() << " > " << dur2.text();

}