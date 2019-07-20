#include "graph.h"
#include "main.h" //debug print statements
#include <vector>
#include <queue>
#include <stack>

Graph::Graph(int vertices, void * matrix, bool alpha){
	//Cast matrix of a 2D int array to the pointer pMatrix.
	this->vertices = vertices;
	outputAlpha = alpha;
	auto pMatrix = (int (*)[vertices][vertices]) matrix;
	//int (*pMatrix)[vertices][vertices] = (int (*)[vertices][vertices]) matrix;
	
	//Dynamically allocate memory for matrix and set each value to input.
	this->matrix = new int * [vertices];
	for(int i = 0; i < vertices; i++){
		this->matrix[i] = new int [vertices];
		for(int j = 0; j < vertices; j++){
			this->matrix[i][j] = (*pMatrix)[i][j];
		}
	}
	
	//DEBUG: print resulting table
	/*for(int i = 0; i < vertices; i++){
		for(int j = 0; j < vertices; j++){
			std::cout << this->matrix[i][j] << " ";
		}
		std::cout << std::endl;
	}*/
	
	//dfs(1);
	printTable();
	std::cout << getVertices() << std::endl;
	std::cout << getEdges() << std::endl;
	
	/*addVertex();
	printTable();
	std::cout << getVertices() << std::endl;
	std::cout << getEdges() << std::endl;
	
	//addEdge(1,4,0);
	removeVertex(1);
	printTable();
	std::cout << getVertices() << std::endl;
	std::cout << getEdges() << std::endl;
	
	addEdge(6,6,0);
	addEdge(6,3,0);
	printTable();
	std::cout << getVertices() << std::endl;
	std::cout << getEdges() << std::endl;*/
	
	std::cout << isConnected(true) << std::endl;
	
	
	//printTable();
}

Graph::~Graph(){
	
}

int Graph::getVertices(){
	return vertices;
}

int Graph::getEdges(){
	int edgeCount = 0, transpose[vertices][vertices];
	
	for(int i = 0; i < vertices; i++){
		for(int j = 0; j < vertices; j++){
			if(matrix[i][j] >= 0) edgeCount++;
		}
	}
	
	if(symmetric() && vertices){
		int selfEdge = 0;
		for(int i = 0; i < vertices; i++){
			if(matrix[i][i] == 0) selfEdge++;
		}
		edgeCount = (edgeCount - selfEdge) / 2 + selfEdge;
	}
	//error when weighted graph happens to be symmetric.
	return edgeCount;
}

bool Graph::symmetric(){
	for(int i = 0; i < vertices; i++){
		for(int j = 0; j < vertices; j++){
			if(matrix[j][i] != matrix[j][i]) return false;
		}
	}
	return true;
}

void Graph::bfs(int vertex){ //input position of vertex wanted starting from 1.
	std::queue<int> queue;
	bool visited[vertices];
	for(int i = 0; i < vertices; i++) visited[i] = false;
	
	queue.push(vertex - 1);
	visited[vertex - 1] = true;
	
	while(!queue.empty()){
		vertex = queue.front();
		queue.pop();
		outputAlpha ? std::cout << "Vertex " << (char)(vertex + 'a') << std::endl:
		std::cout << "Vertex " << vertex + 1 << std::endl;
		for(int i = 0; i < vertices; i++){
			if(matrix[vertex][i] >= 0 && !visited[i]){
				queue.push(i);
				visited[i] = true;
			}
		}
	}
	
	for(int j = 0; j < vertices; j++){
		if(!visited[j])
			outputAlpha ? std::cout << "missing: Vertex " << (char)(j + 'a') << std::endl :
			std::cout << "missing: Vertex " << j + 1 << std::endl;
	}
}

void Graph::dfs(int vertex){
	std::stack<int> stack;
	bool visited[vertices];
	for(int i = 0; i < vertices; i++) visited[i] = false;
	
	stack.push(vertex - 1);
	visited[vertex - 1] = true;
	
	while(!stack.empty()){
		vertex = stack.top();
		outputAlpha ? std::cout << "Vertex " << (char)(vertex + 'a') << std::endl:
		std::cout << "Vertex " << vertex + 1 << std::endl;
		stack.pop();
		for(int i = 0; i < vertices; i++){
			if(matrix[vertex][i] >= 0 && !visited[i]){
				stack.push(i);
				visited[i] = true;
			}
		}		
	}
	
	for(int j = 0; j < vertices; j++){
		if(!visited[j])
			outputAlpha ? std::cout << "missing: Vertex " << (char)(j + 'a') << std::endl:
			std::cout << "missing: Vertex " << j + 1 << std::endl;
	}
}

