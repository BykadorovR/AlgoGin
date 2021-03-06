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
		enum class Color {
			RED,
			BLACK
		};

		struct Tree {
			V value;
			Comparable key;
			Color color;
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

		}

	public:
		Dictionary() = default;
		~Dictionary() = default;
		Dictionary(const Dictionary& dict) noexcept;
		Dictionary& operator=(const Dictionary& rhs) noexcept;
		Dictionary(Dictionary&& dict) noexcept;
		Dictionary& operator=(Dictionary&& rhs) noexcept;


		ALGOGIN_ERROR insert(Comparable key, V value) noexcept {
			std::shared_ptr node = std::make_shared<Tree>();
			node->key = key;
			node->value = value;
			node->color = Color::RED;
			//tree is empty, so set node to head
			if (_head == nullptr) {
				node->color = Color::BLACK;
				_head = node;
				return ALGOGIN_ERROR::OK;
			}
			//find place where should we place current key:value pair
			auto parent = _findParent(key);
			if (parent == nullptr)
				return ALGOGIN_ERROR::WRONG_KEY;
			
			//insert to specific place in tree
			if (value < parent->value) {
				parent->left = node;
				node->parent = parent;
			}
			
			//check if parent's node color is black then no problem
			if (node->parent->color == Color::BLACK)
				return ALGOGIN_ERROR::OK;

			std::shared_ptr<Tree> uncle;
			auto uncle = _findUncle(node);


		}

		ALGOGIN_ERROR find(Comparable key) const noexcept;
		

	};
}