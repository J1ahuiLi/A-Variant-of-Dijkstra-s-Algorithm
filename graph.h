#pragma once
#ifndef GRAPH_H
#define GRAPH_H

#include <iostream>
#include <string>
#include <cstdio>
#include <cstring>
#include <fstream>
#include <sstream>
#include "minheap.h"

using namespace std;
typedef unsigned int uint;
#define INFINITY 65536


typedef struct Edge
{
	uint adjVertex;				
	double weight;              
	struct Edge* next = NULL;   
}Edge;


typedef struct Vertex
{
	uint data;
	struct Edge* next = NULL;
}Vertex;

class Graph
{
public:
	Graph(const char* grapath);
	~Graph();
public:
	int read_Inf(const char* direction);
	int insert_Graph(uint& from, uint& to, double& weight, const char* direction);				
	int addEdgeList(uint& from, uint& to, double& weight);
	void dijkstra(int start, int end, int flag);
private:
	const char* _grapath;
private:

public:
	Vertex* _vVertex;
	Node* nodes;  
	uint _vexNum;
	uint _edgNum;

};

int strtoint(const char* str);

#endif