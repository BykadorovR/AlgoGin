#include <gtest/gtest.h>
#include "Dictionary.h"
#include <any>

TEST(Dictionary, Move_constructor) {
	algogin::Dictionary<int, int> d1;
	d1.insert(10, 110);
	d1.insert(11, 111);
	d1.insert(12, 112);
	d1.insert(13, 113);
	algogin::Dictionary<int, int> d2 = std::move(d1);
	ASSERT_EQ(d2.getSize(), 4);
	ASSERT_EQ(d1.getSize(), 0);
	d1.insert(15, 115);
	ASSERT_EQ(d2.exist(15), false);
	ASSERT_EQ(d1.exist(15), true);
	ASSERT_EQ(d2.exist(10), true);
	ASSERT_EQ(d2.exist(11), true);
	ASSERT_EQ(d2.exist(12), true);
	ASSERT_EQ(d2.exist(13), true);
}

TEST(Dictionary, MoveAssignmentOperator) {
	algogin::Dictionary<int, int> d1;
	d1.insert(10, 110);
	d1.insert(11, 111);
	d1.insert(12, 112);
	d1.insert(13, 113);
	algogin::Dictionary<int, int> d2;
	d2.insert(14, 114);
	d2.insert(15, 115);
	d2 = std::move(d1);

	ASSERT_EQ(d2.getSize(), 4);
	ASSERT_EQ(d1.getSize(), 0);
	d1.insert(15, 115);
	ASSERT_EQ(d2.exist(15), false);
	ASSERT_EQ(d1.exist(15), true);
	ASSERT_EQ(d2.exist(10), true);
	ASSERT_EQ(d2.exist(11), true);
	ASSERT_EQ(d2.exist(12), true);
	ASSERT_EQ(d2.exist(13), true);
}

TEST(Dictionary, AssignOperator_NotEmpty) {
	algogin::Dictionary<int, int> dictionary;
	dictionary.insert(7, 17);
	dictionary.insert(3, 13);
	dictionary.insert(18, 118);
	dictionary.insert(10, 110);
	dictionary.insert(22, 122);
	dictionary.insert(8, 18);
	dictionary.insert(11, 111);
	dictionary.insert(26, 126);
	dictionary.insert(2, 12);
	dictionary.insert(6, 16);
	dictionary.insert(13, 113);

	algogin::Dictionary<int, int> dictionaryNew;
	dictionaryNew.insert(4, 14);
	dictionaryNew.insert(5, 15);
	
	dictionaryNew = dictionary;
	ASSERT_EQ(dictionary.getSize(), dictionaryNew.getSize());
	ASSERT_EQ(dictionaryNew.exist(4), false);
	ASSERT_EQ(dictionaryNew.exist(5), false);

	auto tree = dictionary.traversal(algogin::TraversalMode::LEVEL_ORDER);
	auto treeNew = dictionaryNew.traversal(algogin::TraversalMode::LEVEL_ORDER);
	for (int i = 0; i < tree.size(); i++) {
		ASSERT_EQ(tree[i], treeNew[i]);
	}
}

TEST(Dictionary, AssignOperator_Empty) {
	algogin::Dictionary<int, int> dictionary;
	dictionary.insert(7, 17);
	dictionary.insert(3, 13);
	dictionary.insert(18, 118);
	dictionary.insert(10, 110);
	dictionary.insert(22, 122);
	dictionary.insert(8, 18);
	dictionary.insert(11, 111);
	dictionary.insert(26, 126);
	dictionary.insert(2, 12);
	dictionary.insert(6, 16);
	dictionary.insert(13, 113);

	algogin::Dictionary<int, int> dictionaryNew;
	dictionaryNew = dictionary;
	ASSERT_EQ(dictionary.getSize(), dictionaryNew.getSize());
	auto tree = dictionary.traversal(algogin::TraversalMode::LEVEL_ORDER);
	auto treeNew = dictionaryNew.traversal(algogin::TraversalMode::LEVEL_ORDER);
	for (int i = 0; i < tree.size(); i++) {
		ASSERT_EQ(tree[i], treeNew[i]);
	}
}

TEST(Dictionary, Copy_Constructor) {
	algogin::Dictionary<int, int> dictionary;
	dictionary.insert(7, 17);
	dictionary.insert(3, 13);
	dictionary.insert(18, 118);
	dictionary.insert(10, 110);
	dictionary.insert(22, 122);
	dictionary.insert(8, 18);
	dictionary.insert(11, 111);
	dictionary.insert(26, 126);
	dictionary.insert(2, 12);
	dictionary.insert(6, 16);
	dictionary.insert(13, 113);

	algogin::Dictionary<int, int> dictionaryNew(dictionary);
	ASSERT_EQ(dictionary.getSize(), dictionaryNew.getSize());
	auto tree = dictionary.traversal(algogin::TraversalMode::LEVEL_ORDER);
	auto treeNew = dictionaryNew.traversal(algogin::TraversalMode::LEVEL_ORDER);
	for (int i = 0; i < tree.size(); i++) {
		ASSERT_EQ(tree[i], treeNew[i]);
	}
}

TEST(Dictionary, Find_GeneralTest) {
	algogin::Dictionary<int, int> dictionary;
	dictionary.insert(7, 17);
	dictionary.insert(3, 13);
	dictionary.insert(18, 118);
	dictionary.insert(10, 110);
	dictionary.insert(22, 122);
	dictionary.insert(8, 18);
	dictionary.insert(11, 111);
	dictionary.insert(26, 126);
	dictionary.insert(2, 12);
	dictionary.insert(6, 16);
	dictionary.insert(13, 113);

	ASSERT_EQ(dictionary.find(8), 18);
	ASSERT_EQ(dictionary.find(7), 17);
	ASSERT_EQ(dictionary.find(26), 126);
	dictionary.remove(26);
	ASSERT_THROW(dictionary.find(26), std::range_error);
}

TEST(Dictionary, Insert_GeneralTest) {
	algogin::Dictionary<int, int> dictionary;
	dictionary.insert(7, 17);
	dictionary.insert(3, 13);
	dictionary.insert(18, 118);
	dictionary.insert(10, 110);
	dictionary.insert(22, 122);
	dictionary.insert(8, 18);
	dictionary.insert(11, 111);
	dictionary.insert(26, 126);
	dictionary.insert(2, 12);
	dictionary.insert(6, 16);
	dictionary.insert(13, 113);

	ASSERT_EQ(dictionary.getSize(), 11);

	auto tree = dictionary.traversal(algogin::TraversalMode::LEVEL_ORDER);
	ASSERT_EQ(std::get<0>(tree[0]), 10);
	ASSERT_EQ(std::get<1>(tree[0]), 110);
	ASSERT_EQ(std::get<0>(tree[1]), 7);
	ASSERT_EQ(std::get<1>(tree[1]), 17);
	ASSERT_EQ(std::get<0>(tree[2]), 18);
	ASSERT_EQ(std::get<1>(tree[2]), 118);
	ASSERT_EQ(std::get<0>(tree[3]), 3);
	ASSERT_EQ(std::get<1>(tree[3]), 13);
	ASSERT_EQ(std::get<0>(tree[4]), 8);
	ASSERT_EQ(std::get<1>(tree[4]), 18);
	ASSERT_EQ(std::get<0>(tree[5]), 11);
	ASSERT_EQ(std::get<1>(tree[5]), 111);
	ASSERT_EQ(std::get<0>(tree[6]), 22);
	ASSERT_EQ(std::get<1>(tree[6]), 122);
	ASSERT_EQ(std::get<0>(tree[7]), 2);
	ASSERT_EQ(std::get<1>(tree[7]), 12);
	ASSERT_EQ(std::get<0>(tree[8]), 6);
	ASSERT_EQ(std::get<1>(tree[8]), 16);
	ASSERT_EQ(std::get<0>(tree[9]), 13);
	ASSERT_EQ(std::get<1>(tree[9]), 113);
	ASSERT_EQ(std::get<0>(tree[10]), 26);
	ASSERT_EQ(std::get<1>(tree[10]), 126);
}

