#pragma once

#include <iostream>
#include <fstream>
#include <memory>
#include <optional>
#include <Common.h>
#include <filesystem>
#include <concepts>

namespace algogin {
	//Implementation of single value container with access by index
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

		List(const List& list) noexcept {
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
		
		List& operator=(const List& rhs) noexcept {
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

			return *this;
		}

		List(List&& list) noexcept {
			//define move constructor via move assignment operator
			*this = std::move(list);
		}

		List& operator=(List&& rhs) noexcept {
			if (this != &rhs) {
				_size = std::exchange(rhs._size, 0);
				_head = std::exchange(rhs._head, nullptr);
			}
			return *this;
		}

		T operator[](int index) const {
			std::shared_ptr<Node> currentNode = _head;
			for (int i = 0; i < index; i++) {
				currentNode = currentNode->_next;
			}

			if (currentNode == nullptr)
				throw std::out_of_range("List, operator[]: index is out of range");

			return currentNode->_value;
		}

		ALGOGIN_ERROR insert(T element, int index) noexcept {
			//in insert index should be either in range 0-size inclusive
			if (index > _size || index < 0)
				return ALGOGIN_ERROR::OUT_OF_BOUNDS;

			std::shared_ptr<Node> newNode = std::make_shared<Node>();
			newNode->_value = element;

			std::shared_ptr<Node> currentNode = _head;
			for (int i = 0; i < index - 1; i++) {
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
			if (index >= _size || index < 0)
				return ALGOGIN_ERROR::OUT_OF_BOUNDS;

			_size -= 1;

			if (index == 0) {
				_head = _head->_next;
				return ALGOGIN_ERROR::OK;
			}

			std::shared_ptr previousNode = _head;
			for (int i = 0; i < index - 1; i++) {
				previousNode = previousNode->_next;
			}

			std::shared_ptr currentNode = previousNode->_next;
			previousNode->_next = currentNode->_next;

			return ALGOGIN_ERROR::OK;
		}
		
		int getSize() const noexcept {
			return _size;
		}

		//Auxilary operations
		ALGOGIN_ERROR load(const std::filesystem::path& path) {
			if (std::filesystem::exists(path) == false) {
				return ALGOGIN_ERROR::NOT_FOUND;
			}
			std::ifstream file{path};
			file >> _size;
			std::shared_ptr<Node> previousNode = nullptr;
			for (int i = 0; i < _size; i++) {
				std::shared_ptr currentNode = std::make_shared<Node>();
				if (previousNode)
					previousNode->_next = currentNode;
				if (_head == nullptr)
					_head = currentNode;

				file >> currentNode->_value;
				previousNode = currentNode;
			}

			return ALGOGIN_ERROR::OK;
		}

		ALGOGIN_ERROR dump(const std::filesystem::path& path) {
			std::ofstream file{path};
			file << _size << std::endl;
			std::shared_ptr current = _head;
			for (int i = 0; i < _size; i++) {
				file << current->_value << " ";
				current = current->_next;
			}
			return ALGOGIN_ERROR::OK;
		}

		ALGOGIN_ERROR print() noexcept {
			std::shared_ptr currentNode = _head;
			for (int i = 0; i < _size; i++) {
				std::cout << currentNode->_value << " ";
				currentNode = currentNode->_next;
			}
			std::cout << std::endl;
			return ALGOGIN_ERROR::OK;
		}
	};
}