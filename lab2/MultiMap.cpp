#include "MultiMap.h"
#include "MultiMapIterator.h"
#include <exception>
#include <iostream>

using namespace std;


/**
 * Constructor
 * @complexity θ(1)
 */
MultiMap::MultiMap() {
    head = nullptr;
}

/**
 * Add a key-value pair to the multimap.
 * If the key is found, append to node, else create a new node.
 * @param k key of node to be created/modified
 * @param v value to be added to new/modified node
 * @complexity θ(n)
 * */
void MultiMap::add(TKey k, TValue v) {
    Node *aux = searchNode(k);
    if (aux == nullptr)
        addNewKey(k, v);
    else
        addValueToEnd(aux, v);
}

/**
 * Add a new key/node to the multimap
 * @param k key to be added to new node
 * @param v value to be added to new node
 * @complexity θ(n)
 */
void MultiMap::addNewKey(TKey k, TValue v) {
    if (head == nullptr)
        head = new Node(k, new ValueNode(v, nullptr), nullptr);
    else {
        Node *newNode = new Node(k, new ValueNode(v, nullptr), nullptr);
        Node *tail = head;
        while (tail->next != nullptr)
            tail = tail->next;

        tail->next = newNode;
    }
}

/**
 * Add a new value to an existing node
 * @param node to be edited
 * @param v value to be added to node
 * @complexity θ(n)
 */
void MultiMap::addValueToEnd(Node *node, TValue v) {
    ValueNode *vNode = node->info;
    while (vNode->next != nullptr)
        vNode = vNode->next;

    vNode->next = new ValueNode(v, nullptr);
}

/**
 * Removes a key-value pair from the multimap.
 * If the node doesn't have a value associated, node gets removed.
 * @returns true if the pair was removed, false otherwise
 * @param k key of node to be removed/modified
 * @param v value to be removed
 * @complexity θ(n)
 */
bool MultiMap::remove(TKey k, TValue v) {
    Node *aux = searchNode(k);
    if (aux == nullptr)
        return false;

    bool removed = removeValueFromNode(aux, v);
    if (aux->info == nullptr)
        removeNode(aux);

    return removed;
}

/**
 * Remove a node from the multimap
 * @param node to be removed
 * @complexity θ(n)
 */
void MultiMap::removeNode(Node *node) {
    Node *last = head;
    Node *current = head->next;

    do {
        if (current == node) {
            last->next = current->next;
            delete current;
            return;
        }

        last = current;
        current = current->next;
    } while (current->next != nullptr);
}

/**
 * Remove a value from a node if found
 * @param node to modify
 * @param v value to be removed
 * @returns true if value was removed, false otherwise
 * @complexity θ(n)
 */
bool MultiMap::removeValueFromNode(Node *node, TValue v) {

    return false;
}

/**
 * @returns the vector of values associated to a key.
 * If the key is not found, the vector is empty.
 * @param k key to look for
* @complexity θ(n)
 */
vector<TValue> MultiMap::search(TKey k) const {
    Node *aux = searchNode(k);
    vector<TValue> result{};

    if (aux == nullptr)
        return result;

    ValueNode *vNode = aux->info;
    while (vNode->next != nullptr) {
        result.push_back(vNode->value);
        vNode = vNode->next;
    }

    return result;
}

/**
 * Search a node by it's key
 * @param k key to look for
 * @returns a pointer to the found node or nullptr
* @complexity θ(n)
 */
Node *MultiMap::searchNode(TKey k) const {
    Node *aux = head;

    while (aux != nullptr)
        if (aux->key == k)
            return aux;
        else
            aux = aux->next;

    return nullptr;
}

/**
 * @returns the number of key-value pairs
 * @complexity θ(n)
 */
int MultiMap::size() const {
    Node *aux = head;
    int ct = 0;
    while (aux != nullptr) {
        ct += countValues(aux);
        aux = aux->next;
    }

    return ct;
}

int MultiMap::countValues(Node *node) {
    ValueNode *vNode = node->info;
    int ct = 0;
    while (vNode != nullptr) {
        ct++;
        vNode = vNode->next;
    }
    return ct;
}

//MultiMapIterator MultiMap::iterator() const {
//    return MultiMapIterator(*this);

/**
 * Check whether the multimap is empty
 * @returns true if head is null, false otherwise
 * @complexity θ(1)
 */
bool MultiMap::isEmpty() const {
    return head == nullptr;
}

//}

/**
 * Destructor
 * @complexity θ(n)
 */
MultiMap::~MultiMap() {
    while (head != nullptr) {
        Node *aux = head;
        head = head->next;
        deleteValues(aux);
        delete aux;
    }
}

/**
 * Delete all values from node
 * @param node
 * @complexity θ(n)
 */
void MultiMap::deleteValues(Node *node) {
    ValueNode *vNode = node->info;
    while (vNode != nullptr) {
        ValueNode *aux = vNode;
        vNode = vNode->next;
        delete aux;
    }
}

/**
 * Print MultiMap
 */
void MultiMap::print() const {
    Node *node = head;
    if (node == nullptr) {
        cout << "Multimap is empty" << endl;
        return;
    }

    while (node != nullptr) {
        cout << node->key << ":\n";
        printValues(node);
        node = node->next;
    }

}

/**
 * Print values of specific node
 * @param node
 */
void MultiMap::printValues(Node *node) {
    ValueNode *vNode = node->info;

    while (vNode != nullptr) {
        cout << "  " << vNode->value << endl;
        vNode = vNode->next;
    }

}