TEST(Dictionary, Insert_RightRight) {
	algogin::Dictionary<int, int> dictionary;
	dictionary.insert(3, 10);
	dictionary.insert(21, 11);
	dictionary.insert(32, 12);
	dictionary.insert(17, 13);
	ASSERT_EQ(dictionary.getSize(), 4);
	auto tree = dictionary.traversal(algogin::TraversalMode::LEVEL_ORDER);
	ASSERT_EQ(std::get<0>(tree[0]), 21);
	ASSERT_EQ(std::get<1>(tree[0]), 11);
	ASSERT_EQ(std::get<0>(tree[1]), 3);
	ASSERT_EQ(std::get<1>(tree[1]), 10);
	ASSERT_EQ(std::get<0>(tree[2]), 32);
	ASSERT_EQ(std::get<1>(tree[2]), 12);
	ASSERT_EQ(std::get<0>(tree[3]), 17);
	ASSERT_EQ(std::get<1>(tree[3]), 13);
}

TEST(Dictionary, Insert_LeftLeft) {
	algogin::Dictionary<int, int> dictionary;
	dictionary.insert(32, 10);
	dictionary.insert(21, 11);
	dictionary.insert(17, 12);
	dictionary.insert(42, 13);
	ASSERT_EQ(dictionary.getSize(), 4);
	auto tree = dictionary.traversal(algogin::TraversalMode::LEVEL_ORDER);
	ASSERT_EQ(std::get<0>(tree[0]), 21);
	ASSERT_EQ(std::get<1>(tree[0]), 11);
	ASSERT_EQ(std::get<0>(tree[1]), 17);
	ASSERT_EQ(std::get<1>(tree[1]), 12);
	ASSERT_EQ(std::get<0>(tree[2]), 32);
	ASSERT_EQ(std::get<1>(tree[2]), 10);
	ASSERT_EQ(std::get<0>(tree[3]), 42);
	ASSERT_EQ(std::get<1>(tree[3]), 13);
}

TEST(Dictionary, Insert_RightLeft) {
	algogin::Dictionary<int, int> dictionary;
	dictionary.insert(5, 10);
	dictionary.insert(1, 11);
	dictionary.insert(8, 12);
	dictionary.insert(10, 13);
	dictionary.insert(9, 14);
	ASSERT_EQ(dictionary.getSize(), 5);
	auto tree = dictionary.traversal(algogin::TraversalMode::LEVEL_ORDER);
	ASSERT_EQ(std::get<0>(tree[0]), 5);
	ASSERT_EQ(std::get<1>(tree[0]), 10);
	ASSERT_EQ(std::get<0>(tree[1]), 1);
	ASSERT_EQ(std::get<1>(tree[1]), 11);
	ASSERT_EQ(std::get<0>(tree[2]), 9);
	ASSERT_EQ(std::get<1>(tree[2]), 14);
	ASSERT_EQ(std::get<0>(tree[3]), 8);
	ASSERT_EQ(std::get<1>(tree[3]), 12);
	ASSERT_EQ(std::get<0>(tree[4]), 10);
	ASSERT_EQ(std::get<1>(tree[4]), 13);
}

TEST(Dictionary, Insert_LeftRight) {
	algogin::Dictionary<int, int> dictionary;
	dictionary.insert(7, 10);
	dictionary.insert(5, 11);
	dictionary.insert(10, 12);
	dictionary.insert(1, 13);
	dictionary.insert(3, 14);
	ASSERT_EQ(dictionary.getSize(), 5);
	auto tree = dictionary.traversal(algogin::TraversalMode::LEVEL_ORDER);
	ASSERT_EQ(std::get<0>(tree[0]), 7);
	ASSERT_EQ(std::get<1>(tree[0]), 10);
	ASSERT_EQ(std::get<0>(tree[1]), 3);
	ASSERT_EQ(std::get<1>(tree[1]), 14);
	ASSERT_EQ(std::get<0>(tree[2]), 10);
	ASSERT_EQ(std::get<1>(tree[2]), 12);
	ASSERT_EQ(std::get<0>(tree[3]), 1);
	ASSERT_EQ(std::get<1>(tree[3]), 13);
	ASSERT_EQ(std::get<0>(tree[4]), 5);
	ASSERT_EQ(std::get<1>(tree[4]), 11);
}

TEST(Dictionary, Insert_Recolor_Twice) {
	algogin::Dictionary<int, int> dictionary;
	dictionary.insert(6, 10);
	dictionary.insert(2, 11);
	dictionary.insert(9, 12);
	dictionary.insert(1, 13);
	dictionary.insert(8, 14);
	dictionary.insert(15, 15);
	dictionary.insert(13, 16);
	ASSERT_EQ(dictionary.getSize(), 7);
	auto tree = dictionary.traversal(algogin::TraversalMode::LEVEL_ORDER);
	ASSERT_EQ(std::get<0>(tree[0]), 6);
	ASSERT_EQ(std::get<1>(tree[0]), 10);
	ASSERT_EQ(std::get<0>(tree[1]), 2);
	ASSERT_EQ(std::get<1>(tree[1]), 11);
	ASSERT_EQ(std::get<0>(tree[2]), 9);
	ASSERT_EQ(std::get<1>(tree[2]), 12);
	ASSERT_EQ(std::get<0>(tree[3]), 1);
	ASSERT_EQ(std::get<1>(tree[3]), 13);
	ASSERT_EQ(std::get<0>(tree[4]), 8);
	ASSERT_EQ(std::get<1>(tree[4]), 14);
	ASSERT_EQ(std::get<0>(tree[5]), 15);
	ASSERT_EQ(std::get<1>(tree[5]), 15);
	ASSERT_EQ(std::get<0>(tree[6]), 13);
	ASSERT_EQ(std::get<1>(tree[6]), 16);
}

TEST(Dictionary, Remove_LeafNotHead) {
	algogin::Dictionary<int, int> dictionary;
	dictionary.insert(7, 10);
	dictionary.insert(5, 11);
	dictionary.insert(10, 12);
	ASSERT_EQ(dictionary.getSize(), 3);
	dictionary.remove(10);
	ASSERT_EQ(dictionary.getSize(), 2);
	ASSERT_FALSE(dictionary.exist(10));

	auto tree = dictionary.traversal(algogin::TraversalMode::LEVEL_ORDER);
	ASSERT_EQ(std::get<0>(tree[0]), 7);
	ASSERT_EQ(std::get<1>(tree[0]), 10);
	ASSERT_EQ(std::get<0>(tree[1]), 5);
	ASSERT_EQ(std::get<1>(tree[1]), 11);
}

TEST(Dictionary, Remove_HeadLeaf) {
	algogin::Dictionary<int, int> dictionary;
	dictionary.insert(7, 10);
	ASSERT_EQ(dictionary.getSize(), 1);
	ASSERT_EQ(dictionary.remove(7), algogin::ALGOGIN_ERROR::OK);
	ASSERT_EQ(dictionary.getSize(), 0);
	ASSERT_FALSE(dictionary.exist(7));
}

TEST(Dictionary, Remove_OneChildNotHead) {
	algogin::Dictionary<int, int> dictionary;
	dictionary.insert(7, 10);
	dictionary.insert(5, 11);
	dictionary.insert(10, 12);
	dictionary.insert(12, 13);
	ASSERT_EQ(dictionary.getSize(), 4);
	dictionary.remove(10);
	ASSERT_EQ(dictionary.getSize(), 3);
	ASSERT_FALSE(dictionary.exist(10));

	auto tree = dictionary.traversal(algogin::TraversalMode::LEVEL_ORDER);
	ASSERT_EQ(std::get<0>(tree[0]), 7);
	ASSERT_EQ(std::get<1>(tree[0]), 10);
	ASSERT_EQ(std::get<0>(tree[1]), 5);
	ASSERT_EQ(std::get<1>(tree[1]), 11);
	ASSERT_EQ(std::get<0>(tree[2]), 12);
	ASSERT_EQ(std::get<1>(tree[2]), 13);
}

