#pragma once
#include "Node.h"
template<class Key,class Value>
class Elem {
public:
    Elem* pnext;
    Node<Key,Value>* node;
    Elem(Node<Key, Value>* node, Elem* pNext = nullptr) {
        this->node = node;
        this->pnext = pNext;
    }
};