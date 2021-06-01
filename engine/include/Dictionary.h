#pragma once
#include <memory>
#include "Common.h"
#include <concepts>
#include <optional>
#include <list>
#include <functional>

namespace algogin {

	enum class TraversalMode {
		LEVEL_ORDER
	};

	//Dictionary implementation based on red-black tree
	template <class Comparable, class V>
	class Dictionary {
	private:
		enum class COLOR {
			RED,
			BLACK
		};

		struct Tree {
			V value;
			Comparable key;
			COLOR color;
			std::shared_ptr<Tree> parent;
			std::shared_ptr<Tree> left;
			std::shared_ptr<Tree> right;
		};

		std::shared_ptr<Tree> _head = nullptr;
		int _size = 0;

		std::shared_ptr<Tree> _find(Comparable key) const noexcept {
			std::shared_ptr<Tree> currentNode = _head;
			while (currentNode && key != currentNode->key) {
				if (key < currentNode->key) {
					currentNode = currentNode->left;
				}
				else if (key > currentNode->key) {
					currentNode = currentNode->right;
				}
			}

			return currentNode;
		}

		std::shared_ptr<Tree> _findUncle(std::shared_ptr<Tree> currentNode) const noexcept {
			std::shared_ptr<Tree> parent, grandParent;
			if (currentNode)
				parent = currentNode->parent;
			else
				return nullptr;
			if (parent)
				grandParent = parent->parent;
			else
				return nullptr;

			std::shared_ptr<Tree> uncle = nullptr;
			if (grandParent) {
				if (grandParent->left == parent)
					uncle = grandParent->right;
				else
					uncle = grandParent->left;
			}
			return uncle;
		}

		std::shared_ptr<Tree> _findParent(Comparable key) const noexcept {
			std::shared_ptr<Tree> currentNode = _head;
			std::shared_ptr<Tree> parent = nullptr;
			while (currentNode) {
				parent = currentNode;
				if (key < currentNode->key) {
					currentNode = currentNode->left;
				}
				else if (key > currentNode->key) {
					currentNode = currentNode->right;
				}
			}

			return parent;
		}

		ALGOGIN_ERROR _leftRotation(std::shared_ptr<Tree> current) {
			auto parent = current->parent;
			auto rightChild = current->right;
			if (rightChild == nullptr)
				return ALGOGIN_ERROR::UNKNOWN_ERROR;

			if (current == _head) {
				_head = rightChild;
			}

			if (parent) {
				if (parent->left == current)
					parent->left = rightChild;
				else if (parent->right == current)
					parent->right = rightChild;
			}

			rightChild->parent = parent;
			current->parent = rightChild;
			current->right = rightChild->left;
			if (rightChild->left)
				rightChild->left->parent = current;
			rightChild->left = current;

			return ALGOGIN_ERROR::OK;
		}

		ALGOGIN_ERROR _rightRotation(std::shared_ptr<Tree> current) {
			auto parent = current->parent;
			auto leftChild = current->left;
			if (leftChild == nullptr)
				return ALGOGIN_ERROR::UNKNOWN_ERROR;

			if (current == _head) {
				_head = leftChild;
			}

			if (parent) {
				if (parent->left == current)
					parent->left = leftChild;
				else if (parent->right == current)
					parent->right = leftChild;
			}

			leftChild->parent = parent;
			current->parent = leftChild;
			current->left = leftChild->right;
			if (leftChild->right)
				leftChild->right->parent = current;
			leftChild->right = current;

			return ALGOGIN_ERROR::OK;
		}

		ALGOGIN_ERROR _leftLeftRotation(std::shared_ptr<Tree> current) {
			auto err = _rightRotation(current);
			std::swap(current->color, current->parent->color);

			return err;
		}

		ALGOGIN_ERROR _rightRightRotation(std::shared_ptr<Tree> current) {
			auto err = _leftRotation(current);
			std::swap(current->color, current->parent->color);
			
			return err;
		}


