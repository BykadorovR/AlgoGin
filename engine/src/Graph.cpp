#include "Graph.h"
#include <algorithm>

std::vector<int> GraphList::colorGraph() {
	//maximum color = d + 1, if d = |V| - 1, then maximum color = |V|
	std::vector<int> color(_adjacencyList.size(), _adjacencyList.size());
	std::vector<int> openNodes, closedNodes;
	openNodes.push_back(0);

	while (openNodes.size() > 0) {
		auto currentNode = openNodes.at(0);
		std::vector<int> currentColors;
		for (int i = 0; i < _adjacencyList[currentNode].size(); i++) {
			//find all color of adjustment vertexes
			currentColors.push_back(color[_adjacencyList[currentNode][i]._y]);

			if (std::find(openNodes.begin(), openNodes.end(), _adjacencyList[currentNode][i]._y) == openNodes.end() &&
				std::find(closedNodes.begin(), closedNodes.end(), _adjacencyList[currentNode][i]._y) == closedNodes.end()) {
				openNodes.push_back(_adjacencyList[currentNode][i]._y);
			}
		}
		//decide color of current vertex
		int currentColor = 0;
		for (bool foundColor = false; foundColor == false;) {
			if (std::find(currentColors.begin(), currentColors.end(), currentColor) == currentColors.end()) {
				color[currentNode] = currentColor;
				foundColor = true;
			}
			else
				currentColor++;
		}

		openNodes.erase(openNodes.begin());
		closedNodes.push_back(currentNode);
	}

	return color;
}

std::vector<int> GraphList::getConnectedNumber() {
	std::vector<int> connectedNodes(_adjacencyList.size(), -1);
	std::vector<int> openNodes, closedNodes;

	int currentConnection = 0;
	int startNode = 0;
	while (startNode != -1) {
		openNodes.clear();
		openNodes.push_back(startNode);
		while (openNodes.size() > 0) {
			auto currentNode = openNodes.at(0);
			for (int i = 0; i < _adjacencyList[currentNode].size(); i++) {
				if (std::find(openNodes.begin(), openNodes.end(), _adjacencyList[currentNode][i]._y) == openNodes.end() &&
					std::find(closedNodes.begin(), closedNodes.end(), _adjacencyList[currentNode][i]._y) == closedNodes.end()) {
					openNodes.push_back(_adjacencyList[currentNode][i]._y);
				}
			}
			connectedNodes[currentNode] = currentConnection;

			openNodes.erase(openNodes.begin());
			closedNodes.push_back(currentNode);
		}

		currentConnection++;

		startNode = -1;
		for (int i = 0; i < connectedNodes.size(); i++) {
			if (connectedNodes[i] == -1) {
				startNode = i;
				break;
			}
		}
	}

	return connectedNodes;
}

//1. Traverse nodes or edges?
//2. BFS searches the shortest path but what about DFS?
//3. What about traversing in case of several connectivity components
//4. Commivoyager task, what's the goal?
// 
std::vector<int> GraphList::breadthFirstSearch(int start) {
	std::vector<int> parentNodes(_adjacencyList.size(), -1);
	if (start >= _adjacencyList.size())
		return parentNodes;

	std::vector<int> openNodes, closedNodes;
	openNodes.push_back(start);

	while (openNodes.size() > 0) {
		auto currentNode = openNodes.at(0);
		for (int i = 0; i < _adjacencyList[currentNode].size(); i++) {
			if (std::find(openNodes.begin(), openNodes.end(), _adjacencyList[currentNode][i]._y) == openNodes.end() &&
				std::find(closedNodes.begin(), closedNodes.end(), _adjacencyList[currentNode][i]._y) == closedNodes.end()) {
				openNodes.push_back(_adjacencyList[currentNode][i]._y);
				parentNodes[_adjacencyList[currentNode][i]._y] = currentNode;
			}
		}
		openNodes.erase(openNodes.begin());
		closedNodes.push_back(currentNode);
	}

	return parentNodes;
}

bool GraphList::insert(int x, int y, int weight) {
	while (_adjacencyList.size() < std::max(x, y) + 1) {
		_adjacencyList.push_back(std::vector<EdgeList>());
	}
	
	_adjacencyList[x].push_back(EdgeList{ ._y = y, ._weight = weight });
	_adjacencyList[y].push_back(EdgeList{ ._y = x, ._weight = weight });

	return false;
}

