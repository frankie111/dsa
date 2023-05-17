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
    int probe, index, firstEmpty = -1;

    // Find position of element if it exists, or first empty position
    for (probe = 0; probe < tableSize; probe++) {
        index = hash(e, probe);

        if ((table[index].value == DELETED_TELEM || table[index].value == NULL_TELEM)
            && firstEmpty == -1)
            firstEmpty = index;

        if (table[index].value == NULL_TELEM || table[index].value == e)
            break;
    }

    // Add new Item
    if (table[index].value != e) {
        if (firstEmpty != -1)
            index = firstEmpty;

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
    int probe, index;

    // Find index of element if it exists
    for (probe = 0; probe < tableSize; probe++) {
        index = hash(e, probe);

        if (table[index].value == e)
            break;

        if (table[index].value == NULL_TELEM)
            return false;
    }

    // If element exists, decrement count
    if (table[index].value == e) {
        table[index].ct--;

        // If frequency counter is 0, remove Item
        if (table[index].ct == 0) {
            table[index].value = DELETED_TELEM;
            itemCount--;

            // Resize if load factor is too small
            if ((double) itemCount / tableSize < 1 - MAX_LOAD_FACTOR)
                resize(tableSize / GROWTH_FACTOR);
        }

        elementCount--;
//        cout << 1 << " -> " << e << endl;
        return true;
    }
//    cout << 0 << " -> " << e << endl;
    return false;
}


bool Bag::search(TElem e) const {
    int probe, index;

    for (probe = 0; probe < tableSize; probe++) {
        index = hash(e, probe);

        if (table[index].value == e)
            return true;

        if (table[index].value == NULL_TELEM)
            break;
    }

    return false;
}

int Bag::hash(TElem e, int probe) const {
    return hash(e, probe, tableSize);
}

int Bag::hash(TElem e, int probe, int _tableSize) {
    double c1 = 0.5, c2 = 0.5;
    int h1 = abs(e) % _tableSize;
    return (int) (h1 + c1 * probe + c2 * probe * probe) % _tableSize;
}

int Bag::nrOccurrences(TElem e) const {
    int probe, index;

    for (probe = 0; probe < tableSize; probe++) {
        index = hash(e, probe);

        if (table[index].value == e)
            break;

        if (table[index].value == NULL_TELEM)
            break;
    }

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

void Bag::resize(int capacity) {
    int newTableSize = capacity;
    Item *newTable = new Item[newTableSize]{};

    for (int i = 0; i < tableSize; i++) {
        if (table[i].value != NULL_TELEM && table[i].value != DELETED_TELEM) {
            int probe, index;

            // Find first empty position
            for (probe = 0; probe < newTableSize; probe++) {
                index = hash(table[i].value, probe, newTableSize);

                if (newTable[index].value == NULL_TELEM)
                    break;
            }

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

void Bag::printTable() const {
    int ct = 0;
    for (int i = 0; i < tableSize; i++) {
        if (table[i].value == NULL_TELEM)
//            cout << "NULL" << endl;
            ;
        else {
            ct++;
            cout << table[i].value << endl;
        }
    }

    cout << endl << "ct: " << ct << " tableSize: " << tableSize << endl;

//    for (int i = -100; i < 100; i = i + 2) {
//        bool ok = false;
//        for (int j = 0; j < tableSize; j++) {
//            if (table[j].value == i)
//                ok = true;
//        }
//        if (!ok) {
//            cout << "Missing: " << i << endl;
//        }
//    }

    for (int elem = -100; elem <= 100; elem++) {
        int v[256];
        for (int i = 0; i < 256; i++)
            v[i] = 0;

        for (int probe = 0; probe < tableSize; probe++) {
            int index = hash(elem, probe);
//            cout << index << " ";
            v[index]++;
        }

        cout << endl;

        for (int i = 0; i < 256; i++)
            if (v[i] != 1) {
//                cout << v[i] << " " << i << endl;
                cout << elem << " " << i << endl;
            }
    }

}
