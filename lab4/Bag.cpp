#include "Bag.h"
#include "BagIterator.h"
#include <exception>
#include <iostream>

using namespace std;


Bag::Bag() {
    tableSize = 16;
    table = new Item[tableSize]{};
    itemCount = 0;
    elementCount = 0;
}


void Bag::add(TElem e) {
    int probe = 0;
    int index = hash(e, probe++);

    // Find matching Item or empty slot
    while (table[index].value != NULL_TELEM && table[index].value != e)
        index = hash(e, probe++);

    // Add new Item
    if (table[index].value == NULL_TELEM) {
        table[index].value = e;
        table[index].ct = 1;
        itemCount++;

        // Resize if load factor is too big
        if ((double) itemCount / tableSize > MAX_LOAD_FACTOR)
            resize(tableSize * GROWTH_FACTOR);

    } else// Add existing item
        table[index].ct++;

    elementCount++;
}


bool Bag::remove(TElem e) {
    int probe = 0;
    int index = hash(e, probe++);

    // Find index of element if it exists
    while (table[index].value != NULL_TELEM && table[index].value != e)
        index = hash(e, probe++);

    // If element exists, decrement count
    if (table[index].value == e) {
        table[index].ct--;

        // If frequency counter is 0, remove Item
        if (table[index].ct == 0) {
            table[index].value = NULL_TELEM;
            itemCount--;

            // Resize if load factor is too small
            if ((double) itemCount / tableSize < 1 - MAX_LOAD_FACTOR)
                resize(tableSize / GROWTH_FACTOR);
        }

        elementCount--;
        return true;
    }

    return false;
}


bool Bag::search(TElem e) const {
    int probe = 0;
    int index = hash(e, probe++);

    while (table[index].value != NULL_TELEM && table[index].value != e)
        index = hash(e, probe++);

    return table[index].value == e;
}

int Bag::nrOccurrences(TElem e) const {
    int probe = 0;
    int index = hash(e, probe++);

    while (table[index].value != NULL_TELEM && table[index].value != e)
        index = hash(e, probe++);

    return table[index].value == e ? table[index].ct : 0;
}


int Bag::size() const {
    return elementCount;
}

int Bag::getItemCount() const {
    return itemCount;
}

bool Bag::isEmpty() const {
    return elementCount == 0;
}

BagIterator Bag::iterator() const {
    return BagIterator(*this);
}


int Bag::hash(TElem e, int probe) const {
    int c1 = 0, c2 = 1;
    return (abs(e) + c1 * probe + c2 * probe * probe) % tableSize;
}

void Bag::resize(int capacity) {
    int newTableSize = capacity;
    Item *newTable = new Item[newTableSize]{};

    for (int i = 0; i < tableSize; i++) {
        if (table[i].value != NULL_TELEM) {
            int probe = 0;
            int index = hash(table[i].value, probe++);

            while (newTable[index].value != NULL_TELEM)
                index = hash(table[i].value, probe++);

            newTable[index].value = table[i].value;
            newTable[index].ct = table[i].ct;
        }
    }

    delete[]table;
    table = newTable;
    tableSize = newTableSize;
}

Bag::~Bag() {
    delete[]table;
}

