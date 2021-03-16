#pragma once
#include "Queue.h"
// Стандартный класс итератора
template <class Key, class Value>
class Iterator {
public:
	virtual Node<Key,Value>* next() = 0;
	virtual bool has_next() = 0;
};


// Итератор для обхода в ширину
template <class Key, class Value>
class bft_iterator : public Iterator<Key,Value> {
private:
	Node<Key, Value>* current;
	Queue<Key,Value> NodeQueue;
public:
	bft_iterator(Node<Key, Value>* start) {
		current = start;
		if (current != nullptr) {
			NodeQueue.Enqueue(current);
		}
		else {
			throw std::out_of_range("this tree is empty\n");
		}
	}

	Node<Key,Value>* next() override {
		if (NodeQueue.GetSize() > 0) {
			current = NodeQueue.Dequeue();
			if (!current->leftNode->isLeaf) {
				NodeQueue.Enqueue(current->leftNode);
			}
			if (!current->rightNode->isLeaf) {
				NodeQueue.Enqueue(current->rightNode);
			}
			return current;
		}
		else {
			
			throw std::out_of_range("No more elements\n");
		}
	}

	bool has_next() override {
		return !current->isLeaf;
	}
};