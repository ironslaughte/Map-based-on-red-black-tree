#pragma once
#include "iterator.h"
#include "List.h"
/// Description
/// node - element to insert/delete
/// color = fasle - Black
/// color = true - Red
/// g - grandParent
/// gS - grandSon
/// s - sibling


template<class Key, class Value>
Node<Key,Value>* find_the_biggest(Node<Key, Value>* node) {
	Node<Key, Value>* newNode = (node->leftNode->isLeaf) ? node->rightNode : node->leftNode;
	if (newNode == node->leftNode) {
		if (!newNode->rightNode->isLeaf) {
			while (!newNode->rightNode->isLeaf) {
				newNode = newNode->rightNode;
			}
			return newNode;
		}
		else return newNode;
	}
	else {
		if (!newNode->leftNode->isLeaf) {
			while (!newNode->leftNode->isLeaf) {
				newNode = newNode->leftNode;
			}
			return newNode;
		}
		else return newNode;
	}

}

template<class Key, class Value>
bool has_one_leaf(Node<Key, Value>* node) {
	if (node == nullptr) {
		throw std::invalid_argument("null pointer exception");
	}
	if (node->leftNode->isLeaf && node->rightNode->isLeaf) return false;
	if (!node->leftNode->isLeaf && !node->rightNode->isLeaf) return false; 
	return true;
}


/// Block of tree turn
/// 
template<class Key, class Value>
void rotate_left(Node<Key, Value>* node) {   
	Node<Key, Value>* piviot = node->rightNode;
	piviot->parent = node->parent;
	if (node->parent != nullptr) {
		if (node->parent->leftNode == node) {
			node->parent->leftNode = piviot;
		}
		else {
			node->parent->rightNode = piviot;
		}
	}
	node->rightNode = piviot->leftNode;
	if (!piviot->leftNode->isLeaf) {
		piviot->leftNode->parent = node;
	}
	node->parent = piviot;
	piviot->leftNode = node;
}


template<class Key, class Value>
void rotate_right(Node<Key, Value>* node) {   
	Node<Key, Value>* piviot = node->leftNode;
	piviot->parent = node->parent;
	if (node->parent != nullptr) {
		if (node->parent->leftNode == node) {
			node->parent->leftNode = piviot;
		}
		else {
			node->parent->rightNode = piviot;
		}
	}
	node->leftNode = piviot->rightNode;
	if (!piviot->rightNode->isLeaf) {
		piviot->rightNode->parent = node;
	}
	node->parent = piviot;
	piviot->rightNode = node;
}
///
/// End block 



/// Family Search Block
///  
template<class Key, class Value>
Node<Key,Value>* sibling(Node<Key,Value>* node) {  // search for a node brother
	if (node == node->parent->leftNode)
		return node->parent->rightNode;
	else
		return node->parent->leftNode;
}

template<class Key, class Value>
Node<Key, Value>* grandParent(Node<Key, Value>* node) { // search for the node's grandfather
	if (node->parent != nullptr) {
		return node->parent->parent;
	}
	else {
		return nullptr;
	}
}

template<class Key, class Value>
Node<Key, Value>* uncle(Node<Key, Value>* node) {  // search for the node's uncle (brother of the parent of the inserted node)
	Node<Key, Value>* g = grandParent(node);
	if (g == nullptr) {
		return nullptr;
	}
	else if (node->parent == g->leftNode) {
		return g->rightNode;
	}
	else {
		return g->leftNode;
	}
}
/// 
/// End block



// class RB_Tree
template <class Key,class Value>
class RB_Tree {
private:
	Node<Key, Value>* root;   
	void delete_case9(Node<Key, Value>* node);
	void delete_case8(Node<Key, Value>* node);
	void delete_case7(Node<Key, Value>* node);
	void delete_case6(Node<Key, Value>* node);
	void delete_case5(Node<Key, Value>* node);
	void delete_case4(Node<Key, Value>* node);
	void delete_case3(Node<Key, Value>* node);
	void delete_case2(Node<Key, Value>* node);
	void delete_case1(Node<Key, Value>* node);
	void replace_node(Node<Key, Value>* node, Node<Key, Value>* child);
	void delete_one_child(Node<Key, Value>* node);

