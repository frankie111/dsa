#include "MultiMapIterator.h"
#include "MultiMap.h"
#include <iostream>


MultiMapIterator::MultiMapIterator(const MultiMap &c) : col(c) {
    currentNode = col.head;
    if (currentNode != nullptr)
        valueIterator = ValueIterator(col.head);
}

TElem MultiMapIterator::getCurrent() const {
    if (!valid())
        throw out_of_range("MultiMapIterator::getCurrent(): Node out of range");

    TKey key = currentNode->key;
    TValue val = valueIterator.getCurrent();

    return {key, val};
}

bool MultiMapIterator::valid() const {
    return currentNode != nullptr;
}

void MultiMapIterator::next() {
    valueIterator.next();
    if (!valueIterator.valid()) {
        currentNode = currentNode->next;
        if (currentNode != nullptr)
            valueIterator.setCurrentNode(currentNode);
    }
}

void MultiMapIterator::first() {
    currentNode = col.head;
    valueIterator.first();
}

