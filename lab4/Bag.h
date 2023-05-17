#pragma once
//DO NOT INCLUDE BAGITERATOR
#include <iostream>

//DO NOT CHANGE THIS PART
#define NULL_TELEM (-1111111)
#define DELETED_TELEM (-2222222)
typedef int TElem;

class BagIterator;

struct Item {
    TElem value{NULL_TELEM};
    int ct{0};
};

class Bag {

private:
    Item *table; // Dynamic array of bag items
    int tableSize; // Size of dynamic array
    int itemCount; // Number of distinct items in bag
    int elementCount; // Number of elements in bag

    const int GROWTH_FACTOR = 2;
    const double MAX_LOAD_FACTOR = 0.75;

    //DO NOT CHANGE THIS PART
    friend class BagIterator;

    [[nodiscard]] int hash(TElem e, int probe) const;

    [[nodiscard]] static int hash(TElem e, int probe, int _tableSize) ;

    void resize(int capacity);

public:

    //constructor
    Bag();

    void printTable() const;

    //adds an element to the bag
    void add(TElem e);

    //removes one occurrence of an element from a bag
    //returns true if an element was removed, false otherwise (if e was not part of the bag)
    bool remove(TElem e);

    //checks if an element appears is the bag
    [[nodiscard]] bool search(TElem e) const;

    //returns the number of occurrences for an element in the bag
    [[nodiscard]] int nrOccurrences(TElem e) const;

    //returns the number of elements from the bag
    [[nodiscard]] int size() const;

    //returns the number of distinct items from the bag
    [[nodiscard]] int getItemCount() const;

    //returns an iterator for this bag
    [[nodiscard]] BagIterator iterator() const;

    //checks if the bag is empty
    [[nodiscard]] bool isEmpty() const;

    //destructor
    ~Bag();
};