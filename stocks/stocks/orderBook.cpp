#include <order.h>
#include <orderBook.h>

using namespace std;
//definitions for queue functions

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
void queue<T>::insert(T *info)

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
void queue<T>::delate(T &info) // not quite sure &info
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