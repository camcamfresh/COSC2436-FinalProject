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
	Graph(int, void *, bool);
	~Graph();
	int getVertices();
	int getEdges();
	void bfs(int);
	void dfs(int);
	void printTable(); //debug, maybe turn into output to file method
	
	void addVertex();
	bool addEdge(int, int, int = 0);
	bool removeVertex(int);
	bool removeEdge(int, int);
	
	bool isConnected(bool = false);
	void listDisconnected();
};

#endif