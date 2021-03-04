#pragma once
#include <memory>
#include "Common.h"
#include <concepts>

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

		std::shared_ptr<Tree> findParent(Comparable key) {
			std::shared_ptr<Tree> currentNode = _head;
			std::shared_ptr<Tree> parent = nullptr;
			while (currentNode) {
				if (key < currentNode->key) {
					parent = currentNode->parent;
					currentNode = currentNode->left;
				}
				else if (key > currentNode->key) {
					currentNode = currentNode->right;
				}
			}

			return parent;
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
			if (_head == nullptr) {
				node->color = Color::BLACK;
				_head = node;
				return ALGOGIN_ERROR::OK;
			}

			auto parent = findParent(key);
			if (parent == nullptr)
				return ALGOGIN_ERROR::WRONG_KEY;
			


		}

		ALGOGIN_ERROR find(Comparable key) const noexcept;
		

	};
}