bool GraphList::remove(int x, int y) {
	if (_adjacencyList.size() < std::max(x, y) + 1)
		return true;

	_adjacencyList[x].erase(std::remove_if(_adjacencyList[x].begin(), _adjacencyList[x].end(), [y](EdgeList edge) { return edge._y == y; }));
	_adjacencyList[y].erase(std::remove_if(_adjacencyList[y].begin(), _adjacencyList[y].end(), [x](EdgeList edge) { return edge._y == x; }));

	return false;
}

std::vector<std::vector<EdgeList>> GraphList::getAdjacencyList() {
	return _adjacencyList;
}

std::vector<std::tuple<int, int, int>> GraphList::getGraph() {
	std::vector<std::tuple<int, int, int>> result;
	for (int i = 0; i < _adjacencyList.size(); i++) {
		for (int j = 0; j < _adjacencyList[i].size(); j++) {
			result.push_back({ i, _adjacencyList[i][j]._y, _adjacencyList[i][j]._weight });
		}
	}

	return result;
}

bool GraphMatrix::insert(int x, int y, int weight) {
	if (_adjacencyMatrix.size() < std::max(x, y) + 1) {
		_adjacencyMatrix.resize(std::max(x, y) + 1);
		for (int i = 0; i < _adjacencyMatrix.size(); i++) {
			_adjacencyMatrix[i].resize(std::max(x, y) + 1);
		}
	}
	
	if (_adjacencyMatrix[x][y].has_value() == false)
		_adjacencyMatrix[x][y] = Edge();
	if (_adjacencyMatrix[y][x].has_value() == false)
		_adjacencyMatrix[y][x] = Edge();

	_adjacencyMatrix[x][y].value()._weight = weight;
	_adjacencyMatrix[y][x].value()._weight = weight;

	return false;
}

bool GraphMatrix::remove(int x, int y) {
	if (_adjacencyMatrix.size() < std::max(x, y) + 1) {
		return true;
	}

	_adjacencyMatrix[x][y] = std::nullopt;
	_adjacencyMatrix[y][x] = std::nullopt;

	return false;
}

std::vector<std::tuple<int, int, int>> GraphMatrix::getGraph() {
	std::vector<std::tuple<int, int, int>> result;
	for (int i = 0; i < _adjacencyMatrix.size(); i++)
		for (int j = 0; j < _adjacencyMatrix[i].size(); j++) {
			if (_adjacencyMatrix[i][j].has_value())
				result.push_back({ i, j, _adjacencyMatrix[i][j].value()._weight });
		}

	return result;
}

DFS::DFS(std::shared_ptr<GraphList> graph) {
	_adjacencyList = graph->getAdjacencyList();

	_parent.resize(_adjacencyList.size());
}

DFS::DFS(GraphList& graph) {
	_adjacencyList = graph.getAdjacencyList();

	_parent.resize(_adjacencyList.size());
}

bool DFS::_depthFirstTraversalRecursive(int currentNode, std::map<int, bool>& visitedNodes, std::vector<int>& traversal) {
	for (int i = 0; i < _adjacencyList[currentNode].size(); i++) {
		int adjacentNode = _adjacencyList[currentNode][i]._y;
		if (visitedNodes[adjacentNode] == false) {
			visitedNodes[adjacentNode] = true;
			_edgesType["tree"] = { currentNode, adjacentNode };
			_parent[adjacentNode] = currentNode;
			_timeStart[adjacentNode] = _timeIterator;
			_timeIterator++;
			traversal.push_back(adjacentNode);
			_depthFirstTraversalRecursive(adjacentNode, visitedNodes, traversal);
		}
		else {
			//node isn't closed and parent of adjacent node != current node then back edge
			if (_timeEnd.find(adjacentNode) == _timeEnd.end() && 
				_parent[adjacentNode] != currentNode) {
				_edgesType["back"] = { currentNode, adjacentNode };
			}
			//adjacent node is closed
			else if (_timeEnd.find(adjacentNode) != _timeEnd.end() &&
					 _parent[adjacentNode] != currentNode) {
				_edgesType["forward"] = { currentNode, adjacentNode };
			}
		}
	}
	_timeEnd[currentNode] = _timeIterator;
	_timeIterator++;

	return false;
}

std::map<std::string, std::tuple<int, int>> DFS::getEdgesType() {
	return _edgesType;
}

std::vector<int> DFS::depthFirstTraversal(int start) {
	std::map<int, bool> visitedNodes;
	std::vector<int> traversal;
	_timeIterator = 0;

	visitedNodes[start] = true;
	_timeStart[start] = _timeIterator;
	_timeIterator++;
	traversal.push_back(start);

	_depthFirstTraversalRecursive(start, visitedNodes, traversal);

	return traversal;
}
