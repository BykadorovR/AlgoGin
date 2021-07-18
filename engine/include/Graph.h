#pragma once
#include <vector>
#include <map>
#include <memory>
#include <optional>
#include <string>

class GraphList {
private:
	struct Edge {
		int _y;
		int _weight;
	};

	std::vector<std::vector<Edge>> _adjacencyList;
	std::vector<std::tuple<int, std::string>> _edgesType;

	//edges type
	std::map<int, std::tuple<int, int>> _time;
	int _timeIterator;
	//
	bool _depthFirstTraversalRecursive(int currentNode, std::map<int, bool>& visitedNodes, std::vector<int>& traversal);
public:
	GraphList() = default;
	bool insert(int x, int y, int weight);
	bool remove(int x, int y);
	//traverse all nodes and find the shortest path from x to y
	std::vector<int> breadthFirstSearch(int start);
	std::vector<int> depthFirstTraversal(int start);
	std::vector<int> getConnectedNumber();
	std::map<int, std::tuple<int, int>> getEdgesType();
	std::vector<int> colorGraph();

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