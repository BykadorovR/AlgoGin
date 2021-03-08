#include <gtest/gtest.h>
#include "Container.h"

TEST(List, Insert_out_of_bounds) {
	algogin::List<int> l;
	ASSERT_EQ(l.insert(10, -1), algogin::ALGOGIN_ERROR::OUT_OF_BOUNDS);
	ASSERT_EQ(l.insert(10, 1), algogin::ALGOGIN_ERROR::OUT_OF_BOUNDS);
}

TEST(List, Insert_correct) {
	algogin::List<int> l;
	ASSERT_EQ(l.insert(10, 0), algogin::ALGOGIN_ERROR::OK);
	ASSERT_EQ(l.insert(11, 1), algogin::ALGOGIN_ERROR::OK);
	ASSERT_EQ(l.insert(12, 1), algogin::ALGOGIN_ERROR::OK);
	ASSERT_EQ(l.insert(13, 0), algogin::ALGOGIN_ERROR::OK);
	ASSERT_EQ(l.getSize(), 4);
}

TEST(List, Remove_out_of_bounds) {
	algogin::List<int> l;
	ASSERT_EQ(l.remove(0), algogin::ALGOGIN_ERROR::OUT_OF_BOUNDS);
	ASSERT_EQ(l.remove(-1), algogin::ALGOGIN_ERROR::OUT_OF_BOUNDS);
}

TEST(List, Remove_correct) {
	algogin::List<int> l;
	l.insert(10, 0);
	l.insert(11, 1);
	l.insert(12, 1);
	l.insert(13, 0);
	//13 10 12 11
	ASSERT_EQ(l.remove(2), algogin::ALGOGIN_ERROR::OK);
	ASSERT_EQ(l.getSize(), 3);
	//13 10 11
	ASSERT_EQ(l[2], 11);
	ASSERT_EQ(l.remove(0), algogin::ALGOGIN_ERROR::OK);
	ASSERT_EQ(l.getSize(), 2);
	//10 11
	ASSERT_EQ(l[0], 10);
	ASSERT_EQ(l.remove(1), algogin::ALGOGIN_ERROR::OK);
	ASSERT_EQ(l.getSize(), 1);
	ASSERT_EQ(l[0], 10);
}

TEST(List, Access_operator) {
	algogin::List<int> l;
	l.insert(10, 0);
	l.insert(11, 1);
	l.insert(12, 1);
	l.insert(13, 0);
	ASSERT_EQ(l[0], 13);
	ASSERT_EQ(l[1], 10);
	ASSERT_EQ(l[2], 12);
	ASSERT_EQ(l[3], 11);
}

TEST(List, Copy_constructor) {
	algogin::List<int> l1;
	l1.insert(10, 0);
	l1.insert(11, 1);
	l1.insert(12, 1);
	l1.insert(13, 0);
	algogin::List<int> l2 = l1;
	ASSERT_EQ(l2.getSize(), 4);
	ASSERT_EQ(l1.getSize(), 4);
	l1.insert(15, 0);
	ASSERT_EQ(l1.getSize(), 5);
	ASSERT_EQ(l2[0], 13);
	ASSERT_EQ(l2[1], 10);
	ASSERT_EQ(l2[2], 12);
	ASSERT_EQ(l2[3], 11);
}

TEST(List, Copy_assignment) {
	algogin::List<int> l1;
	l1.insert(10, 0);
	l1.insert(11, 1);
	l1.insert(12, 1);
	l1.insert(13, 0);
	algogin::List<int> l2;
	l2.insert(-10, 0);
	l2.insert(-11, 1);
	l1 = l2;
	ASSERT_EQ(l1.getSize(), 2);
	ASSERT_EQ(l2.getSize(), 2);
	ASSERT_EQ(l1[0], -10);
	ASSERT_EQ(l2[1], -11);
	EXPECT_THROW(l2[2], std::out_of_range);
}

TEST(List, Move_constructor) {
	algogin::List<int> l1;
	l1.insert(10, 0);
	l1.insert(11, 1);
	l1.insert(12, 1);
	l1.insert(13, 0);
	algogin::List<int> l2 = std::move(l1);
	ASSERT_EQ(l2.getSize(), 4);
	ASSERT_EQ(l1.getSize(), 0);
	l1.insert(15, 0);
	ASSERT_EQ(l2[0], 13);
	ASSERT_EQ(l2[1], 10);
	ASSERT_EQ(l2[2], 12);
	ASSERT_EQ(l2[3], 11);
}

TEST(List, Move_assignment_operator) {
	algogin::List<int> l1;
	l1.insert(10, 0);
	l1.insert(11, 1);
	l1.insert(12, 1);
	l1.insert(13, 0);
	algogin::List<int> l2;
	l2.insert(-10, 0);
	l2.insert(-11, 1);
	l2 = std::move(l1);
	ASSERT_EQ(l2.getSize(), 4);
	ASSERT_EQ(l1.getSize(), 0);
	l1.insert(15, 0);
	ASSERT_EQ(l2[0], 13);
	ASSERT_EQ(l2[1], 10);
	ASSERT_EQ(l2[2], 12);
	ASSERT_EQ(l2[3], 11);
}

TEST(List, Dump_list) {
	algogin::List<int> l;
	l.insert(10, 0);
	l.insert(11, 1);
	l.insert(12, 2);
	auto tmp = std::filesystem::current_path() / "temp";
	std::filesystem::create_directory(tmp);
	ASSERT_EQ(l.dump(tmp / "dump.txt"), algogin::ALGOGIN_ERROR::OK);
	ASSERT_EQ(std::filesystem::exists(tmp / "dump.txt"), true);
	ASSERT_EQ(std::filesystem::file_size(tmp / "dump.txt"), 12);
}

TEST(List, Load_list_wrong) {
	algogin::List<int> l;
	auto tmp = std::filesystem::current_path() / "temp";
	ASSERT_EQ(l.load(tmp / "dump_wrong.txt"), algogin::ALGOGIN_ERROR::NOT_FOUND);
}

TEST(List, Load_list) {
	algogin::List<int> l;
	auto tmp = std::filesystem::current_path() / "temp";
	ASSERT_EQ(l.load(tmp / "dump.txt"), algogin::ALGOGIN_ERROR::OK);
	ASSERT_EQ(l.getSize(), 3);
	ASSERT_EQ(l[0], 10);
	ASSERT_EQ(l[1], 11);
	ASSERT_EQ(l[2], 12);
	std::filesystem::remove(tmp / "dump.txt");
}