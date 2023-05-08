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

public:
	Queue()
	{
		front = nullptr;
	}

	void push(T* item);
	T* top();
	void pop();
};