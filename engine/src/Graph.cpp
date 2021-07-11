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

bool GraphList::_depthFirstTraversalRecursive(std::vector<int>& openNodes, std::vector<int>& closedNodes) {
	while (openNodes.size() > 0) {
		int currentNode = openNodes.back();
		for (int i = 0; i < _adjacencyList[currentNode].size(); i++) {
			if (std::find(openNodes.begin(), openNodes.end(), _adjacencyList[currentNode][i]._y) == openNodes.end() &&
				std::find(closedNodes.begin(), closedNodes.end(), _adjacencyList[currentNode][i]._y) == closedNodes.end()) {
				openNodes.push_back(_adjacencyList[currentNode][i]._y);
			}


		}
	}

	return false;
}

std::vector<int> GraphList::depthFirstTraversal() {
	std::vector<int> openNodes;
	std::vector<int> closedNodes;

	openNodes.push_back(0);
	_depthFirstTraversalRecursive(openNodes, closedNodes);
}

bool GraphList::insert(int x, int y, int weight) {
	while (_adjacencyList.size() < std::max(x, y) + 1) {
		_adjacencyList.push_back(std::vector<Edge>());
	}
	
	_adjacencyList[x].push_back(Edge{ ._y = y, ._weight = weight });
	_adjacencyList[y].push_back(Edge{ ._y = x, ._weight = weight });

	return false;
}

bool GraphList::remove(int x, int y) {
	if (_adjacencyList.size() < std::max(x, y) + 1)
		return true;

	_adjacencyList[x].erase(std::remove_if(_adjacencyList[x].begin(), _adjacencyList[x].end(), [y](Edge edge) { return edge._y == y; }));
	_adjacencyList[y].erase(std::remove_if(_adjacencyList[y].begin(), _adjacencyList[y].end(), [x](Edge edge) { return edge._y == x; }));

	return false;
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