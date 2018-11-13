#ifndef ORDERBOOK_H
#define ORDERBOOK_H

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
	int aSize, bSize;
	
	

public:
	Queue();
	~Queue();
	void insertAskBook(Order*);
	void insertBidBook(Order*);
	void deleteOrder(queueNode*); //overloaded deleteOrder functions. looks through q
	void deleteOrder(int); // int indicates book type
	void display(); //used for debugging
    
};

// inheritance ask/bid book

class OrderBook : public Queue {
public:
	void grabdata(); 
	void display(Order*, Order*); // when a deal is matched, display it on screan
	void inbalance(Order*);
	void matchMarket(Order*); 
	void matchLimited(Order*); 
	void inbanlance();

};

#endif

