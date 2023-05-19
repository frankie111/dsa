#include "Bag.h"
#include "BagIterator.h"
#include <exception>
#include <iostream>

using namespace std;

/**
 * @brief Constructor for the Bag class
 * @TimeComplexity θ(n=16)
 */
Bag::Bag() {
    tableSize = 16;
    table = new Item[tableSize]{};
    itemCount = 0;
    elementCount = 0;
}

/**
 * @brief Adds an element to the bag
 * @details If the element already exists in the bag, its count is incremented.
 * @param e Element to be added
 * @TimeComplexity-BestCase θ(1) when the element is already in the bag
 * and is the first element in the probe sequence
 * @TimeComplexity-AverageCase θ(1)
 * @TimeComplexity-WorstCase θ(n) when resize is needed or when you have to traverse the entire table
 */
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


/**
 * @brief Removes an element from the bag
 * @details If the element exists in the bag, its count is decremented.
 * If the count reaches 0, the element is removed.
 * @param e element to remove from bag
 * @returns true if the element was removed, false otherwise
 * @TimeComplexity-BestCase θ(1) when the element is the first element in the probe sequence
 * @TimeComplexity-AverageCase θ(1)
 * @TimeComplexity-WorstCase θ(n) when resize is needed or when you have to traverse the entire table
 */
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
        return true;
    }
    return false;
}

/**
 * @brief Searches for an element in the bag
 * @param e element to search for
 * @returns true if the element exists in the bag, false otherwise
 * @TimeComplexity-BestCase θ(1)
 * @TimeComplexity-AverageCase θ(1)
 * @TimeComplexity-WorstCase θ(n) when you have to traverse the entire table
 */
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

/**
 * @brief Counts the number of occurrences of an element in the bag
 * @param e element to count
 * @TimeComplexity-BestCase θ(1)
 * @TimeComplexity-AverageCase θ(1)
 * @TimeComplexity-WorstCase θ(n)
 */
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

/**
 * @brief Computes the hash of an element.
 * @param e element to hash
 * @param probe iteration number
 * @returns the hash of the element(0..tableSize-1)
 * @TimeComplexity θ(1)
 */
int Bag::hash(TElem e, int probe) const {
    return hash(e, probe, tableSize);
}

/**
 * @brief Computes the hash of an element
 * @param e element to hash
 * @param probe iteration number
 * @param _tableSize size of the hash table
 * @returns the hash of the element(0.._tableSize-1)
 * @TimeComplexity θ(1)
 */
int Bag::hash(TElem e, int probe, int _tableSize) {
    double c1 = 0.5, c2 = 0.5;
    int h1 = abs(e) % _tableSize;
    return (int) (h1 + c1 * probe + c2 * probe * probe) % _tableSize;
}

/**
 * @brief Resize the hash table to a new capacity
 * @param capacity capacity of the new hash table
 * @TimeComplexity θ(n)
 */
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

/**
 * @returns the number of elements in the bag
 * @TimeComplexity θ(1)
 */
int Bag::size() const {
    return elementCount;
}

/**
 * @returns the number of distinct elements / items in the bag
 * @TimeComplexity θ(1)
 */
int Bag::getItemCount() const {
    return itemCount;
}

/**
 * @returns true if the bag is empty, false otherwise
 * @TimeComplexity θ(1)
 */
bool Bag::isEmpty() const {
    return elementCount == 0;
}

/**
 * @brief Creates an iterator for the bag
 * @returns an iterator for the bag
 * @TimeComplexity θ(1)
 */
BagIterator Bag::iterator() const {
    return BagIterator(*this);
}

/**
 * @brief Destructor for the bag
 * @TimeComplexity θ(1)
 */
Bag::~Bag() {
    delete[]table;
}

/**
 * @brief Prints the hash table
 * @TimeComplexity θ(n)
 */
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
}
