#pragma once
#include "order.h"

//dynamic queue template


class Queue {
protected:
	struct queueNode{
		Order* p;
		queueNode* next;
	};
	queueNode* bidFront;
	queueNode* bidRear;
	queueNode* askFront;
	queueNode* askRear;
	int size;

public:
	Queue();
	virtual ~Queue();
	void enqueue(Order*);
	void dequeue(Order&);
	bool isEmpty() const;
	bool isFull() const;
	void clearQ();
};

// inheritance ask/bid book

class OrderBook : public Queue {
public:
	void grabdata(); 
	void display(Order, Order); // when a deal is matched, display it on screan
	
	// int stores actions: 1 bid, -1 ask
	void matchMarket(Order*, int); 
	void matchLimited(Order*, int); 

};


