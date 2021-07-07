#include <gtest/gtest.h>
#include "Graph.h"

/*
	1
  /   \
0   +   3
  \   /
	2
	|
	4 - 5
*/
TEST(GraphList, Insert) {
	GraphList graph;
	graph.insert(0, 1, 1);
	graph.insert(0, 2, 1);
	graph.insert(0, 3, 1);
	graph.insert(1, 2, 2);
	graph.insert(1, 3, 2);
	graph.insert(2, 3, 3);
	graph.insert(2, 4, 3);
	graph.insert(4, 5, 4);

	std::vector<std::tuple<int, int, int>> result = graph.getGraph();
	ASSERT_EQ(result.size(), 16);
	ASSERT_NE(std::find(result.begin(), result.end(), std::tuple{ 0, 1, 1 }), result.end());
	ASSERT_NE(std::find(result.begin(), result.end(), std::tuple{ 1, 0, 1 }), result.end());
	ASSERT_NE(std::find(result.begin(), result.end(), std::tuple{ 0, 2, 1 }), result.end());
	ASSERT_NE(std::find(result.begin(), result.end(), std::tuple{ 2, 0, 1 }), result.end());
	ASSERT_NE(std::find(result.begin(), result.end(), std::tuple{ 0, 3, 1 }), result.end());
	ASSERT_NE(std::find(result.begin(), result.end(), std::tuple{ 3, 0, 1 }), result.end());
	ASSERT_NE(std::find(result.begin(), result.end(), std::tuple{ 1, 2, 2 }), result.end());
	ASSERT_NE(std::find(result.begin(), result.end(), std::tuple{ 2, 1, 2 }), result.end());
	ASSERT_NE(std::find(result.begin(), result.end(), std::tuple{ 1, 3, 2 }), result.end());
	ASSERT_NE(std::find(result.begin(), result.end(), std::tuple{ 3, 1, 2 }), result.end());
	ASSERT_NE(std::find(result.begin(), result.end(), std::tuple{ 2, 3, 3 }), result.end());
	ASSERT_NE(std::find(result.begin(), result.end(), std::tuple{ 3, 2, 3 }), result.end());
	ASSERT_NE(std::find(result.begin(), result.end(), std::tuple{ 2, 4, 3 }), result.end());
	ASSERT_NE(std::find(result.begin(), result.end(), std::tuple{ 4, 2, 3 }), result.end());
	ASSERT_NE(std::find(result.begin(), result.end(), std::tuple{ 4, 5, 4 }), result.end());
	ASSERT_NE(std::find(result.begin(), result.end(), std::tuple{ 5, 4, 4 }), result.end());
}

TEST(GraphList, Remove) {
	GraphList graph;
	graph.insert(0, 1, 1);
	graph.insert(0, 2, 1);
	graph.insert(0, 3, 1);
	graph.insert(1, 2, 2);
	graph.insert(1, 3, 2);
	graph.insert(2, 3, 3);
	graph.insert(2, 4, 3);
	graph.insert(4, 5, 4);

	graph.remove(0, 1);

	std::vector<std::tuple<int, int, int>> result = graph.getGraph();
	ASSERT_EQ(result.size(), 14);
	ASSERT_EQ(std::find(result.begin(), result.end(), std::tuple{ 0, 1, 1 }), result.end());
}

/*
  	1
  /   \
0   +   3
  \   /
	2
	|
	4 - 5
*/
TEST(GraphMatrix, Insert) {
	GraphMatrix graph;
	graph.insert(0, 1, 1);
	graph.insert(0, 2, 1);
	graph.insert(0, 3, 1);
	graph.insert(1, 2, 2);
	graph.insert(1, 3, 2);
	graph.insert(2, 3, 3);
	graph.insert(2, 4, 3);
	graph.insert(4, 5, 4);

	std::vector<std::tuple<int, int, int>> result = graph.getGraph();
	ASSERT_EQ(result.size(), 16);
	ASSERT_NE(std::find(result.begin(), result.end(), std::tuple{ 0, 1, 1 }), result.end());
	ASSERT_NE(std::find(result.begin(), result.end(), std::tuple{ 1, 0, 1 }), result.end());
	ASSERT_NE(std::find(result.begin(), result.end(), std::tuple{ 0, 2, 1 }), result.end());
	ASSERT_NE(std::find(result.begin(), result.end(), std::tuple{ 2, 0, 1 }), result.end());
	ASSERT_NE(std::find(result.begin(), result.end(), std::tuple{ 0, 3, 1 }), result.end());
	ASSERT_NE(std::find(result.begin(), result.end(), std::tuple{ 3, 0, 1 }), result.end());
	ASSERT_NE(std::find(result.begin(), result.end(), std::tuple{ 1, 2, 2 }), result.end());
	ASSERT_NE(std::find(result.begin(), result.end(), std::tuple{ 2, 1, 2 }), result.end());
	ASSERT_NE(std::find(result.begin(), result.end(), std::tuple{ 1, 3, 2 }), result.end());
	ASSERT_NE(std::find(result.begin(), result.end(), std::tuple{ 3, 1, 2 }), result.end());
	ASSERT_NE(std::find(result.begin(), result.end(), std::tuple{ 2, 3, 3 }), result.end());
	ASSERT_NE(std::find(result.begin(), result.end(), std::tuple{ 3, 2, 3 }), result.end());
	ASSERT_NE(std::find(result.begin(), result.end(), std::tuple{ 2, 4, 3 }), result.end());
	ASSERT_NE(std::find(result.begin(), result.end(), std::tuple{ 4, 2, 3 }), result.end());
	ASSERT_NE(std::find(result.begin(), result.end(), std::tuple{ 4, 5, 4 }), result.end());
	ASSERT_NE(std::find(result.begin(), result.end(), std::tuple{ 5, 4, 4 }), result.end());
}

