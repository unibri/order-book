#include "order.h"

//dynamic queue template

template <class T>
class Queue {
private:
	struct queueNode{
		T* p;
		queueNode* next;
	};
	queueNode* front;
	queueNode* rear;
	int size;

public:
	Queue();
	~Queue();
	void enqueue(T*);
	void dequeue(T &);
	bool isEmpty() const;
	bool isFull() const;
	void clearQ();
};

// inheritance ask/bid book

class OrderBook {
private:
	Queue<Order> bidBook, askBook; 
public:
	void grabdata(); 
	void Disaplay(Order, Order); // when a deal is matched, display it on screan
	
	void matchMBid(Order*); //open askBook
	void matchMAsk(Order*); //open bidBook
	void matchLBid(Order*);
	void matchLAsk(Order*);	

};