	void insert_case5(Node<Key, Value>* node);
	void insert_case4(Node<Key, Value>* node);
	void insert_case3(Node<Key, Value>* node);
	void insert_case2(Node<Key, Value>* node);
	void insert_case1(Node<Key, Value>* node);

	void Clear(Node<Key, Value>* curNode);
public:
	RB_Tree();
	RB_Tree(Key& k, Value& v);
	~RB_Tree();
	void Insert(Key& k, Value& v);
	Value Find(const Key& k);
	void Remove(const Key& k);
	void Print();
	Iterator<Key,Value>* create_bft_ierator();
	List<Key>* Get_keys();
	List<Value>* Get_values();
};

template <class Key, class Value>
Iterator<Key, Value>* RB_Tree<Key, Value>::create_bft_ierator() {
	return new bft_iterator<Key, Value>(root);
}


template<class Key, class Value>
List<Key>* RB_Tree<Key, Value>::Get_keys() {
	Iterator<Key, Value>* iter = create_bft_ierator();
	List<Key>* keys = new List<Key>();
	try {
		while (iter->has_next()) {
			Node<Key, Value>* key = iter->next();
			keys->Push_back(key->key);
		}
	}
	catch (std::exception& exp) {
		
	}
	delete iter;
	if (keys->GetSize() == 0) {
		throw std::logic_error("tree is empty");
	}
	return keys;
}

template<class Key, class Value>
List<Value>* RB_Tree<Key, Value>::Get_values() {
	Iterator<Key, Value>* iter = create_bft_ierator();
	List<Value>* values = new List<Value>();
	try {
		while (iter->has_next()) {
			Node<Key, Value>* key = iter->next();
			values->Push_back(key->value);
		}
	}
	catch (std::exception& exp) {
		
	}
	delete iter;
	if (values->GetSize() == 0) {
		throw std::logic_error("tree is empty");
	}
	return values;
}

template <class Key,class Value>
void RB_Tree<Key, Value>::Print() {
	std::cout << "pair 'key : value' of tree nodes:\n";
	List<Value> values = *Get_values();
	List<Key> keys = *Get_keys();
	size_t numNodes = keys.GetSize();
	for (size_t i = 0; i < numNodes; i++) { // The last element is assigned to a leaf node that has no values
		std::cout << "(" << keys[i] << " : " << values[i] << ") ; ";
	}
	values.~List();
	keys.~List();
}

/// Block for deleting and restoring properties of RB_Tree
///

template<class Key, class Value>
void deleteNode(Node<Key, Value>* node) {
	if (node->parent != nullptr) {
		if (node->parent->leftNode == node) {
			node->parent->leftNode = new Node<Key, Value>();		 // now it's a leaf
		}
		else {
			node->parent->rightNode = new Node<Key, Value>();
		}
	}
	// Deleting a node
	if (node->leftNode != nullptr) delete node->leftNode;
	if (node->rightNode != nullptr) delete node->rightNode;
	delete node;
}

/// Block delete node with no child

template<class Key, class Value>
void RB_Tree<Key, Value>::delete_case9(Node<Key, Value>* node) {
	Node<Key, Value>* s = sibling(node);
	if (!s->rightNode->isLeaf && s == node->parent->leftNode) {
		if (s->rightNode->color) {
			s->rightNode->color = false;
			// start big rotate left
			rotate_left(s->parent);
			rotate_right(s->parent->parent);
			// end rotate			
		}
	}
	else if (!s->leftNode->isLeaf && s == node->parent->rightNode) {
		if (s->leftNode->color) {
			s->leftNode->color = false;
			// start big rotate right
			rotate_right(s->parent);
			rotate_left(s->parent->parent);
			// end rotate			
		}
	}
	else {
		s->color = true;
	}
}

