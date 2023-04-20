#include "MultiMapIterator.h"
#include "MultiMap.h"
#include <iostream>


MultiMapIterator::MultiMapIterator(const MultiMap &c) : col(c) {
    currentNode = col.head;
    if (currentNode != nullptr)
        currentVNode = currentNode->info;
}

TElem MultiMapIterator::getCurrent() const {
    if (!valid())
        throw out_of_range("MultiMapIterator::getCurrent(): Invalid Node");

    TKey key = currentNode->key;
    TValue val = currentVNode->value;

    return {key, val};
}

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

void MultiMapIterator::first() {
    currentNode = col.head;
    if (currentNode != nullptr)
        currentVNode = currentNode->info;
}

bool MultiMapIterator::valid() const {
    return currentNode != nullptr;
}
