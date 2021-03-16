#pragma once
#include "Elem.h"

template<class Key,class Value>
class Queue {
private:
    size_t Size;
    Elem<Key,Value>* head;

public:
    Queue();
    ~Queue();
    void Pop_Front();
    void Clear();
    size_t GetSize();
    //Value& operator[] (size_t index);
    Node<Key,Value>* Dequeue();
    void Enqueue(Node<Key, Value>* node);
    Node<Key, Value>* Peek() {
        return this->head->node;
    }
};

template <class Key, class Value>
void Queue<Key, Value>::Enqueue(Node<Key,Value>* node) {
    {
        if (this->head == nullptr) {
            this->head = new Elem<Key,Value>(node);
        }
        else {
            Elem<Key, Value>* cur = this->head;
            while (cur->pnext != nullptr) {
                cur = cur->pnext;
            }
            cur->pnext = new Elem<Key, Value>(node);
        }
        this->Size++;
    }
}

template <class Key, class Value>
Queue<Key, Value>::Queue() {
    this->Size = 0;
    this->head = nullptr;
}

template <class Key, class Value>
Queue<Key, Value>::~Queue() {
    Clear();
}

template <class Key, class Value>
void Queue<Key, Value>::Pop_Front()
{
    Elem<Key, Value>* tmp = this->head;
    this->head = this->head->pnext;
    delete tmp;
    this->Size--;
}

template <class Key, class Value>
Node<Key,Value>* Queue<Key, Value>::Dequeue() {
    Node<Key, Value>* node = this->head->node;
    Pop_Front();
    return node;
}

template <class Key, class Value>
void Queue<Key, Value>::Clear()
{
    while (this->Size > 0) {
        Pop_Front();
    }
}


template <class Key, class Value>
size_t Queue<Key, Value>::GetSize()
{
    return Size;
}



