#pragma once
#include "General.h"

template <class T>
class BTree_nb : public Tree<T> {
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
		int index;
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
			value = 0;
			index = 0;
		}
	};
	Node* head;
	int count;

	l_sts find_parent(Node** res, int index) {
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

	l_sts find_node(Node** res, int index) {
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

	l_sts find_nearest(Node** res, int index) {
		while (*res) {
			*res = (*res)->right;
			if ((*res)->left) {
				*res = (*res)->left;
				return SUCCESS;
			}
		}
		
		*res = (*res)->right > (*res)->left ? (*res)->left : (*res)->right;
		return SUCCESS;
	}

	l_sts print_recursively(Node* current) {
		if (current->left)
			print_recursively(current->left);
		std::cout << "Pointer: " << current << " Index: " << current->index << " Value: " << current->value << std::endl;
		if (current->right)
			print_recursively(current->right);
		return SUCCESS;
	}

	NodeType childType(Node* child) {
		Node* parent = child->parent;
		if (parent) {
			if (parent->left->index == child->index)
				return leftNode;
			return rightNode;
		}
		return headNode;
	}

public:
	BTree_nb() : head(nullptr), count(0) {
	}
	l_sts insert(T value, int index) {
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
		if (!head)
			throw;
		Node* current = head;
		T min = current->value;
		current = current->left;
		while (current != nullptr) {
			if (current->value < min)
				min = current->value;
		}
		return min;
	}
	T maximum() {
		if (!head)
			throw;
		Node* current = head;
		T max = current->value;
		current = current->left;
		while (current != nullptr) {
			if (current->value > max)
				max = current->value;
		}
		return max;
	}
	l_sts remove(int index) {
		if (head == nullptr)
			return EMPTY;
		if (head->index == index) {
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

	T operator[](int index) {
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