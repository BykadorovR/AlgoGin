#include "Graph.h"
#include <algorithm>

GraphList::GraphList(bool oriented) {
	_oriented = oriented;
}

bool GraphList::insert(int x, int y, int weight) {
	while (_adjacencyList.size() < std::max(x, y) + 1) {
		_adjacencyList.push_back(std::vector<EdgeList>());
	}

	_adjacencyList[x].push_back(EdgeList{ ._y = y, ._weight = weight });
	if (_oriented == false)
		_adjacencyList[y].push_back(EdgeList{ ._y = x, ._weight = weight });

	return false;
}

std::vector<std::vector<EdgeList>> GraphList::reverse() {
	std::vector<std::vector<EdgeList>> adjacencyListReversed(_adjacencyList.size());

	for (int current = 0; current < _adjacencyList.size(); current++) {
		for (int j = 0; j < _adjacencyList[current].size(); j++) {
			int adjacementNode = _adjacencyList[current][j]._y;
			int weight = _adjacencyList[current][j]._weight;

			adjacencyListReversed[adjacementNode].push_back(EdgeList{ ._y = current, ._weight = weight });
		}
	}

	return adjacencyListReversed;
}

bool GraphList::remove(int x, int y) {
	if (_adjacencyList.size() < std::max(x, y) + 1)
		return true;

	_adjacencyList[x].erase(std::remove_if(_adjacencyList[x].begin(), _adjacencyList[x].end(), [y](EdgeList edge) { return edge._y == y; }));
	if (_oriented == false)
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

GraphMatrix::GraphMatrix(bool oriented) {
	_oriented = oriented;
}

bool GraphMatrix::insert(int x, int y, int weight) {
	if (_adjacencyMatrix.size() < std::max(x, y) + 1) {
		_adjacencyMatrix.resize(std::max(x, y) + 1);
		for (int i = 0; i < _adjacencyMatrix.size(); i++) {
			_adjacencyMatrix[i].resize(std::max(x, y) + 1);
		}
	}

	if (_adjacencyMatrix[x][y].has_value() == false)
		_adjacencyMatrix[x][y] = EdgeMatrix();
	_adjacencyMatrix[x][y].value()._weight = weight;
	
	if (_oriented == false) {
		if (_adjacencyMatrix[y][x].has_value() == false)
			_adjacencyMatrix[y][x] = EdgeMatrix();
		_adjacencyMatrix[y][x].value()._weight = weight;
	}

	return false;
}

bool GraphMatrix::remove(int x, int y) {
	if (_adjacencyMatrix.size() < std::max(x, y) + 1) {
		return true;
	}

	_adjacencyMatrix[x][y] = std::nullopt;
	if (_oriented == false)
		_adjacencyMatrix[y][x] = std::nullopt;

	return false;
}

std::vector<std::vector<std::optional<EdgeMatrix>>> GraphMatrix::getAdjacencyMatrix() {
	return _adjacencyMatrix;
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

BFS::BFS(GraphList& graph) {
	_adjacencyList = graph.getAdjacencyList();
}

BFS::BFS(std::shared_ptr<GraphList> graph) {
	_adjacencyList = graph->getAdjacencyList();
}

std::vector<int> BFS::colorGraph() {
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

std::vector<int> BFS::getConnectedNumber() {
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
std::vector<int> BFS::breadthFirstSearch(int start) {
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

DFS::DFS(std::shared_ptr<GraphList> graph) {
	_adjacencyList = graph->getAdjacencyList();
	_adjacencyListReversed = graph->reverse();
	_parent.resize(_adjacencyList.size());
}

DFS::DFS(GraphList& graph) {
	_adjacencyList = graph.getAdjacencyList();
	_adjacencyListReversed = graph.reverse();

	_parent.resize(_adjacencyList.size(), -1);
}

std::vector<int> DFS::getArticulationPoints() {
	return _articulationPoints;
}

bool DFS::_depthFirstTraversalRecursive(int currentNode, std::map<int, bool>& visitedNodes, std::vector<int>& traversal) {
	for (int i = 0; i < _adjacencyList[currentNode].size(); i++) {
		int adjacentNode = _adjacencyList[currentNode][i]._y;
		if (visitedNodes[adjacentNode] == false) {
			visitedNodes[adjacentNode] = true;
			_children[currentNode].push_back(adjacentNode);

			_edgesType["tree"].push_back({ currentNode, adjacentNode });
			_parent[adjacentNode] = currentNode;
			_timeStart[adjacentNode] = _timeIterator;
			_low[adjacentNode] = _timeIterator;
			_timeIterator++;
			traversal.push_back(adjacentNode);
			_depthFirstTraversalRecursive(adjacentNode, visitedNodes, traversal);

			//analyze if node is atricular node
			_low[currentNode] = std::min(_low[currentNode], _low[adjacentNode]);
			//case 1: node is root and has more than 1 children
			if (_parent[currentNode] == -1 && _children[currentNode].size() > 1) {
				_articulationPoints.push_back(currentNode);
			}

			//case 2: for current node there is ONE adjacent node with low value greater than in current node
			//so that's mean there is one subtree without back edge to current's ascendant node
			if (_parent[currentNode] != -1 && _low[adjacentNode] >= _timeStart[currentNode]) {
				_articulationPoints.push_back(currentNode);
			}
		}
		else {
			//node isn't closed and parent of adjacent node != current node then back edge
			if (_timeEnd.find(adjacentNode) == _timeEnd.end() && 
				_parent[currentNode] != adjacentNode) {
				_edgesType["back"].push_back({ currentNode, adjacentNode });
				//Graph contains cycle so it's not directed acycled graph
				_DAG = false;
			}
			//adjacent node is closed
			else if (_timeEnd.find(adjacentNode) != _timeEnd.end() &&
					 _timeStart[currentNode] < _timeStart[adjacentNode]) {
				_edgesType["forward"].push_back({ currentNode, adjacentNode });
			}
			else if (_timeEnd.find(adjacentNode) != _timeEnd.end() &&
					 _timeStart[currentNode] > _timeStart[adjacentNode]) {
				_edgesType["cross"].push_back({ currentNode, adjacentNode });
			}

			if (_parent[currentNode] != adjacentNode) {
				//if node has been already visited but we have edge it can be back node so update low
				_low[currentNode] = std::min(_low[currentNode], _timeStart[adjacentNode]);
			}
		}
	}
	_timeEnd[currentNode] = _timeIterator;
	_topologicalSorted.insert(_topologicalSorted.begin(), currentNode);
	_timeIterator++;

	return false;
}

std::map<std::string, std::vector<std::tuple<int, int>>> DFS::getEdgesType() {
	return _edgesType;
}

std::vector<int> DFS::depthFirstTraversal(int start) {
	std::map<int, bool> visitedNodes;
	std::vector<int> traversal;
	_timeIterator = 0;
	for (int i = start; i < _adjacencyList.size() + start; i++) {
		int index = i % _adjacencyList.size();
		if (visitedNodes[index] == false) {
			visitedNodes[index] = true;
			_timeStart[index] = _timeIterator;
			_low[index] = _timeIterator;
			_timeIterator++;
			traversal.push_back(index);
			_depthFirstTraversalRecursive(index, visitedNodes, traversal);
		}
	}
	return traversal;
}

std::vector<int> DFS::getTopologicalSorted() {
	if (_DAG)
		return _topologicalSorted;

	return std::vector<int>();
}


bool _getStronglyConnectedEdgesRecursion(int currentNode, std::vector<std::vector<EdgeList>> adjacencyList, std::map<int, bool>& visited, std::vector<int>& traversal) {
	for (auto adjacement : adjacencyList[currentNode]) {
		int adjacementNode = adjacement._y;
		if (visited[adjacementNode] == false) {
			visited[adjacementNode] = true;
			_getStronglyConnectedEdgesRecursion(adjacementNode, adjacencyList, visited, traversal);
		}
	}

	traversal.insert(traversal.begin(), currentNode);
	return false;
}

std::vector<std::vector<int>> DFS::getStronglyConnectedComponents() {
	//1. Do DFS to get something like topological sorting
	std::map<int, bool> visited;
	std::vector<int> traversal;

	for (int i = 0; i < _adjacencyList.size(); i++) {
		if (visited[i] == false) {
			visited[i] = true;
			_getStronglyConnectedEdgesRecursion(i, _adjacencyList, visited, traversal);
		}
	}

	//2. Reverse graph
	//_adjacencyListReversed

	//3. Execute DFS with cleared visited
	visited.clear();
	std::vector<int> connectedComponent;
	std::vector<std::vector<int>> _stronglyConnectedComponents;
	for (auto node : traversal) {
		if (visited[node] == false) {
			visited[node] = true;
			_getStronglyConnectedEdgesRecursion(node, _adjacencyListReversed, visited, connectedComponent);

			_stronglyConnectedComponents.push_back(connectedComponent);
			connectedComponent.clear();
		}
	}

	return _stronglyConnectedComponents;
}

MinimumSpanningTree::MinimumSpanningTree(GraphList& graph) {
	_adjacencyList = graph.getAdjacencyList();
}
std::vector<std::tuple<int, int, int>> MinimumSpanningTree::prim() {
	std::vector<int> spanningTree;
	//signaling if element in spanningTree, to avoid traversing vector
	std::map<int, bool> visited;

	std::map<int, int> parent;
	std::map<int, int> keyTree;
	for (int i = 0; i < _adjacencyList.size(); i++)
		keyTree[i] = INT_MAX;

	//choose first element
	int current = 0;
	keyTree[current] = 0;
	for (int i = 0; i < _adjacencyList.size(); i++) {
		//find node in keyTree with minimum weight
		int minNodeValue = INT_MAX;
		int minNode = -1;
		for (auto [node, _] : keyTree) {
			if (visited[node] == false) {
				if (keyTree[node] < minNodeValue) {
					minNode = node;
					minNodeValue = keyTree[node];
				}
			}
		}

		visited[minNode] = true;
		//insert key with minimum weight to tree
		spanningTree.push_back(minNode);

		//update weights for newly added minNode
		for (int i = 0; i < _adjacencyList[minNode].size(); i++) {
			EdgeList adjacentNode = _adjacencyList[minNode][i];
			if (visited[adjacentNode._y] == false && adjacentNode._weight < keyTree[adjacentNode._y]) {
				keyTree[adjacentNode._y] = adjacentNode._weight;
				parent[adjacentNode._y] = minNode;
			}
		}
	}

	std::vector<std::tuple<int, int, int>> result;
	//don't need to determine parent for first node because it's just random first node
	for (int i = 1; i < spanningTree.size(); i++) {
		result.push_back({ parent[spanningTree[i]], spanningTree[i], keyTree[spanningTree[i]] });
	}
	return result;
}

std::vector<std::tuple<int, int, int>> MinimumSpanningTree::kruskal() {
	//form vector of trees from vertexes
	std::map<int, int> tree;
	//place every vertex to it's own subtree
	for (int i = 0; i < _adjacencyList.size(); i++) {
		tree[i] = i;
	}

	//Can be improved to ElogE instead of E*E
	std::vector<std::tuple<int, int, int>> sortedEdges;
	//use insertion sort algo
	for (int i = 0; i < _adjacencyList.size(); i++)
		for (int j = 0; j < _adjacencyList[i].size(); j++) {
			int weight = _adjacencyList[i][j]._weight;
			int position = 0;
			for (int k = 0; k < sortedEdges.size(); k++) {
				//find position
				if (weight < std::get<2>(sortedEdges[k])) {
					break;
				}

				position++;
			}
			sortedEdges.insert(sortedEdges.begin() + position, { i, _adjacencyList[i][j]._y, weight });
		}

	//take minimum edges and add them to result if they don't form loop
	std::vector<std::tuple<int, int, int>> spanningTree;
	for (int i = 0; i < sortedEdges.size(); i++) {
		int first = std::get<0>(sortedEdges[i]);
		int second = std::get<1>(sortedEdges[i]);
		if (tree[first] != tree[second]) {
			spanningTree.push_back(sortedEdges[i]);
			//changed connected component for nodes
			int changedValue = tree[second];
			int targetValue = tree[first];
			for (int k = 0; k < tree.size(); k++) {
				if (tree[k] == changedValue)
					tree[k] = targetValue;
			}
		}
	}

	return spanningTree;
}

ShortestPath::ShortestPath(GraphList& graph) {
	_adjacencyList = graph.getAdjacencyList();
}

std::map<int, int> ShortestPath::dijkstra(int start) {
	//handled vertexes
	std::vector<int> shortestPath;
	std::map<int, bool> visited;
	//weight of path from start vertex till current vertex
	std::map<int, int> key;
	for (int i = 0; i < _adjacencyList.size(); i++) {
		key[i] = INT_MAX;
	}

	key[start] = 0;
	for (int i = 0; i < _adjacencyList.size(); i++) {
		//first find the smallest node in key
		int minWeight = INT_MAX;
		int minNode = 0;
		for (auto [node, weight] : key) {
			if (visited[node] == false && weight < minWeight) {
				minWeight = weight;
				minNode = node;
			}
		}

		//add smallest node to shortest path
		shortestPath.push_back(minNode);
		visited[minNode] = true;

		//update weights in key for newly added vertex (smallest node)
		for (int i = 0; i < _adjacencyList[minNode].size(); i++) {
			int firstNode = minNode;
			auto secondNode = _adjacencyList[minNode][i];
			//update key if new route is less than current one
			if (visited[secondNode._y] == false && key[firstNode] + secondNode._weight < key[secondNode._y]) {
				key[secondNode._y] = key[firstNode] + secondNode._weight;
			}
		}
	}

	return key;
}

ShortestPath::ShortestPath(GraphMatrix& graph) {
	_adjacencyMatrix = graph.getAdjacencyMatrix();
}

std::vector<std::vector<int>> ShortestPath::floydWarshall() {
	std::vector<std::vector<int>> result(_adjacencyMatrix.size());
	for (int i = 0; i < _adjacencyMatrix.size(); i++)
		result[i] = std::vector<int>(_adjacencyMatrix.size(), INT_MAX);

	//first of all place adjacencyMatrix to result, it contains first-order relationships between nodes (so node-node relationship)
	for (int i = 0; i < _adjacencyMatrix.size(); i++) {
		for (int j = 0; j < _adjacencyMatrix.size(); j++) {
			// self-loop or a buckle
			if (i == j)
				result[i][j] = 0;
			auto value = _adjacencyMatrix[i][j];
			if (value.has_value())
				result[i][j] = value.value()._weight;
		}
	}

	//next we need to insert k node to any i-j path and check if i-k + j-k have less weight than i-j
	for (int k = 0; k < _adjacencyMatrix.size(); k++) {
		for (int i = 0; i < _adjacencyMatrix.size(); i++) {
			for (int j = 0; j < _adjacencyMatrix.size(); j++) {
				//check for INT_MAX to avoid INT_MAX + INT_MAX
				if (result[i][k] < INT_MAX && result[k][j] < INT_MAX && result[i][k] + result[k][j] < result[i][j]) {
					result[i][j] = result[i][k] + result[k][j];
				}
			}
		}
	}

	return result;
}

MaximumFlow::MaximumFlow(GraphMatrix& graph) {
	_adjacencyMatrix = graph.getAdjacencyMatrix();
}

int MaximumFlow::edmondsKarp(int source, int sink) {
	//first of all execute BFS to find shortest augmented path
	int result = 0;
	std::map<int, int> parent; //array to recover shortest path after BFS
	std::map<int, bool> visited;
	std::vector<int> bfs;
	do {
		parent.clear();
		visited.clear();

		bfs.push_back(source);
		visited[source] = true;
		parent[source] = -1;

		while (bfs.size() > 0) {
			int current = bfs[0];
			bfs.erase(bfs.begin());
			for (int i = 0; i < _adjacencyMatrix[current].size(); i++) {
				//ignore paths with 0 capacity
				if (visited[i] == false && _adjacencyMatrix[current][i].has_value() && _adjacencyMatrix[current][i].value()._weight > 0) {
					visited[i] = true;

					parent[i] = current;
					bfs.push_back(i);
				}
			}
		}

		//if no path found to sink vertex means no more capacity
		if (parent.find(sink) != parent.end()) {
			//find minimum capacity
			int current = sink;
			int minimumCapacity = INT_MAX;
			while (current != source) {
				int currentCapacity = _adjacencyMatrix[parent[current]][current].value()._weight;
				if (currentCapacity < minimumCapacity)
					minimumCapacity = currentCapacity;

				current = parent[current];
			}

			//decrease capacity of all nodes in path by minimum capacity and add to result
			result += minimumCapacity;
			current = sink;
			while (current != source) {
				_adjacencyMatrix[parent[current]][current].value()._weight -= minimumCapacity;
				if (_adjacencyMatrix[current][parent[current]].has_value() == false)
					_adjacencyMatrix[current][parent[current]] = EdgeMatrix(0);
				_adjacencyMatrix[current][parent[current]].value()._weight += minimumCapacity;
				
				current = parent[current];
			}
		}
	} while (parent.find(sink) != parent.end());

	return result;
}