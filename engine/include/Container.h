#pragma once

#include <iostream>
#include <memory>
#include <optional>
#include <Common.h>

namespace algogin {
	//Implementation of signle value container with access by index
	//analog of std::vector
	template <class T>
	class List {
	private:
		struct Node {
			T _value;
			std::shared_ptr<Node> _next;
		};

		std::shared_ptr<Node> _head = nullptr;
		int _size = 0;
	public:
		List() = default;
		~List() = default;

		List(const List& list) {
			_size = list._size;

			std::shared_ptr first = std::make_shared<Node>();
			first->_value = list[0];
			_head = first;
			std::shared_ptr previous = _head;
			for (int i = 1; i < _size; i++) {
				std::shared_ptr current = std::make_shared<Node>();
				current->_value = list[i];
				previous->_next = current;
				previous = current;
			}
		}
		
		void operator=(const List& rhs) {
			_size = rhs._size;

			std::shared_ptr currentNode = _head;
			std::shared_ptr previousNode = currentNode;
			for (int i = 0; i < rhs._size; i++) {
				if (currentNode == nullptr) {
					currentNode = std::make_shared<Node>();
					previousNode->_next = currentNode;
				}

				currentNode->_value = rhs[i];
				previousNode = currentNode;
				currentNode = currentNode->_next;
			}
			//break the list if size of current list is bigger than target list
			//all shared_ptrs in tail should be deallocated
			previousNode->_next = nullptr;
		}

		List(const List&& list) noexcept {

		}
		void operator=(const List&& rhs) {

		}

		T operator[](int index) const {
			std::shared_ptr<Node> currentNode = _head;
			for (int currentIndex = 0; currentIndex < index; currentIndex++) {
				currentNode = currentNode->_next;
			}

			if (currentNode == nullptr)
				throw std::out_of_range("List, operator[]: index is out of range");

			return currentNode->_value;
		}

		ALGOGIN_ERROR insert(T element, int index) noexcept {
			if (index > _size || index < 0)
				return ALGOGIN_ERROR::OUT_OF_BOUNDS;

			std::shared_ptr<Node> newNode = std::make_shared<Node>();
			newNode->_value = element;

			std::shared_ptr<Node> currentNode = _head;
			for (int currentIndex = 0; currentIndex < index - 1; currentIndex++) {
				currentNode = currentNode->_next;
			}

			if (index == 0) {
				newNode->_next = _head;
				_head = newNode;
			}
			else {
				newNode->_next = currentNode->_next;
				currentNode->_next = newNode;
			}
			_size++;

			return ALGOGIN_ERROR::OK;
		}

		ALGOGIN_ERROR remove(int index) noexcept {
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
			std::shared_ptr<Node> currentNode = _head;
			for (int i = 0; i < _size; i++) {
				std::cout << currentNode->_value << " ";
				currentNode = currentNode->_next;
			}
			std::cout << std::endl;
			return ALGOGIN_ERROR::OK;
		}
		ALGOGIN_ERROR random(std::optional<int> size) noexcept {
			return ALGOGIN_ERROR::OK;
		}
	};
}