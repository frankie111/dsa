#include <exception>
#include "BagIterator.h"
#include "Bag.h"

using namespace std;


/**
 * Constructor
 * @param c - Bag to iterate over
 * @TimeComplexity θ(1)
 */
BagIterator::BagIterator(const Bag &c) : bag(c) {
    first();
}


/**
 * @brief Sets the iterator to the first element of the bag
 * @TimeComplexity-BestCase θ(1)
 * @TimeComplexity-AverageCase θ(1)
 * @TimeComplexity-WorstCase θ(n)
 */
void BagIterator::first() {
    currentPos = 0;
    currentCount = 0;

    // Skip empty positions
    while (currentPos < bag.tableSize && bag.table[currentPos].ct == 0)
        currentPos++;
}

/**
 * @brief Sets the iterator to the next element of the bag
 * @TimeComplexity-BestCase θ(1)
 * @TimeComplexity-AverageCase θ(1)
 * @TimeComplexity-WorstCase θ(n)
 */
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


/**
 * @brief Returns the current element of the iterator
 * @TimeComplexity θ(1)
 */
TElem BagIterator::getCurrent() const {
    if (!valid())
        throw out_of_range("BagIterator::getCurrent: Invalid iterator!");

    return bag.table[currentPos].value;
}

/**
 * @brief Checks if the iterator is valid
 * @return True if the iterator is valid, false otherwise
 * @TimeComplexity θ(1)
 */
bool BagIterator::valid() const {
    return currentPos >= 0 && currentPos < bag.tableSize && currentCount < bag.table[currentPos].ct;
}
