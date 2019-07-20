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
	std::cout << getVertices() << std::endl;
	std::cout << getEdges() << std::endl;

}

Graph::~Graph(){
	
}

int Graph::getVertices(){
	return vertices;
}

int Graph::getEdges(){
	int edgeCount = 0, transpose[vertices][vertices];
	bool symetric = true;
	
	for(int i = 0; i < vertices; i++){
		for(int j = 0; j < vertices; j++){
			transpose[j][i] = matrix[i][j];
			if(matrix[i][j] >= 0) edgeCount++;
			if(transpose[j][i] != matrix[j][i]) symetric = false;
		}
	}

	return symetric ? (edgeCount - vertices) / 2 : edgeCount;
}

void Graph::bfs(int vertex){ //input position of vertex wanted starting from 1.
	std::queue<int> queue;
	bool visited[vertices];
	for(int i = 0; i < vertices; i++) visited[i] = false;
	
	queue.push(vertex - 1);
	visited[vertex - 1] = true;
	
	while(!queue.empty()){
		vertex = queue.front();
		outputAlpha ? std::cout << "Vertex " << (char)(vertex + 'a') << std::endl:
		std::cout << "Vertex " << vertex + 1 << std::endl;
		queue.pop();
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

//bool addVertex(


