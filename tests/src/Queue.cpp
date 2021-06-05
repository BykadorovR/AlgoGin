#include <gtest/gtest.h>
#include "Queue.h"

TEST(PrioriryQueue, Insert_Simple) {
	algogin::PriorityQueue<int, int> queue;
	queue.insert(30, 130);
	queue.insert(50, 150);
	queue.insert(20, 120);
	queue.insert(35, 135);
	queue.insert(40, 140);
	queue.insert(70, 170);
	queue.insert(80, 180);
	queue.insert(10, 110);

	auto traversal = queue.traversal(algogin::TraversalMode::LEVEL_ORDER);

	ASSERT_EQ(std::get<0>(traversal[0]), 10);
	ASSERT_EQ(std::get<1>(traversal[0]), 110);
	ASSERT_EQ(std::get<0>(traversal[1]), 20);
	ASSERT_EQ(std::get<1>(traversal[1]), 120);
	ASSERT_EQ(std::get<0>(traversal[2]), 30);
	ASSERT_EQ(std::get<1>(traversal[2]), 130);
	ASSERT_EQ(std::get<0>(traversal[3]), 35);
	ASSERT_EQ(std::get<1>(traversal[3]), 135);
	ASSERT_EQ(std::get<0>(traversal[4]), 40);
	ASSERT_EQ(std::get<1>(traversal[4]), 140);
	ASSERT_EQ(std::get<0>(traversal[5]), 70);
	ASSERT_EQ(std::get<1>(traversal[5]), 170);
	ASSERT_EQ(std::get<0>(traversal[6]), 80);
	ASSERT_EQ(std::get<1>(traversal[6]), 180);
	ASSERT_EQ(std::get<0>(traversal[7]), 50);
	ASSERT_EQ(std::get<1>(traversal[7]), 150);
}

