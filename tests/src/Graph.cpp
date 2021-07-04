#include <gtest/gtest.h>
#include "Graph.h"

/*
    1
0   +   3  
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
0   +   3
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

	graph.breadthFirstTraversal();
}