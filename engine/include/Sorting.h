#pragma once
#include <vector>

class Sorting {
	Sorting() = default;
	~Sorting() = default;
	
	template <class T>
	std::vector<T> bubbleSort(std::vector<T> input) {
		std::vector<T> output;
		std::copy(input.begin(), input.end(), output);

		bool swapped = false;
		for (int i = 1; i < output.size(); i++) {
			for (int j = 0; j < output.size() - i; j++) {
				if (output[j] > output[j + 1]) {
					std::swap(output[j], output[j + 1]);
					swapped = true;
				}
			}


		}
	}
};
