#pragma once

#include "MultiMap.h"
#include "ValueIterator.h"

class MultiMap;

class MultiMapIterator {
    friend class MultiMap;

private:
    const MultiMap &col;
    Node *currentNode;
    ValueIterator valueIterator;


public:
    explicit MultiMapIterator(const MultiMap &c);

    [[nodiscard]] TElem getCurrent() const;

    [[nodiscard]] bool valid() const;

    void next();

    void first();
};

