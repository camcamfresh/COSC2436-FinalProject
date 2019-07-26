#ifndef FPROJECT_GRAPH_H
#define FPROJECT_GRAPH_H

#include <fstream>
#include <iostream>
#include <queue>
#include <stack>

class Graph{
private:
	int ** matrix;
	int vertices;
	bool outputAlpha;
	
	bool symmetric();
	bool fileExist(std::string);
public:
	//input number of vertices, pointer to square 2D int array, & bool to output vertices alphabetically (true) instead of numerically (false).
	//no checks on the 2d matrix, disconnected edges are must be set to -1, unweighted edges must be set to 0 and weighted edges must be set to their respective integer weight.
	Graph(int, void *, bool); 
	~Graph();
	
	//Information & Search Methods.
	void printGraph(); //prints out object's representation of the graph.
	void exportGraph();
	
	void bfs(int);
	void dfs(int);
	
	int getVertices();
	int getEdges();
	
	//Manipulation Methods.
	void addVertex();
	bool removeVertex(int); //must input vertex as integer starting at one.
	
	bool addEdge(int, int, int = 0); //vertexOne, vertexTwo, weight
	bool removeEdge(int, int); //vertexOne, vertexTwo
	
	bool isConnected(bool = false); //listDisconnected
	void listDisconnected(); //listDisconnected wrapper
};

#endif