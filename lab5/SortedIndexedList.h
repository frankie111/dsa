#pragma once
//DO NOT INCLUDE LISTITERATOR

//DO NOT CHANGE THIS PART
class ListIterator;

typedef int TComp;

typedef bool (*Relation)(TComp, TComp);

#define NULL_TCOMP -11111

struct Node {
    TComp info = NULL_TCOMP;
    int left = -1;
    int right = -1;
    int parent = -1;
    int leftCount = 0;
};

class SortedIndexedList {
private:
    friend class ListIterator;

private:
    Node *nodes;
    int root;
    int capacity;
    int length; // size of array
    int elemCount;
    int firstEmpty;
    Relation r;

    const int GROWTH_FACTOR = 2;

    int findFirstEmpty();

    void resize();

public:
    // constructor
    explicit SortedIndexedList(Relation r);

    // returns the size of the list
    [[nodiscard]] int size() const;

    //checks if the list is empty
    [[nodiscard]] bool isEmpty() const;

    // returns an element from a position
    //throws exception if the position is not valid
    [[nodiscard]] TComp getElement(int pos) const;

    // adds an element to a given position
    //throws an exception if the position is not valid
    void add(TComp e);

    void addRec(int pos, TComp e);

    // removes an element from a given position
    //returns the removed element
    //throws an exception if the position is not valid
    TComp remove(int pos);

    [[nodiscard]] int searchRec(int pos, TComp e) const;

    // searches for an element and returns the first position where the element appears or -1 if the element is not in the list
    [[nodiscard]] int search(TComp e) const;

    // returns an iterator set to the first element of the list or invalid if the list is empty
    ListIterator iterator();

    //destructor
    ~SortedIndexedList();

};
