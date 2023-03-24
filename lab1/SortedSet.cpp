#include "SortedSet.h"
#include "SortedSetIterator.h"
#include <iostream>

/**
 * Constructor
 * @complexity Ω(1)
 * @complexity θ(1)
 * @complexity O(1)
 * */
SortedSet::SortedSet(Relation r) {
    cap = 1;
    len = 0;
    elems = new TComp[1]{0};
    this->r = r;
}


/**
 * Add elem to set
 * @complexity Ω(log n)
 * @complexity θ(n)
 * @complexity O(n)
 * */
bool SortedSet::add(TComp elem) {
    if (search(elem))
        return false;

    resize();

    // Put elem on ordered position
    if (len == 0) {
        elems[0] = elem;
    } else {
        int i;
        for (i = len - 1; i >= 0; i--)
            if (r(elem, elems[i])) // elem <= elems[i]
                elems[i + 1] = elems[i];
            else break;

        elems[i + 1] = elem;
    }
    len++;

    return true;
}

/**
 * Resize set: \n
 *
 * Grow set if current capacity is reached or
 * shrink set if len \< 1/4 capacity
 *
 * @complexity θ(1)
 * @complexity O(n)
 * */
void SortedSet::resize() {
    if (len == cap)
        cap *= GROWTH_FACTOR;
    else if (len < cap / (GROWTH_FACTOR * 2))
        cap /= GROWTH_FACTOR;
    else return;

    auto *newElems = new TComp[cap];
    std::copy(elems, elems + len, newElems);
    delete[]elems;
    elems = newElems;
}


/**
 * Remove elem from set if elem exists \n
 *
 * Find index of elem in set and shift all elements by 1
 * position to the left
 * @complexity Ω(log n)
 * @complexity θ(n)
 * @complexity O(n)
 * */
bool SortedSet::remove(TComp elem) {
    int pos = getIndex(elem);

    if (pos != -1) {
        for (int i = pos; i < len; i++)
            elems[i] = elems[i + 1];
        len--;
        resize();
        return true;
    }
    return false;
}


/**
 * binary search for elem in elems
 * @complexity Ω(1)
 * @complexity θ(log n)
 * @complexity O(log n)
 * */
bool SortedSet::search(TComp elem) const {
    return getIndex(elem) != -1;
}


/**
 * return length of set
 * @complexity Ω(1)
 * @complexity θ(1)
 * @complexity O(1)
 * */
int SortedSet::size() const {
    return len;
}


/**
 * return 1 if set is empty, 0 otherwise
 * @complexity Ω(1)
 * @complexity θ(1)
 * @complexity O(1)
 * */
bool SortedSet::isEmpty() const {
    return len == 0;
}


/**
 * return an iterator for this set
 * @complexity Ω(1)
 * @complexity θ(1)
 * @complexity O(1)
 * */
SortedSetIterator SortedSet::iterator() const {
    return {*this};
}


/**
 * Delete elems array
 * @complexity Ω(n)
 * @complexity θ(n)
 * @complexity O(n)
 * */
SortedSet::~SortedSet() {
    delete[] elems;
}

/**
 * binary search for elem in elems
 *
 * @returns index of elem in set or -1 if elem doesn't exist
 * @complexity Ω(1)
 * @complexity θ(log n)
 * @complexity O(log n)
 * */
int SortedSet::getIndex(TComp elem) const {
    int low = 0, high = len - 1, mid;
    while (low <= high) {
        mid = (low + high) / 2;
        if (elem == elems[mid]) {
            return mid;
        } else if (!r(elem, elems[mid])) //elem > elems[mid]
            low = mid + 1;
        else
            high = mid - 1;
    }

    return -1;
}