TEST(Dictionary, Remove_OneChildHead) {
	algogin::Dictionary<int, int> dictionary;
	dictionary.insert(7, 10);
	dictionary.insert(10, 11);
	ASSERT_EQ(dictionary.getSize(), 2);
	dictionary.remove(7);
	ASSERT_EQ(dictionary.getSize(), 1);
	ASSERT_FALSE(dictionary.exist(7));

	auto tree = dictionary.traversal(algogin::TraversalMode::LEVEL_ORDER);
	ASSERT_EQ(std::get<0>(tree[0]), 10);
	ASSERT_EQ(std::get<1>(tree[0]), 11);
}

TEST(Dictionary, Remove_TwoChildHead) {
	algogin::Dictionary<int, int> dictionary;
	dictionary.insert(7, 10);
	dictionary.insert(5, 11);
	dictionary.insert(10, 12);
	ASSERT_EQ(dictionary.getSize(), 3);
	dictionary.remove(7);
	ASSERT_EQ(dictionary.getSize(), 2);
	ASSERT_FALSE(dictionary.exist(7));

	auto tree = dictionary.traversal(algogin::TraversalMode::LEVEL_ORDER);
	ASSERT_EQ(std::get<0>(tree[0]), 10);
	ASSERT_EQ(std::get<1>(tree[0]), 12);
	ASSERT_EQ(std::get<0>(tree[1]), 5);
	ASSERT_EQ(std::get<1>(tree[1]), 11);
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
	ASSERT_EQ(dictionary.getSize(), 7);
	dictionary.remove(9);
	ASSERT_EQ(dictionary.getSize(), 6);
	ASSERT_FALSE(dictionary.exist(9));

	auto tree = dictionary.traversal(algogin::TraversalMode::LEVEL_ORDER);
	ASSERT_EQ(std::get<0>(tree[0]), 6);
	ASSERT_EQ(std::get<1>(tree[0]), 10);
	ASSERT_EQ(std::get<0>(tree[1]), 2);
	ASSERT_EQ(std::get<1>(tree[1]), 11);
	ASSERT_EQ(std::get<0>(tree[2]), 13);
	ASSERT_EQ(std::get<1>(tree[2]), 16);
	ASSERT_EQ(std::get<0>(tree[3]), 1);
	ASSERT_EQ(std::get<1>(tree[3]), 13);
	ASSERT_EQ(std::get<0>(tree[4]), 8);
	ASSERT_EQ(std::get<1>(tree[4]), 14);
	ASSERT_EQ(std::get<0>(tree[5]), 15);
	ASSERT_EQ(std::get<1>(tree[5]), 15);
}

TEST(Dictionary, Remove_LeafDoubleBlackRightRight) {
	algogin::Dictionary<int, int> dictionary;
	dictionary.insert(30, 13);
	dictionary.insert(20, 12);
	dictionary.insert(40, 14);
	dictionary.insert(50, 15);
	dictionary.insert(35, 135);
	ASSERT_EQ(dictionary.getSize(), 5);
	dictionary.remove(20);
	ASSERT_EQ(dictionary.getSize(), 4);
	ASSERT_FALSE(dictionary.exist(20));

	auto tree = dictionary.traversal(algogin::TraversalMode::LEVEL_ORDER);
	ASSERT_EQ(std::get<0>(tree[0]), 40);
	ASSERT_EQ(std::get<1>(tree[0]), 14);
	ASSERT_EQ(std::get<0>(tree[1]), 30);
	ASSERT_EQ(std::get<1>(tree[1]), 13);
	ASSERT_EQ(std::get<0>(tree[2]), 50);
	ASSERT_EQ(std::get<1>(tree[2]), 15);
	ASSERT_EQ(std::get<0>(tree[3]), 35);
	ASSERT_EQ(std::get<1>(tree[3]), 135);
}

TEST(Dictionary, Remove_LeafDoubleBlackLeftLeft) {
	algogin::Dictionary<int, int> dictionary;
	dictionary.insert(30, 13);
	dictionary.insert(20, 12);
	dictionary.insert(40, 14);
	dictionary.insert(15, 115);
	ASSERT_EQ(dictionary.getSize(), 4);
	dictionary.remove(40);
	ASSERT_EQ(dictionary.getSize(), 3);
	ASSERT_FALSE(dictionary.exist(40));

	auto tree = dictionary.traversal(algogin::TraversalMode::LEVEL_ORDER);
	ASSERT_EQ(std::get<0>(tree[0]), 20);
	ASSERT_EQ(std::get<1>(tree[0]), 12);
	ASSERT_EQ(std::get<0>(tree[1]), 15);
	ASSERT_EQ(std::get<1>(tree[1]), 115);
	ASSERT_EQ(std::get<0>(tree[2]), 30);
	ASSERT_EQ(std::get<1>(tree[2]), 13);
}

TEST(Dictionary, Remove_LeafDoubleBlackRightLeft) {
	algogin::Dictionary<int, int> dictionary;
	dictionary.insert(30, 13);
	dictionary.insert(20, 12);
	dictionary.insert(40, 14);
	dictionary.insert(35, 135);
	ASSERT_EQ(dictionary.getSize(), 4);
	dictionary.remove(20);
	ASSERT_EQ(dictionary.getSize(), 3);
	ASSERT_FALSE(dictionary.exist(20));

	auto tree = dictionary.traversal(algogin::TraversalMode::LEVEL_ORDER);
	ASSERT_EQ(std::get<0>(tree[0]), 35);
	ASSERT_EQ(std::get<1>(tree[0]), 135);
	ASSERT_EQ(std::get<0>(tree[1]), 30);
	ASSERT_EQ(std::get<1>(tree[1]), 13);
	ASSERT_EQ(std::get<0>(tree[2]), 40);
	ASSERT_EQ(std::get<1>(tree[2]), 14);
}

TEST(Dictionary, Remove_LeafDoubleBlackLeftRight) {
	algogin::Dictionary<int, int> dictionary;
	dictionary.insert(30, 13);
	dictionary.insert(20, 12);
	dictionary.insert(40, 14);
	dictionary.insert(25, 125);
	ASSERT_EQ(dictionary.getSize(), 4);
	dictionary.remove(40);
	ASSERT_EQ(dictionary.getSize(), 3);
	ASSERT_FALSE(dictionary.exist(40));

	auto tree = dictionary.traversal(algogin::TraversalMode::LEVEL_ORDER);
	ASSERT_EQ(std::get<0>(tree[0]), 25);
	ASSERT_EQ(std::get<1>(tree[0]), 125);
	ASSERT_EQ(std::get<0>(tree[1]), 20);
	ASSERT_EQ(std::get<1>(tree[1]), 12);
	ASSERT_EQ(std::get<0>(tree[2]), 30);
	ASSERT_EQ(std::get<1>(tree[2]), 13);
}

TEST(Dictionary, Remove_AllBlackRecolor) {
	algogin::Dictionary<int, int> dictionary;
	dictionary.insert(30, 13);
	dictionary.insert(20, 12);
	dictionary.insert(40, 14);
	dictionary.insert(25, 125);
	ASSERT_EQ(dictionary.getSize(), 4);
	dictionary.remove(25);
	ASSERT_EQ(dictionary.getSize(), 3);
	dictionary.remove(20);
	ASSERT_EQ(dictionary.getSize(), 2);
	auto tree = dictionary.traversal(algogin::TraversalMode::LEVEL_ORDER);
	ASSERT_EQ(std::get<0>(tree[0]), 30);
	ASSERT_EQ(std::get<1>(tree[0]), 13);
	ASSERT_EQ(std::get<0>(tree[1]), 40);
	ASSERT_EQ(std::get<1>(tree[1]), 14);
}

