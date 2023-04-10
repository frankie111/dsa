#include <iostream>
#include "MultiMap.h"

using namespace std;

int main() {
    MultiMap mm;
    mm.add(1, 11);
    mm.add(1, 12);
    mm.add(2, 21);
    cout << mm.remove(1, 11) << endl;
    mm.print();
//    cout << mm.size();
}
