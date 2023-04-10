#include "ValueIterator.h"

ValueIterator::ValueIterator(ValueNode *valueNode) : currentVNode{valueNode} {}

TValue ValueIterator::getCurrent() const {
    return currentVNode->value;
}

bool ValueIterator::valid() const {
    return false;
}

void ValueIterator::next() {

}

void ValueIterator::first() {

}