TEST(Dictionary, Remove_General) {
	algogin::Dictionary<int, int> dictionary;
	dictionary.insert(7, 17);
	dictionary.insert(3, 13);
	dictionary.insert(18, 118);
	dictionary.insert(10, 110);
	dictionary.insert(22, 122);
	dictionary.insert(8, 18);
	dictionary.insert(11, 111);
	dictionary.insert(26, 126);
	dictionary.insert(2, 12);
	dictionary.insert(6, 16);
	dictionary.insert(13, 113);
	ASSERT_EQ(dictionary.getSize(), 11);
	dictionary.remove(18);
	dictionary.remove(11);
	dictionary.remove(3);
	dictionary.remove(10);
	dictionary.remove(22);
	ASSERT_EQ(dictionary.getSize(), 6);
	auto tree = dictionary.traversal(algogin::TraversalMode::LEVEL_ORDER);
	ASSERT_EQ(std::get<0>(tree[0]), 13);
	ASSERT_EQ(std::get<1>(tree[0]), 113);
	ASSERT_EQ(std::get<0>(tree[1]), 7);
	ASSERT_EQ(std::get<1>(tree[1]), 17);
	ASSERT_EQ(std::get<0>(tree[2]), 26);
	ASSERT_EQ(std::get<1>(tree[2]), 126);
	ASSERT_EQ(std::get<0>(tree[3]), 6);
	ASSERT_EQ(std::get<1>(tree[3]), 16);
	ASSERT_EQ(std::get<0>(tree[4]), 8);
	ASSERT_EQ(std::get<1>(tree[4]), 18);
	ASSERT_EQ(std::get<0>(tree[5]), 2);
	ASSERT_EQ(std::get<1>(tree[5]), 12);
}

TEST(DictionaryDisk, Insert_General) {
	algogin::DictionaryDisk<int, int> dictionary(3);
	dictionary.insert(10, 110);
	dictionary.insert(20, 120);
	dictionary.insert(30, 130);
	dictionary.insert(40, 140);
	dictionary.insert(50, 150);
	dictionary.insert(60, 160);
	dictionary.insert(70, 170);
	dictionary.insert(80, 180);
	dictionary.insert(90, 190);

	auto tree = dictionary.traversal(algogin::TraversalMode::LEVEL_ORDER);
	ASSERT_EQ(std::get<0>(tree[0]), 30);
	ASSERT_EQ(std::get<1>(tree[0]), 130);
	ASSERT_EQ(std::get<0>(tree[1]), 60);
	ASSERT_EQ(std::get<1>(tree[1]), 160);
	ASSERT_EQ(std::get<0>(tree[2]), 10);
	ASSERT_EQ(std::get<1>(tree[2]), 110);
	ASSERT_EQ(std::get<0>(tree[3]), 20);
	ASSERT_EQ(std::get<1>(tree[3]), 120);
	ASSERT_EQ(std::get<0>(tree[4]), 40);
	ASSERT_EQ(std::get<1>(tree[4]), 140);
	ASSERT_EQ(std::get<0>(tree[5]), 50);
	ASSERT_EQ(std::get<1>(tree[5]), 150);
	ASSERT_EQ(std::get<0>(tree[6]), 70);
	ASSERT_EQ(std::get<1>(tree[6]), 170);
	ASSERT_EQ(std::get<0>(tree[7]), 80);
	ASSERT_EQ(std::get<1>(tree[7]), 180);
	ASSERT_EQ(std::get<0>(tree[8]), 90);
	ASSERT_EQ(std::get<1>(tree[8]), 190);
}

TEST(DictionaryDisk, Insert_GeneralTest) {
	algogin::DictionaryDisk<int, int> dictionary(3);
	dictionary.insert(10, 110);
	dictionary.insert(20, 120);
	dictionary.insert(5, 15);
	dictionary.insert(6, 16);
	dictionary.insert(12, 120);
	dictionary.insert(30, 130);
	dictionary.insert(7, 17);
	dictionary.insert(17, 170);

	auto tree = dictionary.traversal(algogin::TraversalMode::LEVEL_ORDER);
	ASSERT_EQ(std::get<0>(tree[0]), 10);
	ASSERT_EQ(std::get<1>(tree[0]), 110);
	ASSERT_EQ(std::get<0>(tree[1]), 5);
	ASSERT_EQ(std::get<1>(tree[1]), 15);
	ASSERT_EQ(std::get<0>(tree[2]), 6);
	ASSERT_EQ(std::get<1>(tree[2]), 16);
	ASSERT_EQ(std::get<0>(tree[3]), 7);
	ASSERT_EQ(std::get<1>(tree[3]), 17);
	ASSERT_EQ(std::get<0>(tree[4]), 12);
	ASSERT_EQ(std::get<1>(tree[4]), 120);
	ASSERT_EQ(std::get<0>(tree[5]), 17);
	ASSERT_EQ(std::get<1>(tree[5]), 170);
	ASSERT_EQ(std::get<0>(tree[6]), 20);
	ASSERT_EQ(std::get<1>(tree[6]), 120);
	ASSERT_EQ(std::get<0>(tree[7]), 30);
	ASSERT_EQ(std::get<1>(tree[7]), 130);
}

TEST(DictionaryDisk, Insert_SmallT) {
	algogin::DictionaryDisk<int, int> dictionary(2);
	dictionary.insert(10, 110);
	dictionary.insert(20, 120);
	dictionary.insert(5, 15);
	dictionary.insert(6, 16);
	dictionary.insert(12, 120);
	dictionary.insert(30, 130);
	dictionary.insert(7, 17);
	dictionary.insert(17, 170);
	dictionary.insert(4, 14);

	auto tree = dictionary.traversal(algogin::TraversalMode::LEVEL_ORDER);
	ASSERT_EQ(std::get<0>(tree[0]), 6);
	ASSERT_EQ(std::get<1>(tree[0]), 16);
	ASSERT_EQ(std::get<0>(tree[1]), 10);
	ASSERT_EQ(std::get<1>(tree[1]), 110);
	ASSERT_EQ(std::get<0>(tree[2]), 20);
	ASSERT_EQ(std::get<1>(tree[2]), 120);
	ASSERT_EQ(std::get<0>(tree[3]), 4);
	ASSERT_EQ(std::get<1>(tree[3]), 14);
	ASSERT_EQ(std::get<0>(tree[4]), 5);
	ASSERT_EQ(std::get<1>(tree[4]), 15);
	ASSERT_EQ(std::get<0>(tree[5]), 7);
	ASSERT_EQ(std::get<1>(tree[5]), 17);
	ASSERT_EQ(std::get<0>(tree[6]), 12);
	ASSERT_EQ(std::get<1>(tree[6]), 120);
	ASSERT_EQ(std::get<0>(tree[7]), 17);
	ASSERT_EQ(std::get<1>(tree[7]), 170);
	ASSERT_EQ(std::get<0>(tree[8]), 30);
	ASSERT_EQ(std::get<1>(tree[8]), 130);
}

TEST(DictionaryDisk, Insert_SmallT_SplitHead) {
	algogin::DictionaryDisk<int, int> dictionary(2);
	dictionary.insert(10, 110);
	dictionary.insert(20, 120);
	dictionary.insert(5, 15);
	dictionary.insert(6, 16);
	dictionary.insert(12, 120);
	dictionary.insert(30, 130);
	dictionary.insert(7, 17);
	dictionary.insert(17, 170);
	dictionary.insert(4, 14);
	dictionary.insert(3, 13);
	dictionary.insert(2, 12);

	auto tree = dictionary.traversal(algogin::TraversalMode::LEVEL_ORDER);
	ASSERT_EQ(std::get<0>(tree[0]), 10);
	ASSERT_EQ(std::get<1>(tree[0]), 110);
	ASSERT_EQ(std::get<0>(tree[1]), 4);
	ASSERT_EQ(std::get<1>(tree[1]), 14);
	ASSERT_EQ(std::get<0>(tree[2]), 6);
	ASSERT_EQ(std::get<1>(tree[2]), 16);
	ASSERT_EQ(std::get<0>(tree[3]), 20);
	ASSERT_EQ(std::get<1>(tree[3]), 120);
	ASSERT_EQ(std::get<0>(tree[4]), 2);
	ASSERT_EQ(std::get<1>(tree[4]), 12);
	ASSERT_EQ(std::get<0>(tree[5]), 3);
	ASSERT_EQ(std::get<1>(tree[5]), 13);
	ASSERT_EQ(std::get<0>(tree[6]), 5);
	ASSERT_EQ(std::get<1>(tree[6]), 15);
	ASSERT_EQ(std::get<0>(tree[7]), 7);
	ASSERT_EQ(std::get<1>(tree[7]), 17);
	ASSERT_EQ(std::get<0>(tree[8]), 12);
	ASSERT_EQ(std::get<1>(tree[8]), 120);
	ASSERT_EQ(std::get<0>(tree[9]), 17);
	ASSERT_EQ(std::get<1>(tree[9]), 170);
	ASSERT_EQ(std::get<0>(tree[10]), 30);
	ASSERT_EQ(std::get<1>(tree[10]), 130);
}

