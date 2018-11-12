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
	void insert(T*);
	void delate(T &);
	bool isEmpty() const;
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
	
	//int stores two actions: 1 bid(buy), -1 ask(sell)
	void matchMarket(order*, int); //for market orders 
	void matchLimited(order*, int); //dor limited orders


};


