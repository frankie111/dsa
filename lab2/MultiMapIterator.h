#pragma once

#include "MultiMap.h"

class MultiMap;

class MultiMapIterator {
    friend class MultiMap;

private:
    const MultiMap &col;
    Node *currentNode;
    ValueNode *currentVNode;


    explicit MultiMapIterator(const MultiMap &c);

public:
    [[nodiscard]] TElem getCurrent() const;

    [[nodiscard]] bool valid() const;

    void next();

    void first();
};