		ALGOGIN_ERROR _leftRightRotation(std::shared_ptr<Tree> current) {
			auto err = _leftRotation(current);
			if (err != ALGOGIN_ERROR::OK)
				return err;

			err = _leftLeftRotation(current->parent->parent);

			return err;
		}

		ALGOGIN_ERROR _rightLeftRotation(std::shared_ptr<Tree> current) {
			auto err = _rightRotation(current);
			if (err != ALGOGIN_ERROR::OK)
				return err;

			err = _rightRightRotation(current->parent->parent);

			return err;
		}

		//the node in the right subtree that has the minimum value
		std::shared_ptr<Tree> _successor(std::shared_ptr<Tree> current) {
			if (current == nullptr || (current && current->right == nullptr))
				return nullptr;

			auto leftSubtree = current->right;
			while (leftSubtree->left != nullptr) {
				leftSubtree = leftSubtree->left;
			}

			return leftSubtree;
		}

		ALGOGIN_ERROR _removeDoubleBlack(std::shared_ptr<Tree> target) {
			auto parent = target->parent;

			//2 case
			//if head is double black just make it black and return
			if (target == _head)
				return ALGOGIN_ERROR::OK;

			//if RED we can just remove node, if BLACK:
			if (target->color == COLOR::BLACK) {
				std::shared_ptr<Tree> sibling;
				if (parent && parent->left == target) {
					sibling = parent->right;
				}
				else if (parent && parent->right == target) {
					sibling = parent->left;
				}

				//After target delete it's child (null) will be double black
				//if sibling is black and at least 1 child of sibling is red
				//case 5 (right left/left right) and 6 (right right/left left)
				if (sibling && sibling->color == COLOR::BLACK &&
					((sibling->left && sibling->left->color == COLOR::RED) || (sibling->right && sibling->right->color == COLOR::RED))) {
					if (parent && parent->left == target) {
						parent->left = nullptr;
					}
					else if (parent && parent->right == target) {
						parent->right = nullptr;
					}
					if (sibling->right && sibling->right->color == COLOR::RED) {
						//left right case
						if (parent->left == sibling) {
							auto err = _leftRotation(sibling);
							if (err != ALGOGIN_ERROR::OK)
								return err;
							std::swap(sibling->color, sibling->parent->color);

							auto current = sibling->parent->parent;
							err = _rightRotation(current);
							std::swap(current->color, current->parent->color);
							sibling->color = COLOR::BLACK;
						}
						//right right case
						else if (parent->right == sibling) {
							auto err = _leftRotation(parent);
							std::swap(parent->color, sibling->color);
							sibling->right->color = COLOR::BLACK;
						}
					} else if (sibling->left && sibling->left->color == COLOR::RED) {
						// left left case
						if (parent->left == sibling) {
							auto err = _rightRotation(parent);
							std::swap(parent->color, sibling->color);
							sibling->left->color = COLOR::BLACK;
						}
						//right left case
						else if (parent->right == sibling) {
							auto err = _rightRotation(sibling);
							if (err != ALGOGIN_ERROR::OK)
								return err;
							std::swap(sibling->color, sibling->parent->color);

							auto current = sibling->parent->parent;
							err = _leftRotation(current);
							std::swap(current->color, current->parent->color); //after rotate current parent = sibling
							sibling->color = COLOR::BLACK;
						}
					}
				}
				else if (sibling && sibling->color == COLOR::BLACK &&
					(sibling->left == nullptr || (sibling->left && sibling->left->color == COLOR::BLACK)) &&
					(sibling->right == nullptr || (sibling->left && sibling->left->color == COLOR::BLACK))) {
					if (parent && parent->left == target) {
						parent->left = nullptr;
					}
					else if (parent && parent->right == target) {
						parent->right = nullptr;
					}

					sibling->color = COLOR::RED;
					if (parent->color == COLOR::BLACK)
						//1 case
						_removeDoubleBlack(parent);
					else
						//4 case
						parent->color = COLOR::BLACK;
				}
				//3 case
				//do rotate + recolor and transform tree to above case
				else if (sibling && sibling->color == COLOR::RED) {
					if (parent->left == sibling) {
						_rightRotation(parent);
					}
					else if (parent->right == sibling) {
						_leftRotation(parent);
					}

					std::swap(parent->color, sibling->color);

					_removeDoubleBlack(target);
				}
			}

			return ALGOGIN_ERROR::OK;
		}