template<class Key, class Value>
void RB_Tree<Key, Value>::delete_case8(Node<Key, Value>* node) {
	// if paren black
	Node<Key, Value>* s = sibling(node);
	if (s->color) {
		Node<Key, Value>* gS = (s->leftNode->isLeaf) ? s->rightNode : s->leftNode; // gS - grandSon
		if (!gS->leftNode->isLeaf && !gS->rightNode->isLeaf && !gS->color) {
			if (gS == s->rightNode) {		
				if (!gS->leftNode->color && !gS->rightNode->color) {
					s->color = false;
					gS->color = true;
					rotate_right(s->parent);
				}
				else if (gS->leftNode->color) {
					gS->color = false;
					// start big rotate left
					rotate_left(s->parent);
					rotate_right(s->parent->parent);
					// end rotate
				}			

			}
			else if (gS == s->leftNode) {
				if (!gS->leftNode->color && !gS->rightNode->color) {
					s->color = false;
					gS->color = true;
					rotate_left(s->parent);
				}
				else if (gS->rightNode->color) {
					gS->color = false;
					// start big rotate right
					rotate_right(s->parent);
					rotate_left(s->parent->parent);
					// end rotate
				}
			}
			
		}
	}
	else {
		delete_case9(node);
	}
}


template<class Key, class Value>
void RB_Tree<Key, Value>::delete_case7(Node<Key, Value>* node) {	
	if (node->parent->color) { // if parent red
		Node<Key, Value>* s = sibling(node);
		if (!s->leftNode->isLeaf || !s->rightNode->isLeaf) {
			if (!s->color && !s->leftNode->color && !s->rightNode->color) {  // if the brother node is black with black grandchildren	                                       
				s->color = true;                                  // then we repaint it in red, the parent in black
				s->parent->color = false;
			}
			else if (!s->color) {  // if a brother has one child
				Node<Key, Value>* gS = (s->leftNode->isLeaf) ? s->rightNode : s->leftNode;
				if (gS->color) { // if child red
					if (s == s->parent->leftNode && gS == s->leftNode) { 
						gS->color = false;
						s->parent->color = true;
						rotate_right(s->parent);
					}
					else if (s == s->parent->rightNode && gS == s->rightNode) {
						gS->color = false;
						s->color = true;
						s->parent->color = false;
						rotate_left(s->parent);
					}
					else if(s == s->parent->rightNode && gS == s->leftNode){
						s->parent->color = false;
						rotate_right(s);
						rotate_left(gS->parent);
					}
					else {
						s->parent->color = false;
						rotate_left(s);
						rotate_right(gS->parent);
					}
				}
			}
		}
		
	}
	else  {
		delete_case8(node);
	}

}

/// End delete node with no child


/// block delete node with one child

template<class Key, class Value>
void RB_Tree<Key, Value>::delete_case6(Node<Key, Value>* node) {
	Node<Key, Value>* s = sibling(node);

	s->color = node->parent->color;
	node->parent->color = false;

	if (node == node->parent->leftNode) {
		s->rightNode->color = false;
		rotate_left(node->parent);
	}
	else {
		s->leftNode->color = false;
		rotate_right(node->parent);
	}
}

template<class Key, class Value>
void RB_Tree<Key, Value>::delete_case5(Node<Key, Value>* node) {
	Node<Key, Value>* s = sibling(node);

	if (s->color == false) {
		if ((node == node->parent->leftNode) && (s->rightNode->color == false) && (s->leftNode->color == true)) {
			s->color = true;
			s->leftNode->color = false;
			rotate_right(s);
		}
		else if ((node == node->parent->rightNode) && (s->leftNode->color == false) && (s->rightNode->color == true)) {
			s->color = true;
			s->rightNode->color = false;
			rotate_left(s);
		}
	}
	delete_case6(node);
}

template<class Key, class Value>
void RB_Tree<Key, Value>::delete_case4(Node<Key, Value>* node) {
	Node<Key, Value>* s = sibling(node);

	if ((node->parent->color == true) && (s->color == false) && (s->leftNode->color == false) && (s->rightNode->color == false)) {
		s->color = true;
		node->parent->color = false;
	}
	else
		delete_case5(node);
}

template<class Key, class Value>
void RB_Tree<Key, Value>::delete_case3(Node<Key, Value>* node) {
	Node<Key, Value>* s = sibling(node);

	if ((node->parent->color == false) && (s->color == false) && (s->leftNode->color == false) && (s->rightNode->color == false)) {
		s->color = true;
		delete_case1(node->parent);
	}
	else
		delete_case4(node);
}

