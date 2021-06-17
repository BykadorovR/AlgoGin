#pragma once
#include <vector>

class Sorting {
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
			while (j > 0) {
				if (output[j] < output[j - 1]) {
					std::swap(output[j], output[j - 1]);
				}
				j--;
			}
		}

		return output;
	}
};
