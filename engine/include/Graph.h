#pragma once
#include <vector>
#include <memory>
#include <optional>

class GraphList {
private:
	struct Edge {
		int _y;
		int _weight;
	};

	std::vector<std::vector<Edge>> _adjacencyList;
public:
	bool insert(int x, int y, int weight);
	bool remove(int x, int y);
	//traverse all nodes and find the shortest path from x to y
	std::vector<int> breadthFirstTraversal(int start);
	std::vector<int> getConnectedNumber();

	std::vector<std::tuple<int, int, int>> getGraph();
};

class GraphMatrix {
private:
	struct Edge {
		int _weight;
	};

	std::vector<std::vector<std::optional<Edge>>> _adjacencyMatrix;
public:
	bool insert(int x, int y, int weight);
	bool remove(int x, int y);

	std::vector<std::tuple<int, int, int>> getGraph();
};