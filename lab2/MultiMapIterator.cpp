#include "MultiMapIterator.h"
#include "MultiMap.h"
#include <iostream>


/**
 * Constructor
 * @complexity θ(1)
 */
MultiMapIterator::MultiMapIterator(const MultiMap &c) : col(c) {
    first();
}

/**
 * @returns the current key-value pair
 * @complexity θ(1)
 */
TElem MultiMapIterator::getCurrent() const {
    if (!valid())
        throw out_of_range("MultiMapIterator::getCurrent(): Invalid Node");

    TKey key = currentNode->key;
    TValue val = currentVNode->value;

    return {key, val};
}

/**
 * Move the iterator to the next value
 * @complexity θ(1)
 */
void MultiMapIterator::next() {
    if (!valid())
        throw out_of_range("MultiMapIterator::next(): Invalid Node");

    currentVNode = currentVNode->next;
    if (currentVNode == nullptr) {
        currentNode = currentNode->next;
        if (valid())
            currentVNode = currentNode->info;
    }
}

/**
 * Move the iterator to the first node/value
 * @complexity θ(1)
 */
void MultiMapIterator::first() {
    currentNode = col.head;
    if (currentNode != nullptr)
        currentVNode = currentNode->info;
}

/**
 * @returns true if the current Node is valid, false otherwise
 * @complexity θ(1)
 */
bool MultiMapIterator::valid() const {
    return currentNode != nullptr;
}
