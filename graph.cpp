#include "graph.h"

using namespace std;

Graph::Graph(const char* grapath)
	:_grapath(grapath)
{

}
Graph::~Graph()
{
	delete[] _vVertex;
	delete[] nodes;
}
//Read file
int Graph::read_Inf(const char* direction)
{
	//Load data file
	ifstream fin;
	string line;     //Output characters per line of the cache file
	fin.open(_grapath);
	if (fin)
	{
		double dtmp = 0;
		uint pos = 0;
		//Get edge and point information
		getline(fin, line);
		istringstream str(line);

		//Initialize edge point information
		while (str >> dtmp)
		{
			if(pos == 0)
				_vexNum = uint(dtmp);
			else if(pos == 1)
				_edgNum = (uint)dtmp;
			pos++;
		}
		//Initialize adjacency list information
		_vVertex = new Vertex[_vexNum+1];
		nodes = new Node[_vexNum+1];

		uint* inf_ft = new uint[3];
		double inf_wgt = 0;

		while (getline(fin, line))
		{			
			istringstream str(line);
			int num = 0;
			pos = 0;
			while (str >> dtmp)
			{
				if (pos < 3)
					inf_ft[pos] = uint(dtmp);
				else
					inf_wgt = dtmp;
				pos++;
			}
			insert_Graph(inf_ft[1], inf_ft[2], inf_wgt, direction);
		}
		delete[] inf_ft;
	}

	return 0;
}

int Graph::insert_Graph(uint& from, uint& to, double& weight, const char* direction)
{	
	if (strcmp("directed", direction) == 0)
	{
		_vVertex[from].data = from;
		addEdgeList(from, to, weight);
	}
	else if(strcmp("undirected", direction) == 0)
	{
		_vVertex[from].data = from;
		_vVertex[to].data = to;
		addEdgeList(from, to, weight);
		addEdgeList(to, from, weight);
	}
	return 0;
}

int Graph::addEdgeList(uint& from, uint& to, double& weight)
{
	Edge* edge = new Edge();
	edge->adjVertex = to;
	edge->weight = weight;
	edge->next = NULL;

	Edge* tmp = _vVertex[from].next;

	if (!tmp)
	{
		_vVertex[from].next = edge;
	}
	else
	{
		Edge* pre = tmp;
		_vVertex[from].next = edge;
		edge->next = pre;
	}
	return 0;
}

void Graph::dijkstra(int start, int end, int flag) 
{
	for (int i = 1; i < _vexNum+1; i++) 
	{
		nodes[i].data = i;
		nodes[i].isvisited = false;
		nodes[i].isinheap = false;
		nodes[i].iscalcul = false;
		nodes[i].distance = INFINITY;
		nodes[i].previous = NULL;
	}
	nodes[start].distance = 0;

	MinHeap min_heap(_vexNum);
	min_heap.push(nodes[start], flag);	

	while (!min_heap.empty() && !nodes[end].isvisited)
	{
		//Find the closest point to start that has not been visited
		double mindis = min_heap.top().distance;
		int minvex = min_heap.top().data;

		min_heap.pop(flag, nodes[minvex].distance);
		nodes[minvex].isinheap = false;

		// The same point may be pressed multiple times
		if (nodes[minvex].isvisited)
			continue;

		// Relax all edges starting from minVertex
		nodes[minvex].isvisited = true;
		if(end > 0 && end <= _vexNum && nodes[end].isvisited)
		{
			break;
		}

		Edge* p = _vVertex[minvex].next;

		while (p)
		{
			if (!nodes[p->adjVertex].isvisited && nodes[p->adjVertex].distance > mindis + p->weight) 
			{		
				double dis_now = mindis + p->weight;
				if(flag == 1 && nodes[p->adjVertex].distance != INFINITY)
					printf("Decrease key of vertex %d, from %12.4f to %12.4f\n", p->adjVertex, nodes[p->adjVertex].distance, dis_now);

				nodes[p->adjVertex].distance = dis_now;
				nodes[p->adjVertex].previous = &nodes[minvex];
				min_heap.push(nodes[p->adjVertex], flag);
				nodes[p->adjVertex].isinheap = true;
				nodes[p->adjVertex].iscalcul = true;
			}
			p = p->next;
		}
	}
}


int strtoint(const char* str)//Convert character array to integer
{
	if (str == NULL || *str == '\0')
	{
		return 0;
	}	
	long long num = 0;
	int sign = 1;
	while (*str == ' ')//Skip if you encounter a space
	{
		str++;
	}
	if (*str == '+')//Encountered ‘+’ means it’s an integer
	{
		str++;
	}
	else if (*str == '-')//Encountered ‘-’ means negative number
	{
		str++;
		sign = -1;
	}
	while (*str != '\0')
	{
		if (*str >= '0'&&*str <= '9')
		{
			num = num * 10 + (*str - '0')*sign;
			if (num >= INFINITY)
			{
				return INFINITY;
			}
			else if (num <= -INFINITY)
			{
				return -INFINITY;
			}
		}
		else
		{
			break;
		}
		str++;
	}
	return (int)num;
}
