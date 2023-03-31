#include "SortedSetIterator.h"
#include <stdexcept>

using namespace std;

/**
 * Constructor
 * @complexity θ(1)
 * */
SortedSetIterator::SortedSetIterator(const SortedSet &m) : multime(m) {
    i = 0;
}


/**
 * Set iterator to first position
 * throws out_of_range exception if set is empty
 * @complexity θ(1)
 * */
void SortedSetIterator::first() {
    if (multime.isEmpty())
        throw std::out_of_range("first(): Index out of range for index 0");
    i = 0;
}


/**
 * Increment current position
 * @throws out_of_range exception if next index is invalid
 * @complexity θ(1)
 * */
void SortedSetIterator::next() {
    if (!valid()) {
        throw std::out_of_range("next(): Index out of range for index " + to_string(i));
    }
    i++;
}


/**
 * @returns element on current position
 * @throws out_of_range exception if index is invalid
 * @complexity θ(1)
 * */
TElem SortedSetIterator::getCurrent() {
    if (valid())
        return multime.elems[i];
    else
        throw std::out_of_range("getCurrent(): Index out of range for index " + to_string(i));

    return NULL_TELEM;
}


/**
 * Check if current index is valid
 *
 * @returns true if index is valid, false otherwise
 * @complexity θ(1)
 * */
bool SortedSetIterator::valid() const {
    if (multime.isEmpty())
        return false;
    if (i < 0 || i >= multime.len) {
        return false;
    }
    return true;
}

