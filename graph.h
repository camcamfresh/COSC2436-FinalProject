#ifndef FPROJECT_GRAPH_H
#define FPROJECT_GRAPH_H

class Graph{
private:
	int ** matrix;
	int vertices;
	bool outputAlpha;
	
public:
	Graph(int, void *, bool);
	~Graph();
	int getVertices();
	int getEdges();
	void bfs(int);
	void dfs(int);
};

#endif