TEST(DictionaryDisk, Insert_3Layers) {
	algogin::DictionaryDisk<int, int> dictionary(2);
	dictionary.insert(10, 110);
	dictionary.insert(20, 120);
	dictionary.insert(30, 130);
	dictionary.insert(40, 140);
	dictionary.insert(50, 150);
	dictionary.insert(60, 160);
	dictionary.insert(70, 170);
	dictionary.insert(80, 180);
	dictionary.insert(90, 190);
	dictionary.insert(100, 1000);

	auto tree = dictionary.traversal(algogin::TraversalMode::LEVEL_ORDER);
	
	ASSERT_EQ(std::get<0>(tree[0]), 40);
	ASSERT_EQ(std::get<1>(tree[0]), 140);
	ASSERT_EQ(std::get<0>(tree[1]), 20);
	ASSERT_EQ(std::get<1>(tree[1]), 120);
	ASSERT_EQ(std::get<0>(tree[2]), 60);
	ASSERT_EQ(std::get<1>(tree[2]), 160);
	ASSERT_EQ(std::get<0>(tree[3]), 80);
	ASSERT_EQ(std::get<1>(tree[3]), 180);
	ASSERT_EQ(std::get<0>(tree[4]), 10);
	ASSERT_EQ(std::get<1>(tree[4]), 110);
	ASSERT_EQ(std::get<0>(tree[5]), 30);
	ASSERT_EQ(std::get<1>(tree[5]), 130);
	ASSERT_EQ(std::get<0>(tree[6]), 50);
	ASSERT_EQ(std::get<1>(tree[6]), 150);
	ASSERT_EQ(std::get<0>(tree[7]), 70);
	ASSERT_EQ(std::get<1>(tree[7]), 170);
	ASSERT_EQ(std::get<0>(tree[8]), 90);
	ASSERT_EQ(std::get<1>(tree[8]), 190);
	ASSERT_EQ(std::get<0>(tree[9]), 100);
	ASSERT_EQ(std::get<1>(tree[9]), 1000);
}

TEST(DictionaryDisk, Find_GeneralTest) {
	algogin::DictionaryDisk<int, int> dictionary(2);
	dictionary.insert(10, 110);
	dictionary.insert(20, 120);
	dictionary.insert(5, 15);
	dictionary.insert(6, 16);
	dictionary.insert(12, 120);
	dictionary.insert(30, 130);
	dictionary.insert(7, 17);
	dictionary.insert(17, 170);
	dictionary.insert(4, 14);
	dictionary.insert(3, 13);
	dictionary.insert(2, 12);

	ASSERT_EQ(dictionary.find(10), 110);
	ASSERT_EQ(dictionary.find(4), 14);
	ASSERT_EQ(dictionary.find(6), 16);
	ASSERT_EQ(dictionary.find(20), 120);
	ASSERT_EQ(dictionary.find(2), 12);
	ASSERT_EQ(dictionary.find(3), 13);
	ASSERT_EQ(dictionary.find(5), 15);
	ASSERT_EQ(dictionary.find(7), 17);
	ASSERT_EQ(dictionary.find(12), 120);
	ASSERT_EQ(dictionary.find(17), 170);
	ASSERT_EQ(dictionary.find(30), 130);

	ASSERT_EQ(dictionary.find(1), std::nullopt);
	ASSERT_EQ(dictionary.find(11), std::nullopt);
	ASSERT_EQ(dictionary.find(50), std::nullopt);
}

TEST(DictionaryDisk, Remove_Leaf_Case1) {
	algogin::DictionaryDisk<int, int> dictionary(3);
	dictionary.insert(10, 110);
	dictionary.insert(20, 120);
	dictionary.insert(30, 130);
	dictionary.insert(40, 140);
	dictionary.insert(50, 150);
	dictionary.insert(60, 160);
	dictionary.insert(70, 170);
	dictionary.insert(80, 180);
	dictionary.insert(90, 190);

	dictionary.remove(90);

	auto tree = dictionary.traversal(algogin::TraversalMode::LEVEL_ORDER);
	ASSERT_EQ(std::get<0>(tree[0]), 30);
	ASSERT_EQ(std::get<1>(tree[0]), 130);
	ASSERT_EQ(std::get<0>(tree[1]), 60);
	ASSERT_EQ(std::get<1>(tree[1]), 160);
	ASSERT_EQ(std::get<0>(tree[2]), 10);
	ASSERT_EQ(std::get<1>(tree[2]), 110);
	ASSERT_EQ(std::get<0>(tree[3]), 20);
	ASSERT_EQ(std::get<1>(tree[3]), 120);
	ASSERT_EQ(std::get<0>(tree[4]), 40);
	ASSERT_EQ(std::get<1>(tree[4]), 140);
	ASSERT_EQ(std::get<0>(tree[5]), 50);
	ASSERT_EQ(std::get<1>(tree[5]), 150);
	ASSERT_EQ(std::get<0>(tree[6]), 70);
	ASSERT_EQ(std::get<1>(tree[6]), 170);
	ASSERT_EQ(std::get<0>(tree[7]), 80);
	ASSERT_EQ(std::get<1>(tree[7]), 180);
}

TEST(DictionaryDisk, Remove_Leaf_Case3a) {
	algogin::DictionaryDisk<int, int> dictionary(3);
	dictionary.insert(10, 110);
	dictionary.insert(20, 120);
	dictionary.insert(30, 130);
	dictionary.insert(40, 140);
	dictionary.insert(50, 150);
	dictionary.insert(60, 160);
	dictionary.insert(70, 170);
	dictionary.insert(80, 180);
	dictionary.insert(90, 190);

	dictionary.remove(50);

	auto tree = dictionary.traversal(algogin::TraversalMode::LEVEL_ORDER);
	ASSERT_EQ(std::get<0>(tree[0]), 30);
	ASSERT_EQ(std::get<1>(tree[0]), 130);
	ASSERT_EQ(std::get<0>(tree[1]), 70);
	ASSERT_EQ(std::get<1>(tree[1]), 170);
	ASSERT_EQ(std::get<0>(tree[2]), 10);
	ASSERT_EQ(std::get<1>(tree[2]), 110);
	ASSERT_EQ(std::get<0>(tree[3]), 20);
	ASSERT_EQ(std::get<1>(tree[3]), 120);
	ASSERT_EQ(std::get<0>(tree[4]), 40);
	ASSERT_EQ(std::get<1>(tree[4]), 140);
	ASSERT_EQ(std::get<0>(tree[5]), 60);
	ASSERT_EQ(std::get<1>(tree[5]), 160);
	ASSERT_EQ(std::get<0>(tree[6]), 80);
	ASSERT_EQ(std::get<1>(tree[6]), 180);
	ASSERT_EQ(std::get<0>(tree[7]), 90);
	ASSERT_EQ(std::get<1>(tree[7]), 190);
}

