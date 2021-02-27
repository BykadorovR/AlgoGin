#define GMOCK_DEBUG

#include <gtest/gtest.h>
#include "Container.h"

int main(int argc, char *argv[])
{
	testing::InitGoogleTest(&argc, argv);
//	::testing::GTEST_FLAG(filter) = "Pointer.Callstack";
	return RUN_ALL_TESTS();
}

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
	l1.insert(15, 0);
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
	ASSERT_EQ(l1[0], -10);
	ASSERT_EQ(l2[1], -11);
	EXPECT_THROW(l2[2], std::out_of_range);
}