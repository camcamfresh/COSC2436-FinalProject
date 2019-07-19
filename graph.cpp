#include "graph.h"
#include "main.h"

Graph::Graph(int vertices, int ** matrix){
	this->vertices = vertices;
	
	this->matrix = new int * [vertices];
	for(int i = 0; i < vertices; i++){
		this->matrix[i] = new int[vertices];
	}
	
	for(int i = 0; i < vertices; i++){
		for(int j = 0; j < vertices; j++){
			std::cout << this->matrix[i][j] << " ";
		} std::cout << std::endl;
	}
}

Graph::~Graph(){
	
}


