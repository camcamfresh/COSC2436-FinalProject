#include "graph.h"
#include "main.h" //debug print statments

Graph::Graph(int vertices, void * matrix){
	//Cast matrix to a 2D array pointer to the pointer pMatrix.
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
	for(int i = 0; i < vertices; i++){
		for(int j = 0; j < vertices; j++){
			std::cout << this->matrix[i][j] << " ";
		}
		std::cout << std::endl;
	}

}

Graph::~Graph(){
	
}