TEST(DictionaryDisk, Remove_Leaf_Case3b) {
	algogin::DictionaryDisk<int, int> dictionary(3);
	dictionary.insert(10, 110);
	dictionary.insert(20, 120);
	dictionary.insert(30, 130);
	dictionary.insert(40, 140);
	dictionary.insert(50, 150);
	dictionary.insert(60, 160);
	dictionary.insert(70, 170);
	dictionary.insert(80, 180);
	dictionary.insert(90, 190);

	dictionary.remove(20);

	auto tree = dictionary.traversal(algogin::TraversalMode::LEVEL_ORDER);
	ASSERT_EQ(std::get<0>(tree[0]), 60);
	ASSERT_EQ(std::get<1>(tree[0]), 160);
	ASSERT_EQ(std::get<0>(tree[1]), 10);
	ASSERT_EQ(std::get<1>(tree[1]), 110);
	ASSERT_EQ(std::get<0>(tree[2]), 30);
	ASSERT_EQ(std::get<1>(tree[2]), 130);
	ASSERT_EQ(std::get<0>(tree[3]), 40);
	ASSERT_EQ(std::get<1>(tree[3]), 140);
	ASSERT_EQ(std::get<0>(tree[4]), 50);
	ASSERT_EQ(std::get<1>(tree[4]), 150);
	ASSERT_EQ(std::get<0>(tree[5]), 70);
	ASSERT_EQ(std::get<1>(tree[5]), 170);
	ASSERT_EQ(std::get<0>(tree[6]), 80);
	ASSERT_EQ(std::get<1>(tree[6]), 180);
	ASSERT_EQ(std::get<0>(tree[7]), 90);
	ASSERT_EQ(std::get<1>(tree[7]), 190);
}

TEST(DictionaryDisk, Remove_Leaf_Case3b_2b) {
	algogin::DictionaryDisk<int, int> dictionary(2);
	dictionary.insert(10, 110);
	dictionary.insert(20, 120);
	dictionary.insert(30, 130);
	dictionary.insert(40, 140);
	dictionary.insert(50, 150);
	dictionary.insert(60, 160);
	dictionary.insert(70, 170);
	dictionary.insert(80, 180);
	dictionary.insert(90, 190);

	dictionary.remove(60);

	auto tree = dictionary.traversal(algogin::TraversalMode::LEVEL_ORDER);
	ASSERT_EQ(std::get<0>(tree[0]), 20);
	ASSERT_EQ(std::get<1>(tree[0]), 120);
	ASSERT_EQ(std::get<0>(tree[1]), 40);
	ASSERT_EQ(std::get<1>(tree[1]), 140);
	ASSERT_EQ(std::get<0>(tree[2]), 70);
	ASSERT_EQ(std::get<1>(tree[2]), 170);
	ASSERT_EQ(std::get<0>(tree[3]), 10);
	ASSERT_EQ(std::get<1>(tree[3]), 110);
	ASSERT_EQ(std::get<0>(tree[4]), 30);
	ASSERT_EQ(std::get<1>(tree[4]), 130);
	ASSERT_EQ(std::get<0>(tree[5]), 50);
	ASSERT_EQ(std::get<1>(tree[5]), 150);
	ASSERT_EQ(std::get<0>(tree[6]), 80);
	ASSERT_EQ(std::get<1>(tree[6]), 180);
	ASSERT_EQ(std::get<0>(tree[7]), 90);
	ASSERT_EQ(std::get<1>(tree[7]), 190);
}

TEST(DictionaryDisk, Remove_Leaf_Case2c) {
	algogin::DictionaryDisk<int, int> dictionary(2);
	dictionary.insert(10, 110);
	dictionary.insert(20, 120);
	dictionary.insert(30, 130);
	dictionary.insert(40, 140);
	dictionary.insert(50, 150);
	dictionary.insert(60, 160);
	dictionary.insert(70, 170);
	dictionary.insert(80, 180);
	dictionary.insert(90, 190);
	dictionary.insert(100, 1000);

	dictionary.remove(60);

	auto tree = dictionary.traversal(algogin::TraversalMode::LEVEL_ORDER);
	ASSERT_EQ(std::get<0>(tree[0]), 40);
	ASSERT_EQ(std::get<1>(tree[0]), 140);
	ASSERT_EQ(std::get<0>(tree[1]), 20);
	ASSERT_EQ(std::get<1>(tree[1]), 120);
	ASSERT_EQ(std::get<0>(tree[2]), 80);
	ASSERT_EQ(std::get<1>(tree[2]), 180);
	ASSERT_EQ(std::get<0>(tree[3]), 10);
	ASSERT_EQ(std::get<1>(tree[3]), 110);
	ASSERT_EQ(std::get<0>(tree[4]), 30);
	ASSERT_EQ(std::get<1>(tree[4]), 130);
	ASSERT_EQ(std::get<0>(tree[5]), 50);
	ASSERT_EQ(std::get<1>(tree[5]), 150);
	ASSERT_EQ(std::get<0>(tree[6]), 70);
	ASSERT_EQ(std::get<1>(tree[6]), 170);
	ASSERT_EQ(std::get<0>(tree[7]), 90);
	ASSERT_EQ(std::get<1>(tree[7]), 190);
	ASSERT_EQ(std::get<0>(tree[8]), 100);
	ASSERT_EQ(std::get<1>(tree[8]), 1000);
}

TEST(DictionaryDisk, CopyConstructor) {
	algogin::DictionaryDisk<int, int> dictionary(2);
	dictionary.insert(10, 110);
	dictionary.insert(20, 120);
	dictionary.insert(30, 130);
	dictionary.insert(40, 140);
	dictionary.insert(50, 150);
	dictionary.insert(60, 160);
	dictionary.insert(70, 170);
	dictionary.insert(80, 180);
	dictionary.insert(90, 190);
	dictionary.insert(100, 1000);

	auto tree = dictionary.traversal(algogin::TraversalMode::LEVEL_ORDER);
	
	algogin::DictionaryDisk<int, int> dictionaryNew(dictionary);
	auto treeNew = dictionaryNew.traversal(algogin::TraversalMode::LEVEL_ORDER);

	for (int i = 0; i < tree.size(); i++) {
		ASSERT_EQ(tree[i], treeNew[i]);
	}
}

TEST(DictionaryDisk, CopyAssignment) {
	algogin::DictionaryDisk<int, int> dictionary(2);
	dictionary.insert(10, 110);
	dictionary.insert(20, 120);
	dictionary.insert(30, 130);
	dictionary.insert(40, 140);
	dictionary.insert(50, 150);
	dictionary.insert(60, 160);
	dictionary.insert(70, 170);
	dictionary.insert(80, 180);
	dictionary.insert(90, 190);
	dictionary.insert(100, 1000);

	auto tree = dictionary.traversal(algogin::TraversalMode::LEVEL_ORDER);

	algogin::DictionaryDisk<int, int> dictionaryNew(2);
	dictionaryNew.insert(110, 210);
	dictionaryNew.insert(120, 220);
	dictionaryNew.insert(130, 230);
	dictionaryNew.insert(140, 240);
	dictionaryNew.insert(150, 250);
	dictionaryNew.insert(160, 260);
	dictionaryNew.insert(170, 270);
	dictionaryNew.insert(180, 280);
	dictionaryNew.insert(190, 290);
	dictionaryNew.insert(1100, 2000);

	dictionaryNew = dictionary;

	auto treeNew = dictionaryNew.traversal(algogin::TraversalMode::LEVEL_ORDER);

	for (int i = 0; i < tree.size(); i++) {
		ASSERT_EQ(tree[i], treeNew[i]);
	}
}

TEST(DictionaryDisk, MoveConstructor) {
	algogin::DictionaryDisk<int, int> dictionary(2);
	dictionary.insert(10, 110);
	dictionary.insert(20, 120);
	dictionary.insert(30, 130);
	dictionary.insert(40, 140);
	dictionary.insert(50, 150);
	dictionary.insert(60, 160);
	dictionary.insert(70, 170);
	dictionary.insert(80, 180);
	dictionary.insert(90, 190);
	dictionary.insert(100, 1000);

	auto tree = dictionary.traversal(algogin::TraversalMode::LEVEL_ORDER);

	algogin::DictionaryDisk<int, int> dictionaryNew(std::move(dictionary));

	auto treeEmpty = dictionary.traversal(algogin::TraversalMode::LEVEL_ORDER);
	ASSERT_EQ(treeEmpty.size(), 0);

	auto treeNew = dictionaryNew.traversal(algogin::TraversalMode::LEVEL_ORDER);

	for (int i = 0; i < tree.size(); i++) {
		ASSERT_EQ(tree[i], treeNew[i]);
	}
}

