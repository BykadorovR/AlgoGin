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

struct EdgeMatrix {
	int _weight;
};

class GraphList {
private:
	std::vector<std::vector<EdgeList>> _adjacencyList;
	bool _oriented;
public:
	GraphList(bool oriented = false);
	bool insert(int x, int y, int weight);
	bool remove(int x, int y);
	std::vector<std::vector<EdgeList>> reverse();
	
	std::vector<std::vector<EdgeList>> getAdjacencyList();
	std::vector<std::tuple<int, int, int>> getGraph();
};


class GraphMatrix {
private:
	std::vector<std::vector<std::optional<EdgeMatrix>>> _adjacencyMatrix;
public:
	bool insert(int x, int y, int weight);
	bool remove(int x, int y);

	std::vector<std::tuple<int, int, int>> getGraph();
};

class BFS {
private:
	std::vector<std::vector<EdgeList>> _adjacencyList;
public:
	BFS(GraphList& graph);
	BFS(std::shared_ptr<GraphList> graph);
	//traverse all nodes and find the shortest path from x to y
	std::vector<int> breadthFirstSearch(int start);
	std::vector<int> getConnectedNumber();

	std::vector<int> colorGraph();
};

class DFS {
private:
	std::vector<std::vector<EdgeList>> _adjacencyList;
	std::vector<std::vector<EdgeList>> _adjacencyListReversed;
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
	//topological sorting
	std::vector<int> _topologicalSorted;
	bool _DAG = true;
	//

	bool _depthFirstTraversalRecursive(int currentNode, std::map<int, bool>& visitedNodes, std::vector<int>& traversal);
public:
	DFS(GraphList& graph);
	DFS(std::shared_ptr<GraphList> graph);
	std::vector<int> depthFirstTraversal(int start);
	std::vector<std::vector<int>> getStronglyConnectedComponents();
	std::vector<int> getArticulationPoints();
	std::vector<int> getTopologicalSorted();
	std::map<std::string, std::vector<std::tuple<int, int>>> getEdgesType();
};

class MinimumSpanningTree {
private:
	std::vector<std::vector<EdgeList>> _adjacencyList;
public:
	MinimumSpanningTree(GraphList& graph);
	std::vector<std::tuple<int, int, int>> prim();
	std::vector<std::tuple<int, int, int>> kruskal();
};

class ShortestPath {
private:
	std::vector<std::vector<EdgeList>> _adjacencyList;
public:
	ShortestPath(GraphList& graph);
	std::map<int, int> dijkstra(int start);
};