#pragma once
#include "../chapter-5/linearList.h"
#include <iostream>
#include <sstream>		//including the ostringstream 
#include <string>
#include <stdexcept>


template<typename T>
struct chainNode
{
	T element;
	chainNode<T>* next;

	//ADT
	chainNode() {}
	chainNode(const T& element)
	{
		this->element = element;
	}
	chainNode(const T& element, chainNode<T>* next)
	{
		this->element = element;
		this->next = next;
	}
};


template<typename  T>
class chain :
    public linearList<T>
{
public:
    chain(int initialCapacity=0);
    chain(const chain <T> &);
    ~chain();

	//ADT
	bool empty() const { return listSize == 0; }
	int size() const { return listSize; }
	T& get(int theIndex) const;
	int indexOf(const T& theElement) const;

	void erase(int theIndex);
	void insert(int theIndex, const T& theElement);
	void output() const;

	template <typename U>
	friend std::ostream& operator<<(std::ostream& out, const chain<U>& x);

	// additional methods
	void binSort(int range);
	void binSort(int range, int(*value)(T& x));

	class iterator;
	iterator begin() { return iterator(firstNode); }
	iterator end() { 
		checkIndex(listSize);
		int i = 0;
		chainNode<T>* getNode = firstNode;
		while (i < listSize)
		{
			getNode = getNode->next;
			i++;
		}
		return iterator(getNode);
	}
	// iterator for chain
	class iterator
	{
	public:
		// typedefs required by C++ for a bidirectional iterator
		//typedef bidirectional_iterator_tag iterator_category;
		//typedef T value_type;
		//typedef ptrdiff_t difference_type;
		//typedef T* pointer;
		//typedef T& reference;

		// constructor
		iterator(chainNode<T> * theNode = NULL) { 
			position = theNode;
		}

		// dereferencing operators
		T& operator*() const { return position->element; }
		T* operator->() const { return &position->element; }

		// increment
		iterator& operator++()   // preincrement
		{
			position=position->next; return *this;
		}
		iterator operator++(int) // postincrement
		{
			iterator old = *this;
			position = position->next; 
			return old;
		}

		// equality testing
		bool operator!=(const iterator right) const
		{
			return position != right.position;
		}
		bool operator==(const iterator right) const
		{
			return position == right.position;
		}
	protected:
		chainNode<T>* position;
	};  // end of iterator class

protected:
	void checkIndex(int& theIndex) const;
	chainNode<T>* firstNode;
	int listSize;
};

template<typename T>
inline chain<T>::chain(int initialCapacity)
{
	if (initialCapacity < 1)
	{
		std::ostringstream s;
		s << "Initial capacity = " << initialCapacity << "Must be > 0";
		throw std::runtime_error(s.str());
	}
	firstNode = NULL;
	listSize = 0;
}

template<typename T>
inline chain<T>::chain(const chain<T>& theList)
{
	listSize = theList.listSize;
	if (0 == listSize) {
		firstNode = NULL;
		return;
	}

	chainNode<T>* sourceNode = theList.firstNode;
	firstNode = new chainNode<T>(sourceNode->element);

	sourceNode = sourceNode->next;
	chainNode<T>* targetNode = firstNode;

	while (sourceNode!=NULL) {
		targetNode->next = new chainNode<T>(sourceNode->element);
		targetNode = targetNode->next;
		sourceNode = sourceNode->next;
	}
	targetNode->next = NULL;
}

template<typename T>
inline chain<T>::~chain()
{
	while (firstNode!=NULL)
	{
		chainNode<T>* nextNode = firstNode->next;
		delete firstNode;
		firstNode = nextNode;
	}
}

template<typename T>
inline T& chain<T>::get(int theIndex) const
{
	checkIndex(theIndex);
	int i = 0;
	chainNode<T>* getNode = firstNode;
	while (i < theIndex)
	{
		getNode = getNode->next;
		i++;
	}

	return getNode->element;;
}

template<typename T>
inline int chain<T>::indexOf(const T& theElement) const
{
	chainNode<T>* findNode = firstNode;
	int i = 0;
	while (findNode->next!=NULL) {
		if (findNode->element==theElement) {
			return i;
		}
		else {
			findNode = findNode->next;
		}
		i++;
	}
	return -1;
}

template<typename T>
inline void chain<T>::erase(int theIndex)
{
	checkIndex(theIndex);
	chainNode<T>* deleteNode;
	if (theIndex == 0)
	{// remove first node from chain
		deleteNode = firstNode;
		firstNode = firstNode->next;
	}
	else
	{  // use p to get to predecessor of desired node
		chainNode<T>* p = firstNode;
		for (int i = 0; i < theIndex - 1; i++)
			p = p->next;

		deleteNode = p->next;
		p->next = p->next->next; // remove deleteNode from chain
	}
	listSize--;
	delete deleteNode;

}

template<typename T>
inline void chain<T>::insert(int theIndex, const T& theElement)
{
	checkIndex(theIndex);
	chainNode<T>* insertNode = firstNode;
	if (theIndex == 0)
	{
		firstNode = new chainNode<T>(theElement, firstNode);
	}
	else {
		for (int i = 0; i < theIndex - 1; i++) {
			insertNode = insertNode->next;
		}
		insertNode->next = new chainNode<T>(theElement,insertNode->next);
	}
	listSize++;
}

template<typename T>
inline void chain<T>::output() const
{
	for (chainNode<T>* currentNode = firstNode;
		currentNode != NULL;
		currentNode = currentNode->next) {
		std::cout << currentNode->element << "  ";
	}

		std::cout << std::endl;
}

template<typename T>
inline void chain<T>::binSort(int range)
{
	chainNode<T>** bottom, ** top;
	bottom = new chainNode<T>*[range + 1];
	top = new chainNode<T>*[range + 1];
	for (int b = 0; b <= range; b++)
		bottom[b] = NULL;

	// distribute to bins
	for (; firstNode != NULL; firstNode = firstNode->next)
	{// add firstNode to proper bin
		int theBin = firstNode->element; // type conversion to int
		if (bottom[theBin] == NULL) // bin is empty
			bottom[theBin] = top[theBin] = firstNode;
		else
		{// bin not empty
			top[theBin]->next = firstNode;
			top[theBin] = firstNode;
		}
	}

	// collect from bins into sorted chain
	chainNode<T>* y = NULL;
	for (int theBin = 0; theBin <= range; theBin++)
		if (bottom[theBin] != NULL)
		{// bin not empty
			if (y == NULL) // first nonempty bin
				firstNode = bottom[theBin];
			else // not first nonempty bin
				y->next = bottom[theBin];
			y = top[theBin];
		}
	if (y != NULL)
		y->next = NULL;

	delete[] bottom;
	delete[] top;
}

template <class T>
std::ostream& operator<<(std::ostream& out, const chain<T>& x)
{
	x.output(); 
	return out;
}


template<typename T>
inline void chain<T>::checkIndex(int& theIndex) const
{
	if (theIndex > listSize || theIndex < 0)
	{
		std::ostringstream s;
		s << "theIndex is out of the range of listSize" << std::endl;
		throw std::runtime_error(s.str());
	}
}

