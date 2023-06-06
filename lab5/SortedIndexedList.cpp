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
}

int SortedIndexedList::size() const {
    return elemCount;
}

bool SortedIndexedList::isEmpty() const {
    return elemCount == 0;
}

TComp SortedIndexedList::getElement(int i) const {
    if (i < 0 || i >= elemCount)
        throw std::exception();

    return NULL_TCOMP;
}

TComp SortedIndexedList::remove(int i) {
    if (i < 0 || i >= elemCount)
        throw std::exception();

    if (i == nodes[root].leftCount){
        // Remove root
        if (nodes[root].left == -1 && nodes[root].right == -1){
            TComp removed = nodes[root].info;
            nodes[root].info = NULL_TCOMP;
            root = -1;
            elemCount--;
            return removed;
        }

        // Remove root with one child
        if (nodes[root].left == -1){
            TComp removed = nodes[root].info;
            nodes[root].info = nodes[root].right;
            nodes[root].right = -1;
            elemCount--;
            return removed;
        }

        if (nodes[root].right == -1){
            TComp removed = nodes[root].info;
            nodes[root].info = nodes[root].left;
            nodes[root].left = -1;
            elemCount--;
            return removed;
        }

        // Remove root with two children
        int curr = nodes[root].right;
        while (nodes[curr].left != -1)
            curr = nodes[curr].left;

        TComp removed = nodes[root].info;
        nodes[root].info = nodes[curr].info;
        nodes[curr].info = NULL_TCOMP;
        elemCount--;
        return removed;
    }

    return NULL_TCOMP;
}

int SortedIndexedList::search(TComp e) const {
    return searchRec(root, e);
}

int SortedIndexedList::searchRec(int pos, TComp e) const{
    if (pos == -1)
        return -1;

    if (nodes[pos].info == e)
        return pos;

    if (r(e, nodes[pos].info))
        return searchRec(nodes[pos].left, e);
    else
        return searchRec(nodes[pos].right, e);

}

void SortedIndexedList::add(TComp e) {
    // Add root node
    if (root == -1) {
        root = 0;
        nodes[root] = Node(e, -1, -1, -1, 0);
        elemCount++;
        length = 1;
        return;
    }

    addRec(root, e);

//    int curr = root;
//    Node newNode(e, -1, -1, -1, 0);
//    elemCount++;
//
//    // Add root node
//    if (curr == -1) {
//        root = 0;
//        nodes[root] = newNode;
//        return;
//    }
//
//    // Only root exists, add second node to the left
//    if (nodes[root].left == -1 && r(e, nodes[root].info)) {
//        nodes[root].leftCount = 1;
//        int pos = findFirstEmpty();
//        nodes[pos] = newNode;
//        nodes[pos].parent = root;
//        nodes[head].left = pos;
//        if (pos == length)
//            length++;
//        return;
//    }
//
//    // Only root exists, add second node to the right
//    if (nodes[root].right == -1 && !r(e, nodes[root].info)) {
//        int pos = findFirstEmpty();
//        nodes[pos] = newNode;
//        nodes[pos].parent = root;
//        nodes[root].right = pos;
//        if (pos == length)
//            length++;
//        return;
//    }

}

void SortedIndexedList::addRec(int pos, TComp e) {
    if (pos == -1) {
        int newPos = findFirstEmpty();
        nodes[newPos] = Node(e, -1, -1, -1, 0);
        elemCount++;
        return;
    }

    if (r(e, nodes[pos].info)) {
        nodes[pos].leftCount++;
        addRec(nodes[pos].left, e);
    } else {
        addRec(nodes[pos].right, e);
    }
}

ListIterator SortedIndexedList::iterator() {
    return ListIterator(*this);
}

//destructor
SortedIndexedList::~SortedIndexedList() {
    delete[]nodes;
}

void SortedIndexedList::resize() {
    Node *newNodes = new Node[capacity * GROWTH_FACTOR];
    for (int i = 0; i < capacity; i++)
        newNodes[i] = nodes[i];

    delete[]nodes;
    nodes = newNodes;
    capacity *= GROWTH_FACTOR;
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

    // No empty space -> resize
    resize();

    return findFirstEmpty();
}
