#pragma once
#include <vector>
#include <map>
#include <memory>
#include <optional>
#include <string>

struct EdgeList {
	int _y;
	int _weight;
};

class GraphList {
private:
	std::vector<std::vector<EdgeList>> _adjacencyList;
public:
	GraphList() = default;
	bool insert(int x, int y, int weight);
	bool remove(int x, int y);
	//traverse all nodes and find the shortest path from x to y
	std::vector<int> breadthFirstSearch(int start);
	std::vector<int> getConnectedNumber();

	std::vector<int> colorGraph();

	std::vector<std::vector<EdgeList>> getAdjacencyList();
	std::vector<std::tuple<int, int, int>> getGraph();
};

class DFS {
private:
	std::vector<std::vector<EdgeList>> _adjacencyList;
	std::map<std::string, std::vector<std::tuple<int, int>>> _edgesType;
	std::vector<int> _parent;
	//edges type
	std::map<int, int> _timeStart, _timeEnd;
	int _timeIterator;
	//
	//articulation point
	std::map<int, int> _low;
	std::vector<int> _articulationPoints;
	std::map<int, std::vector<int>> _children;
	//
	bool _depthFirstTraversalRecursive(int currentNode, std::map<int, bool>& visitedNodes, std::vector<int>& traversal);
public:
	DFS(GraphList& graph);
	DFS(std::shared_ptr<GraphList> graph);
	std::vector<int> depthFirstTraversal(int start);
	std::vector<int> getArticulationPoints();
	std::map<std::string, std::vector<std::tuple<int, int>>> getEdgesType();
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