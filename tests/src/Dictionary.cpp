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

TEST(Dictionary, Insert_Recolor_NoUncle) {
	algogin::Dictionary<int, int> dictionary;
	dictionary.insert(6, 10);
	dictionary.insert(2, 11);
	dictionary.insert(9, 12);
	dictionary.insert(1, 13);
	dictionary.insert(8, 14);
	dictionary.insert(15, 15);
	dictionary.insert(13, 16);
	//TODO: check color
}

TEST(Dictionary, Remove_LeafNotHead) {
	algogin::Dictionary<int, int> dictionary;
	dictionary.insert(7, 10);
	dictionary.insert(5, 11);
	dictionary.insert(10, 12);

	dictionary.remove(10);

	ASSERT_FALSE(dictionary.exist(10));
}

TEST(Dictionary, Remove_HeadLeaf) {
	algogin::Dictionary<int, int> dictionary;
	dictionary.insert(7, 10);

	ASSERT_EQ(dictionary.remove(7), algogin::ALGOGIN_ERROR::OK);

	ASSERT_FALSE(dictionary.exist(7));
}

TEST(Dictionary, Remove_OneChildNotHead) {
	algogin::Dictionary<int, int> dictionary;
	dictionary.insert(7, 10);
	dictionary.insert(5, 11);
	dictionary.insert(10, 12);
	dictionary.insert(12, 13);

	dictionary.remove(10);

	ASSERT_FALSE(dictionary.exist(10));
}

TEST(Dictionary, Remove_OneChildHead) {
	algogin::Dictionary<int, int> dictionary;
	dictionary.insert(7, 10);
	dictionary.insert(10, 11);

	dictionary.remove(7);

	ASSERT_FALSE(dictionary.exist(7));
}

TEST(Dictionary, Remove_TwoChildHead) {
	algogin::Dictionary<int, int> dictionary;
	dictionary.insert(7, 10);
	dictionary.insert(5, 11);
	dictionary.insert(10, 12);

	dictionary.remove(7);

	ASSERT_FALSE(dictionary.exist(7));
}

TEST(Dictionary, Remove_TwoChildNotHead) {
	algogin::Dictionary<int, int> dictionary;
	dictionary.insert(6, 10);
	dictionary.insert(2, 11);
	dictionary.insert(9, 12);
	dictionary.insert(1, 13);
	dictionary.insert(8, 14);
	dictionary.insert(15, 15);
	dictionary.insert(13, 16);

	dictionary.remove(9);

	ASSERT_FALSE(dictionary.exist(9));
}