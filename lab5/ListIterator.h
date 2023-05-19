#pragma once

#include "SortedIndexedList.h"


//DO NOT CHANGE THIS PART
class ListIterator {
    friend class SortedIndexedList;

private:
    const SortedIndexedList &list;
    int curr; //index of the current element

    ListIterator(const SortedIndexedList &list);

public:
    void first();

    void next();

    bool valid() const;

    TComp getCurrent() const;
};

