#include <gtest/gtest.h>
#include "Dictionary.h"

TEST(Dictionary, Insert_RightRight) {
	algogin::Dictionary<int, int> dictionary;
	dictionary.insert(3, 10);
	dictionary.insert(21, 11);
	dictionary.insert(32, 12);
	dictionary.insert(17, 13);
}

TEST(Dictionary, Insert_LeftLeft) {
	algogin::Dictionary<int, int> dictionary;
	dictionary.insert(32, 10);
	dictionary.insert(21, 11);
	dictionary.insert(17, 12);
	dictionary.insert(42, 13);
}

TEST(Dictionary, Insert_RightLeft) {
	algogin::Dictionary<int, int> dictionary;
	dictionary.insert(5, 10);
	dictionary.insert(1, 11);
	dictionary.insert(8, 12);
	dictionary.insert(10, 13);
	dictionary.insert(9, 14);
}

TEST(Dictionary, Insert_LeftRight) {
	algogin::Dictionary<int, int> dictionary;
	dictionary.insert(7, 10);
	dictionary.insert(5, 11);
	dictionary.insert(10, 12);
	dictionary.insert(1, 13);
	dictionary.insert(3, 14);
}