		ALGOGIN_ERROR _remove(std::shared_ptr<Tree> target) {
			//handle simple case when target has no childs
			if (target->left == nullptr && target->right == nullptr) {
				if (target->color == COLOR::BLACK) {
					if (target == _head)
						_head = nullptr;
					else
						_removeDoubleBlack(target);
				} else {
					//update parent
					auto parent = target->parent;
					//check parent != null in case we want to delete root node
					if (parent == nullptr)
						_head = nullptr;

					std::shared_ptr<Tree> sibling;
					if (parent && parent->left == target) {
						sibling = parent->right;
						parent->left = nullptr;
					}
					else if (parent && parent->right == target) {
						sibling = parent->left;
						parent->right = nullptr;
					}
				}
			}
			//handle case when target has only one child
			else if (target->left && target->right == nullptr || target->right && target->left == nullptr) {
				std::shared_ptr<Tree> child = nullptr;
				if (target->left)
					child = target->left;
				else if (target->right)
					child = target->right;

				if (target->color == COLOR::BLACK && child->color == COLOR::BLACK) {
					_removeDoubleBlack(child);
				}
				else if (target->color == COLOR::BLACK && child->color == COLOR::RED) {
					child->color = COLOR::BLACK;

					auto parent = target->parent;
					if (parent == nullptr) {
						_head = child;
					}

					if (parent && parent->left == target) {
						parent->left = child;
						child->parent = parent;
					}
					else if (parent && parent->right == target) {
						parent->right = child;
						child->parent = parent;
					}
				}
			}
			//handle case when target has two childs
			else if (target->left && target->right) {
				//first find successor
				auto successor = _successor(target);
				if (successor) {
					target->value = successor->value;
					target->key = successor->key;
					_remove(successor);
				}

			}

			return ALGOGIN_ERROR::OK;
		}

		ALGOGIN_ERROR _insert(std::shared_ptr<Tree> current) noexcept {
			//tree is empty, so set node to head
			if (_head == current) {
				current->color = COLOR::BLACK;
				return ALGOGIN_ERROR::OK;
			}

			auto parent = current->parent;

			//check if parent's node color is black then no problem
			if (current->parent->color == COLOR::BLACK)
				return ALGOGIN_ERROR::OK;

			//if father's color is red when we have to recolor or rebalance tree depending on uncle's color
			auto uncle = _findUncle(current);
			//if uncle color is red, when need to recolor nodes
			if (uncle && uncle->color == COLOR::RED) {
				//recolor father and uncle to black and grandfather to red
				if (current == nullptr)
					return ALGOGIN_ERROR::OK;

				auto father = current->parent;
				if (father)
					father->color = COLOR::BLACK;

				auto uncle = _findUncle(current);
				if (uncle)
					uncle->color = COLOR::BLACK;

				std::shared_ptr<Tree> grandParent = nullptr;
				if (father) {
					grandParent = father->parent;
					//head can be black even if it should be red
					if (grandParent == _head)
						grandParent->color = COLOR::BLACK;
					else if (grandParent)
						grandParent->color = COLOR::RED;
				}

				_insert(grandParent);
			}
			else if (uncle == nullptr || uncle->color == COLOR::BLACK) {
				//if parent left sub-tree and current left sub-tree
				if (parent->parent->left == parent && parent->left == current) {
					_leftLeftRotation(parent->parent);
				}
				else if (parent->parent->right == parent && parent->right == current) {
					_rightRightRotation(parent->parent);
				}
				else if (parent->parent->left == parent && parent->right == current) {
					_leftRightRotation(parent);
				}
				else if (parent->parent->right == parent && parent->left == current) {
					_rightLeftRotation(parent);
				}
			}

			return ALGOGIN_ERROR::OK;
		}

