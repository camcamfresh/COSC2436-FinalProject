#include "graph.h"

Graph::Graph(int vertices, void * matrix, bool alpha){
	//Cast matrix of a square 2D int array to the pointer pMatrix.
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
}

Graph::~Graph(){
	//Delete allocated memory.
	for(int i = 0; i < vertices; i++)
		delete matrix[i];
	delete matrix;
	
	//Remove previously set values (not really needed).
	matrix = NULL;
	vertices = 0;
	outputAlpha = false;
}

int Graph::getVertices(){
	return vertices;
}

int Graph::getEdges(){
	int edgeCount = 0;
	//Count all the edges
	for(int i = 0; i < vertices; i++){
		for(int j = 0; j < vertices; j++){
			if(matrix[i][j] >= 0) edgeCount++;
		}
	}
	
	if(vertices && matrix[0][0] == 0 && symmetric()){
		int selfEdge = 0;
		for(int i = 0; i < vertices; i++){
			if(matrix[i][i] == 0) selfEdge++;
		}
		edgeCount = (edgeCount - selfEdge) / 2;
	}
	//error when weighted graph happens to be symmetric.
	return edgeCount;
}

bool Graph::symmetric(){
	for(int i = 0; i < vertices; i++){
		for(int j = 0; j < vertices; j++){
			//transposing matrix to determine if it is symmetric
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
	
	while(!stack.empty()){
		vertex = stack.top();
		stack.pop();
		if(visited[vertex]) continue;
		visited[vertex] = true;
		outputAlpha ? std::cout << "Vertex " << (char)(vertex + 'a') << std::endl:
		std::cout << "Vertex " << vertex + 1 << std::endl;
				
		for(int i = 0; i < vertices; i++){
			if(matrix[vertex][i] >= 0 && !visited[i]){
				stack.push(i);	
			}
		}
	}
	
	for(int j = 0; j < vertices; j++){
		if(!visited[j])
			outputAlpha ? std::cout << "missing: Vertex " << (char)(j + 'a') << std::endl:
			std::cout << "missing: Vertex " << j + 1 << std::endl;
	}
}

void Graph::printGraph(){
	for(int i = 0; i < vertices; i++){
		for(int j = 0; j < vertices; j++){
			std::cout << matrix[i][j];
			if(j != vertices - 1) std::cout << ",";
		}
		std::cout << std::endl;		
	}
}

void Graph::exportGraph(){
	std::ofstream file;
	
	//Find the next available file name in the current folder.
	int fnum = 1;
	bool fileFound = false;
	std::string name;
	while(!fileFound){
		name = "graph0" + std::to_string(fnum) + ".dat";
		if(!fileExist(name)) fileFound = true;
		else fnum++;
	}
	file.open(name);
	
	if(outputAlpha){
		file << "X,";
		for(int i = 0; i < vertices; i++){
			file << (char)(i + 'a');
			if(i != vertices - 1) file << ",";
			else file << std::endl;
		}
	}	
	for(int i = 0; i < vertices; i++){
		if(outputAlpha) file << (char)(i + 'a') << ",";
		for(int j = 0; j < vertices; j++){
			if(outputAlpha) file << matrix[i][j] + 1;
			else if(matrix[i][j] == -1) file << "x";
			else file << matrix[i][j];
			if(j != vertices - 1) file << ",";
		}
		file << std::endl;
	}
	
	file.close();
}

//input file name, returns whether it exists in the current folder.
bool Graph::fileExist(std::string name){
	std::ifstream file;
	file.open(name.c_str());
	if(!file) return false;
	file.close();
	return true;
}

void Graph::addVertex(){
	//Increment vertices and allocate a new square 2D int array.
	vertices++;
	int ** holder = new int * [vertices];
	for(int i = 0; i < vertices; i++){
		holder[i] = new int [vertices];
		for(int j = 0; j < vertices; j++){ //store previous values into holder and set new vertex to -1.
			if(i == vertices - 1) holder[i][j] = -1;
			else if(j == vertices - 1) holder[i][j] = -1;
			else holder[i][j] = matrix[i][j];
		}
		if(i != vertices - 1) delete matrix[i]; //delete old matrix rows
	}
	delete matrix;
	matrix = holder;
}

bool Graph::addEdge(int vertex1, int vertex2, int weight){
	//check to see if vertex exists, ensure weight is either -1 or 0 when it is directed unweighted graph (symmetric and alphabetical output).
	//TODO: CHECK IF SYMMETRY IS A GOOD SIGN OF WEIGHTED UNDIRECTED GRAPHS.
	if(vertex1 < 1 || vertex2 < 1 ||
	  (matrix[vertex1 - 1][vertex2 - 1] >= 0) ||
	  (matrix[0][0] != 0 && weight > 0 && !symmetric()) ||
	   vertex1 > vertices || vertex2 > vertices ||
	   weight < 0) return false;
	   
	if(matrix[0][0] == 0 && symmetric()) matrix[vertex2 - 1][vertex1 - 1] = weight;
	matrix[vertex1 - 1][vertex2 - 1] = weight;
	return true;
}

bool Graph::removeVertex(int vertex){
	//check if vertex exists.
	if(vertex < 1 || vertex > vertices) return false;
	//allocate new matrix and transfer old values to new matrix.
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
	vertex1--; vertex2--;
	//check if edge exists.
	if(matrix[vertex1][vertex2] < 0) return false;
	else{
		//if symmetric keep graph symmetric by adding corresponding edge.
		if(matrix[0][0] == 0 && symmetric()) matrix[vertex2][vertex1] = -1;
		matrix[vertex1][vertex2] = -1;
	}
	return true;
}

bool Graph::isConnected(bool listDisconnected){
	//keep track of each vertex's net.
	int net[vertices];
	for(int i = 0; i < vertices; i++) net[i] = -1;
	net[0] = 0;
	
	//search each vertex's edges and add them to the same net if the net has not been set.
	//if the previous net is smaller, then loop through nets and replace current net with the smallest one connected to it.	
	for(int i = 0; i < vertices; i++){
		if(net[i] == -1) net[i] = i;
		for(int j = 0; j < vertices; j++){
			if(matrix[i][j] > -1){
				if(net[j] == -1) net[j] = net[i];
				else if(net[j] < net[i]){
					int change = net[j];
					net[i] = net[j];
					for(int k = 0; k < vertices; k++)
						if(net[k] == change) net[k] = net[i];
				}					
			}
		}
	}
	
	//loop through each vertex's net to see if it is greater than 0
	//if listDisconnected set to true, outputs each vertex's net.
	bool result = true;
	for(int i = 0; i < vertices; i++){
		if(net[i] != 0) result = false;
		if(!listDisconnected) continue;
		if(net[i] == 0)
			outputAlpha ? std::cout << "Vertex " << (char)(i + 'a') << ": is connected to net " << (char)(net[i] + 'A') << std::endl :
			std::cout << "Vertex " << i + 1 << ": is connected to net " << (char)(net[i] + 'A') << std::endl;
		else if(net[i] == -1)
			outputAlpha ? std::cout << "Vertex " << (char)(i + 'a') << ": is disconnected. " << net[i] << std::endl:
			std::cout << "Vertex " << i + 1 << ": is disconnected. " << net[i] << std::endl;
		else
			outputAlpha ? std::cout << "Vertex " << (char)(i + 'a') << ": is connected to net " << (char)(net[i] + 'A') << std::endl:
			std::cout << "Vertex " << i + 1 << ": is connected to net " << (char)(net[i] + 'A') << std::endl;
	}
	return result;
}

void Graph::listDisconnected(){
	isConnected(true);
}




