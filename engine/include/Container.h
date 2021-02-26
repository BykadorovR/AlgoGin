#pragma once

#include <iostream>
#include <optional>
#include <functional>
#include <Common.h>

namespace algogin {
	//Implementation of container - stack, with access by index
	template <class T>
	class List {
	private:
		struct Node {
			T _value;
			std::shared_ptr<Node> _next;
			std::shared_ptr<Node> _previous;
		};

		std::shared_ptr<Node> _head = nullptr;
		int _size = 0;
	public:
		List() = default;
		~List() = default;
		List(const List& list) {

		}
		void operator=(const List& rhs) {

		}
		List(const List&& list) noexcept {

		}
		void operator=(const List&& rhs) {

		}

		T operator[](int index) {
			std::shared_ptr<Node> currentNode = _head;
			for (int currentIndex = 0; currentIndex < index; currentIndex++) {
				currentNode = currentNode->_next;
			}
			return currentNode->_value;
		}

		ALGOGIN_ERROR insert(T element, int index) noexcept {
			if (index > _size)
				return ALGOGIN_ERROR::OUT_OF_BOUNDS;

			std::shared_ptr<Node> currentNode = _head;
			for (int currentIndex = 0; currentIndex < index; currentIndex++) {
				currentNode = currentNode->_next;
			}
			std::shared_ptr<Node> newNode = std::make_shared<Node>();
			newNode->_value = element;
			newNode->_previous = currentNode;
			newNode->_next = currentNode->_next;
			_size++;

			return ALGOGIN_ERROR::OK;
		}

		ALGOGIN_ERROR remove(T value) noexcept {
			return ALGOGIN_ERROR::OK;
		}
		
		//Auxilary operations
		ALGOGIN_ERROR load(std::string path) {
			return ALGOGIN_ERROR::OK;
		}
		ALGOGIN_ERROR dump(std::string path) {
			return ALGOGIN_ERROR::OK;
		}
		ALGOGIN_ERROR print() noexcept {
			return ALGOGIN_ERROR::OK;
		}
		ALGOGIN_ERROR random(std::optional<int> size) noexcept {
			return ALGOGIN_ERROR::OK;
		}
	};
}