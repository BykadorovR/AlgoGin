#pragma once
#include "General.h"

template <class T, class I>
class BTree {
#ifdef GMOCK_DEBUG
public:
#else
protected:
#endif

	enum NodeColor {
		none = 0,
		red,
		black,
	};

	enum NodeType {
		headNode = 0,
		leftNode,
		rightNode,
	};

	struct Node {
		Node* left;
		Node* right;
		Node* parent;
		T value;
		I index;
		NodeColor color;
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

	l_sts maximum_recursively(Node* current, T& value) {
		if (!current)
			return EMPTY;
		if (current->left)
			maximum_recursively(current->left, value);
		if (current->value > value)
			value = current->value;
		if (current->right)
			maximum_recursively(current->right, value);
		return SUCCESS;
	}

	l_sts minimum_recursively(Node* current, T& value) {
		if (!current)
			return EMPTY;
		if (current->left)
			minimum_recursively(current->left, value);
		if (current->value < value)
			value = current->value;
		if (current->right)
			minimum_recursively(current->right, value);
		return SUCCESS;
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

	/*
        (1) vt.          (1) vt.
          \                \
	      (3) re.           (2) tm. 
	      / \     right     / \
	tm. (2)  c   ------>   a  (3) re.
	    / \                   / \
	   a   b                 b   c
	*/
	//First uprocessed node and last node of final vine
	l_sts rightRotation(Node** remaining, Node* vineTail) {
		Node* temp = (*remaining)->left;

		//reassign one of subtrees from temp to remainder
		(*remaining)->left = temp->right;
		if (temp->right)
			temp->right->parent = (*remaining);

		//raise temp node. It has to be between vineTail and remainder
		temp->right = (*remaining);
		temp->parent = vineTail;
		(*remaining)->parent = temp;
		vineTail->right = temp;

		(*remaining) = temp;
		return SUCCESS;
	}

	/*
       (1) sc.               (1) sc.
		 \                     \
	     (2) ch.               (3)
	     / \     left          / \
	    a  (3)  ------>  ch. (2)  c
	       / \               / \
	      b   c	            a   b
	*/
	l_sts leftRotation(Node** scanner, Node* child) {
		(*scanner)->right = child->right;
		if (child->right)
			child->right->parent = (*scanner);

		(*scanner) = (*scanner)->right;

		//reassign scanner left to child right
		child->right = (*scanner)->left;
		if ((*scanner)->left)
			(*scanner)->left->parent = child;

		//now child node is left child of scanner
		(*scanner)->left = child;
		child->parent = (*scanner);

		return SUCCESS;
	}

	int getHeight(Node* root) {
		auto max = [](int left, int right) -> int {
			return left > right ? left : right;
		};
		if (root == NULL)
			return 0;
		else
			return max(getHeight(root->left) + 1,
				getHeight(root->right) + 1);
	}

	T _operator(I index) {
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

	l_sts _insert(T value, I index, Node** inserted = nullptr) {
		if (head == nullptr) {
			head = new Node();
			head->value = value;
			head->index = index;
			if (inserted)
				*inserted = head;
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
			if (inserted)
				*inserted = cur;
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
	T _minimum() {
		T min = head->value;
		minimum_recursively(head, min);
		return min;
	}
	T _maximum() {
		T max = head->value;
		maximum_recursively(head, max);
		return max;
	}
	l_sts _remove(I index) {
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
			}
			else
				//if there is 1 child
				if (current->left && current->right == nullptr) {
					//not deep copy, only index and value
					current->index = current->left->index;
					current->value = current->left->value;
					delete current->left;
					current->left = nullptr;
				}
				else
					if (current->right && current->left == nullptr) {
						current->index = current->right->index;
						current->value = current->right->value;
						delete current->right;
						current->right = nullptr;
					}
					else
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

	l_sts free(Node* current) {
		if (current->left != nullptr)
			free(current->left);
		if (current->right != nullptr)
			free(current->right);
		delete current;
		count--;
		return SUCCESS;
	}

public:
	int getNodeCount() {
		return count;
	}

	bool isTreeBalanced() {
		if (!head)
			return false;
		if (abs(getHeight(head->left) - getHeight(head->right)) <= 1)
			return true;
		return false;
	}
};

//Manually balancing binary search tree
template <class T, class I>
class BTree_mb : public BTree<T, I>, public Tree<T, I> {
#ifdef GMOCK_DEBUG
public:
#else
protected:
#endif
	/*Day-Stout-Warren algorithm of balancing BST*/
	//TreeToVine transform to vine where is all of nodes are right (just ordered list)
	l_sts treeToVine(typename BTree<T, I>::Node* root) {
		//last element of vain (no additional work is needed)
		typename BTree<T, I>::Node* vineTail = root;
		//first element of unprocessed part
		typename BTree<T, I>::Node* remainder = vineTail->right;
		while (remainder != nullptr) {
			if (remainder->left == nullptr) {
				//move vineTail down
				vineTail = remainder;
				//no need to rebind parent due of right structure of vine
				remainder = remainder->right;
			}
			else {
				//right rotate: from left bottom to left top
				BTree<T, I>::rightRotation(&remainder, vineTail);
			}
		}
		return SUCCESS;
	}

	l_sts compress(typename BTree<T, I>::Node* root, int size) {
		typename BTree<T, I>::Node* scanner = root;
		for (int i = 0; i < size; i++) {
			typename BTree<T, I>::Node* child = scanner->right;
			//(1)-(2)-(3)
			//ommit child node(2) and link scanner(1) and child->right(3) nodes together
			BTree<T, I>::leftRotation(&scanner, child);
		}
		return SUCCESS;
	}

	l_sts vineToTree(typename BTree<T, I>::Node* root) {
		int size = BTree<T, I>::count; //add 1 due of fake root
		int leafCount = static_cast<int>(size + 1 - pow(2, floor(log2(size + 1))));
		//create deepest leaves
		compress(root, leafCount);
		size -= leafCount;
		while (size > 1) {
			compress(root, static_cast<int>(floor(size / 2)));
			size = static_cast<int>(floor(size / 2));
		}
		return SUCCESS;
	}

	l_sts print_recursively(typename BTree<T, I>::Node* current) {
		if (!current)
			return EMPTY;
		if (current->left)
			print_recursively(current->left);
		std::cout << "Pointer: " << current << " Index: " << current->index << " Value: " << current->value << std::endl;
		if (current->right)
			print_recursively(current->right);
		return SUCCESS;
	}


public:
	BTree_mb() {
		BTree<T, I>::head = nullptr;
		BTree<T, I>::count = 0;
	}

	~BTree_mb() {
		if (BTree<T, I>::head)
			BTree<T, I>::free(BTree<T, I>::head);
	}

	T operator[](I index) {
		return BTree<T, I>::_operator(index);
	}

	l_sts insert(T value, I index) {
		l_sts sts;
		sts = BTree<T, I>::_insert(value, index);
		//balancing
		if (BTree<T, I>::count > 10)
			sts = getWorst(balanceTree(), sts);
		return sts;
	}

	T minimum() {
		return BTree<T, I>::_minimum();
	}

	T maximum() {
		return BTree<T, I>::_maximum();
	}

	l_sts remove(I index) {
		return BTree<T, I>::_remove(index);
	}

	l_sts balanceTree() {
		if (!BTree<T, I>::head)
			return EMPTY;
		typename BTree<T, I>::Node* temp = new typename BTree<T, I>::Node();
		temp->right = BTree<T, I>::head;
		treeToVine(temp);
		vineToTree(temp);
		delete temp;
		return SUCCESS;
	}

	l_sts print_ordered() {
		return print_recursively(BTree<T, I>::head);
	}
};

template <class T, class I>
class BTree_rb : public BTree<T, I>, public Tree<T, I> {
#ifdef GMOCK_DEBUG
public:
#else
protected:
#endif

	l_sts findUncle(BTree<T, I>::Node* current, BTree<T, I>::Node** uncle) {
		if (!current->parent) {
			*uncle = nullptr;
			return NOT_FOUND;
		}
		BTree<T, I>::Node* parent = current->parent;
		NodeType parentType = childType(parent);
		if (parentType == rightNode)
			*uncle = parent->parent->left;
		else
		if (parentType == leftNode)
			*uncle = parent->parent->right;
		else {
			*uncle = nullptr;
			return NOT_FOUND;
		}
		return SUCCESS;
	}
	//if x is root change color of x as BLACK
	//if color of x's parent is RED and x isn't root do:
	//change color of parent and uncle as BLACK; color of grand parent as RED; x = x's grandparent and repeat;
	l_sts recoloring(BTree<T, I>::Node* current) {
		while (current != nullptr) {
			//If inserted node is first in tree
			if (current == BTree<T, I>::head) {
				current->color = black;
				return SUCCESS;
			}
			//parent is black node so it's ok
			if (current->parent->color == black) {
				return SUCCESS;
			}

			BTree<T, I>::Node* uncle;
			findUncle(current, &uncle);
			if (uncle && uncle->color == red) {
				//current->parent exists because in other case current is head node and we would exit from this loop
				current->parent->color = black;
				uncle->color = black;
				if (current->parent->parent)
					current->parent->parent->color = red;
				current = current->parent->parent;
			}
		}
		return SUCCESS;

	}
public:
	BTree_rb() {
		BTree<T, I>::head = nullptr;
		BTree<T, I>::count = 0;
	}

	l_sts insert(T value, I index) {
		BTree<T, I>::Node* inserted;
		l_sts sts = BTree<T, I>::_insert(value, index, &inserted);
		//Newly inserted nodes have to be red
		inserted->color = red;

		//try to do recoloring if needed
		recoloring(inserted);
		return SUCCESS;
	}

	T operator[](I index) {
		return BTree<T, I>::_operator(index);
	}

	T minimum() {
		return BTree<T, I>::_minimum();
	}

	T maximum() {
		return BTree<T, I>::_maximum();
	}

	l_sts remove(I index) {
		return BTree<T, I>::_remove(index);
	}
};