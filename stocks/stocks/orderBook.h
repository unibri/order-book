#pragma once
#include "order.h"

//dynamic queue template


class Queue {
protected:
	struct queueNode{
		Order* p;
		queueNode* next;
	};
	queueNode* front;
	queueNode* rear;
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
	void matchMBid(Order*); //open askBook
	void matchMAsk(Order*); //open bidBook
	void matchLBid(Order*);
	void matchLAsk(Order*);	

};


