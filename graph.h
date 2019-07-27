/* Assignment: Final Project
 * Date: 7/26/2019
 * Description: This program implements a graph using a 2D int array. The program handles
 * 		weighted undirected and unweighted directed graphs the same. Disconneced edges must
 * 		be set to -1, unweighted edges to 0 and weighted edges to their respective integer
 * 		value. The manipulation methods allow graphs to be changed (e.g., weighted undirected
 * 		graph to weighted directed graph, etc.). Read graph.h for more details.
*/
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
	//input number of vertices, pointer to square 2D int array (aka the name of the array),
	//    & bool to output vertices alphabetically (true) instead of numerically (false).
	//no checks on the 2d matrix, disconnected edges are must be set to -1, unweighted edges must be set to 0 and weighted edges must be set to their respective integer weight.
	Graph(int, void *, bool); 
	~Graph();
	
	//Information & Search Methods.
	void printGraph(); //prints out object's representation of the graph.
	void exportGraph(); //exports graph to file
	
	void bfs(int);//Note: Vertices start at 1, not zero or 'a'.
	void dfs(int);
	
	int getVertices();
	int getEdges();
	
	bool isConnected(bool = false); //contains listDisconnected
	void listDisconnected(); //listDisconnected wrapper
	
	//Manipulation Methods.
	void addVertex();
	bool removeVertex(int); //Note: Vertices start at 1, not zero or 'a'.
	
	bool addEdge(int, int, int = 0); //vertexOne, vertexTwo, weight
	bool removeEdge(int, int); //vertexOne, vertexTwo
};

#endif