template<class Key, class Value>
void RB_Tree<Key, Value>::delete_case2(Node<Key, Value>* node) {
	Node<Key, Value>* s = sibling(node);

	if (s->color == true) {
		node->parent->color = true;
		s->color = false;
		if (node == node->parent->leftNode)
			rotate_left(node->parent);
		else
			rotate_right(node->parent);
	}
	delete_case3(node);
}

template<class Key, class Value>
void RB_Tree<Key, Value>::delete_case1(Node<Key, Value>* node) {
	if (node->parent != nullptr) {
		delete_case2(node);
	}
}

template<class Key, class Value>
void RB_Tree<Key, Value>::replace_node(Node<Key, Value>* node, Node<Key, Value>* child) {
	if (node->parent != nullptr) {
		child->parent = node->parent;
		if (node == node->parent->leftNode) {
			node->parent->leftNode = child;
		}
		else {
			node->parent->rightNode = child;
		}
	}
	else {
		child->parent = nullptr;
	}
}

template<class Key, class Value>
void RB_Tree<Key, Value>::delete_one_child(Node<Key, Value>* node) {
	// Condition: n has at most one non-zero child      
	Node<Key, Value>* child = (node->rightNode->isLeaf) ? node->leftNode : node->rightNode;
	replace_node(node, child);
	if (child->parent != nullptr) {
		if (node->color == false) {
			if (child->color == true) {
				child->color = false;

			}
			else {
				delete_case1(child);
			}
			
		}
		delete node;
		
	}
	else {
		node->value = child->value;
		node->key = child->key;
		deleteNode(child);
	}
		
}

/// End block delete node with one child

template <class Key, class Value>  // Deleting a node by key
void RB_Tree<Key, Value>::Remove(const Key& k) {  // k - key
	if (this->root == nullptr) {
		throw std::out_of_range("this tree is empty");
	}
	else {
		Node<Key, Value>* cur = root;
		while (k != cur->key) {
			if (k < cur->key) {
				if (!cur->leftNode->isLeaf) {
					cur = cur->leftNode;
				}
				else {
					throw std::invalid_argument("the key is not in the tree, so it cannot be deleted");
				}
			}
			else {
				if (!cur->rightNode->isLeaf) {
					cur = cur->rightNode;
				}
				else {
					throw std::invalid_argument("the key is not in the tree, so it cannot be deleted");
				}
			}
		}

		if (has_one_leaf(cur)) { // has one non-zero child
			delete_one_child(cur);
		}
		else if(cur->leftNode->isLeaf && cur->rightNode->isLeaf) {  // has two null children
			if (cur->color == true) {         
				deleteNode(cur);
			}
			else {
				Node<Key, Value>* gP = grandParent(cur);
				delete_case7(cur);	
				deleteNode(cur);
				while (gP->parent != nullptr) {
					delete_case7(gP);
					gP = grandParent(gP);
				}
			}

		}
		else { // has two children
			Node<Key, Value>* node_to_delete = find_the_biggest(cur);
			cur->value = node_to_delete->value;
			cur->key = node_to_delete->key;
			if (node_to_delete->leftNode->isLeaf && node_to_delete->rightNode->isLeaf && !node_to_delete->color) { // if the node being deleted had no children
				Node<Key, Value>* gP = grandParent(node_to_delete);
				delete_case7(node_to_delete);
				deleteNode(node_to_delete);
				while (gP->parent != nullptr) {
					delete_case7(gP);
					gP = grandParent(gP);
				}
			}
			else if(has_one_leaf(node_to_delete)) { // if the node being deleted had one child
				delete_one_child(node_to_delete);
			}
			else { // if the node red without children
				deleteNode(node_to_delete);
			}
		}
	}        
}
///
///  End of block


/// Block of different insertion situations
/// 
template<class Key, class Value>
void RB_Tree<Key, Value>::insert_case5(Node<Key, Value>* node) {
	Node<Key, Value>* g = grandParent(node);
	if (g == root) {
		root = node->parent;
	}
	node->parent->color = false;
	g->color = true;
	if ((node->parent->leftNode == node) && (node->parent == g->leftNode)) {
		rotate_right(g);
	}
	else { /* (n == n->parent->rightNode) && (n->parent == g->rightNode) */
		rotate_left(g);		
	}
	
}

