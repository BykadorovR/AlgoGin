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
		doubleBlack,
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
	//smallest in the right subtree
	l_sts findNearest(Node** res) {
		Node* start = (*res)->right;
		while (start->left != nullptr) {
			start = start->left;
		}

		*res = start;
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
			else if (parent->right && parent->right->index == child->index)
				return rightNode;
		}
		return headNode;
	}

	bool isOnlyChild(Node* current) {
		NodeType currentType = childType(current);
		if (currentType == leftNode)
			if (current->parent->right != nullptr)
				return false;
		if (currentType == rightNode)
			if (current->parent->left != nullptr)
				return false;
		//lets head node be the only child
		return true;
	}

	bool isLeaf(Node* current) {
		if (current->right == nullptr && current->left == nullptr)
			return true;
		return false;
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
		(*remaining)->parent = temp;
		temp->parent = vineTail;
		if (vineTail)
		    vineTail->right = temp;

		(*remaining) = temp;
		return SUCCESS;
	}

	/*
       (1) sc.               (1)
		 \                     \
	     (2) ch.               (3) sc.
	     / \     left          / \
	    a  (3)  ------>  ch. (2)  c
	       / \               / \
	      b   c	            a   b
	*/
	//(1) doesn't change own location so there is case when child of scanner isn't right but left (it doesn't matter because left rotation is applied to
	//child not scanner
	l_sts leftRotation(Node** scanner, Node* child) {
		NodeType childNodeType = childType(child);
		if (childNodeType == rightNode)
			//if child is right node of scanner 
			(*scanner)->right = child->right;
		else
			//if child is left node of scanner 
			(*scanner)->left = child->right;

		if (child->right)
			child->right->parent = (*scanner);

		if (childNodeType == rightNode)
			//if child is right node of scanner 
			(*scanner) = (*scanner)->right;
		else
			//if child is left node of scanner 
			(*scanner) = (*scanner)->left;

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

	l_sts _removeLeaf(Node** current) {
		return WRONG_ARGS;
	}

	l_sts _removeRecursively(Node** current, Node** deleted = nullptr) {
		if ((*current)->left == nullptr && (*current)->right == nullptr) {
			//we want to memory deleted node for further handling
			if (deleted) {
				(*deleted) = (*current);
			}
			else {
				//
				NodeType type = childType(*current);
				if (type == leftNode)
					(*current)->parent->left = nullptr;
				else if (type == rightNode)
					(*current)->parent->right = nullptr;
				delete (*current);
			}
			return SUCCESS;
		} else
		if ((*current)->left && (*current)->right == nullptr) {
			//not deep copy, only index and value
			(*current)->index = (*current)->left->index;
			(*current)->value = (*current)->left->value;
			(*current) = (*current)->left;
		} else 
		if ((*current)->right && (*current)->left == nullptr) {
			(*current)->index = (*current)->right->index;
			(*current)->value = (*current)->right->value;
			(*current) = (*current)->right;
		} else
		if ((*current)->right && (*current)->left) {
			Node* nearest = (*current);
			findNearest(&nearest);
			(*current)->index = nearest->index;
			(*current)->value = nearest->value;
			(*current) = nearest;
		}

		return _removeRecursively(current, deleted);
	}

	l_sts _removeTwoChild(Node** current) {
		return SUCCESS;
	}

	l_sts _remove(I index, Node** deleted = nullptr) {
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
			_removeRecursively(&current, deleted);
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
		if (BTree<T, I>::count > 20)
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
		BTree<T, I>::head->parent = temp;
		treeToVine(temp);
		vineToTree(temp);
		BTree<T, I>::head = temp->right;
		delete temp;
		BTree<T, I>::head->parent = nullptr;
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
	l_sts setCorrectHead() {
		while (BTree<T, I>::head->parent != nullptr)
			BTree<T, I>::head = BTree<T, I>::head->parent;
		return SUCCESS;
	}

	l_sts findUncle(typename BTree<T, I>::Node* current, typename BTree<T, I>::Node** uncle) {
		if (!current->parent) {
			*uncle = nullptr;
			return NOT_FOUND;
		}
		typename BTree<T, I>::Node* parent = current->parent;
		typename BTree<T, I>::NodeType parentType = BTree<T, I>::childType(parent);
		if (parentType == BTree<T, I>::rightNode)
			*uncle = parent->parent->left;
		else
		if (parentType == BTree<T, I>::leftNode)
			*uncle = parent->parent->right;
		else {
			*uncle = nullptr;
			return NOT_FOUND;
		}
		return SUCCESS;
	}

	//left left case - curent left child and parent left child
	l_sts leftLeftCase(typename BTree<T, I>::Node* current) {	
		if (BTree<T, I>::childType(current) == BTree<T, I>::leftNode && BTree<T, I>::childType(current->parent) == BTree<T, I>::leftNode) {
			typename BTree<T, I>::Node* grandParent = current->parent->parent;
			typename BTree<T, I>::NodeColor tempColor = grandParent->color;
			grandParent->color = current->parent->color;
			current->parent->color = tempColor;
			BTree<T, I>::rightRotation(&grandParent, grandParent->parent);
			setCorrectHead();
			return SUCCESS;
		}
		return NOT_FOUND;
	}

	l_sts leftRightCase(typename BTree<T, I>::Node* current) {
		if (BTree<T, I>::childType(current) == BTree<T, I>::rightNode && BTree<T, I>::childType(current->parent) == BTree<T, I>::leftNode) {
			typename BTree<T, I>::Node* grandParent = current->parent->parent;
			BTree<T, I>::leftRotation(&grandParent, current->parent);
			return leftLeftCase(grandParent->left);
		}
		return NOT_FOUND;
	}

	l_sts rightRightCase(typename BTree<T, I>::Node* current) {
		if (BTree<T, I>::childType(current) == BTree<T, I>::rightNode && BTree<T, I>::childType(current->parent) == BTree<T, I>::rightNode) {
			typename BTree<T, I>::Node* grandParent = current->parent->parent;
			typename BTree<T, I>::NodeColor temp = grandParent->color;
			grandParent->color = current->parent->color;
			current->parent->color = temp;
			//due of realisation of left rotation as in BSW algorithm (where fake node is used) we have to add fake node for left rotation too
			//if we want to rotate grandparent
			if (!grandParent->parent) {
				typename BTree<T, I>::Node* fake = new typename BTree<T, I>::Node();
				fake->right = grandParent;
				grandParent->parent = fake;
				//we have to make left rotate of grandParent so we need to pass grand parent node and its parent
				BTree<T, I>::leftRotation(&fake, grandParent);
				delete fake->parent;
				fake->parent = nullptr;
			}
			else {
				BTree<T, I>::leftRotation(&(grandParent->parent), grandParent);
			}
			setCorrectHead();
			return SUCCESS;
		}
		return NOT_FOUND;
	}

	l_sts rightLeftCase(typename BTree<T, I>::Node* current) {
		if (BTree<T, I>::childType(current) == BTree<T, I>::leftNode && BTree<T, I>::childType(current->parent) == BTree<T, I>::rightNode) {
			typename BTree<T, I>::Node* parentNode = current->parent;
			BTree<T, I>::rightRotation(&parentNode, parentNode->parent);
			return rightRightCase(current->right);
		}
		return NOT_FOUND;
	}
	//if x is root change color of x as BLACK
	//if color of x's parent is RED and x isn't root do:
	//change color of parent and uncle as BLACK; color of grand parent as RED; x = x's grandparent and repeat;
	l_sts rebalancing(typename BTree<T, I>::Node* current) {
		while (current != nullptr) {
			//If inserted node is first in tree
			if (current == BTree<T, I>::head) {
				current->color = BTree<T, I>::black;
				return SUCCESS;
			}
			//parent is black node so it's ok
			if (current->parent->color == BTree<T, I>::black) {
				return SUCCESS;
			}

			typename BTree<T, I>::Node* uncle;
			findUncle(current, &uncle);
			if (uncle && uncle->color == BTree<T, I>::red) {
				//current->parent exists because in other case current is head node and we would exit from this loop
				current->parent->color = BTree<T, I>::black;
				uncle->color = BTree<T, I>::black;
				if (current->parent->parent)
					current->parent->parent->color = BTree<T, I>::red;
				current = current->parent->parent;
			}
			else if (!uncle || uncle->color == BTree<T, I>::black) {
				l_sts sts = leftLeftCase(current);
				if (sts == SUCCESS)
					return sts;
				sts = leftRightCase(current);
				if (sts == SUCCESS)
					return sts;
				sts = rightRightCase(current);
				if (sts == SUCCESS)
					return sts;
				sts = rightLeftCase(current);
				if (sts == SUCCESS)
					return sts;

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
		typename BTree<T, I>::Node* inserted;
		l_sts sts = BTree<T, I>::_insert(value, index, &inserted);
		//Newly inserted nodes have to be red
		inserted->color = BTree<T, I>::red;

		//try to do rebalancing if needed
		rebalancing(inserted);
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
		typename BTree<T, I>::Node* deleted;
		BTree<T, I>::_remove(index, &deleted);

		NodeType currentType = BTree<T, I>::childType(deleted);
		bool onlyOneChild = BTree<T, I>::isOnlyChild(deleted);

		if (currentType == leftNode)
			(deleted)->parent->left = nullptr;
		else if (currentType == rightNode)
			(deleted)->parent->right = nullptr;

		//if deleted node is red so no addtitional actions are required
		if (deleted->color == BTree<T, I>::red) {
			delete deleted;
			deleted = nullptr;
			return SUCCESS;
		} else
		//if one child and deleted node is black and parent red this case is applicable
		if (onlyOneChild && deleted->color == BTree<T, I>::black && deleted->parent->color == BTree<T, I>::red) {
			deleted->parent->color = BTree<T, I>::black;
			delete deleted;
			deleted = nullptr;
			return SUCCESS;
		} else
		//otherwise, if deleted node is black and has sibling
		if (!onlyOneChild && deleted->color == BTree<T, I>::black) {
			typename BTree<T, I>::Node* current = deleted;
			current->color = BTree<T, I>::doubleBlack;
			while (current->color == BTree<T, I>::doubleBlack && current != BTree<T, I>::head) {
				typename BTree<T, I>::Node* sibling = currentType == BTree<T, I>::leftNode ? current->parent->right : current->parent->left;
				//if sibling is black and at lease one child is red perform rotation
				if (sibling->color == BTree<T, I>::black && ((sibling->right && sibling->right->color == BTree<T, I>::red)
					                       || (sibling->left && sibling->left->color == BTree<T, I>::red))) {
					typename BTree<T, I>::Node* redChild;
					if (sibling->right && sibling->right->color == BTree<T, I>::red)
						redChild = sibling->right;
					else if (sibling->left && sibling->left->color == BTree<T, I>::red)
						redChild = sibling->left;

					//deleted node isn't contained in tree so no problems will be observed in case of rotation
					l_sts sts = leftLeftCase(redChild);
					if (sts == SUCCESS) {
						redChild->color = BTree<T, I>::black;
						delete deleted;
						deleted = nullptr;
						return sts;
					}
					sts = leftRightCase(redChild);
					if (sts == SUCCESS) {
						redChild->right->color = BTree<T, I>::black;
						delete deleted;
						deleted = nullptr;
						return sts;
					}
					sts = rightRightCase(redChild);
					if (sts == SUCCESS) {
						redChild->color = BTree<T, I>::black;
						delete deleted;
						deleted = nullptr;
						return sts;
					}
					sts = rightLeftCase(redChild);
					if (sts == SUCCESS) {
						redChild->left->color = BTree<T, I>::black;
						delete deleted;
						deleted = nullptr;
						return sts;
					}
				} else
				//if sibling is black and it's both children are black: recoloring and recur for new doubleBlack node (new iteration of while loop)
				if (sibling->color == BTree<T, I>::black && ((sibling->right && sibling->right->color == BTree<T, I>::black) || sibling->right == nullptr)
					                                     && ((sibling->left && sibling->left->color == BTree<T, I>::black) || sibling->left == nullptr)) {
					//remove one black from current node and from sibling, so current node will be black and sibling will be red. Also parent will be doubleBlack
					sibling->color = BTree<T, I>::red;
					current->color = BTree<T, I>::black;
					if (sibling->parent->color == BTree<T, I>::red) {
						sibling->parent->color = BTree<T, I>::black;
					}
					else {
						sibling->parent->color = BTree<T, I>::doubleBlack;
						current = sibling->parent;
					}
				} else
				if (sibling->color == BTree<T, I>::red) {
					typename BTree<T, I>::Node* redChild;
					if (sibling->right && sibling->right->color == BTree<T, I>::red)
						redChild = sibling->right;
					else if (sibling->left && sibling->left->color == BTree<T, I>::red)
						redChild = sibling->left;
					//right case: sibling is right child so left rotate parent and after that previous case is applicable
					typename BTree<T, I>::Node* siblingParent = sibling->parent;
					if (!siblingParent->parent) {
						typename BTree<T, I>::Node* fake = new typename BTree<T, I>::Node();
						fake->right = siblingParent;
						siblingParent->parent = fake;
						//we have to make left rotate of grandParent so we need to pass grand parent node and its parent
						BTree<T, I>::leftRotation(&fake, siblingParent);
						delete fake->parent;
						fake->parent = nullptr;
					}
					else {
						BTree<T, I>::leftRotation(&(siblingParent->parent), siblingParent);
					}
					//left case: sibling is left child so right rotate parent and after that previous case is applicable
					BTree<T, I>::rightRotation(&siblingParent, siblingParent->parent);
					//let's set head to correct node
					setCorrectHead();
				}
				currentType = BTree<T, I>::childType(current);
			}
			if (current == BTree<T, I>::head)
				current->color = BTree<T, I>::black;
		}
		else {
			delete deleted;
			deleted = nullptr;
			return UNKNOWN;
		}
		delete deleted;
		deleted = nullptr;
		return SUCCESS;
	}
};