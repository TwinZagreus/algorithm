#pragma once

#include "queue.h"
#include "../myExceptions.h"
#include <sstream>

using namespace std;


template<typename T>
class arrayQueue : public queue<T>
{
public:
	arrayQueue(int initialCapacity = 10);
	~arrayQueue() { delete[] queue; }
    bool empty() const { return theFront == theBack; }
    int size() const
    {
        return (theBack - theFront + arrayLength) % arrayLength;
    }
    T& front()
    {// return front element
        if (theFront == theBack)
            throw queueEmpty();
        return queue[(theFront + 1) % arrayLength];
    }
    T& back()
    {// return theBack element
        if (theFront == theBack)
            throw queueEmpty();
        return queue[theBack];
    }
    void pop()
    {// remove theFront element
        if (theFront == theBack)
            throw queueEmpty();
        theFront = (theFront + 1) % arrayLength;
        queue[theFront].~T();  // destructor for T
    }
    void push(const T& theElement);
private:
	int theFront;
	int theBack;
	int arrayLength;
	T* queue;
};

template<typename T>
inline arrayQueue<T>::arrayQueue(int initialCapacity)
{
    if (initialCapacity <1) {
        ostringstream s;
        s << "Initial capacity = " << initialCapacity << " Must be > 0";
        throw illegalParameterValue(s.str());
    }
    arrayLength = initialCapacity;
    queue = new T[arrayLength];
    theFront = 0;
    theBack = 0;
}

template<typename T>
inline void arrayQueue<T>::push(const T& theElement)
{
    if ((theBack+1)%arrayLength==theFront) {
        T* newQueue = new T[2 * arrayLength];

        int start = (theFront + 1) % arrayLength;
        //判断原队列是否循环换行
        if (start <2 ) {
            copy(queue + start, queue + start + arrayLength - 1, newQueue);
        }
        else {
            copy(queue + start, queue + arrayLength, newQueue);
            copy(queue, queue + theBack + 1, newQueue + arrayLength - start);
        }
        //重新设置开始和结束指针
        theFront = 2 * arrayLength - 1;
        theBack = arrayLength - 2;
        arrayLength *= 2;
        delete[] queue;
        queue = newQueue;
    }
    theBack = (theBack + 1) % arrayLength;
    queue[theBack] = theElement;
}