template<class Key, class Value>
void RB_Tree<Key, Value>::insert_case4(Node<Key, Value>* node) {
	Node<Key, Value>* g = grandParent(node);
	if ((node == node->parent->rightNode) && (g->leftNode == node->parent)) {
		rotate_left(node->parent);
		node = node->leftNode;
	}
	else if ((node == node->parent->leftNode) && (g->rightNode == node->parent)) {
		rotate_right(node->parent);
		node = node->rightNode;
	}
	insert_case5(node);
}


template<class Key, class Value>
void RB_Tree<Key, Value>::insert_case3(Node<Key, Value>* node) {
	Node<Key, Value>* Uncle = uncle(node), * g;
	if (!Uncle->isLeaf && Uncle->color) {
		node->parent->color = false;
		Uncle->color = false;
		g = grandParent(node);
		g->color = true;
		insert_case1(g);
	}
	else {
		insert_case4(node);
	}
}

template<class Key, class Value>
void RB_Tree<Key, Value>::insert_case2(Node<Key, Value>* node) {
	if (node->parent->color == false)
		return; /* Tree is still valid */
	else
		insert_case3(node);
}

template<class Key, class Value>
void RB_Tree<Key, Value>::insert_case1(Node<Key, Value>* node) {

	if (node->parent == nullptr)
		node->color = false;
	else
		insert_case2(node);
}


template <class Key, class Value>  // Insert method
void RB_Tree<Key, Value>::Insert(Key& k, Value& v) { // k - key, v - value
	if (root == nullptr) {
		this->root = new Node<Key, Value>(k, v,nullptr,new Node<Key,Value>(), new Node<Key, Value>());
		this->root->color = false;
	}
	else {
		Node<Key, Value>* cur = root;
		// cur->leftNode/rightNode - The node to insert
		while (true) {
			if (k < cur->key) {
				if (!cur->leftNode->isLeaf) {
					cur = cur->leftNode;
				}
				else {
					delete cur->leftNode;
					cur->leftNode = new Node<Key, Value>(k, v, cur, new Node<Key, Value>(), new Node<Key, Value>());
					insert_case2(cur->leftNode);	
					break;
				}
			}
			else {
				if (!cur->rightNode->isLeaf) {
					cur = cur->rightNode;
				}
				else {
					delete cur->rightNode;
					cur->rightNode = new Node<Key, Value>(k, v, cur, new Node<Key, Value>(), new Node<Key, Value>());
					insert_case2(cur->rightNode);
					break;
				}
			}
		}
	}
}
///
/// End of block



template <class Key, class Value> // Default Constructor
RB_Tree<Key,Value>::RB_Tree() {
	this->root = nullptr;
}


template <class Key, class Value>  // Constructor with direct parameters
RB_Tree<Key, Value>::RB_Tree(Key& k, Value& v) {
	this->root = new Node<Key, Value>(k, v,nullptr,new Node<Key,Value>(), new Node<Key, Value>());
	this->root->color = false;
}


template <class Key, class Value> // Method for deleting a tree
void RB_Tree<Key, Value>::Clear(Node<Key, Value>* curNode) {
	if (!curNode->isLeaf) {
		Clear(curNode->leftNode);
		Clear(curNode->rightNode);
		delete curNode;
	}	
}


template <class Key, class Value> // Destructor
RB_Tree<Key, Value>::~RB_Tree() {
	Clear(this->root);

}


template <class Key, class Value>  // Search in the tree by key
Value RB_Tree<Key, Value>::Find(const Key& k) { // k - key
	if (this->root == nullptr) {
		throw std::out_of_range("this tree is empty");
	}
	Node<Key,Value>* cur = this->root;
	while (k != cur->key) {
		if (k < cur->key) {
			if (cur->leftNode != nullptr) {
				cur = cur->leftNode;
			}
			else {
				throw std::invalid_argument("the key is not in the tree");
			}
		}
		else {
			if (cur->rightNode != nullptr) {
				cur = cur->rightNode;
			}
			else {
				throw std::invalid_argument("the key is not in the tree");
			}
		}
	} return cur->value;
}
