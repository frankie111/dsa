#ifndef LAB2_VALUEITERATOR_H
#define LAB2_VALUEITERATOR_H


#include "MultiMap.h"

class ValueIterator {
private:
    friend class MultiMap;
    ValueNode *currentVNode;

public:
    explicit ValueIterator(ValueNode *valueNode);

    TValue getCurrent() const;

    bool valid() const;

    void next();

    void first();
};


#endif //LAB2_VALUEITERATOR_H
