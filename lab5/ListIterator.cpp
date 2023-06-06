#include "ListIterator.h"
#include "SortedIndexedList.h"
#include <iostream>

using namespace std;

ListIterator::ListIterator(const SortedIndexedList &list) : list(list) {
    curr = list.root;
    // Find the leftmost node
    while (curr != -1 && list.nodes[curr].left != -1)
        curr = list.nodes[curr].left;
}

void ListIterator::first() {
    curr = list.root;
    // Find the leftmost node
    while (curr != -1 && list.nodes[curr].left != -1)
        curr = list.nodes[curr].left;
}

void ListIterator::next() {
    if (!valid())
        throw std::exception();

    // If the current node has a right child, go to it and then find the leftmost node
    if (list.nodes[curr].right != -1) {
        curr = list.nodes[curr].right;
        while (list.nodes[curr].left != -1)
            curr = list.nodes[curr].left;
    } else {
        // If the current node doesn't have a right child, go up until the current node is a left child
        while (list.nodes[curr].parent != -1 && list.nodes[list.nodes[curr].parent].right == curr)
            curr = list.nodes[curr].parent;
        curr = list.nodes[curr].parent;
    }
}

bool ListIterator::valid() const {
    return curr != -1;
}

TComp ListIterator::getCurrent() const {
    return list.nodes[curr].info;
}
