#pragma once
#include "Common.h"
#include <vector>
#include <functional>
#include <optional>

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
			int parentIndex = (index - 1) / 2;

			//now we should swap this element with parent node if the element less than parent + repeat recursively
			while (parentIndex != index && _heap[parentIndex].priority > _heap[index].priority) {
				//swap parent and current elements
				std::swap(_heap[parentIndex], _heap[index]);

				index = parentIndex;
				parentIndex = (index - 1) / 2;
			}

			return ALGOGIN_ERROR::OK;
		}

		std::vector<std::tuple<Comparable, V>> traversal(TraversalMode mode) {
			std::vector<std::tuple<Comparable, V>> result;
			for (auto elem : _heap) {
				result.push_back({elem.priority, elem.value});
			}

			return result;
		}

		std::optional<std::tuple<Comparable, V>> getMinimum(Comparable priority) {
			if (_heap.size() == 0)
				return std::nullopt;

			std::tuple<Comparable, V> result = { _heap[0].priority, _heap[0].value };

			//first we have to swap minimum element with the last element		
			std::swap(_heap[0], _heap[_heap.size() - 1]);
			//remove last element
			_heap.pop_back();
			//heapify (if parent bigger than child then need to swap with the smallest child)
			int index = 0;
			std::function findMinimumChild = [_heap](int index) -> int {
				int leftChild = index * 2 + 1;
				int rightChild = index * 2 + 2;
				int childMinimum = -1;
				if (leftChild < _heap.size()) {
					childMinimum = leftChild;
				}
				if (rightChild < _heap.size() && _heap[rightChild] < _heap[leftChild]) {
					childMinimum = rightChild;
				}

				return childMinimum;
			};

			int childMinimum = findMinimumChild(index);
			while (childMinimum > 0 && _heap[index] > _heap[childMinimum]) {
				std::swap(_heap[index], _heap[childMinimum]);

				index = childMinimum;
				childMinimum = findMinimumChild(index);
			}

			return result;
		}
	};
}