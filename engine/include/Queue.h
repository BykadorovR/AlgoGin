#pragma once
#include "Common.h"
#include <vector>

namespace algogin {

	template <class Comparable, class V>
	class PriorityQueue {
	private:
		struct Heap {
			Comparable priority;
			V value;
		};

		std::vector<Heap> _heap;
	public:
		PriorityQueue() = default;
		~PriorityQueue() = default;

		PriorityQueue(const PriorityQueue& queue) noexcept {

		}

		PriorityQueue(PriorityQueue&& queue) noexcept {

		}

		PriorityQueue& operator=(const PriorityQueue& queue) noexcept {

		}

		PriorityQueue& operator=(PriorityQueue&& queue) noexcept {

		}

		ALGOGIN_ERROR insert(Comparable priority, V value) {
			//first we insert element to the end of the heap
			_heap.push_back(Heap{ .priority = priority, .value = value });

			int index = _heap.size() - 1;
			int parentIndex = index / 2;

			//now we should swap this element with parent node if the element less than parent + repeat recursively
			while (parentIndex > 0 && parentIndex != index && _heap[parentIndex].priority > _heap[index].priority) {
				//swap parent and current elements
				std::swap(_heap[parentIndex], _heap[index]);

				index = parentIndex;
				parentIndex = index / 2;
			}

			return ALGOGIN_ERROR::OK;
		}

		V getMinimum(Comparable priority) {
			return 0;
		}
	};
}