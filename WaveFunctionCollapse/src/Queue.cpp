#include "../include/PPM.h"
#include "../include/Queue.h"

// Queue class function implementation goes brrrrrrrrrrrr

template <typename T> void Queue<T>::push(T* item)
{
	node* tmp = new node();
	tmp->data = item;
	tmp->link = nullptr;

	node* p = front;

	// queue is empty
	if (!p)
	{
		front = tmp;
		size++;
		return;
	}
	//iterate thru queue until end
	while (p->link)
	{
		p = p->link;
	}
	p->link = tmp;
	size++;
}

template <typename T> T* Queue<T>::top()
{
	if (!front) return nullptr;
	return front->data;
}

template <typename T> void Queue<T>::pop()
{
	if (front)
	{
		front = front->link;
		size--;
	}
}

int size() { return size; }