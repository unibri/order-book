#include "orderBook.h"

//definitions for queue functions
/*template <class T>
Queue<T>::Queue(){
	front = nullptr;
	rear = nullptr;
	size = 0;
}

template <class T>
Queue<T>::~Queue(){
	clear();
}

template <class T>
void Queue<T>::enqueue(T *info){
	queueNode *newNode = nullptr;

	newNode = new queueNode;
	newNode->p = info;
	newNode->next = nullptr;

	if (isEmpty()){
		front = newNode;
		rear = newNode;
	}
	else {
		rear->next = newNode;
		rear = newNode;
	}
	size++;
}

template <class T>
void Queue<T>::dequeue(T &info){// not quite sure &info
	queueNode *temp = nullptr;
	if (!isEmpty()){
		info = front->value;
		temp = front;
		front = front->next;
		delete temp;
		size--;
	}
}

template <class T>
bool Queue<T>::isEmpty() const{
	bool status;
	if (size > 0) status = false;
	else status = true;
	return status;
}

template <class T>
void Queue<T>::clearQ(){    // not quite sure p or *p
	T p;
	while (!isEmpty()) dequeue(p);
}