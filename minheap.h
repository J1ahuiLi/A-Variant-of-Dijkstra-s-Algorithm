#pragma once
#ifndef MINHEAP_H
#define MINHEAP_H

#include <iostream>
using namespace std;


struct Node {
	int data;
	double distance;  
	Node* previous;
	bool isvisited;
	bool isinheap;
	bool iscalcul;
	bool operator< (const Node& a) const {
		return distance > a.distance;
	}
};

class MinHeap
{
private:
	Node* _vecdata;   
	int _size;		
	int _capacity;
public:
	MinHeap(Node data[], int len);
	MinHeap(int capacity);
	virtual ~MinHeap();
public:
	Node top();
	bool pop(int flag, double mindis);
	bool push(Node data, int flag);

	void print();
	bool full();
	bool empty();

private:
	void _swap(int i, int j);
	void _sink(int index);
	void _floating(int index);
};



#endif