//
// Created by Mircea on 3/31/2023.
//

#include "ExtendedIterator.h"
#include <stdexcept>

using namespace std;

/**
 * Constructor
 * @complexity θ(1)
 *
 * subalgorithm init(it, m, start_index) is:
 * //pre:
 *      m ist ein SortedSet
 *      start_index ist ein positiver int
 * //post:
 *      it ist ein SortedSetIterator für m
 *      it.i <- start_index
 * end_subalgorithm
 * */
ExtendedIterator::ExtendedIterator(const SortedSet &m, int start_index) : multime(m) {
    if (start_index < 0)
        throw std::out_of_range("constructor(): Start index out of range for index" + to_string(start_index));
    i = start_index;
}

/**
 * Set iterator to first position
 * @throws out_of_range exception if set is empty
 *
 * @complexity θ(1)
 *
 * function first(it, multime) is:
 * //pre:
 *      multime ist ein SortedSet
 *      it ist ein SortedSetIterator
 * //post:
 *      it.i <- 0
 * end_function
 * */
void ExtendedIterator::first() {
    if (multime.isEmpty())
        throw std::out_of_range("first(): Index out of range for index 0");
    i = 0;
}

/**
 * Increment current position by step_size
 * @throws exception if step_size \< 1
 * @throws out_of_range exception if next index is invalid
 * @complexity θ(1)
 *
  * function next(it, step_size) is:
 * //pre:
 *      it ist ein SortedSetIterator
 *      step_size ist ein int >= 1
 * //post:
 *      it.i verweist auf das element mit index it.i + step_size
 * //throws: Exception falls step_size oder it nicht gültig
 * end_function
 * */
void ExtendedIterator::next(int step_size) {
    if (step_size < 1)
        throw std::exception();
    if (!valid())
        throw std::out_of_range("next(): Index out of range for index " + to_string(i));
    i += step_size;
}

/**
 * Decrement current position by step_size
 * @throws exception if step_size \< 1
 * @throws out_of_range exception if next index is invalid
 * @complexity θ(1)
 *
 * function previous(it, step_size) is:
 * //pre:
 *      it ist ein SortedSetIterator
 *      step_size ist ein int >= 1
 * //post:
 *      it.i verweist auf das element mit index it.i - step_size
 * //throws: Exception falls step_size oder it nicht gültig
 * end_function
 * */
void ExtendedIterator::previous(int step_size) {
    if (step_size < 1)
        throw std::exception();
    i -= step_size;
    if (!valid())
        throw std::out_of_range("next(): Index out of range for index " + to_string(i));
}


/**
 * @returns element on current position
 * @throws out_of_range exception if index is invalid
 * @complexity θ(1)
 *
 * function getCurrent(it, multime) is:
 * //pre:
 *      multime ist ein SortedSet
 *      it ist ein SortedSetIterator
 * //post:
 *      it.i ist das aktuelle Element aus it
 * //throws: Exception falls it nicht gültig
 * end_function
 * */
TElem ExtendedIterator::getCurrent() {
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
 *
 * function valid(it, multime) is:
 * //pre:
 *      it ist ein SortedSetIterator
 *      multime ist ein SortedSet
 * //post:
 *      Wahr falls it gültig ist, falsch ansonsten
 * end_function
 * */
bool ExtendedIterator::valid() const {
    if (multime.isEmpty())
        return false;
    if (i < 0 || i >= multime.len) {
        return false;
    }
    return true;
}
