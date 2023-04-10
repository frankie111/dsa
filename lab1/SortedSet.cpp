#include "SortedSet.h"
#include "SortedSetIterator.h"
#include <iostream>

/**
 * Constructor
 * @param r relation for sorting the set
 * @complexity θ(1)
 * */
SortedSet::SortedSet(Relation r) {
    cap = 1;
    len = 0;
    elems = new TComp[1]{0};
    this->r = r;
}


/**
 * Add elem to set
 * @param elem object of type TComp to be added to the set
 * @returns true if element was added, false otherwise
 * @complexityΩ θ(1) \n elem is found in the middle of the set
 * @complexityθ θ(n)
 * @complexityO θ(n)
 * */
bool SortedSet::add(TComp elem) {
    if (search(elem))
        return false;

    // Resize array if needed
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
 * @complexityΩ θ(1) \n No resize needed
 * @complexityθ θ(n) \n
 * @complexityO θ(n) \n Performs exactly n steps if resize is needed
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
 * Remove elem from set \n\n
 *
 * Find index of elem in set and shift all elements after that
 * by 1 position to the left
 *
 * @param elem element to be removed
 * @returns true if elem was removed, false otherwise
 * @complexityΩ θ(log n) \n element not found
 * @complexityθ θ(n)
 * @complexityO θ(n)
 * */
bool SortedSet::remove(TComp elem) {
    int pos = getIndex(elem);

    if (pos != -1) {
        for (int i = pos; i < len; i++)
            elems[i] = elems[i + 1];
        len--;

        // Resize if threshold is met
        resize();
        return true;
    }
    return false;
}


/**
 * @returns length of set
 *
 * @complexity θ(1)
 * */
int SortedSet::size() const {
    return len;
}


/**
 * return true if set is empty, false otherwise
 *
 * @complexity θ(1)
 * */
bool SortedSet::isEmpty() const {
    return len == 0;
}


/**
 * return an iterator for this set
 * @complexity θ(1)
 * */
SortedSetIterator SortedSet::iterator() const {
    return SortedSetIterator(*this);
}


/**
 * Destructor
 *
 * @complexity θ(n) \n performs exactly n steps
 * */
SortedSet::~SortedSet() {
    delete[] elems;
}


/**
 * binary search for elem in elems
 * @param elem the element to search for
 *
 * @returns true if elem was found, false otherwise
 * @complexityΩ θ(1) \n elem found at middle position
 * @complexityθ θ(log n)
 * @complexityO θ(log n)
 * */
bool SortedSet::search(TComp elem) const {
    return getIndex(elem) != -1;
}


/**
 * binary search for elem in elems
 * @param elem the element to search for
 *
 * @returns index of elem in set or -1 if elem doesn't exist
 * @complexityΩ θ(1) \n elem found at middle position
 * @complexityθ θ(log n)
 * @complexityO θ(log n)
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

