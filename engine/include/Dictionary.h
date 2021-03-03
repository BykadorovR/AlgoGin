#pragma once
#include <memory>
#include "Common.h"
#include <concepts>

namespace algogin {
	template <class Comparable, class V>
	class Dictionary
	{
	private:
		struct Tree {
			V value;
			Comparable key;
			std::shared_ptr<Tree> parent;
			std::shared_ptr<Tree> left;
			std::shared_ptr<Tree> right;
		};

		std::shared_ptr<Tree> _head = nullptr;
		int _size = 0;
	public:
		Dictionary() = default;
		~Dictionary() = default;
		Dictionary(const Dictionary& dict) noexcept;
		Dictionary& operator=(const Dictionary& rhs) noexcept;
		Dictionary(Dictionary&& dict) noexcept;
		Dictionary& operator=(Dictionary&& rhs) noexcept;

		ALGOGIN_ERROR find(Comparable key) const noexcept;
		ALGOGIN_ERROR insert(Comparable key, V value) noexcept;

	};
}