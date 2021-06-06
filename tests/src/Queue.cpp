#include <gtest/gtest.h>
#include "Queue.h"

TEST(PrioriryQueue, CopyConstructor) {
	algogin::PriorityQueue<int, int> queue;
	queue.insert(30, 130);
	queue.insert(50, 150);
	queue.insert(20, 120);
	queue.insert(35, 135);
	queue.insert(40, 140);
	queue.insert(70, 170);
	queue.insert(80, 180);
	queue.insert(10, 110);

	algogin::PriorityQueue<int, int> queue2(queue);
	auto traversal = queue.traversal(algogin::TraversalMode::LEVEL_ORDER);
	auto traversal2 = queue2.traversal(algogin::TraversalMode::LEVEL_ORDER);
	ASSERT_EQ(traversal.size(), traversal2.size());
	for (int i = 0; i < traversal.size(); i++)
		ASSERT_EQ(traversal[i], traversal2[i]);
}

TEST(PrioriryQueue, MoveConstructor) {
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
	algogin::PriorityQueue<int, int> queue2(std::move(queue));
	auto traversalTemp = queue.traversal(algogin::TraversalMode::LEVEL_ORDER);
	ASSERT_EQ(traversalTemp.size(), 0);

	auto traversal2 = queue2.traversal(algogin::TraversalMode::LEVEL_ORDER);
	ASSERT_EQ(traversal.size(), traversal2.size());
	for (int i = 0; i < traversal.size(); i++)
		ASSERT_EQ(traversal[i], traversal2[i]);
}

TEST(PrioriryQueue, CopyAssignOperator) {
	algogin::PriorityQueue<int, int> queue;
	queue.insert(30, 130);
	queue.insert(50, 150);
	queue.insert(20, 120);
	queue.insert(35, 135);
	queue.insert(40, 140);
	queue.insert(70, 170);
	queue.insert(80, 180);
	queue.insert(10, 110);

	algogin::PriorityQueue<int, int> queue2;
	queue2.insert(300, 1300);
	queue2.insert(400, 1400);
	queue2 = queue;
	auto traversal = queue.traversal(algogin::TraversalMode::LEVEL_ORDER);
	auto traversal2 = queue2.traversal(algogin::TraversalMode::LEVEL_ORDER);
	ASSERT_EQ(traversal.size(), traversal2.size());
	for (int i = 0; i < traversal.size(); i++)
		ASSERT_EQ(traversal[i], traversal2[i]);
}

TEST(PrioriryQueue, MoveAssignOperator) {
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

	algogin::PriorityQueue<int, int> queue2;
	queue2.insert(300, 1300);
	queue2.insert(400, 1400);
	queue2 = std::move(queue);
	auto traversalTemp = queue.traversal(algogin::TraversalMode::LEVEL_ORDER);
	ASSERT_EQ(traversalTemp.size(), 0);
	auto traversal2 = queue2.traversal(algogin::TraversalMode::LEVEL_ORDER);
	ASSERT_EQ(traversal.size(), traversal2.size());
	for (int i = 0; i < traversal.size(); i++)
		ASSERT_EQ(traversal[i], traversal2[i]);
}

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

TEST(PrioriryQueue, Remove_Simple) {
	algogin::PriorityQueue<int, int> queue;
	queue.insert(30, 130);
	queue.insert(50, 150);
	queue.insert(20, 120);
	queue.insert(35, 135);
	queue.insert(40, 140);
	queue.insert(70, 170);
	queue.insert(80, 180);
	queue.insert(10, 110);

	ASSERT_EQ(std::get<1>(queue.getMinimum().value()), 110);
	ASSERT_EQ(std::get<1>(queue.getMinimum().value()), 120);
	ASSERT_EQ(std::get<1>(queue.getMinimum().value()), 130);
	ASSERT_EQ(std::get<1>(queue.getMinimum().value()), 135);
	ASSERT_EQ(std::get<1>(queue.getMinimum().value()), 140);
	ASSERT_EQ(std::get<1>(queue.getMinimum().value()), 150);
	ASSERT_EQ(std::get<1>(queue.getMinimum().value()), 170);
	ASSERT_EQ(std::get<1>(queue.getMinimum().value()), 180);
	ASSERT_EQ(queue.getMinimum(), std::nullopt);
}

