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

	void push(T* item);
	T* top();
	void pop();
	int size();
};