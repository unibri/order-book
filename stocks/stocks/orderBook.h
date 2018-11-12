#pragma once

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

// inheritance ask/bid book

class orderBook 
{
private:
	queue<order> bidBook, askBook; 

public:
	void grabdata(); 
	void Disaplay(order, order); // when a deal is matched, display it on screan
	
	void matchMBid(order*); //open askBook
	void matchMAsk(order*); //open bidBook
	void matchLBid(order*);
	void matchLAsk(order*);	

};


