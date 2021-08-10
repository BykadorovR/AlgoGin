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

	BFS bfs(graph);
	auto parents = bfs.breadthFirstSearch(0);
	ASSERT_EQ(-1, parents[0]);
	ASSERT_EQ(0, parents[1]);
	ASSERT_EQ(0, parents[2]);
	ASSERT_EQ(0, parents[3]);
	ASSERT_EQ(2, parents[4]);
	ASSERT_EQ(4, parents[5]);
	parents = bfs.breadthFirstSearch(1);
	ASSERT_EQ(1, parents[0]);
	ASSERT_EQ(-1, parents[1]);
	ASSERT_EQ(1, parents[2]);
	ASSERT_EQ(1, parents[3]);
	ASSERT_EQ(2, parents[4]);
	ASSERT_EQ(4, parents[5]);
	parents = bfs.breadthFirstSearch(2);
	ASSERT_EQ(2, parents[0]);
	ASSERT_EQ(2, parents[1]);
	ASSERT_EQ(-1, parents[2]);
	ASSERT_EQ(2, parents[3]);
	ASSERT_EQ(2, parents[4]);
	ASSERT_EQ(4, parents[5]);
	parents = bfs.breadthFirstSearch(3);
	ASSERT_EQ(3, parents[0]);
	ASSERT_EQ(3, parents[1]);
	ASSERT_EQ(3, parents[2]);
	ASSERT_EQ(-1, parents[3]);
	ASSERT_EQ(2, parents[4]);
	ASSERT_EQ(4, parents[5]);
	parents = bfs.breadthFirstSearch(4);
	ASSERT_EQ(2, parents[0]);
	ASSERT_EQ(2, parents[1]);
	ASSERT_EQ(4, parents[2]);
	ASSERT_EQ(2, parents[3]);
	ASSERT_EQ(-1, parents[4]);
	ASSERT_EQ(4, parents[5]);
	parents = bfs.breadthFirstSearch(6);
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
TEST(GraphList, Connected_Several) {
	GraphList graph;
	graph.insert(0, 1, 1);
	graph.insert(0, 2, 1);
	graph.insert(0, 3, 1);
	graph.insert(1, 2, 2);
	graph.insert(1, 3, 2);
	graph.insert(2, 3, 3);
	graph.insert(4, 5, 4);

	BFS bfs(graph);
	auto connected = bfs.getConnectedNumber();
	ASSERT_EQ(connected[0], 0);
	ASSERT_EQ(connected[1], 0);
	ASSERT_EQ(connected[2], 0);
	ASSERT_EQ(connected[3], 0);
	ASSERT_EQ(connected[4], 1);
	ASSERT_EQ(connected[5], 1);
}

