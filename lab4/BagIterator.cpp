#include <exception>
#include "BagIterator.h"
#include "Bag.h"

using namespace std;


BagIterator::BagIterator(const Bag &c) : bag(c) {
    currentPos = 0;
    currentCount = 0;
}


void BagIterator::first() {
    currentPos = 0;
    currentCount = 0;
}


void BagIterator::next() {
    if (!valid())
        throw out_of_range("BagIterator::next: Invalid iterator!");

    if (currentCount < bag.table[currentPos].ct - 1)
        currentCount++;
    else {
        currentPos++;
        currentCount = 0;

        // Skip empty positions
        while (currentPos < bag.tableSize && bag.table[currentPos].ct == 0)
            currentPos++;
    }
}


TElem BagIterator::getCurrent() const {
    if (!valid())
        throw out_of_range("BagIterator::getCurrent: Invalid iterator!");

    return bag.table[currentPos].value;
}


bool BagIterator::valid() const {
    return currentPos >= 0 && currentPos < bag.tableSize && currentCount < bag.table[currentPos].ct;
}