		ALGOGIN_ERROR _deepCopy(std::shared_ptr<Tree> src, std::shared_ptr<Tree> dst) {
			if (src) {
				//left sub-tree
				auto leftNode = src->left;
				if (leftNode) {
					if (dst->left == nullptr)
						dst->left = std::make_shared<Tree>();

					dst->left->key = leftNode->key;
					dst->left->value = leftNode->value;
					dst->left->color = leftNode->color;
					dst->left->parent = dst;
					_deepCopy(src->left, dst->left);
				}
				//right sub-tree
				auto rightNode = src->right;
				if (rightNode) {
					if (dst->right == nullptr)
						dst->right = std::make_shared<Tree>();
					
					dst->right->key = rightNode->key;
					dst->right->value = rightNode->value;
					dst->right->color = rightNode->color;
					dst->right->parent = dst;
					_deepCopy(src->right, dst->right);
				}
			}

			return ALGOGIN_ERROR::OK;
		}

	public:
		Dictionary() = default;
		~Dictionary() = default;
		//deep copy of dict
		Dictionary(const Dictionary& dict) noexcept {
			std::shared_ptr<Tree> newHead = std::make_shared<Tree>();
			newHead->key = dict._head->key;
			newHead->value = dict._head->value;
			newHead->color = dict._head->color;
			_head = newHead;
			_size = dict._size;
			_deepCopy(dict._head, newHead);
		};
		Dictionary& operator=(const Dictionary& rhs) noexcept {
			if (_head == nullptr)
				_head = std::make_shared<Tree>();

			_head->key = rhs._head->key;
			_head->value = rhs._head->value;
			_head->color = rhs._head->color;
			
			_size = rhs._size;
			_deepCopy(rhs._head, _head);

			return *this;
		}

		Dictionary(Dictionary&& dict) noexcept {
			//define move constructor via move assignment operator
			*this = std::move(dict);
		}

		Dictionary& operator=(Dictionary&& rhs) noexcept {
			if (this != &rhs) {
				_size = std::exchange(rhs._size, 0);
				_head = std::exchange(rhs._head, nullptr);
			}
			return *this;
		}


		ALGOGIN_ERROR insert(Comparable key, V value) noexcept {
			std::shared_ptr current = std::make_shared<Tree>();
			current->key = key;
			current->value = value;
			current->color = COLOR::RED;

			_size++;
			//tree is empty, so set node to head
			if (_head == nullptr) {
				current->color = COLOR::BLACK;
				_head = current;
				return ALGOGIN_ERROR::OK;
			}
			//find place where should we place current key:value pair
			auto parent = _findParent(key);
			if (parent == nullptr)
				return ALGOGIN_ERROR::WRONG_KEY;

			current->parent = parent;
			//insert to specific place in tree
			if (key < parent->key) {
				parent->left = current;
			}
			else {
				parent->right = current;
			}

			return _insert(current);
		}

		ALGOGIN_ERROR remove(Comparable key) noexcept {
			auto target = _find(key);
			if (target == nullptr)
				return ALGOGIN_ERROR::NOT_FOUND;

			//Standard binary search tree remove algorithm
			ALGOGIN_ERROR err = _remove(target);

			_size--;
			return err;
		}

		std::vector<std::tuple<Comparable, V>> traversal(TraversalMode mode) {
			std::vector<std::tuple<Comparable, V>> nodes;

			if (mode == TraversalMode::LEVEL_ORDER) {
				std::list<std::shared_ptr<Tree>> openNodes;

				auto currentNode = _head;
				nodes.push_back({ _head->key, _head->value });
				openNodes.push_back(currentNode);

				while (openNodes.size() > 0) {
					currentNode = openNodes.front();

					auto leftChild = currentNode->left;
					auto rightChild = currentNode->right;

					if (leftChild &&
						std::find(openNodes.begin(), openNodes.end(), leftChild) == openNodes.end()) {
						nodes.push_back({ leftChild->key, leftChild->value });
						openNodes.push_back(leftChild);
					}
					if (rightChild &&
						std::find(openNodes.begin(), openNodes.end(), rightChild) == openNodes.end()) {
						nodes.push_back({ rightChild->key, rightChild->value });
						openNodes.push_back(rightChild);
					}

					openNodes.remove(currentNode);
				}
			}
			return nodes;
		}

