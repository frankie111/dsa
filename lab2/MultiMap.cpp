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
 * If the key is found, append to Node, else create a new Node.
 * @param k key of currentNode to be created/modified
 * @param v value to be added to new/modified currentNode
 * @complexity θ(n)
 * */
void MultiMap::add(TKey k, TValue v) {
    Node *aux = searchNode(k);
    if (aux == nullptr)
        addNewKey(k, v);
    else
        addValue(aux, v);
}

/**
 * Add a new key/currentNode to the multimap
 * @param k key to be added to new Node
 * @param v value to be added to new Node
 * @complexity θ(1)
 */
void MultiMap::addNewKey(TKey k, TValue v) {
    if (head == nullptr)
        head = new Node(k, new ValueNode(v, nullptr), nullptr);
    else {
        // Add new node right after head
        Node *newNode = new Node(k, new ValueNode(v, nullptr), head->next);
        head->next = newNode;
    }
}

/**
 * Add a new value to an existing Node
 * @param node to be edited
 * @param v value to be added to Node
 * @complexity θ(1)
 */
void MultiMap::addValue(Node *node, TValue v) {
    ValueNode *vNode = node->info;
    auto *newNode = new ValueNode(v, vNode->next);
    vNode->next = newNode;
}

/**
 * Removes a key-value pair from the multimap.
 * If the currentNode doesn't have a value associated, currentNode gets removed.
 * @returns true if the pair was removed, false otherwise
 * @param k key of currentNode to be removed/modified
 * @param v value to be removed
 * @complexity θ(n)
 */
bool MultiMap::remove(TKey k, TValue v) {
    Node *aux = searchNode(k);
    if (aux == nullptr)
        return false;

    bool removed = removeValueFromNode(aux, v);

    // If the Node doesn't have any more values remove it
    if (aux->info == nullptr)
        removeNode(aux);

    return removed;
}

/**
 * Remove a value from a Node if found
 * @param node to modify
 * @param v value to be removed
 * @returns true if value was removed, false otherwise
 * @complexity θ(n)
 */
bool MultiMap::removeValueFromNode(Node *node, TValue v) {
    ValueNode *prev = nullptr;
    ValueNode *curr;
    for (curr = node->info; curr != nullptr; curr = curr->next) {
        if (curr->value == v)
            break;

        prev = curr;
    }

    // Value wasn't found
    if (curr == nullptr)
        return false;

    // if the value to remove is found in the head ValueNode, update the head
    if (prev == nullptr)
        node->info = curr->next;
    else
        prev->next = curr->next;

    delete curr;
    return true;
}

/**
 * Remove a Node from the multimap
 * @param node to be removed
 * @complexity θ(n)
 */
void MultiMap::removeNode(Node *node) {
    Node *prev = nullptr;
    for (Node *curr = head; curr != nullptr; curr = curr->next) {
        if (curr == node)
            break;

        prev = curr;
    }

    // if the Node to remove is the head, update the head
    if (prev == nullptr)
        head = node->next;
    else
        prev->next = node->next;

    delete node;
}

/**
 * Removes a node and all it's associated values
 * @param k key to be searched
 * @return true if the node was found and removed, false otherwise
 * @complexity θ(n)
 *
 * function removeNodeValues(mm, k) is:
 * ------------------------------------------------------------------
 *  //pre:
 *      mm ist ein MultiMap
 *      k ist ein Tkey
 *  //post:
 *      Der Knoten mit dem Key = k aus mm wird gelöscht zusammen mit
 *      sein SLL von Value Knoten
 *
 *      Wahr falls der Knoten gefunden wurde, falsch ansonsten
 *-------------------------------------------------------------------
 *      currNode <- searchNode(mm, k)
 *      if currNode = NIL then
 *          removeNodeValues <- false
 *      endif
 *
 *      vNode <- currNode.info
 *      while vNode != NIL
 *          aux <- vNode;
 *          vNode <- vNode.next
 *          free(aux)
 *      endwhile
 *
 *      removeNode(currNode)
 *      removeNodeValues <- true
 *
 * end_function
 *
 */
bool MultiMap::removeNodeValues(TKey k) {
    Node *currNode = searchNode(k);
    if (currNode == nullptr)
        return false;

    // Delete all values from the current node
    ValueNode *vNode = currNode->info;
    while (vNode != nullptr) {
        ValueNode *aux = vNode;
        vNode = vNode->next;
        delete aux;
    }

    //Delete the current node
    removeNode(currNode);

    return true;
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
    while (vNode != nullptr) {
        result.push_back(vNode->value);
        vNode = vNode->next;
    }

    return result;
}

/**
 * Search a Node by it's key
 * @param k key to look for
 * @returns a pointer to the found Node or nullptr
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

/**
 * @returns the number of values associated to a node
 * @param node
 * @complexity θ(n)
 */
int MultiMap::countValues(Node *node) {
    ValueNode *vNode = node->info;
    int ct = 0;
    while (vNode != nullptr) {
        ct++;
        vNode = vNode->next;
    }
    return ct;
}

/**
 * Check whether the multimap is empty
 * @returns true if head is null, false otherwise
 * @complexity θ(1)
 */
bool MultiMap::isEmpty() const {
    return head == nullptr;
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
 * Print values of specific Node
 * @param node
 */
void MultiMap::printValues(Node *node) {
    ValueNode *vNode = node->info;

    while (vNode != nullptr) {
        cout << "  " << vNode->value << endl;
        vNode = vNode->next;
    }

}

/**
 * @returns an iterator for this MultiMap
 * @complexity θ(1)
 */
MultiMapIterator MultiMap::iterator() const {
    return MultiMapIterator(*this);
}

/**
 * Delete all values from currentNode
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

