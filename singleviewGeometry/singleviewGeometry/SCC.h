#pragma once
// A C++ program to find strongly connected components in a given
// directed graph using Tarjan's algorithm (single DFS)
#include<iostream>
#include <list>
#include <stack>
#include <algorithm>
#include "Line.h"
#define NIL -1
using namespace std;

// A class that represents an directed graph
class Graph
{
	int V;    // No. of vertices
	list<int> *adj;    // A dynamic array of adjacency lists

					   // A Recursive DFS based function used by SCC()
	void SCCUtil(int u, int disc[], int low[],
		stack<int> *st, bool stackMember[], vector<Line> line_array, vector<Line> *merged_line_array);
public:
	Graph(int V);   // Constructor
	void addEdge(int v, int w);   // function to add an edge to graph
	vector<Line> SCC(vector<Line> line_array);    // prints strongly connected components
	~Graph() {}
};