TEST(DictionaryDisk, MoveAssignment) {
	algogin::DictionaryDisk<int, int> dictionary(2);
	dictionary.insert(10, 110);
	dictionary.insert(20, 120);
	dictionary.insert(30, 130);
	dictionary.insert(40, 140);
	dictionary.insert(50, 150);
	dictionary.insert(60, 160);
	dictionary.insert(70, 170);
	dictionary.insert(80, 180);
	dictionary.insert(90, 190);
	dictionary.insert(100, 1000);

	auto tree = dictionary.traversal(algogin::TraversalMode::LEVEL_ORDER);

	algogin::DictionaryDisk<int, int> dictionaryNew(2);
	dictionaryNew.insert(110, 210);
	dictionaryNew.insert(120, 220);
	dictionaryNew.insert(130, 230);
	dictionaryNew.insert(140, 240);
	dictionaryNew.insert(150, 250);
	dictionaryNew.insert(160, 260);
	dictionaryNew.insert(170, 270);
	dictionaryNew.insert(180, 280);
	dictionaryNew.insert(190, 290);
	dictionaryNew.insert(1100, 2000);

	dictionaryNew = std::move(dictionary);
	auto treeEmpty = dictionary.traversal(algogin::TraversalMode::LEVEL_ORDER);
	ASSERT_EQ(treeEmpty.size(), 0);

	auto treeNew = dictionaryNew.traversal(algogin::TraversalMode::LEVEL_ORDER);

	for (int i = 0; i < tree.size(); i++) {
		ASSERT_EQ(tree[i], treeNew[i]);
	}
}

TEST(HashTable, HashTable_CopyConstructor) {
	algogin::HashTable<int, int> hashTable(5);
	hashTable.insert(100, 2);
	hashTable.insert(12120, 3);
	hashTable.insert(6, 3);
	hashTable.insert(16, 4);

	algogin::HashTable<int, int> hashTable2(hashTable);
	ASSERT_EQ(std::get<0>(hashTable.find(100).value()), 100);
	ASSERT_EQ(std::get<1>(hashTable.find(100).value()), 2);
	ASSERT_EQ(std::get<0>(hashTable.find(12120).value()), 12120);
	ASSERT_EQ(std::get<1>(hashTable.find(12120).value()), 3);
	ASSERT_EQ(std::get<0>(hashTable.find(6).value()), 6);
	ASSERT_EQ(std::get<1>(hashTable.find(6).value()), 3);
	ASSERT_EQ(std::get<0>(hashTable.find(16).value()), 16);
	ASSERT_EQ(std::get<1>(hashTable.find(16).value()), 4);
	ASSERT_EQ(std::get<0>(hashTable2.find(100).value()), 100);
	ASSERT_EQ(std::get<1>(hashTable2.find(100).value()), 2);
	ASSERT_EQ(std::get<0>(hashTable2.find(12120).value()), 12120);
	ASSERT_EQ(std::get<1>(hashTable2.find(12120).value()), 3);
	ASSERT_EQ(std::get<0>(hashTable2.find(6).value()), 6);
	ASSERT_EQ(std::get<1>(hashTable2.find(6).value()), 3);
	ASSERT_EQ(std::get<0>(hashTable2.find(16).value()), 16);
	ASSERT_EQ(std::get<1>(hashTable2.find(16).value()), 4);
}

TEST(HashTable, HashTable_MoveConstructor) {
	algogin::HashTable<int, int> hashTable(5);
	hashTable.insert(100, 2);
	hashTable.insert(12120, 3);
	hashTable.insert(6, 3);
	hashTable.insert(16, 4);

	algogin::HashTable<int, int> hashTable2(std::move(hashTable));
	ASSERT_EQ(hashTable.find(100), std::nullopt);
	ASSERT_EQ(hashTable.find(12120), std::nullopt);
	ASSERT_EQ(hashTable.find(6), std::nullopt);
	ASSERT_EQ(hashTable.find(16), std::nullopt);

	ASSERT_EQ(std::get<0>(hashTable2.find(100).value()), 100);
	ASSERT_EQ(std::get<1>(hashTable2.find(100).value()), 2);
	ASSERT_EQ(std::get<0>(hashTable2.find(12120).value()), 12120);
	ASSERT_EQ(std::get<1>(hashTable2.find(12120).value()), 3);
	ASSERT_EQ(std::get<0>(hashTable2.find(6).value()), 6);
	ASSERT_EQ(std::get<1>(hashTable2.find(6).value()), 3);
	ASSERT_EQ(std::get<0>(hashTable2.find(16).value()), 16);
	ASSERT_EQ(std::get<1>(hashTable2.find(16).value()), 4);
}

TEST(HashTable, HashTable_CopyOperator) {
	algogin::HashTable<int, int> hashTable(5);
	hashTable.insert(100, 2);
	hashTable.insert(12120, 3);
	hashTable.insert(6, 3);
	hashTable.insert(16, 4);

	algogin::HashTable<int, int> hashTable2(2);
	hashTable2.insert(1, 0);
	ASSERT_EQ(std::get<0>(hashTable2.find(1).value()), 1);
	ASSERT_EQ(std::get<1>(hashTable2.find(1).value()), 0);

	hashTable2 = hashTable;
	ASSERT_EQ(hashTable2.find(1), std::nullopt);

	ASSERT_EQ(std::get<0>(hashTable.find(100).value()), 100);
	ASSERT_EQ(std::get<1>(hashTable.find(100).value()), 2);
	ASSERT_EQ(std::get<0>(hashTable.find(12120).value()), 12120);
	ASSERT_EQ(std::get<1>(hashTable.find(12120).value()), 3);
	ASSERT_EQ(std::get<0>(hashTable.find(6).value()), 6);
	ASSERT_EQ(std::get<1>(hashTable.find(6).value()), 3);
	ASSERT_EQ(std::get<0>(hashTable.find(16).value()), 16);
	ASSERT_EQ(std::get<1>(hashTable.find(16).value()), 4);
	ASSERT_EQ(std::get<0>(hashTable2.find(100).value()), 100);
	ASSERT_EQ(std::get<1>(hashTable2.find(100).value()), 2);
	ASSERT_EQ(std::get<0>(hashTable2.find(12120).value()), 12120);
	ASSERT_EQ(std::get<1>(hashTable2.find(12120).value()), 3);
	ASSERT_EQ(std::get<0>(hashTable2.find(6).value()), 6);
	ASSERT_EQ(std::get<1>(hashTable2.find(6).value()), 3);
	ASSERT_EQ(std::get<0>(hashTable2.find(16).value()), 16);
	ASSERT_EQ(std::get<1>(hashTable2.find(16).value()), 4);
}

TEST(HashTable, HashTable_MoveOperator) {
	algogin::HashTable<int, int> hashTable(5);
	hashTable.insert(100, 2);
	hashTable.insert(12120, 3);
	hashTable.insert(6, 3);
	hashTable.insert(16, 4);

	algogin::HashTable<int, int> hashTable2(2);
	hashTable2.insert(1, 0);
	ASSERT_EQ(std::get<0>(hashTable2.find(1).value()), 1);
	ASSERT_EQ(std::get<1>(hashTable2.find(1).value()), 0);

	hashTable2 = std::move(hashTable);
	ASSERT_EQ(hashTable2.find(1), std::nullopt);

	ASSERT_EQ(hashTable.find(100), std::nullopt);
	ASSERT_EQ(hashTable.find(12120), std::nullopt);
	ASSERT_EQ(hashTable.find(6), std::nullopt);
	ASSERT_EQ(hashTable.find(16), std::nullopt);
	ASSERT_EQ(std::get<0>(hashTable2.find(100).value()), 100);
	ASSERT_EQ(std::get<1>(hashTable2.find(100).value()), 2);
	ASSERT_EQ(std::get<0>(hashTable2.find(12120).value()), 12120);
	ASSERT_EQ(std::get<1>(hashTable2.find(12120).value()), 3);
	ASSERT_EQ(std::get<0>(hashTable2.find(6).value()), 6);
	ASSERT_EQ(std::get<1>(hashTable2.find(6).value()), 3);
	ASSERT_EQ(std::get<0>(hashTable2.find(16).value()), 16);
	ASSERT_EQ(std::get<1>(hashTable2.find(16).value()), 4);
}

