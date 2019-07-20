#ifndef FPROJECT_GRAPH_H
#define FPROJECT_GRAPH_H

class Graph{
private:
	int ** matrix;
	int vertices;
public:
	Graph(int, void *);
	~Graph();
};

#endif