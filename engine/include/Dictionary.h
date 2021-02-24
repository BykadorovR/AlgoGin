#pragma once

#include <iostream>
#include <optional>
#include <functional>
#include "Errors.h"
#include <Common.h>

namespace algogin {
	//Strategy class
	template <class K = std::string, class T = int>
	class Dictionary {
	private:
		std::shared_ptr<Dictionary> _impl;
	public:
		explicit Dictionary(std::shared_ptr<Dictionary> impl) : _impl(impl) {};
		//Dictionary operations
		virtual T get(K key) noexcept = 0;
		virtual ALGOGIN_ERROR insert(std::pair<K, T> element) noexcept = 0;
		virtual ALGOGIN_ERROR remove(K value) noexcept = 0;
		virtual ALGOGIN_ERROR successor(T value) noexcept = 0;
		virtual ALGOGIN_ERROR predecessor(T value) noexcept = 0;
		//Auxilary operations
		virtual ALGOGIN_ERROR load(std::string path) = 0;
		virtual ALGOGIN_ERROR dump(std::string path) = 0;
		virtual ALGOGIN_ERROR print(std::string path) noexcept = 0;
		virtual ALGOGIN_ERROR random(std::optional<int> size) noexcept = 0;
	};

	//Implementation of dictionary using doubly linked list
	template <class K = std::string, class T = int>
	class List : protected Dictionary {
	private:
		struct Node {
			std::pair<K, T> value;
			std::unique_ptr<Node> next;
			std::unique_ptr<Node> previous;
		};

		std::unique_ptr<Node> _head = nullptr;
		std::unique_ptr<Node> _last = nullptr;
		std::unique_ptr<Node> _current = nullptr;
		int _size = 0;
	public:
		List() = default;
		~List() = default;
		List(const List& list) = delete;
		void operator=(const List& rhs) = delete;
		List(const List&& list) noexcept {

		}
		void operator=(const List&& rhs) {

		}
	};
}