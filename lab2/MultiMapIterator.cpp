#include "MultiMapIterator.h"
#include "MultiMap.h"


MultiMapIterator::MultiMapIterator(const MultiMap &c) : col(c) {
    currentNode = col.head;
    if (currentNode != nullptr)
        valueIterator = ValueIterator(col.head->info);
}

TElem MultiMapIterator::getCurrent() const {
    TKey key = currentNode->key;
    TValue val = currentVNode->value;

    return {key, val};
}

bool MultiMapIterator::valid() const {
    if (currentNode == nullptr)
        return false;

    return true;
}

void MultiMapIterator::next() {

}

void MultiMapIterator::first() {
    currentNode = col.head;
    currentVNode = col.head->info;
}

