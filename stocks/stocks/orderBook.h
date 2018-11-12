#pragma once
//hello
//this is annoying
#ifndef ORDERBOOK_H
#define ORDERBOOK_H

#include<string>
#include <order.h>

using namespace std;

//dynamic queue template

template <class T>
class queue 
{
private:
	struct queueNode
	{
		T* p;
		queueNode* next;
	};
	queueNode* front;
	queueNode* rear;
	int size;

public:
	queue();
	~queue();
	void enqueue(T*);
	void dequeue(T &);
	bool isEmpty() const;
	bool isFull() const;
	void clear();
};

template <class T>
queue<T>::queue()
{
	front = nullptr;
	rear = nullptr;
	size = 0;
}

template <class T>
queue<T>::~queue()
{
	clear();
}

template <class T>
void queue<T>::enqueue(T *info)
{
	queueNode *newNode = nullptr;

	newNode = new queueNode;
	newNode->p = info;
	newNode->next = nullptr;

	if (isEmpty())
	{
		front = newNode;
		rear = newNode;
	}
	else
	{
		rear->next = newNode;
		rear = newNode;
	}
	size++;
}

template <class T>
void queue<T>::dequeue(T &info) // not quite sure &info
{
	queueNode *temp = nullptr;
	if (!isEmpty())
	{
		info = front->value;
		temp = front;
		front = front->next;
		delete temp;
		size--;
	}
}

template <class T>
bool queue<T>::isEmpty() const
{
	bool status;
	if (size > 0) status = false;
	else status = true;
	return status;
}

template <class T>
void queue<T>::clear()    // not quite sure p or *p
{
	T p;
	while (!isEmpty()) dequeue(p);
}

// inheritance ask/bid book

class orderBook 
{
private:
	queue<order> bidBook, askBook; 

public:
	void grabdata(); 
	void Disaplay(order, order); // when a deal is matched, display it on screan
	
	void matchMarket(order*,int); 
	void matchLimit(order*,int);

};


#endif