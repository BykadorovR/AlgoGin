#pragma once
#include "General.h"

template <class T, class I>
class BTree_nb : public Tree<T, I> {
#ifdef GMOCK_DEBUG
public:
#else
protected:
#endif
	enum NodeType {
		headNode = 0,
		leftNode = 1,
		rightNode = 2,
	};

	struct Node {
		Node* left;
		Node* right;
		Node* parent;
		T value;
		I index;
		Node(Node& src) {
			left = src->left;
			right = src->right;
			parent = src->parent;
			value = src->value;
			index = src->index;
		}
		Node() {
			left = nullptr;
			right = nullptr;
			parent = nullptr;
		}
	};
	Node* head;
	int count;

	l_sts find_parent(Node** res, I index) {
		Node* cur = head;
		while (cur != nullptr) {
			*res = cur;
			if (cur->index < index)
				cur = cur->right;
			else if (cur->index > index) 
				cur = cur->left;
			else return WRONG_ARGS;
		}
		return SUCCESS;
	}

	l_sts find_node(Node** res, I index) {
		*res = head;
		while ((*res) != nullptr && (*res)->index != index) {
			if ((*res)->index < index)
				*res = (*res)->right;
			else if ((*res)->index > index)
				*res = (*res)->left;
			else return WRONG_ARGS;
		}
		if (*res)
			return SUCCESS;
		return NOT_FOUND;
	}

	l_sts find_nearest(Node** res, I index) {
		Node* start = *res;
		while (*res) {
			*res = (*res)->right;
			if ((*res) != nullptr && (*res)->left) {
				*res = (*res)->left;
				return SUCCESS;
			}
		}
		
		*res = start->left;
		return SUCCESS;
	}

	l_sts print_recursively(Node* current) {
		if (!current)
			return EMPTY;
		if (current->left)
			print_recursively(current->left);
		std::cout << "Pointer: " << current << " Index: " << current->index << " Value: " << current->value << std::endl;
		if (current->right)
			print_recursively(current->right);
		return SUCCESS;
	}

	l_sts _maximum(Node* current, T& value) {
		if (!current)
			return EMPTY;
		if (current->left)
			_maximum(current->left, value);
		if (current->value > value)
			value = current->value;
		if (current->right)
			_maximum(current->right, value);
	}

	l_sts _minimum(Node* current, T& value) {
		if (!current)
			return EMPTY;
		if (current->left)
			_minimum(current->left, value);
		if (current->value < value)
			value = current->value;
		if (current->right)
			_minimum(current->right, value);
	}

	NodeType childType(Node* child) {
		Node* parent = child->parent;
		if (parent) {
			if (parent->left && parent->left->index == child->index)
				return leftNode;
			return rightNode;
		}
		return headNode;
	}
	/*Day-Stout-Warren algorithm of balancing BST*/

	//TreeToVine transform to vine where is all of nodes are right (just ordered list)
	l_sts treeToVine(Node* root) {
		//last element of vain (no additional work is needed)
		Node* vineTail = root;
		//first element of unprocessed part
		Node* remainder = vineTail->right;
		while (remainder != nullptr) {
			if (remainder->left == nullptr) {
				//move vineTail down
				vineTail = remainder;
				remainder = remainder->right;
			}
			else {
				//right rotate: from left bottom to left top
				//save left subtree
				Node* temp = remainder->left;
				
				//reassign one of subtrees from temp to remainder
				remainder->left = temp->right;
				if (temp->right)
					temp->right->parent = remainder->left;

				//raise temp node. It has to be between vineTail and remainder
				temp->right = remainder;
				remainder->parent = temp->right;
				vineTail->right = temp;
				temp->parent = vineTail;
				
				remainder = temp;
			}
		}
		return SUCCESS;
	}

	l_sts compress(Node* root, int size) {
		Node* scanner = root;
		for (i = 0; i < size; i++) {
			Node* child = scanner->right;
			//(1)-(2)-(3)
			//ommit child node(2) and link scanner(1) and child->right(3) nodes together
			scanner->right = child->right;
			if (child->right)
				child->right->parent = scanner->right;

			//scanner now (3)
			scanner = scanner->right;
			
			//reassign scanner left to child right
			child->right = scanner->left;
			if (scanner->left)
				scanner->left->parent = child->right;

			//now child node is left child of scanner
			scanner->left = child;
			child->parent = scanner->left;
		}
		return SUCCESS;
	}

public:
	BTree_nb() : head(nullptr), count(0) {
	}
	l_sts insert(T value, I index) {
		if (head == nullptr) {
			head = new Node();
			head->value = value;
			head->index = index;
			count++;
			return SUCCESS;
		}
		Node* parent;
		l_sts sts = find_parent(&parent, index);
		if (sts != WRONG_ARGS) {
			Node* cur = new Node();
			cur->index = index;
			cur->value = value;
			cur->parent = parent;
			if (parent->index > index) {
				parent->left = cur;
			}
			else if (parent->index < index) {
				parent->right = cur;
			}
			count++;
		}
		return sts;
	}
	T minimum() {
		T min = head->value;
		_minimum(head, min);
		return min;
	}
	T maximum() {
		T max = head->value;
		_maximum(head, max);
		return max;
	}
	l_sts remove(I index) {
		if (head == nullptr)
			return EMPTY;
		if (head->index == index && !head->left && !head->right) {
			delete head;
			head = nullptr;
			count--;
		}
		Node* current;
		l_sts sts = find_node(&current, index);
		
		if (sts == SUCCESS) {
			//if node is leaf
			if (current->left == nullptr && current->right == nullptr) {
				NodeType type = childType(current);
				if (type == leftNode)
					current->parent->left = nullptr;
				else if (type == rightNode)
					current->parent->right = nullptr;
				delete current;
			} else
			//if there is 1 child
			if (current->left && current->right == nullptr) {
				//not deep copy, only index and value
				current->index = current->left->index;
				current->value = current->left->value;
				delete current->left;
				current->left = nullptr;
			} else
			if (current->right && current->left == nullptr) {
				current->index = current->right->index;
				current->value = current->right->value;
				delete current->right;
				current->right = nullptr;
			} else
			//if there are 2 children
			if (current->right && current->left) {
				Node* nearest = current;
				sts = find_nearest(&nearest, index);
				current->index = nearest->index;
				current->value = nearest->value;
				NodeType type = childType(nearest);
				if (type == leftNode)
					nearest->parent->left = nullptr;
				else if (type == rightNode)
					nearest->parent->right = nullptr;
				delete nearest;
			}
			count--;
		}
		return sts;
	}

	T operator[](I index) {
		if (!head)
			throw;
		Node* current = head;
		while (current->index != index && current != nullptr) {
			if (index < current->index)
				current = current->left;
			else current = current->right;
		}
		if (!current)
			throw;
		return current->value;
	}

	int getNodeCount() {
		return count;
	}

	void print_ordered() {
		print_recursively(head);
	}
};