TEST(HashTable, Insert_Simple_Int) {
	algogin::HashTable<int, int> hashTable(5);
	hashTable.insert(100, 2);
	hashTable.insert(12120, 3);
	hashTable.insert(6, 3);
	hashTable.insert(16, 4);
	hashTable.insert(1236, 5);
	hashTable.insert(126, 6);
	hashTable.insert(73, 7);
	hashTable.insert(99, 8);

	ASSERT_EQ(std::get<0>(hashTable.find(100).value()), 100);
	ASSERT_EQ(std::get<1>(hashTable.find(100).value()), 2);
	ASSERT_EQ(std::get<0>(hashTable.find(12120).value()), 12120);
	ASSERT_EQ(std::get<1>(hashTable.find(12120).value()), 3);
	ASSERT_EQ(std::get<0>(hashTable.find(6).value()), 6);
	ASSERT_EQ(std::get<1>(hashTable.find(6).value()), 3);
	ASSERT_EQ(std::get<0>(hashTable.find(16).value()), 16);
	ASSERT_EQ(std::get<1>(hashTable.find(16).value()), 4);
	ASSERT_EQ(std::get<0>(hashTable.find(1236).value()), 1236);
	ASSERT_EQ(std::get<1>(hashTable.find(1236).value()), 5);
	ASSERT_EQ(std::get<0>(hashTable.find(126).value()), 126);
	ASSERT_EQ(std::get<1>(hashTable.find(126).value()), 6);
	ASSERT_EQ(std::get<0>(hashTable.find(73).value()), 73);
	ASSERT_EQ(std::get<1>(hashTable.find(73).value()), 7);
	ASSERT_EQ(std::get<0>(hashTable.find(99).value()), 99);
	ASSERT_EQ(std::get<1>(hashTable.find(99).value()), 8);
}

TEST(HashTable, Insert_Simple_String) {
	algogin::HashTable<std::string, int> hashTable(5);
	hashTable.insert("here", 2);
	hashTable.insert("we are", 3);
	hashTable.insert("windows", 3);
	hashTable.insert("friends", 4);
	hashTable.insert("kekw", 5);
	hashTable.insert("sure", 6);
	hashTable.insert("who are u", 7);
	hashTable.insert("123", 8);

	ASSERT_EQ(std::get<0>(hashTable.find("here").value()), "here");
	ASSERT_EQ(std::get<1>(hashTable.find("here").value()), 2);
	ASSERT_EQ(std::get<0>(hashTable.find("we are").value()), "we are");
	ASSERT_EQ(std::get<1>(hashTable.find("we are").value()), 3);
	ASSERT_EQ(std::get<0>(hashTable.find("windows").value()), "windows");
	ASSERT_EQ(std::get<1>(hashTable.find("windows").value()), 3);
	ASSERT_EQ(std::get<0>(hashTable.find("friends").value()), "friends");
	ASSERT_EQ(std::get<1>(hashTable.find("friends").value()), 4);
	ASSERT_EQ(std::get<0>(hashTable.find("kekw").value()), "kekw");
	ASSERT_EQ(std::get<1>(hashTable.find("kekw").value()), 5);
	ASSERT_EQ(std::get<0>(hashTable.find("sure").value()), "sure");
	ASSERT_EQ(std::get<1>(hashTable.find("sure").value()), 6);
	ASSERT_EQ(std::get<0>(hashTable.find("who are u").value()), "who are u");
	ASSERT_EQ(std::get<1>(hashTable.find("who are u").value()), 7);
	ASSERT_EQ(std::get<0>(hashTable.find("123").value()), "123");
	ASSERT_EQ(std::get<1>(hashTable.find("123").value()), 8);
}

TEST(HashTable, Find_Simple_Int) {
	algogin::HashTable<int, int> hashTable(5);
	hashTable.insert(100, 2);
	hashTable.insert(12120, 3);
	hashTable.insert(6, 3);
	hashTable.insert(16, 4);
	hashTable.insert(1236, 5);
	hashTable.insert(126, 6);
	hashTable.insert(73, 7);
	hashTable.insert(99, 8);

	ASSERT_EQ(std::get<0>(hashTable.find(12120).value()), 12120);
	ASSERT_EQ(std::get<1>(hashTable.find(12120).value()), 3);
	ASSERT_EQ(std::get<0>(hashTable.find(100).value()), 100);
	ASSERT_EQ(std::get<1>(hashTable.find(100).value()), 2);
	ASSERT_EQ(std::get<0>(hashTable.find(126).value()), 126);
	ASSERT_EQ(std::get<1>(hashTable.find(126).value()), 6);
	ASSERT_EQ(hashTable.find(0), std::nullopt);
}

TEST(HashTable, Find_Simple_String) {
	algogin::HashTable<std::string, int> hashTable(5);
	hashTable.insert("here", 2);
	hashTable.insert("we are", 3);
	hashTable.insert("windows", 3);
	hashTable.insert("friends", 4);
	hashTable.insert("kekw", 5);
	hashTable.insert("sure", 6);
	hashTable.insert("who are u", 7);
	hashTable.insert("123", 8);

	ASSERT_EQ(std::get<0>(hashTable.find("sure").value()), "sure");
	ASSERT_EQ(std::get<1>(hashTable.find("sure").value()), 6);
	ASSERT_EQ(std::get<0>(hashTable.find("friends").value()), "friends");
	ASSERT_EQ(std::get<1>(hashTable.find("friends").value()), 4);
	ASSERT_EQ(std::get<0>(hashTable.find("we are").value()), "we are");
	ASSERT_EQ(std::get<1>(hashTable.find("we are").value()), 3);
	ASSERT_EQ(hashTable.find("empty"), std::nullopt);
}

TEST(HashTable, Remove_Simple_Int) {
	algogin::HashTable<int, int> hashTable(5);
	hashTable.insert(100, 2);
	hashTable.insert(12120, 3);
	hashTable.insert(6, 3);
	hashTable.insert(16, 4);
	hashTable.insert(1236, 5);
	hashTable.insert(126, 6);
	hashTable.insert(73, 7);
	hashTable.insert(99, 8);

	hashTable.remove(12120);
	ASSERT_EQ(hashTable.find(12120), std::nullopt);
	ASSERT_EQ(hashTable.remove(12120), algogin::ALGOGIN_ERROR::UNKNOWN_ERROR);
	hashTable.remove(99);
	ASSERT_EQ(hashTable.find(99), std::nullopt);
	hashTable.remove(1236);
	ASSERT_EQ(hashTable.find(1236), std::nullopt);
	hashTable.remove(6);
	ASSERT_EQ(hashTable.find(6), std::nullopt);
}

TEST(HashTable, Remove_Simple_String) {
	algogin::HashTable<std::string, int> hashTable(5);
	hashTable.insert("here", 2);
	hashTable.insert("we are", 3);
	hashTable.insert("windows", 3);
	hashTable.insert("friends", 4);
	hashTable.insert("kekw", 5);
	hashTable.insert("sure", 6);
	hashTable.insert("who are u", 7);
	hashTable.insert("123", 8);

	hashTable.remove("kekw");
	ASSERT_EQ(hashTable.find("kekw"), std::nullopt);
	ASSERT_EQ(hashTable.remove("kekw"), algogin::ALGOGIN_ERROR::UNKNOWN_ERROR);
	hashTable.remove("sure");
	ASSERT_EQ(hashTable.find("sure"), std::nullopt);
	hashTable.remove("123");
	ASSERT_EQ(hashTable.find("123"), std::nullopt);
	hashTable.remove("here");
	ASSERT_EQ(hashTable.find("here"), std::nullopt);
}