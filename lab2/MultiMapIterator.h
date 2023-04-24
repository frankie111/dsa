#pragma once

#include "MultiMap.h"

class MultiMap;

class MultiMapIterator {
    friend class MultiMap;

private:
    const MultiMap &col;
    Node *currentNode{};
    ValueNode *currentVNode{};

public:

    explicit MultiMapIterator(const MultiMap &c);

    [[nodiscard]] TElem getCurrent() const;

    void next();

    void first();

    [[nodiscard]] bool valid() const;
};

