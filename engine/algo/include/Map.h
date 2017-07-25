#pragma once
#include "General.h"

template <class T>
class BTree_nb : public Tree<T> {
#ifdef GMOCK_DEBUG
public:
#else
protected:
#endif
	struct Node {
		Node* left;
		Node* right;
		Node* parent;
		T value;
		int index;
	};
	Node* head;
	int count;

	l_sts find(Node** res, int index) {
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

public:
	BTree_nb() : head(nullptr), count(0) {
	}
	l_sts insert(T value, int index) {
		if (head == nullptr) {
			head = new Node();
			head->value = value;
			head->index = index;
			return SUCCESS;
		}
		Node* parent;
		l_sts sts = find(&parent, index);
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
		}
		return sts;
	}
	T minimum() {
		return 0;
	}
	T maximum() {
		return 0;
	}
	l_sts remove(int index) {
		return SUCCESS;
	}

	T operator[](int index) {
		return 0;
	}

};