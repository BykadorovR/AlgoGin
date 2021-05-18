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