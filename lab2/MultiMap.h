#pragma once

#include<vector>
#include<utility>
//DO NOT INCLUDE MultiMapIterator

using namespace std;

//DO NOT CHANGE THIS PART
typedef int TKey;
typedef int TValue;
//typedef int TElem;
typedef std::pair<TKey, TValue> TElem;
#define NULL_TVALUE -111111
#define NULL_TELEM pair<int,int>(-111111, -111111)

class MultiMapIterator;

struct ValueNode {
    TValue value{NULL_TVALUE};
    ValueNode *next{nullptr};
};

struct Node {
    TKey key{0};
    ValueNode *info{nullptr};
    Node *next{nullptr};
};

class MultiMap {
    friend class MultiMapIterator;

private:
    Node *head;

    //returns a pointer to currentNode with specific key or nullptr
    [[nodiscard]] Node *searchNode(TKey k) const;

    void addNewKey(TKey k, TValue v);

    static void addValue(Node *node, TValue v);

    static bool removeValueFromNode(Node *node, TValue v);

    void removeNode(Node *node);

    //delete all values from a currentNode
    static void deleteValues(Node *node);

    static void printValues(Node *node);

    static int countValues(Node *node);

public:
    //constructor
    MultiMap();

    //adds a key value pair to the multimap
    void add(TKey k, TValue v);

    //removes a key value pair from the multimap
    //returns true if the pair was removed (if it was in the multimap) and false otherwise
    bool remove(TKey k, TValue v);

    //removes a Node and all the values associated with it
    bool removeNodeValues(TKey k);

    //returns the vector of values associated to a key. If the key is not in the MultiMap, the vector is empty
    [[nodiscard]] vector<TValue> search(TKey k) const;

    //returns the number of pairs from the multimap
    [[nodiscard]] int size() const;

    //checks whether the multimap is empty
    [[nodiscard]] bool isEmpty() const;

    //returns an iterator for the multimap
    [[nodiscard]] MultiMapIterator iterator() const;

    void print() const;

    //descturctor
    ~MultiMap();

};