		bool exist(Comparable key) noexcept {
			auto target = _find(key);
			if (target == nullptr)
				return false;

			return true;
		}

		V find(Comparable key) {
			auto target = _find(key);
			if (target == nullptr)
				throw std::range_error("Element with index " + std::to_string(key) + " doesn't exist");

			return target->value;
		}

		int getSize() noexcept {
			return _size;
		}
	};

	template <class Comparable, class V>
	class DictionaryDisk {
	private:
		struct Tree {
			std::vector<std::tuple<Comparable, V>> elems;
			std::vector<std::shared_ptr<Tree>> childs;
			std::shared_ptr<Tree> parent;
		};
		//special parameter of B-tree
		int _t;
		std::shared_ptr<Tree> _head;

		int _findPlace(std::shared_ptr<Tree> currentNode, Comparable key) {
			int index = 0;
			for (int i = 1; i < currentNode->elems.size(); i++) {
				if (key >= std::get<0>(currentNode->elems[i - 1]) && key < std::get<0>(currentNode->elems[i])) {
					index = i;
					break;
				}
			}
			if (index == 0 && currentNode->elems.size() > 0 && key > std::get<0>(currentNode->elems[currentNode->elems.size() - 1])) {
				index = currentNode->elems.size();
			}
			
			return index;
		}

		std::tuple<std::shared_ptr<Tree>, int> _find(Comparable key) {
			auto currentNode = _head;
			int index = -1;
			while (currentNode) {
				index = _findPlace(currentNode, key);
				//handle corner cases
				if (index == 0) {
					//element either 0 or last
					if (key == std::get<0>(currentNode->elems[0])) {
						return { currentNode, 0 };
					}
					else if (key == std::get<0>(currentNode->elems[currentNode->elems.size() - 1])) {
						return { currentNode, currentNode->elems.size() - 1 };
					}
					else {
						if (currentNode->childs.size() > 0) {
							currentNode = currentNode->childs[0];
						}
						else
							currentNode = nullptr;
					}
				}
				else if (index > 0) {
					if (key == std::get<0>(currentNode->elems[index - 1])) {
						return { currentNode, index - 1 };
					}
					else {
						if (index < currentNode->childs.size()) {
							currentNode = currentNode->childs[index];
						}
						else
							currentNode = nullptr;
					}
				}
			}

			return { currentNode, index };
		}

		std::shared_ptr<Tree> _split(std::shared_ptr<Tree> currentNode) {
			//find mid element
			int midIndex = _t - 1;
			auto& parent = currentNode->parent;
			if (parent == nullptr) {
				parent = std::make_shared<Tree>();
				if (currentNode == _head)
					_head = parent;
			}

			//move mid element to appropriate place in parent
			auto parentIndex = _findPlace(parent, std::get<0>(currentNode->elems[midIndex]));
			parent->elems.insert(parent->elems.begin() + parentIndex, currentNode->elems[midIndex]);
			//create another node and place all keys greater than mid one there
			auto rightNode = std::make_shared<Tree>();
			rightNode->parent = parent;
			//if parent node just created need to add both childs, otherwise only one
			if (parent->childs.size() == 0)
				parent->childs.push_back(currentNode);
			//+1 because it's right child, left child +0
			parent->childs.insert(parent->childs.begin() + parentIndex + 1, rightNode);
			for (int i = midIndex + 1; i < currentNode->elems.size(); i++) {
				//elements are sorted so may just push back
				rightNode->elems.push_back(currentNode->elems[i]);
			}

			for (int i = midIndex + 1; i < currentNode->childs.size(); i++) {
				rightNode->childs.push_back(currentNode->childs[i]);
				currentNode->childs[i]->parent = rightNode;
			}

			//midIndex without +1 because we move mid element
			currentNode->elems.erase(currentNode->elems.begin() + midIndex, currentNode->elems.end());
			//midIndex + 1 because we have to keep all childs
			if (currentNode->childs.size() > midIndex + 1)
				currentNode->childs.erase(currentNode->childs.begin() + midIndex + 1, currentNode->childs.end());

			return rightNode;
		}