TEST(GraphMatrix, Remove) {
	GraphMatrix graph;
	graph.insert(0, 1, 1);
	graph.insert(0, 2, 1);
	graph.insert(0, 3, 1);
	graph.insert(1, 2, 2);
	graph.insert(1, 3, 2);
	graph.insert(2, 3, 3);
	graph.insert(2, 4, 3);
	graph.insert(4, 5, 4);

	graph.remove(0, 1);

	std::vector<std::tuple<int, int, int>> result = graph.getGraph();
	ASSERT_EQ(result.size(), 14);
	ASSERT_EQ(std::find(result.begin(), result.end(), std::tuple{ 0, 1, 1 }), result.end());
}

TEST(GraphList, Traversal) {
	GraphList graph;
	graph.insert(0, 1, 1);
	graph.insert(0, 2, 1);
	graph.insert(0, 3, 1);
	graph.insert(1, 2, 2);
	graph.insert(1, 3, 2);
	graph.insert(2, 3, 3);
	graph.insert(2, 4, 3);
	graph.insert(4, 5, 4);

	auto parents = graph.breadthFirstTraversal(0);
	ASSERT_EQ(-1, parents[0]);
	ASSERT_EQ(0, parents[1]);
	ASSERT_EQ(0, parents[2]);
	ASSERT_EQ(0, parents[3]);
	ASSERT_EQ(2, parents[4]);
	ASSERT_EQ(4, parents[5]);
	parents = graph.breadthFirstTraversal(1);
	ASSERT_EQ(1, parents[0]);
	ASSERT_EQ(-1, parents[1]);
	ASSERT_EQ(1, parents[2]);
	ASSERT_EQ(1, parents[3]);
	ASSERT_EQ(2, parents[4]);
	ASSERT_EQ(4, parents[5]);
	parents = graph.breadthFirstTraversal(2);
	ASSERT_EQ(2, parents[0]);
	ASSERT_EQ(2, parents[1]);
	ASSERT_EQ(-1, parents[2]);
	ASSERT_EQ(2, parents[3]);
	ASSERT_EQ(2, parents[4]);
	ASSERT_EQ(4, parents[5]);
	parents = graph.breadthFirstTraversal(3);
	ASSERT_EQ(3, parents[0]);
	ASSERT_EQ(3, parents[1]);
	ASSERT_EQ(3, parents[2]);
	ASSERT_EQ(-1, parents[3]);
	ASSERT_EQ(2, parents[4]);
	ASSERT_EQ(4, parents[5]);
	parents = graph.breadthFirstTraversal(4);
	ASSERT_EQ(2, parents[0]);
	ASSERT_EQ(2, parents[1]);
	ASSERT_EQ(4, parents[2]);
	ASSERT_EQ(2, parents[3]);
	ASSERT_EQ(-1, parents[4]);
	ASSERT_EQ(4, parents[5]);
	parents = graph.breadthFirstTraversal(6);
	ASSERT_EQ(-1, parents[0]);
	ASSERT_EQ(-1, parents[1]);
	ASSERT_EQ(-1, parents[2]);
	ASSERT_EQ(-1, parents[3]);
	ASSERT_EQ(-1, parents[4]);
	ASSERT_EQ(-1, parents[5]);
}

/*
	1
  /   \
0   +   3
  \   /
	2
	
	4 - 5
*/
TEST(GraphList, Connected) {
	GraphList graph;
	graph.insert(0, 1, 1);
	graph.insert(0, 2, 1);
	graph.insert(0, 3, 1);
	graph.insert(1, 2, 2);
	graph.insert(1, 3, 2);
	graph.insert(2, 3, 3);
	graph.insert(4, 5, 4);

	auto connected = graph.getConnectedNumber();
	std::cout << "qwe";
}