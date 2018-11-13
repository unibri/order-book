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
	void insertAskBook(queueNode*);
	void insertBidBook(queueNode*);
	void deleteOrder(int); // int indicates book type
	bool isEmpty(int ) const;
	void clearQ();
    
};

// inheritance ask/bid book

class OrderBook : public Queue {
public:
	void grabdata(); 
	void display(Order*, Order*); // when a deal is matched, display it on screan
	void inbalance(Order*);

	// int stores actions: 1 bid, -1 ask
	void matchMarket(Order*); 
	void matchLimited(Order*); 

	void inbanlance();
	

};

#endif