		ALGOGIN_ERROR _deepCopy(std::shared_ptr<Tree> src, std::shared_ptr<Tree> dst) {
			for (int i = 0; i < src->elems.size(); i++) {
				if (i < dst->elems.size())
					dst->elems[i] = src->elems[i];
				else
					dst->elems.push_back(src->elems[i]);
			}

			for (int i = 0; i < src->childs.size(); i++) {
				std::shared_ptr<Tree> node;
				if (i < dst->childs.size())
					node = dst->childs[i];
				else
					node = std::make_shared<Tree>();

				node->parent = dst;
				dst->childs.push_back(node);

				_deepCopy(src->childs[i], node);
			}

			return ALGOGIN_ERROR::OK;
		}

	public:
		DictionaryDisk(int t) {
			_t = t;
		}

		~DictionaryDisk() = default;

		DictionaryDisk(const DictionaryDisk& disk)  noexcept {
			_t = disk._t;
			_head = std::make_shared<Tree>();
			_deepCopy(disk._head, _head);
		}

		DictionaryDisk& operator=(const DictionaryDisk& disk) noexcept {
			_t = disk._t;
			if (_head == nullptr)
				_head = std::make_shared<Tree>();

			_deepCopy(disk._head, _head);

			return *this;
		}

		DictionaryDisk(DictionaryDisk&& disk) noexcept {
			*this = std::move(disk);
		}


		DictionaryDisk& operator=(DictionaryDisk&& disk) noexcept {
			_t = disk._t;
			_head = std::move(disk._head);

			disk._t = 0;
			disk._head = nullptr;

			return *this;
		}

		//IMPORTANT: A new key is always inserted to the leaf node
		ALGOGIN_ERROR insert(Comparable key, V value) noexcept {
			//2
			if (_head == nullptr) {
				_head = std::make_shared<Tree>();
			}

			auto currentNode = _head;
			int leaf = false;
			while (leaf == false) {
				//3
				//check if there is place in current node
				if (currentNode->elems.size() < 2 * _t - 1) {
					//head is the only node, so it's leaf, insert to head
					//3.i
					if (currentNode->childs.size() == 0) {
						auto index = _findPlace(currentNode, key);
						//insert with shift to left?
						currentNode->elems.insert(currentNode->elems.begin() + index, { key, value });
						leaf = true;
					}
					//treat child as current node
					//3.ii
					else {
						auto index = _findPlace(currentNode, key);
						currentNode = currentNode->childs[index];
					}
				}
				//split
				else {
					//4.i
					auto rightChild = _split(currentNode);
					auto leftChild = currentNode;
					auto parent = currentNode->parent;
					//4.ii
					//find appropriate place to insert key (right or left child)
					if (key > std::get<0>(parent->elems[parent->elems.size() - 1])) {
						currentNode = rightChild;
					}
					else {
						currentNode = leftChild;
					}
				}
			}
			return ALGOGIN_ERROR::OK;
		}

