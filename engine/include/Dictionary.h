#pragma once
#include <memory>
#include "Common.h"
#include <concepts>
#include <optional>

namespace algogin {
	//Dictionary implementation based on red-black tree
	template <class Comparable, class V>
	class Dictionary
	{
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

		std::shared_ptr<Tree> _findUncle(std::shared_ptr<Tree> currentNode) {
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
			if (grandParent->left == parent)
				uncle = grandParent->right;
			else
				uncle = grandParent->left;

			return uncle;
		}

		std::shared_ptr<Tree> _findParent(Comparable key) {
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

		ALGOGIN_ERROR _recolor(std::shared_ptr<Tree> current) {
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
			return _recolor(grandParent);
		}

		//small rotation (left sub-tree for parent and left sub-tree for current node)
		ALGOGIN_ERROR _leftLeftRotation(std::shared_ptr<Tree> current) {
			//parent of currentNode parent - p, grand-parent - g
			//p takes g parent, g becomes p right child + g parent = p
			//swap p and g colors
			auto father = current->parent;
			if (father == nullptr)
				return ALGOGIN_ERROR::UNKNOWN_ERROR;

			auto grandFather = father->parent;
			if (grandFather == nullptr)
				return ALGOGIN_ERROR::UNKNOWN_ERROR;

			if (_head == grandFather)
				_head = father;

			father->parent = grandFather->parent;
			if (grandFather->parent) {
				if (grandFather->parent->left == grandFather)
					grandFather->parent->left = father;
				else
					grandFather->parent->right = father;
			}
			grandFather->left = father->right;
			father->right = grandFather;
			grandFather->parent = father;

			std::swap(grandFather->color, father->color);

			return ALGOGIN_ERROR::OK;
		}

		//small rotation (mirror of left-left one - right sub-tree for parent and right sub-tree for current node)
		ALGOGIN_ERROR _rightRightRotation(std::shared_ptr<Tree> current) {
			auto father = current->parent;
			if (father == nullptr)
				return ALGOGIN_ERROR::UNKNOWN_ERROR;

			auto grandFather = father->parent;
			if (grandFather == nullptr)
				return ALGOGIN_ERROR::UNKNOWN_ERROR;

			if (_head == grandFather)
				_head = father;

			father->parent = grandFather->parent;
			if (grandFather->parent) {
				if (grandFather->parent->left == grandFather)
					grandFather->parent->left = father;
				else
					grandFather->parent->right = father;
			}
			grandFather->right = father->left;
			father->left = grandFather;
			grandFather->parent = father;

			std::swap(grandFather->color, father->color);

			return ALGOGIN_ERROR::OK;
		}


		ALGOGIN_ERROR _leftRightRotation(std::shared_ptr<Tree> current) {
			//rotate parent to left
			auto father = current->parent;
			if (father == nullptr)
				return ALGOGIN_ERROR::UNKNOWN_ERROR;

			auto grandFather = father->parent;
			if (grandFather == nullptr)
				return ALGOGIN_ERROR::UNKNOWN_ERROR;

			if (_head == grandFather)
				_head = father;

			grandFather->left = current;
			current->parent = grandFather;
			father->parent = current;
			father->right = current->left;
			current->left = father;

			_leftLeftRotation(father);
		}

		ALGOGIN_ERROR _rightLeftRotation(std::shared_ptr<Tree> current) {
			//rotate parent to right
			auto father = current->parent;
			if (father == nullptr)
				return ALGOGIN_ERROR::UNKNOWN_ERROR;

			auto grandFather = father->parent;
			if (grandFather == nullptr)
				return ALGOGIN_ERROR::UNKNOWN_ERROR;

			if (_head == grandFather)
				_head = father;

			grandFather->right = current;
			current->parent = grandFather;
			father->parent = current;
			father->left = current->right;
			current->right = father;

			_rightRightRotation(father);
		}

	public:
		Dictionary() = default;
		~Dictionary() = default;
		Dictionary(const Dictionary& dict) noexcept;
		Dictionary& operator=(const Dictionary& rhs) noexcept;
		Dictionary(Dictionary&& dict) noexcept;
		Dictionary& operator=(Dictionary&& rhs) noexcept;


		ALGOGIN_ERROR insert(Comparable key, V value) noexcept {
			std::shared_ptr current = std::make_shared<Tree>();
			current->key = key;
			current->value = value;
			current->color = COLOR::RED;
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
			
			//check if parent's node color is black then no problem
			if (current->parent->color == COLOR::BLACK)
				return ALGOGIN_ERROR::OK;

			//if father's color is red when we have to recolor or rebalance tree depending on uncle's color
			auto uncle = _findUncle(current);
			//if uncle color is red, when need to recolor nodes
			if (uncle && uncle->color == COLOR::RED) {
				_recolor(current);
			}
			else if (uncle == nullptr || uncle->color == COLOR::BLACK) {
				//if parent left sub-tree and current left sub-tree
				if (parent->parent->left == parent && parent->left == current) {
					_leftLeftRotation(current);
				}
				else if (parent->parent->right == parent && parent->right == current) {
					_rightRightRotation(current);
				}
				else if (parent->parent->left == parent && parent->right == current) {
					_leftRightRotation(current);
				}
				else if (parent->parent->right == parent && parent->left == current) {
					_rightLeftRotation(current);
				}
			}

		}

		ALGOGIN_ERROR find(Comparable key) const noexcept;
		

	};
}