#pragma once
#include <vector>

class Sorting {
private:
	template <class T>
	void _merge(std::vector<T>& input, int start, int midpoint, int end) {
		std::vector<T> left(input.begin() + start, input.begin() + midpoint + 1);
		std::vector<T> right(input.begin() + midpoint + 1, input.begin() + end + 1);

		int index = 0;
		while (left.size() > 0 && right.size() > 0) {
			if (left[0] < right[0]) {
				input[index] = left[0];
				left.erase(left.begin());
			}
			else {
				input[index] = right[0];
				right.erase(right.begin());
			}
			index++;
		}

		if (left.size() == 0)
			while (right.size() > 0) {
				input[index] = right[0];
				right.erase(right.begin());
				index++;
			}

		if (right.size() == 0)
			while (left.size() > 0) {
				input[index] = left[0];
				left.erase(left.begin());
				index++;
			}
	}

	template <class T>
	void _mergeSort(std::vector<T>& input, int start, int end) {
		if (start < end) {
			int midpoint = (start + end) / 2;
			_mergeSort(input, start, midpoint);
			_mergeSort(input, midpoint+1, end);
			_merge(input, start, midpoint, end);
		}
	}
public:
	Sorting() = default;
	~Sorting() = default;
	
	template <class T>
	std::vector<T> bubbleSort(std::vector<T> input) {
		std::vector<T> output(input);

		//early stop to guarantee O(n) if array is sorted
		for (int i = 1; i < output.size(); i++) {
			bool swapped = false;
			for (int j = 0; j < output.size() - i; j++) {
				if (output[j] > output[j + 1]) {
					std::swap(output[j], output[j + 1]);
					swapped = true;
				}
			}
			if (swapped == false)
				break;
		}

		return output;
	}

	template <class T>
	std::vector<T> selectionSort(std::vector<T> input) {
		std::vector<T> output(input);

		for (int i = 0; i < output.size() - 1; i++) {
			T minimum = i;
			for (int j = i + 1; j < output.size(); j++) {
				if (output[minimum] > output[j])
					minimum = j;
			}
			std::swap(output[i], output[minimum]);
		}

		return output;
	}

	template <class T>
	std::vector<T> insertionSort(std::vector<T> input) {
		std::vector<T> output(input);
		//we divide array to 2 parts: sorted and unsorted
		//first element is already sorted so pick starting from second
		for (int i = 1; i < output.size(); i++) {
			int j = i;
			//swap all elements to one element right if current element less than previous one
			while (j > 0 && output[j] < output[j - 1]) {
				std::swap(output[j], output[j - 1]);
				j--;
			}
		}

		return output;
	}

	template <class T>
	std::vector<T> mergeSort(std::vector<T> input) {
		std::vector<T> output(input);
		_mergeSort(output, 0, output.size());

		return output;
	}
};