		ALGOGIN_ERROR remove(Comparable key) noexcept {
			//first find key and do 3. - prepare tree for remove (so keep at least t keys in the path to key)
			auto currentNode = _head;
			bool deleted = false;
			while (deleted == false) {
				//first of all try to find key in current node
				auto keyIterator = std::find_if(currentNode->elems.begin(), currentNode->elems.end(),
					[key](std::tuple<int, int> item) { return std::get<0>(item) == key; }
				);

				if (keyIterator == std::end(currentNode->elems)) {
					//3. if key isn't found in node we need to check childs sizes and recursively go down
					int indexChild = _findPlace(currentNode, key);

					auto childNode = currentNode->childs[indexChild];

					if (childNode->elems.size() >= _t) {
						currentNode = childNode;
					}
					else {
						std::shared_ptr<Tree> siblingNodeLeft = nullptr;
						std::shared_ptr<Tree> siblingNodeRight = nullptr;
						std::string childSide = "";
						//try to find sibling with at least t keys

						if (indexChild - 1 >= 0 && currentNode->childs.size() > 0) {
							siblingNodeLeft = currentNode->childs[indexChild - 1];
							if (siblingNodeLeft->elems.size() >= _t) {
								childSide = "right";
							}
						}

						if (indexChild + 1 < currentNode->childs.size()) {
							siblingNodeRight = currentNode->childs[indexChild + 1];
							if (siblingNodeRight->elems.size() >= _t) {
								childSide = "left";
							}
						}

						//3.a child node has t-1 elems and sibling has >= t
						if (childSide != "") {
							std::shared_ptr<Tree> siblingNode;
							if (childSide == "left") {
								siblingNode = siblingNodeRight;
								//take right sibling
								//         current
								//        /       \
								//child x.         x. sibling
								childNode->elems.push_back(currentNode->elems[indexChild]);
								currentNode->elems[indexChild] = siblingNode->elems[0];
								siblingNode->elems.erase(siblingNode->elems.begin());
								//move child from sibling to child
								if (siblingNode->childs.size() > 0) {
									childNode->childs.push_back(siblingNode->childs[0]);
									siblingNode->childs.erase(siblingNode->childs.begin());
								}
							}
							else if (childSide == "right") {
								siblingNode = siblingNodeLeft;
								//take left sibling
							    //           current
							    //          /       \
							    //sibling x.         x. child
								childNode->elems.insert(childNode->elems.begin(), currentNode->elems[indexChild]);
								currentNode->elems[indexChild] = siblingNode->elems[siblingNode->elems.size() - 1];
								siblingNode->elems.erase(siblingNode->elems.end());
								//move child from sibling to child
								if (siblingNode->childs.size() > 0) {
									childNode->childs.insert(childNode->childs.begin(), siblingNode->childs[siblingNode->childs.size() - 1]);
									siblingNode->childs.erase(siblingNode->childs.end());
								}
							}

							currentNode = childNode;
						}
						//3.b both siblings contain t - 1 elements, so merge child and sibling into left node (either child or sibling whatever is left) and make element from currentNode as mid element
						else {
							//take any sibling
							std::shared_ptr<Tree> siblingNode;
							if (siblingNodeRight) {
								siblingNode = siblingNodeRight;
								childSide = "left";
							}
							else if (siblingNodeLeft) {
								siblingNode = siblingNodeLeft;
								childSide = "right";
							}

							std::shared_ptr<Tree> leftChild, rightChild;
							if (childSide == "left") {
								leftChild = childNode;
								rightChild = siblingNode;

								leftChild->elems.push_back(currentNode->elems[indexChild]);
								currentNode->elems.erase(currentNode->elems.begin() + indexChild);
								currentNode->childs.erase(currentNode->childs.begin() + indexChild + 1);
							}
							else {
								rightChild = childNode;
								leftChild = siblingNode;

								//index is related to childs but we want element from current node to become mid key for current node childs
								leftChild->elems.push_back(currentNode->elems[indexChild - 1]);
								currentNode->elems.erase(currentNode->elems.begin() + indexChild - 1);
								currentNode->childs.erase(currentNode->childs.begin() + indexChild);
							}

							for (auto elem : rightChild->elems)
								leftChild->elems.push_back(elem);

							for (auto child : rightChild->childs)
								leftChild->childs.push_back(child);

							if (currentNode == _head && currentNode->elems.size() == 0)
								_head = leftChild;

							currentNode = leftChild;
						}
					}
				}
				else {
					int indexKey = std::distance(currentNode->elems.begin(), keyIterator);
					//1. If the key k is in node x and x is a leaf, delete the key k from x
					if (currentNode->childs.size() == 0) {
						//node is leaf
						currentNode->elems.erase(currentNode->elems.begin() + indexKey);
						deleted = true;
					}
					//2. If the key k is in node x and x is an internal node
					else {
						if (currentNode->childs[indexKey] && currentNode->childs[indexKey]->elems.size() >= _t) {
							//2.a take left child of key, if it contains at least t keys, then find predeccessor in child subtree and swap with key and recursively delete key
							auto leftChild = currentNode->childs[indexKey];
							//find predecessor of key in sub-tree of left child (it's right-most node in left child)
							auto findNode = leftChild;
							while (findNode->childs.size() > 0) {
								findNode = findNode->childs[findNode->childs.size() - 1];
							}

							currentNode->elems[indexKey] = findNode->elems[findNode->elems.size() - 1];
							currentNode = leftChild;
							//now we need to delete successor node, we can't swap because it can break tree somehow, so just do more robust approach
							key = std::get<0>(findNode->elems[findNode->elems.size() - 1]);
						}
						else if (currentNode->childs[indexKey + 1] && currentNode->childs[indexKey + 1]->elems.size() >= _t) {
							//2.b take right child of key, if it contains at least t keys, then find successor in child subtree and swap with key and recursively delete key
							auto rightChild = currentNode->childs[indexKey + 1];
							//find successor of key in sub-tree of right child (it's left-most node in right child)
							auto findNode = rightChild;
							while (findNode->childs.size() > 0) {
								findNode = findNode->childs[0];
							}

							currentNode->elems[indexKey] = findNode->elems[0];
							currentNode = rightChild;
							//now we need to delete successor node, we can't swap because it can break tree somehow, so just do more robust approach
							key = std::get<0>(findNode->elems[0]);
						}
						else if (currentNode->childs[indexKey] && currentNode->childs[indexKey + 1]) {
							//2.c both children have only t-1 keys, merge key and keys from right child to left child, remove right child (as key from node), so new child will be left child of key's right element in node
							//recursively delete key from child
							auto leftChild = currentNode->childs[indexKey];
							auto rightChild = currentNode->childs[indexKey + 1];
							//insert key to left child
							leftChild->elems.push_back(currentNode->elems[indexKey]);
							//remove key
							currentNode->elems.erase(currentNode->elems.begin() + indexKey);
							//move all items from right child to left child
							leftChild->elems.insert(leftChild->elems.end(), rightChild->elems.begin(), rightChild->elems.end());
							//remove right child from tree
							currentNode->childs.erase(currentNode->childs.begin() + indexKey + 1);
							//recursively call delete from left child
							currentNode = leftChild;
						}
					}
				}
			}
			return ALGOGIN_ERROR::OK;
		}

		std::vector<std::tuple<Comparable, V>> traversal(TraversalMode mode) noexcept {
			std::vector<std::tuple<Comparable, V>> nodes;
			
			if (mode == TraversalMode::LEVEL_ORDER) {
				std::list<std::shared_ptr<Tree>> openNodes;
				if (_head) {
					auto currentNode = _head;
					for (int i = 0; i < _head->elems.size(); i++)
						nodes.push_back({ std::get<0>(_head->elems[i]), std::get<1>(_head->elems[i]) });

					openNodes.push_back(currentNode);

					while (openNodes.size() > 0) {
						currentNode = openNodes.front();

						for (auto child : currentNode->childs) {
							if (child && std::find(openNodes.begin(), openNodes.end(), child) == openNodes.end()) {
								for (int i = 0; i < child->elems.size(); i++)
									nodes.push_back({ std::get<0>(child->elems[i]), std::get<1>(child->elems[i]) });
								openNodes.push_back(child);
							}
						}

						openNodes.remove(currentNode);
					}
				}
			}
			return nodes;
		}

		std::optional<V> find(Comparable key) noexcept {
			auto [node, index] = _find(key);
			if (node)
				return std::get<1>(node->elems[index]);

			return std::nullopt;
		}
	};
}
