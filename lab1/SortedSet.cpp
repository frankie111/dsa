#include "SortedSet.h"
#include "SortedSetIterator.h"

SortedSet::SortedSet(Relation r) {
    cap = 1;
    len = 0;
    elems = new TComp[1];
    this->r = r;
}


bool SortedSet::add(TComp elem) {
    if (search(elem))
        return false;

    // double size of array if current capacity is reached
    if (len == cap) {
        cap *= 2;
        auto *newElems = new TComp[cap];
        for (int i = 0; i < len; i++)
            newElems[i] = elems[i];

        delete[]elems;
        elems = newElems;
    }

    // Put elem on ordered position
    for (int i = len - 1; i >= 0; i--)
        if (elem < elems[i])
            elems[i + 1] = elems[i];
        else
            elems[i + 1] = elem;


    return true;
}


bool SortedSet::remove(TComp elem) {
    //TODO - Implementation
    return false;
}

//binary search for elem in elems
bool SortedSet::search(TComp elem) const {
    int low = 0, high = len - 1, mid;
    while (low < high) {
        mid = (low + high) / 2;
        if (elem == elems[mid])
            return true;
        else if (elem > elems[mid])
            low = mid + 1;
        else
            high = mid - 1;
    }

    return false;
}


int SortedSet::size() const {
    return len;
}


bool SortedSet::isEmpty() const {
    //TODO - Implementation
    return false;
}

SortedSetIterator SortedSet::iterator() const {
    return SortedSetIterator(*this);
}


SortedSet::~SortedSet() {
    //TODO - Implementation
    delete[]elems;
}


