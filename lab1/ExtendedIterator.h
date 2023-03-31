#pragma once

#include "SortedSet.h"
#ifndef LAB1_EXTENDEDITERATOR_H
#define LAB1_EXTENDEDITERATOR_H


class ExtendedIterator {
    friend class SortedSet;

private:
    const SortedSet &multime;
    int i;

    explicit ExtendedIterator(const SortedSet &m, int start_index);

public:
    void first();

    void next(int step_size);

    void previous(int step_size);

    TElem getCurrent();

    [[nodiscard]] bool valid() const;
};


#endif //LAB1_EXTENDEDITERATOR_H
