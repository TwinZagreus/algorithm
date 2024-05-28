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
		if (queueSize==0) {
			throw queueEmpty();
		}
		return queueFront->element;
	}


private:
	chainNode<T>* queueFront;  // pointer to queue front
	chainNode<T>* queueBack;   // pointer to queue back
	int queueSize;             // number of elements in queue
};