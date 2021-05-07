#pragma once
#include <memory>
#include "Common.h"
#include <concepts>
#include <optional>
#include <list>

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
			int index = currentNode->elems.size() - 1;
			//head is the only node, so it's leaf, insert to head
			if (currentNode->childs.size() == 0) {
				index = 0;
				for (int i = 1; i < currentNode->elems.size(); i++) {
					if (key > std::get<0>(currentNode->elems[i - 1]) && key < std::get<0>(currentNode->elems[i])) {
						index = i;
						break;
					}
				}
				if (index == 0 && key > std::get<0>(currentNode->elems[currentNode->elems.size() - 1])) {
					index = currentNode->elems.size() - 1;
				}
			}
			return index;
		}

		std::shared_ptr<Tree> _split(std::shared_ptr<Tree> currentNode) {
			//find mid element
			int midIndex = _t - 1;
			auto parent = currentNode->parent;
			//move mid element to appropriate place in parent
			auto parentIndex = _findPlace(parent, std::get<0>(currentNode->elems[midIndex]));
			parent->elems.insert(parent->elems.begin() + parentIndex, currentNode->elems[midIndex]);
			//create another node and place all keys greater than mid one there
			auto rightNode = std::make_shared<Tree>();
			rightNode->parent = parent;
			parent->childs.insert(parent->childs.begin() + parentIndex, rightNode);
			for (int i = midIndex + 1; i < currentNode->elems.size(); i++) {
				//elements are sorted so may just push back
				rightNode->elems.push_back(currentNode->elems[i]);
				rightNode->childs.push_back(currentNode->childs[i]);
			}
			currentNode->elems.erase(currentNode->elems.begin() + midIndex, currentNode->elems.end());
			currentNode->childs.erase(currentNode->childs.begin() + midIndex, currentNode->childs.end());

			return rightNode;
		}

	public:
		DictionaryDisk(int t) {
			_t = t;
		}

		//IMPORTANT: A new key is always inserted to the leaf node
		ALGOGIN_ERROR insert(Comparable key, V value) {
			if (_head == nullptr) {
				_head = std::make_shared<Tree>();
				_head->elems.push_back({ key, value });
				return ALGOGIN_ERROR::OK;
			}

			auto currentNode = _head;
			int leaf = false;
			while (leaf == false) {
				//check if there is place in current node
				if (currentNode->elems.size() < 2 * _t - 1) {
					//head is the only node, so it's leaf, insert to head
					if (currentNode->childs.size() == 0) {
						auto index = _findPlace(currentNode, key);
						//insert with shift to left?
						currentNode->elems.insert(currentNode->elems.begin() + index, { key, value });
						leaf = true;
					}
					//treat child as current node
					else {
						auto index = _findPlace(currentNode, key);
						currentNode = currentNode->childs[index];
					}
				}
				//split
				else {
					auto rightNode = _split(currentNode);
					//find appropriate place to insert key
					if (key > std::get<0>(currentNode->elems[currentNode->elems.size() - 1])) {
						if (rightNode->childs.size() == 0) {
							auto index = _findPlace(rightNode, key);
							rightNode->elems.insert(rightNode->elems.begin() + index, { key, value });
							leaf = true;
						}
						else {
							auto index = _findPlace(rightNode, key);
							currentNode = rightNode->childs[index];
						}
					}
					else {
						if (currentNode->childs.size() == 0) {
							auto index = _findPlace(currentNode, key);
							currentNode->elems.insert(currentNode->elems.begin() + index, { key, value });
							leaf = true;
						}
						else {
							auto index = _findPlace(currentNode, key);
							currentNode = currentNode->childs[index];
						}
					}

				}
			}

		}

	};
}