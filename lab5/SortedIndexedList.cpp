#include "ListIterator.h"
#include "SortedIndexedList.h"
#include <iostream>

using namespace std;

#include <exception>

SortedIndexedList::SortedIndexedList(Relation r) {
    this->r = r;
    capacity = 20;
    length = 0;
    elemCount = 0;
    nodes = new Node[capacity];
    root = -1;
    firstEmpty = 0;
    head = -1;
}

int SortedIndexedList::size() const {
    return elemCount;
}

bool SortedIndexedList::isEmpty() const {
    return elemCount == 0;
}

TComp SortedIndexedList::getElement(int i) const {
    //TODO - Implementation
    return NULL_TCOMP;
}

TComp SortedIndexedList::remove(int i) {
    //TODO - Implementation
    return NULL_TCOMP;
}

int SortedIndexedList::search(TComp e) const {
    //TODO - Implementation
    return 0;
}

void SortedIndexedList::add(TComp e) {
    int curr = head;
    Node newNode(e, -1, -1, -1, 0);
    elemCount++;

    // Add root node
    if (curr == -1) {
        head = 0;
        nodes[head] = newNode;
        return;
    }

    // Only root exists, add second node to the left
    if (nodes[head].left == -1 && r(e, nodes[head].info)) {
        nodes[head].leftCount = 1;
        int pos = findFirstEmpty();
        nodes[pos] = newNode;
        nodes[pos].parent = head;
        nodes[head].left = pos;
        if (pos == length)
            length++;
        return;
    }

    // Only root exists, add second node to the right
    if (nodes[head].right == -1 && !r(e, nodes[head].info)) {
        int pos = findFirstEmpty();
        nodes[pos] = newNode;
        nodes[pos].parent = head;
        nodes[head].right = pos;
        if (pos == length)
            length++;
        return;
    }

}

ListIterator SortedIndexedList::iterator() {
    return ListIterator(*this);
}

//destructor
SortedIndexedList::~SortedIndexedList() {
    delete[]nodes;
}

int SortedIndexedList::findFirstEmpty() {
    if (firstEmpty != -1)
        return firstEmpty = -1;

    for (int i = length; i < capacity; i++) {
        if (nodes[i].info == NULL_TCOMP)
            return i;
    }

    for (int i = 0; i < length; i++)
        if (nodes[i].info == NULL_TCOMP)
            return i;

    return -1;
}
