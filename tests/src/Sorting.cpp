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

	std::vector<int> input = { 10, 3, 5, 1, 2, 30, 31 };
	auto output = sorting.insertionSort(input);

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