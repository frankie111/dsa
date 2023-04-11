#ifndef LAB2_VALUEITERATOR_H
#define LAB2_VALUEITERATOR_H


#include "MultiMap.h"

using namespace std;

class ValueIterator {
private:
    friend class MultiMap;

    Node *currentNode;
    ValueNode *currentVNode;

public:
    ValueIterator() = default;

    explicit ValueIterator(Node *node);

    [[nodiscard]] TValue getCurrent() const;

    [[nodiscard]] bool valid() const;

    void next();

    void first();

    void setCurrentNode(Node *node);
};


#endif //LAB2_VALUEITERATOR_H
