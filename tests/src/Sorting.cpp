#include <gtest/gtest.h>
#include "Sorting.h"

TEST(BubbleSorting, Simple) {
	Sorting sorting;

	std::vector<int> input = { 10, 3, 5, 1, 2, 30, 31 };
	auto output = sorting.bubbleSort(input);

	ASSERT_EQ(output[0], 1);
	ASSERT_EQ(output[1], 2);
	ASSERT_EQ(output[2], 3);
	ASSERT_EQ(output[3], 5);
	ASSERT_EQ(output[4], 10);
	ASSERT_EQ(output[5], 30);
	ASSERT_EQ(output[6], 31);

	input = { 5, 1, 4, 2, 8 };
	output = sorting.bubbleSort(input);
	ASSERT_EQ(output[0], 1);
	ASSERT_EQ(output[1], 2);
	ASSERT_EQ(output[2], 4);
	ASSERT_EQ(output[3], 5);
	ASSERT_EQ(output[4], 8);
}

TEST(SelectionSorting, Simple) {
	Sorting sorting;

	std::vector<int> input = { 10, 3, 5, 1, 2, 30, 31 };
	auto output = sorting.selectionSort(input);

	ASSERT_EQ(output[0], 1);
	ASSERT_EQ(output[1], 2);
	ASSERT_EQ(output[2], 3);
	ASSERT_EQ(output[3], 5);
	ASSERT_EQ(output[4], 10);
	ASSERT_EQ(output[5], 30);
	ASSERT_EQ(output[6], 31);

	input = { 5, 1, 4, 2, 8 };
	output = sorting.selectionSort(input);
	ASSERT_EQ(output[0], 1);
	ASSERT_EQ(output[1], 2);
	ASSERT_EQ(output[2], 4);
	ASSERT_EQ(output[3], 5);
	ASSERT_EQ(output[4], 8);
}

TEST(InsertionSorting, Simple) {
	Sorting sorting;

	std::vector<int> input = { 10, 3, 5, 1, 4, 30, 31 };
	auto output = sorting.insertionSort(input);

	ASSERT_EQ(output[0], 1);
	ASSERT_EQ(output[1], 3);
	ASSERT_EQ(output[2], 4);
	ASSERT_EQ(output[3], 5);
	ASSERT_EQ(output[4], 10);
	ASSERT_EQ(output[5], 30);
	ASSERT_EQ(output[6], 31);

	input = { 5, 1, 4, 2, 8 };
	output = sorting.selectionSort(input);
	ASSERT_EQ(output[0], 1);
	ASSERT_EQ(output[1], 2);
	ASSERT_EQ(output[2], 4);
	ASSERT_EQ(output[3], 5);
	ASSERT_EQ(output[4], 8);
}

TEST(MergeSorting, Simple) {
	Sorting sorting;

	std::vector<int> input = { 10, 3, 5, 1, 4, 30, 31 };
	auto output = sorting.mergeSort(input);

	ASSERT_EQ(output[0], 1);
	ASSERT_EQ(output[1], 3);
	ASSERT_EQ(output[2], 4);
	ASSERT_EQ(output[3], 5);
	ASSERT_EQ(output[4], 10);
	ASSERT_EQ(output[5], 30);
	ASSERT_EQ(output[6], 31);

	input = { 5, 1, 4, 2, 8 };
	output = sorting.mergeSort(input);
	ASSERT_EQ(output[0], 1);
	ASSERT_EQ(output[1], 2);
	ASSERT_EQ(output[2], 4);
	ASSERT_EQ(output[3], 5);
	ASSERT_EQ(output[4], 8);
}

TEST(QuickSorting, Simple) {
	Sorting sorting;

	std::vector<int> input = { 10, 3, 5, 1, 4, 30, 31 };
	auto output = sorting.quickSort(input);

	ASSERT_EQ(output[0], 1);
	ASSERT_EQ(output[1], 3);
	ASSERT_EQ(output[2], 4);
	ASSERT_EQ(output[3], 5);
	ASSERT_EQ(output[4], 10);
	ASSERT_EQ(output[5], 30);
	ASSERT_EQ(output[6], 31);

	input = { 5, 1, 4, 2, 8 };
	output = sorting.quickSort(input);
	ASSERT_EQ(output[0], 1);
	ASSERT_EQ(output[1], 2);
	ASSERT_EQ(output[2], 4);
	ASSERT_EQ(output[3], 5);
	ASSERT_EQ(output[4], 8);
}

TEST(CycleSorting, Simple) {
	Sorting sorting;

	std::vector<int> input = { 10, 3, 5, 1, 4, 30, 31 };
	auto output = sorting.cycleSort(input);

	ASSERT_EQ(output[0], 1);
	ASSERT_EQ(output[1], 3);
	ASSERT_EQ(output[2], 4);
	ASSERT_EQ(output[3], 5);
	ASSERT_EQ(output[4], 10);
	ASSERT_EQ(output[5], 30);
	ASSERT_EQ(output[6], 31);

	input = { 5, 1, 4, 2, 8 };
	output = sorting.cycleSort(input);
	ASSERT_EQ(output[0], 1);
	ASSERT_EQ(output[1], 2);
	ASSERT_EQ(output[2], 4);
	ASSERT_EQ(output[3], 5);
	ASSERT_EQ(output[4], 8);

	input = { 5, 15, 5, 15, 8, 8, 2, 1, 2, 3, 4, 6, 0, 9, 10, 23, 25, 21, 1, 2, 3, 5, 6, 7 };
	output = sorting.cycleSort(input);
	ASSERT_EQ(output[0], 0);
	ASSERT_EQ(output[1], 1);
	ASSERT_EQ(output[2], 1);
	ASSERT_EQ(output[3], 2);
	ASSERT_EQ(output[4], 2);
	ASSERT_EQ(output[5], 2);
	ASSERT_EQ(output[6], 3);
	ASSERT_EQ(output[7], 3);
	ASSERT_EQ(output[8], 4);
	ASSERT_EQ(output[9], 5);
	ASSERT_EQ(output[10], 5);
	ASSERT_EQ(output[11], 5);
	ASSERT_EQ(output[12], 6);
	ASSERT_EQ(output[13], 6);
	ASSERT_EQ(output[14], 7);
	ASSERT_EQ(output[15], 8);
	ASSERT_EQ(output[16], 8);
	ASSERT_EQ(output[17], 9);
	ASSERT_EQ(output[18], 10);
	ASSERT_EQ(output[19], 15);
	ASSERT_EQ(output[20], 15);
	ASSERT_EQ(output[21], 21);
	ASSERT_EQ(output[22], 23);
	ASSERT_EQ(output[23], 25);
}