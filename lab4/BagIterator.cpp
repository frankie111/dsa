#include <exception>
#include "BagIterator.h"
#include "Bag.h"

using namespace std;


BagIterator::BagIterator(const Bag &c) : bag(c) {
    currentPos = 0;
    currentCount = 0;
}

void BagIterator::first() {
    //TODO - Implementation
}


void BagIterator::next() {
    //TODO - Implementation
}


TElem BagIterator::getCurrent() const {
    //TODO - Implementation
    return NULL_TELEM;
}


bool BagIterator::valid() const {
    return currentPos >= 0 && currentPos < bag.tableSize;
}
