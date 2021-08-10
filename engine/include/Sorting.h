#pragma once
#include <vector>

class Sorting {
private:
	template <class T>
	int _partition(std::vector<T>& input, int start, int end) {
		int i = start - 1;
		//choose anchor element
		T anchor = input[end - 1];
		for (int j = start; j < end - 1; j++) {
			//swap element i with j if element j less than anchor
			if (input[j] < anchor) {
				i++;
				std::swap(input[j], input[i]);
			}
			//if element bigger do nothing
		}
		//place anchor to correct place (end of section with elements less than anchor)
		i++;
		std::swap(input[end - 1], input[i]);
		return i;
	}

	template <class T>
	void _quickSort(std::vector<T>& input, int start, int end) {
		//end exclusive
		if (end - start > 1) {
			int anchorIndex = _partition(input, start, end);

			//elements less than anchor
			_quickSort(input, start, anchorIndex);
			//elements greater than anchor
			_quickSort(input, anchorIndex + 1, end);
		}
	}

	template <class T>
	void _merge(std::vector<T>& input, int start, int midpoint, int end) {
		std::vector<T> left(input.begin() + start, input.begin() + midpoint + 1);
		int endID = end + 1;
		if (endID > input.size())
			endID = input.size();

		std::vector<T> right(input.begin() + midpoint + 1, input.begin() + endID);
		int indexLeft = 0, indexRight = 0;
		int index = start;
		//sorting: choose first element from left and right (they are sorted) and compare. Move least one to resulting array.
		//do until both arrays have elements
		while (indexLeft < left.size() && indexRight < right.size()) {
			if (left[indexLeft] < right[indexRight]) {
				input[index] = left[indexLeft];
				indexLeft++;
			}
			else {
				input[index] = right[indexRight];
				indexRight++;
			}

			index++;
		}

		//move elements from array with size > 0 (there is only one array left with size > 0)
		while (indexRight < right.size()) {
			input[index] = right[indexRight];
			indexRight++;
			index++;
		}

		while (indexLeft < left.size()) {
			input[index] = left[indexLeft];
			indexLeft++;
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

	template <class T>
	std::vector<T> quickSort(std::vector<T> input) {
		std::vector<T> output(input);

		_quickSort(output, 0, output.size());

		return output;
	}

	template <class T>
	std::vector<T> cycleSort(std::vector<T> input) {
		for (int start = 0; start < input.size(); start++) {
			int current = start;
			//calculate place to insert by finding all elements current is greater than
			for (int i = start + 1; i < input.size(); i++) {
				if (input[start] > input[i]) {
					current++;
				}
			}

			if (current != start) {
				while (input[current] == input[start])
					current++;

				std::swap(input[current], input[start]);
			}

			while (start != current) {
				current = start;
				//find appropriate place for rest of loop
				for (int i = start + 1; i < input.size(); i++) {
					if (input[start] > input[i])
						current++;
				}

				if (current != start) {
					while (input[current] == input[start])
						current++;

					std::swap(input[current], input[start]);
				}
			}
		}

		return input;
	}
};
