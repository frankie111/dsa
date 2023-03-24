#include "SortedSetIterator.h"
#include <stdexcept>

using namespace std;

/**
 * Constructor
 * @complexity Ω(1)
 * @complexity θ(1)
 * @complexity O(1)
 * */
SortedSetIterator::SortedSetIterator(const SortedSet &m) : multime(m) {
    i = 0;
}


/**
 * Set iterator to first position
 * @complexity Ω(1)
 * @complexity θ(1)
 * @complexity O(1)
 * */
void SortedSetIterator::first() {
    if (multime.isEmpty())
        throw std::out_of_range("first(): Index out of range for index " + to_string(i));
    i = 0;
}


/**
 * Increment current position
 * @complexity Ω(1)
 * @complexity θ(1)
 * @complexity O(1)
 * */
void SortedSetIterator::next() {
    if (!valid()) {
        throw std::out_of_range("next(): Index out of range for index " + to_string(i));
    }
    i++;
}


/**
 * Return element on current position
 * @complexity Ω(1)
 * @complexity θ(1)
 * @complexity O(1)
 * */
TElem SortedSetIterator::getCurrent() {
    if (valid())
        return multime.elems[i];
    else
        throw std::out_of_range("getCurrent(): Index out of range for index " + to_string(i));

//    return NULL_TELEM;
}


/**
 * Check if current index is valid
 * @complexity Ω(1)
 * @complexity θ(1)
 * @complexity O(1)
 * */
bool SortedSetIterator::valid() const {
    if (multime.isEmpty())
        return false;
    if (i < 0 || i >= multime.len) {
        return false;
    }
    return true;
}

