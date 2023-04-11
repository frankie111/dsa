#include "ValueIterator.h"
#include <iostream>

ValueIterator::ValueIterator(Node *node) : currentNode(node), currentVNode{node->info} {}

TValue ValueIterator::getCurrent() const {
    if (!valid())
        throw out_of_range("ValueIterator::getCurrent(): Value Node out of range");

    return currentVNode->value;
}

bool ValueIterator::valid() const {
    return currentVNode != nullptr;
}

void ValueIterator::next() {
    currentVNode = currentVNode->next;
}

void ValueIterator::first() {
    currentVNode = currentNode->info;
}

void ValueIterator::setCurrentNode(Node *node) {
    currentNode = node;
    currentVNode = node->info;
}