void Graph::printTable(){
	for(int i = 0; i < vertices; i++){
		for(int j = 0; j < vertices; j++){
			std::cout << matrix[i][j];
			if(j != vertices - 1) std::cout << ",";
		}
		std::cout << std::endl;		
	}
}

void Graph::addVertex(){
	vertices++;
	int ** holder = new int * [vertices];
	for(int i = 0; i < vertices; i++){
		holder[i] = new int [vertices];
		for(int j = 0; j < vertices; j++){
			if(i == vertices - 1) holder[i][j] = -1;
			else if(j == vertices - 1) holder[i][j] = -1;
			else holder[i][j] = matrix[i][j];
		}
		if(i != vertices - 1) delete matrix[i];
	}
	delete matrix;
	matrix = holder;
}

bool Graph::addEdge(int vertex1, int vertex2, int weight){
	if(vertex1 < 1 || vertex2 < 1 ||
	  (symmetric() && !outputAlpha && weight > 1) ||
	   vertex1 > vertices || vertex2 > vertices) return false;
	
	matrix[vertex1 - 1][vertex2 - 1] = weight;
	matrix[vertex2 - 1][vertex1 - 1] = weight;
	return true;
}

bool Graph::removeVertex(int vertex){
	if(vertex < 1 || vertex > vertices) return false;
	int ** holder = new int * [vertices - 1];
	for(int i = 0; i < vertices - 1; i++){
		holder[i] = new int [vertices - 1];
		for(int j = 0; j < vertices - 1; j++){
			if(i < vertex - 1 && j < vertex - 1){
				holder[i][j] = matrix[i][j];
			}
			else if(i < vertex - 1){
				holder[i][j] = matrix[i][j + 1];
			}
			else if(j < vertex - 1){
				holder[i][j] = matrix[i + 1][j];
			}
			else{
				holder[i][j] = matrix[i + 1][j + 1];
			}
		}
	}
	matrix = holder;
	vertices--;
	return true;
}

bool Graph::removeEdge(int vertex1, int vertex2){
	if(matrix[vertex1][vertex2] < 0) return false;
	else matrix[vertex1][vertex2] = -1;
	if(symmetric() && !outputAlpha) matrix[vertex2][vertex1] = -1;
	return true;
}

bool Graph::isConnected(bool listDisconnected){
	int net[vertices];
	std::queue<int> queue;
	for(int i = 0; i < vertices; i++){
		net[i] = -1;
		queue.push(i);
	}
	net[0] = 0;
	
	while(!queue.empty()){
		for(int i = 0; i < vertices; i++){
			if(matrix[queue.front()][i] != -1){
				if(net[i] == -1) net[i] = net[queue.front()];
				else if(net[queue.front()] < net[i]) net[i] = net[queue.front()];
				else{
					int change = net[queue.front()];
					for(int j = 0; j < vertices; j++)
						if(net[j] == change) net[j] = net[i];
				}
			}
		}
		queue.pop();
	}
	
	bool result = true;

	for(int i = 0; i < vertices; i++){
		if(net[i] != 0) result = false;
		if(!listDisconnected) continue;
		if(net[i] == 0)
			outputAlpha ? std::cout << "Vertex " << (char)(i + 'a') << ": is connected." << std::endl:
			std::cout << "Vertex " << i + 1 << ": is connected to net " << (char)(net[i] + 'A') << std::endl;
		else if(net[i] == -1)
			outputAlpha ? std::cout << "Vertex " << (char)(i + 'a') << ": is disconnected." << std::endl:
			std::cout << "Vertex " << i + 1 << ": is disconnected." << std::endl;
		else
			outputAlpha ? std::cout << "Vertex " << (char)(i + 'a') << ": is connected to net" << (char)(net[i] + 'A') << std::endl:
			std::cout << "Vertex " << i + 1 << ": is connected to net" << (char)(net[i] + 'A') << std::endl;
	}
	return result;
}

void Graph::listDisconnected(){
	isConnected(true);
}