TEST(GraphList, Connected_One) {
	GraphList graph;
	graph.insert(0, 1, 1);
	graph.insert(0, 2, 1);
	graph.insert(0, 3, 1);
	graph.insert(1, 2, 2);
	graph.insert(1, 3, 2);
	graph.insert(2, 3, 3);
	graph.insert(2, 4, 4);
	graph.insert(4, 5, 5);

	BFS bfs(graph);
	auto connected = bfs.getConnectedNumber();
	ASSERT_EQ(connected[0], 0);
	ASSERT_EQ(connected[1], 0);
	ASSERT_EQ(connected[2], 0);
	ASSERT_EQ(connected[3], 0);
	ASSERT_EQ(connected[4], 0);
	ASSERT_EQ(connected[5], 0);
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
TEST(GraphList, Coloring_4) {
	GraphList graph;
	graph.insert(0, 1, 1);
	graph.insert(0, 2, 1);
	graph.insert(0, 3, 1);
	graph.insert(1, 2, 2);
	graph.insert(1, 3, 2);
	graph.insert(2, 3, 3);
	graph.insert(2, 4, 4);
	graph.insert(4, 5, 5);

	BFS bfs(graph);
	auto colors = bfs.colorGraph();
	ASSERT_EQ(colors[0], 0);
	ASSERT_EQ(colors[1], 1);
	ASSERT_EQ(colors[2], 2);
	ASSERT_EQ(colors[3], 3);
	ASSERT_EQ(colors[4], 0);
	ASSERT_EQ(colors[5], 1);
}

/*
0   -   1
      /
|   3   |
  /
2   -   4
*/
TEST(GraphList, Coloring_2) {
	GraphList graph;
	graph.insert(0, 1, 1);
	graph.insert(0, 2, 2);
	graph.insert(2, 3, 3);
	graph.insert(2, 4, 4);
	graph.insert(1, 3, 5);
	graph.insert(1, 4, 6);

	BFS bfs(graph);
	auto colors = bfs.colorGraph();
	ASSERT_EQ(colors[0], 0);
	ASSERT_EQ(colors[1], 1);
	ASSERT_EQ(colors[2], 1);
	ASSERT_EQ(colors[3], 0);
	ASSERT_EQ(colors[4], 0);
}

TEST(GraphList, DFS_start0) {
/*
	0   -   1
		  /
	|   3   |
	  /
	2   -   4
*/
	GraphList graph;
	graph.insert(0, 1, 1);
	graph.insert(0, 2, 2);
	graph.insert(2, 3, 3);
	graph.insert(2, 4, 4);
	graph.insert(1, 3, 5);
	graph.insert(1, 4, 6);

	DFS dfs(graph);
	auto traversal = dfs.depthFirstTraversal(0);
	ASSERT_EQ(traversal[0], 0);
	ASSERT_EQ(traversal[1], 1);
	ASSERT_EQ(traversal[2], 3);
	ASSERT_EQ(traversal[3], 2);
	ASSERT_EQ(traversal[4], 4);
/*
	1
  /   \
0   +   3
  \   /
	2
	|
	4 - 5
*/
	GraphList graph2;
	graph2.insert(0, 1, 1);
	graph2.insert(0, 2, 1);
	graph2.insert(0, 3, 1);
	graph2.insert(1, 2, 2);
	graph2.insert(1, 3, 2);
	graph2.insert(2, 3, 3);
	graph2.insert(2, 4, 3);
	graph2.insert(4, 5, 4);

	DFS dfs2(graph2);
	traversal = dfs2.depthFirstTraversal(0);
	ASSERT_EQ(traversal[0], 0);
	ASSERT_EQ(traversal[1], 1);
	ASSERT_EQ(traversal[2], 2);
	ASSERT_EQ(traversal[3], 3);
	ASSERT_EQ(traversal[4], 4);
	ASSERT_EQ(traversal[5], 5);
}

TEST(GraphList, DFS_startNot0) {
	/*
		0   -   1
			  /
		|   3   |
		  /
		2   -   4
	*/
	GraphList graph;
	graph.insert(0, 1, 1);
	graph.insert(0, 2, 2);
	graph.insert(2, 3, 3);
	graph.insert(2, 4, 4);
	graph.insert(1, 3, 5);
	graph.insert(1, 4, 6);

	DFS dfs(graph);
	auto traversal = dfs.depthFirstTraversal(3);
	ASSERT_EQ(traversal[0], 3);
	ASSERT_EQ(traversal[1], 2);
	ASSERT_EQ(traversal[2], 0);
	ASSERT_EQ(traversal[3], 1);
	ASSERT_EQ(traversal[4], 4);
	/*
		1
	  /   \
	0   +   3
	  \   /
		2
		|
		4 - 5
	*/
	GraphList graph2;
	graph2.insert(0, 1, 1);
	graph2.insert(0, 2, 1);
	graph2.insert(0, 3, 1);
	graph2.insert(1, 2, 2);
	graph2.insert(1, 3, 2);
	graph2.insert(2, 3, 3);
	graph2.insert(2, 4, 3);
	graph2.insert(4, 5, 4);

	DFS dfs2(graph2);
	traversal = dfs2.depthFirstTraversal(3);
	ASSERT_EQ(traversal[0], 3);
	ASSERT_EQ(traversal[1], 0);
	ASSERT_EQ(traversal[2], 1);
	ASSERT_EQ(traversal[3], 2);
	ASSERT_EQ(traversal[4], 4);
	ASSERT_EQ(traversal[5], 5);
}

TEST(GraphList, DFS_getEdgesType) {
	/*
		0   -   1
			  /
		|   3   |
		  /
		2   -   4
	*/
	GraphList graph;
	graph.insert(0, 1, 1);
	graph.insert(0, 2, 2);
	graph.insert(2, 3, 3);
	graph.insert(2, 4, 4);
	graph.insert(1, 3, 5);
	graph.insert(1, 4, 6);

	DFS dfs(graph);
	auto traversal = dfs.depthFirstTraversal(3);
	auto types = dfs.getEdgesType();
	ASSERT_EQ(std::get<0>(types["tree"][0]), 3);
	ASSERT_EQ(std::get<1>(types["tree"][0]), 2);
	ASSERT_EQ(std::get<0>(types["tree"][1]), 2);
	ASSERT_EQ(std::get<1>(types["tree"][1]), 0);
	ASSERT_EQ(std::get<0>(types["tree"][2]), 0);
	ASSERT_EQ(std::get<1>(types["tree"][2]), 1);
	ASSERT_EQ(std::get<0>(types["tree"][3]), 1);
	ASSERT_EQ(std::get<1>(types["tree"][3]), 4);
	ASSERT_EQ(std::get<0>(types["back"][0]), 1);
	ASSERT_EQ(std::get<1>(types["back"][0]), 3);
	ASSERT_EQ(std::get<0>(types["back"][1]), 4);
	ASSERT_EQ(std::get<1>(types["back"][1]), 2);
	ASSERT_EQ(std::get<0>(types["forward"][0]), 2);
	ASSERT_EQ(std::get<1>(types["forward"][0]), 4);
	ASSERT_EQ(std::get<0>(types["forward"][1]), 3);
	ASSERT_EQ(std::get<1>(types["forward"][1]), 1);
}

TEST(GraphList, DFS_getArticularPoints) {
	/*
	       3
	      /
	0 - 1
	|     \
	\	   2 - 4
	 \_ _ _ _ /
	*/
	GraphList graph;
	graph.insert(0, 1, 1);
	graph.insert(1, 3, 2);
	graph.insert(1, 2, 3);
	graph.insert(2, 4, 4);
	graph.insert(4, 0, 5);

	DFS dfs(graph);
	auto traversal = dfs.depthFirstTraversal(0);
	auto articulation = dfs.getArticulationPoints();
	ASSERT_EQ(articulation[0], 1);

	/*
	
	1 - 0 - 3
	|  /    |
	2       4
	*/
	GraphList graph2;
	graph2.insert(1, 0, 1);
	graph2.insert(1, 2, 2);
	graph2.insert(2, 0, 3);
	graph2.insert(0, 3, 4);
	graph2.insert(3, 4, 5);

	DFS dfs2(graph2);
	traversal = dfs2.depthFirstTraversal(0);
	articulation = dfs2.getArticulationPoints();
	ASSERT_EQ(articulation[0], 3);
	ASSERT_EQ(articulation[1], 0);
}

TEST(GraphList, DFS_topologicalSorting) {
	/*
	5      4
	| \   / \
	   * *   \
	|   0     \
	*          *
	2 -> 3 -->  1
	*/
	GraphList graph(true);
	graph.insert(5, 0, 1);
	graph.insert(4, 0, 2);
	graph.insert(5, 2, 3);
	graph.insert(2, 3, 4);
	graph.insert(4, 1, 5);
	graph.insert(3, 1, 5);

	DFS dfs(graph);
	dfs.depthFirstTraversal(0);
	auto topological = dfs.getTopologicalSorted();
	ASSERT_EQ(topological[0], 5);
	ASSERT_EQ(topological[1], 4);
	ASSERT_EQ(topological[2], 2);
	ASSERT_EQ(topological[3], 3);
	ASSERT_EQ(topological[4], 1);
	ASSERT_EQ(topological[5], 0);

	//almost the same but with cycle 3->5
	graph.insert(3, 5, 5);
	dfs = DFS(graph);
	dfs.depthFirstTraversal(0);
	topological = dfs.getTopologicalSorted();
	ASSERT_EQ(topological.size(), 0);
}

TEST(GraphList, DFS_stronglyConnectedComponents) {
	/*
	1 -> 0 -> 3
	*   /     |
	| *       *
	2         4
	*/

	GraphList graph(true);
	graph.insert(1, 0, 1);
	graph.insert(2, 1, 2);
	graph.insert(0, 2, 3);
	graph.insert(0, 3, 4);
	graph.insert(3, 4, 5);

	DFS dfs(graph);
	auto strongly = dfs.getStronglyConnectedComponents();
	ASSERT_EQ(strongly[0].size(), 3);
	ASSERT_EQ(strongly[0][0], 0);
	ASSERT_EQ(strongly[0][1], 1);
	ASSERT_EQ(strongly[0][2], 2);
	ASSERT_EQ(strongly[1].size(), 1);
	ASSERT_EQ(strongly[1][0], 3);
	ASSERT_EQ(strongly[2].size(), 1);
	ASSERT_EQ(strongly[2][0], 4);
}

TEST(GraphList, Prim_algorithm) {
	//graph from geeksforgeeks
	GraphList graph;
	graph.insert(0, 1, 4);
	graph.insert(0, 7, 8);
	graph.insert(1, 7, 11);
	graph.insert(1, 2, 8);
	graph.insert(7, 6, 1);
	graph.insert(7, 8, 7);
	graph.insert(2, 8, 2);
	graph.insert(8, 6, 6);
	graph.insert(2, 3, 7);
	graph.insert(2, 5, 4);
	graph.insert(6, 5, 2);
	graph.insert(3, 5, 14);
	graph.insert(3, 4, 9);
	graph.insert(5, 4, 10);

	MinimumSpanningTree MST(graph);
	auto result = MST.prim();
	ASSERT_EQ(std::get<0>(result[0]), 0);
	ASSERT_EQ(std::get<1>(result[0]), 1);
	ASSERT_EQ(std::get<2>(result[0]), 4);
	ASSERT_EQ(std::get<0>(result[1]), 1);
	ASSERT_EQ(std::get<1>(result[1]), 2);
	ASSERT_EQ(std::get<2>(result[1]), 8);
	ASSERT_EQ(std::get<0>(result[2]), 2);
	ASSERT_EQ(std::get<1>(result[2]), 8);
	ASSERT_EQ(std::get<2>(result[2]), 2);
	ASSERT_EQ(std::get<0>(result[3]), 2);
	ASSERT_EQ(std::get<1>(result[3]), 5);
	ASSERT_EQ(std::get<2>(result[3]), 4);
	ASSERT_EQ(std::get<0>(result[4]), 5);
	ASSERT_EQ(std::get<1>(result[4]), 6);
	ASSERT_EQ(std::get<2>(result[4]), 2);
	ASSERT_EQ(std::get<0>(result[5]), 6);
	ASSERT_EQ(std::get<1>(result[5]), 7);
	ASSERT_EQ(std::get<2>(result[5]), 1);
	ASSERT_EQ(std::get<0>(result[6]), 2);
	ASSERT_EQ(std::get<1>(result[6]), 3);
	ASSERT_EQ(std::get<2>(result[6]), 7);
	ASSERT_EQ(std::get<0>(result[7]), 3);
	ASSERT_EQ(std::get<1>(result[7]), 4);
	ASSERT_EQ(std::get<2>(result[7]), 9);

	//graph from one note
	GraphList graph2;
	graph2.insert(0, 1, 7);
	graph2.insert(0, 3, 5);
	graph2.insert(1, 3, 9);
	graph2.insert(1, 2, 8);
	graph2.insert(1, 4, 7);
	graph2.insert(2, 4, 5);
	graph2.insert(3, 4, 15);
	graph2.insert(3, 5, 6);
	graph2.insert(4, 5, 8);
	graph2.insert(4, 6, 9);
	graph2.insert(5, 6, 11);

	MinimumSpanningTree MST2(graph2);
	result = MST2.prim();
	ASSERT_EQ(std::get<0>(result[0]), 0);
	ASSERT_EQ(std::get<1>(result[0]), 3);
	ASSERT_EQ(std::get<2>(result[0]), 5);
	ASSERT_EQ(std::get<0>(result[1]), 3);
	ASSERT_EQ(std::get<1>(result[1]), 5);
	ASSERT_EQ(std::get<2>(result[1]), 6);
	ASSERT_EQ(std::get<0>(result[2]), 0);
	ASSERT_EQ(std::get<1>(result[2]), 1);
	ASSERT_EQ(std::get<2>(result[2]), 7);
	ASSERT_EQ(std::get<0>(result[3]), 1);
	ASSERT_EQ(std::get<1>(result[3]), 4);
	ASSERT_EQ(std::get<2>(result[3]), 7);
	ASSERT_EQ(std::get<0>(result[4]), 4);
	ASSERT_EQ(std::get<1>(result[4]), 2);
	ASSERT_EQ(std::get<2>(result[4]), 5);
	ASSERT_EQ(std::get<0>(result[5]), 4);
	ASSERT_EQ(std::get<1>(result[5]), 6);
	ASSERT_EQ(std::get<2>(result[5]), 9);
}

TEST(GraphList, Kruskal_algorithm) {
	//graph from geeksforgeeks
	GraphList graph;
	graph.insert(0, 1, 4);
	graph.insert(0, 7, 8);
	graph.insert(1, 7, 11);
	graph.insert(1, 2, 8);
	graph.insert(7, 6, 1);
	graph.insert(7, 8, 7);
	graph.insert(2, 8, 2);
	graph.insert(8, 6, 6);
	graph.insert(2, 3, 7);
	graph.insert(2, 5, 4);
	graph.insert(6, 5, 2);
	graph.insert(3, 5, 14);
	graph.insert(3, 4, 9);
	graph.insert(5, 4, 10);

	MinimumSpanningTree MST(graph);
	auto result = MST.kruskal();
	ASSERT_EQ(std::get<0>(result[0]), 6);
	ASSERT_EQ(std::get<1>(result[0]), 7);
	ASSERT_EQ(std::get<2>(result[0]), 1);
	ASSERT_EQ(std::get<0>(result[1]), 2);
	ASSERT_EQ(std::get<1>(result[1]), 8);
	ASSERT_EQ(std::get<2>(result[1]), 2);
	ASSERT_EQ(std::get<0>(result[2]), 5);
	ASSERT_EQ(std::get<1>(result[2]), 6);
	ASSERT_EQ(std::get<2>(result[2]), 2);
	ASSERT_EQ(std::get<0>(result[3]), 0);
	ASSERT_EQ(std::get<1>(result[3]), 1);
	ASSERT_EQ(std::get<2>(result[3]), 4);
	ASSERT_EQ(std::get<0>(result[4]), 2);
	ASSERT_EQ(std::get<1>(result[4]), 5);
	ASSERT_EQ(std::get<2>(result[4]), 4);
	ASSERT_EQ(std::get<0>(result[5]), 2);
	ASSERT_EQ(std::get<1>(result[5]), 3);
	ASSERT_EQ(std::get<2>(result[5]), 7);
	ASSERT_EQ(std::get<0>(result[6]), 0);
	ASSERT_EQ(std::get<1>(result[6]), 7);
	ASSERT_EQ(std::get<2>(result[6]), 8);
	ASSERT_EQ(std::get<0>(result[7]), 3);
	ASSERT_EQ(std::get<1>(result[7]), 4);
	ASSERT_EQ(std::get<2>(result[7]), 9);

	//graph from one note
	GraphList graph2;
	graph2.insert(0, 1, 7);
	graph2.insert(0, 3, 5);
	graph2.insert(1, 3, 9);
	graph2.insert(1, 2, 8);
	graph2.insert(1, 4, 7);
	graph2.insert(2, 4, 5);
	graph2.insert(3, 4, 15);
	graph2.insert(3, 5, 6);
	graph2.insert(4, 5, 8);
	graph2.insert(4, 6, 9);
	graph2.insert(5, 6, 11);

	MinimumSpanningTree MST2(graph2);
	result = MST2.kruskal();
	ASSERT_EQ(std::get<0>(result[0]), 0);
	ASSERT_EQ(std::get<1>(result[0]), 3);
	ASSERT_EQ(std::get<2>(result[0]), 5);
	ASSERT_EQ(std::get<0>(result[1]), 2);
	ASSERT_EQ(std::get<1>(result[1]), 4);
	ASSERT_EQ(std::get<2>(result[1]), 5);
	ASSERT_EQ(std::get<0>(result[2]), 3);
	ASSERT_EQ(std::get<1>(result[2]), 5);
	ASSERT_EQ(std::get<2>(result[2]), 6);
	ASSERT_EQ(std::get<0>(result[3]), 0);
	ASSERT_EQ(std::get<1>(result[3]), 1);
	ASSERT_EQ(std::get<2>(result[3]), 7);
	ASSERT_EQ(std::get<0>(result[4]), 1);
	ASSERT_EQ(std::get<1>(result[4]), 4);
	ASSERT_EQ(std::get<2>(result[4]), 7);
	ASSERT_EQ(std::get<0>(result[5]), 4);
	ASSERT_EQ(std::get<1>(result[5]), 6);
	ASSERT_EQ(std::get<2>(result[5]), 9);
}

TEST(GraphList, Dijkstra_algorithm) {
	//graph from geeksforgeeks
	GraphList graph;
	graph.insert(0, 1, 4);
	graph.insert(0, 7, 8);
	graph.insert(1, 7, 11);
	graph.insert(1, 2, 8);
	graph.insert(7, 6, 1);
	graph.insert(7, 8, 7);
	graph.insert(2, 8, 2);
	graph.insert(8, 6, 6);
	graph.insert(2, 3, 7);
	graph.insert(2, 5, 4);
	graph.insert(6, 5, 2);
	graph.insert(3, 5, 14);
	graph.insert(3, 4, 9);
	graph.insert(5, 4, 10);

	ShortestPath sp(graph);
	auto result = sp.dijkstra(0);
	ASSERT_EQ(result[0], 0);
	ASSERT_EQ(result[1], 4);
	ASSERT_EQ(result[2], 12);
	ASSERT_EQ(result[3], 19);
	ASSERT_EQ(result[4], 21);
	ASSERT_EQ(result[5], 11);
	ASSERT_EQ(result[6], 9);
	ASSERT_EQ(result[7], 8);
	ASSERT_EQ(result[8], 14);

	result = sp.dijkstra(5);
	ASSERT_EQ(result[0], 11);
	ASSERT_EQ(result[1], 12);
	ASSERT_EQ(result[2], 4);
	ASSERT_EQ(result[3], 11);
	ASSERT_EQ(result[4], 10);
	ASSERT_EQ(result[5], 0);
	ASSERT_EQ(result[6], 2);
	ASSERT_EQ(result[7], 3);
	ASSERT_EQ(result[8], 6);
}

TEST(GraphMatrix, FloydWarshall_algorithm) {
	GraphMatrix graph;
	graph.insert(0, 1, 4);
	graph.insert(0, 7, 8);
	graph.insert(1, 7, 11);
	graph.insert(1, 2, 8);
	graph.insert(7, 6, 1);
	graph.insert(7, 8, 7);
	graph.insert(2, 8, 2);
	graph.insert(8, 6, 6);
	graph.insert(2, 3, 7);
	graph.insert(2, 5, 4);
	graph.insert(6, 5, 2);
	graph.insert(3, 5, 14);
	graph.insert(3, 4, 9);
	graph.insert(5, 4, 10);

	ShortestPath sp(graph);
	auto result = sp.floydWarshall();
}

TEST(GraphList, EdmondKarp_algorithm) {
	//wiki graph
	GraphMatrix graph(true);
	graph.insert(0, 1, 3);
	graph.insert(0, 3, 3);
	graph.insert(1, 2, 4);
	graph.insert(2, 0, 3);
	graph.insert(2, 3, 1);
	graph.insert(4, 1, 1);
	graph.insert(2, 4, 2);
	graph.insert(3, 4, 2);
	graph.insert(3, 5, 6);
	graph.insert(4, 6, 1);
	graph.insert(5, 6, 9);

	MaximumFlow mf(graph);
	auto result = mf.edmondsKarp(0, 6);
	ASSERT_EQ(result, 5);

	//one note graph
	GraphMatrix graph2(true);
	graph2.insert(0, 1, 10);
	graph2.insert(0, 3, 2);
	graph2.insert(0, 4, 4);
	graph2.insert(1, 3, 7);
	graph2.insert(1, 2, 5);
	graph2.insert(2, 6, 8);
	graph2.insert(3, 2, 6);
	graph2.insert(3, 6, 2);
	graph2.insert(4, 5, 10);
	graph2.insert(5, 6, 13);

	mf = MaximumFlow(graph2);
	result = mf.edmondsKarp(0, 6);
	ASSERT_EQ(result, 14);
}