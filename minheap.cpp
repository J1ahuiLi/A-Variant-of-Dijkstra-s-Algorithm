#include "minheap.h"
#include "graph.h"

MinHeap::MinHeap(Node data[], int len)
	:_size(0), _capacity(len)
{
	_vecdata = new Node[_capacity];
	for (int i = 0; i < len; i++)
		push(data[i], 0);
}
MinHeap::MinHeap(int capacity) 
	:_size(0), _capacity(capacity)
{
	_vecdata = new Node[_capacity];
}

MinHeap::~MinHeap()
{
	delete[] _vecdata;
}
bool MinHeap::push(Node data, int flag)
{ 
	if (full()) 
	{
		throw("The heap is full !!\n");
		return false;
	}
	else
	{
		_vecdata[_size] = data;
		if(flag == 1 && data.isinheap == false) 
		{
			printf("Insert vertex %d, key=%12.4f\n", _vecdata[_size].data,  _vecdata[_size].distance);
		}
		++_size;
		_floating(_size);
		return true;
	}
}

bool MinHeap::pop(int flag, double mindis)
{
	if (empty())
	{
		return false;
	}	
	if(flag == 1 && (mindis == 0 || _vecdata[0].distance <= mindis))
	{
		printf("Delete vertex %d, key=%12.4f\n", _vecdata[0].data,  _vecdata[0].distance);
	}
	_vecdata[0] = _vecdata[_size - 1];
	--_size;
	_sink(1);
	return true;
}

void MinHeap::_floating(int index)
{
	if (_size == 1)
		return;
	for (int i = index; i > 0; i *= 0.5)
	{
		if (_vecdata[i - 1].distance < _vecdata[int(i * 0.5 - 1)].distance)
			_swap(i - 1, i * 0.5 - 1);
		else
			break;
	}
	return;
}
void MinHeap::_swap(int i, int j)
{
	Node temp = _vecdata[i];
	_vecdata[i] = _vecdata[j];
	_vecdata[j] = temp;
	return;
}

void MinHeap::_sink(int index)
{
	int i = index;

	while (i * 2 <= _size)
	{
		if (_vecdata[i - 1].distance > _vecdata[i * 2 - 1].distance)
		{
			_swap(i - 1, i * 2 - 1);
			if (i * 2 + 1 <= _size && _vecdata[i - 1].distance > _vecdata[i * 2].distance)
				_swap(i - 1, i * 2);
			i = i * 2;
		}
		else if (i * 2 + 1 <= _size && _vecdata[i - 1].distance > _vecdata[i * 2].distance)
		{
			_swap(i - 1, i * 2);
			i = i * 2 + 1;
		}
		else
			break;
	}

}
void MinHeap::print() {
	for (int i = 0; i < _size; i++)
		std::cout << _vecdata[i].data << " ";
	std::cout << endl;
	return;
}

Node MinHeap::top() {
	return _vecdata[0];
}

bool MinHeap::full()
{
	if (_size >= _capacity)
	{
		return true;
	}
	return false;
}
bool MinHeap::empty()
{
	return _size == 0;
}