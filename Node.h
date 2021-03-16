#pragma once
#include <tuple>

template <class Key, class Value>
struct Node{ 
	Node<Key, Value>* rightNode;
	Node<Key, Value>* leftNode;
	Node<Key, Value>* parent;
	Key key;
	Value value;
	bool color;   // false - black, true - red
	bool isLeaf = false;
	Node() {
			this->leftNode = nullptr;
			this->rightNode = nullptr;
			this->parent = nullptr;
			this->color = false;
			this->isLeaf = true;
	}

	Node(Key k, Value v, Node<Key, Value>* parent = nullptr, Node<Key, Value>* left = nullptr, Node<Key, Value>* right = nullptr) {
		this->key = k;
		this->value = v;
		this->parent = parent;
		this->leftNode = left;
		this->rightNode = right;
		this->color = true;	
	}
};