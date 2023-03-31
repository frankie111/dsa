#pragma once
//DO NOT INCLUDE SETITERATOR

//DO NOT CHANGE THIS PART
typedef int TElem;
typedef TElem TComp;

typedef bool(*Relation)(TComp, TComp);

#define NULL_TELEM (-11111)

class SortedSetIterator;


class SortedSet {
    friend class SortedSetIterator;
    friend class ExtendedIterator;

private:
    static const int GROWTH_FACTOR = 2;
    int cap;
    int len;
    TComp *elems;
    Relation r;

    [[nodiscard]] int getIndex(TComp elem) const;

    void resize();

public:
    //constructor
    explicit SortedSet(Relation r);

    //adds an element to the sorted set
    //if the element was added, the operation returns true, otherwise (if the element was already in the set)
    //it returns false
    bool add(TComp e);

    //removes an element from the sorted set
    //if the element was removed, it returns true, otherwise false
    bool remove(TComp e);

    //checks if an element is in the sorted set
    [[nodiscard]] bool search(TElem elem) const;

    //returns the number of elements from the sorted set
    [[nodiscard]] int size() const;

    //checks if the sorted set is empty
    [[nodiscard]] bool isEmpty() const;

    //returns an iterator for the sorted set
    [[nodiscard]] SortedSetIterator iterator() const;

    // destructor
    ~SortedSet();

};
