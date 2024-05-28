#pragma once

#include "queue.h"
#include "../chapter-6/chain.h"
#include "../myExceptions.h"
#include <sstream>

using namespace std;


template<typename T>
class linkedQueue : public queue<T> {
public:
	linkedQueue(int initialCapacity = 10) {
		queueFront = NULL;
		queueSize = 0;
	}
	~linkedQueue();
	bool empty() const {
		return queueSize == 0;
	}
	int size() const {
		return queueSize;
	}
	T& front() {
		if (queueSize == 0) {
			throw queueEmpty();
		}
		return queueFront->element;
	}
	T& back() {
		if (queueSize == 0) {
			throw queueEmpty();
		}
		return queueBack->element;
	}
	void pop();
	void push(const T & theElement);

private:
	chainNode<T>* queueFront;  // pointer to queue front
	chainNode<T>* queueBack;   // pointer to queue back
	int queueSize;             // number of elements in queue
};

template<typename T>
inline linkedQueue<T>::~linkedQueue()
{
	while (queueFront !=NULL)
	{
		chainNode<T>* nextNode = queueFront->next;
		delete queueFront;
		queueFront = nextNode;
	}
}

template<typename T>
inline void linkedQueue<T>::pop()
{
	if (queueFront ==NULL) {
		throw queueEmpty();
	}
	chainNode<T>* nextNode = queueFront->next;
	delete queueFront;
	queueFront = nextNode;
	queueSize--;
}

template<typename T>
inline void linkedQueue<T>::push(const T& theElement)
{
	chainNode<T> * newNode = new chainNode<T>(theElement,NULL);

	if (queueSize == 0) {
		queueFront = newNode;
	}
	else {
		queueBack->next = newNode;
	}
	queueBack = newNode;
	queueSize++;
}
