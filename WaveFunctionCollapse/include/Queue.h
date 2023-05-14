#pragma once

// yummy queue :P

template <typename T>
class Queue
{
	struct node
	{
		node* link;
		T* data;
	};

private:
	node* front;
	int size;

public:
	Queue()
	{
		front = nullptr;
		size = 0;
	}

	void push(T* item)
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

	T* top()
	{
		if (!front) return nullptr;
		return front->data;
	}

	void pop()
	{
		if (front)
		{
			front = front->link;
			size--;
		}
	}

	int getSize() { return size; }
};