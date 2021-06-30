#include "Graph.h"

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

	std::remove_if(_adjacencyList[x].begin(), _adjacencyList[x].end(), [y](Edge edge) { return edge._y == y; });
	std::remove_if(_adjacencyList[y].begin(), _adjacencyList[y].end(), [x](Edge edge) { return edge._y == x; });

	return false;
}

std::vector<std::tuple<int, int, int>> GraphList::traversal() {
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
		for (int i = 0; i < _adjacencyMatrix.size(); i++) {
			_adjacencyMatrix[i].resize(std::max(x, y) + 1);
		}
		_adjacencyMatrix.resize(std::max(x, y) + 1);
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

std::vector<std::tuple<int, int, int>> GraphMatrix::traversal() {
	std::vector<std::tuple<int, int, int>> result;
	for (int i = 0; i < _adjacencyMatrix.size(); i++)
		for (int j = 0; j < _adjacencyMatrix[i].size(); j++) {
			if (_adjacencyMatrix[i][j].has_value())
				result.push_back({ i, j, _adjacencyMatrix[i][j].value()._weight });
		}

	return result;
}