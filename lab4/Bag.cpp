#include "Bag.h"
#include "BagIterator.h"
#include <exception>
#include <iostream>

using namespace std;


Bag::Bag() {
    tableSize = 16;
    table = new Item[tableSize]{};
    count = 0;
}


void Bag::add(TElem e) {
    int probe = 0;
    int index = hash(e, probe++);

    // Find matching Item or empty slot
    while (table[index].value != NULL_TELEM && table[index].value != e) {
        index = hash(e, probe);
        probe++;
    }

    // Add new Item
    if (table[index].value == NULL_TELEM) {
        table[index].value = e;
        table[index].ct = 1;
        count++;
    } else { // Add existing item
        table[index].ct++;
    }
}


bool Bag::remove(TElem e) {
    int probe = 0;
    int index = hash(e, probe++);

    // Find index of element if it exists
    while (table[index].value != NULL_TELEM && table[index].value != e) {
        index = hash(e, probe);
        probe++;
    }

    // If element exists, decrement counter
    if (table[index].value == e) {
        table[index].ct--;

        // If frequency counter is 0, remove Item
        if (table[index].ct == 0) {
            table[index].value = NULL_TELEM;
            count--;
        }

        return true;
    }

    return false;
}


bool Bag::search(TElem elem) const {
    //TODO - Implementation
    return false;
}

int Bag::nrOccurrences(TElem elem) const {
    //TODO - Implementation
    return 0;
}


int Bag::size() const {
    //TODO - Implementation
    return 0;
}


bool Bag::isEmpty() const {
    //TODO - Implementation
    return 0;
}

BagIterator Bag::iterator() const {
    return BagIterator(*this);
}


Bag::~Bag() {
    delete[]table;
}

int Bag::hash(TElem e, int probe) const {
    int c1 = 0, c2 = 1;
    return (abs(e) + c1 * probe + c2 * probe * probe) % tableSize;
}

void Bag::resize(int capacity) {

}

