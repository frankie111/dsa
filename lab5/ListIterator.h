#pragma once

#include "SortedIndexedList.h"


//DO NOT CHANGE THIS PART
class ListIterator {
    friend class SortedIndexedList;

private:
    const SortedIndexedList &list;
    int curr; //index of the current element

    explicit ListIterator(const SortedIndexedList &list);

public:
    void first();

    void next();

    [[nodiscard]] bool valid() const;

    [[nodiscard]] TComp getCurrent() const;
};

