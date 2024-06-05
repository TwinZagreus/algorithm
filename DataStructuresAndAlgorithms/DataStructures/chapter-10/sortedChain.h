#pragma once

#include <iostream>
#include "dictionary.h"
#include "pairNode.h"

using namespace std;

template <typename K ,typename E>
class sortedChain :public dictionary<K, E> {
public:
	sortedChain() {
		firstNode = NULL;
		dSize = 0;
	}
	~sortedChain();

	bool empty() const { return dSize == 0; }
	int size() const { return dSize; }
	pair<const K, E>* find(const K&) const;
	void erase(const K&);
	void insert(const pair<const K, E>&);
	void output(ostream & out) const;

private:
	pairNode<K, E>* firstNode;  // pointer to first node in chain
	int dSize;                 // number of elements in dictionary
};

template<typename K, typename E>
inline sortedChain<K, E>::~sortedChain()
{
	while (firstNode != NULL) {
		pairNode<K, E>* nextNode = firstNode->next;
		delete firstNode;
		firstNode = nextNode;
	}
}

template<typename K, typename E>
inline pair<const K, E>* sortedChain<K, E>::find(const K& theKey) const
{
	pairNode<K, E>* currentNode = firstNode;
	while (currentNode != NULL && currentNode->element.first!=theKey) {
		currentNode = currentNode->next;
	}
	if (currentNode!=NULL&&currentNode->element.first==theKey) {
		return &(currentNode->element);
	}
	return NULL;
}

template<typename K, typename E>
inline void sortedChain<K, E>::erase(const K& theKey)
{
	pairNode<K, E>* p = firstNode;
	pairNode<K, E>* tp = NULL;

	while (p!=NULL&&p->element.first!=theKey)
	{
		tp = p;
		p = p->next;
	}

	if (p != NULL && p->element.first == theKey) {
		if (tp==NULL) {
			firstNode = p->next;
		}
		else {
			tp->next = p->next;
		}
		delete p;
		dSize--;
	}
}

template<typename K, typename E>
inline void sortedChain<K, E>::insert(const pair<const K, E>& thePair)
{
	pairNode<K, E>* p = firstNode;
	pairNode<K, E>* tp = NULL;

	while (p != NULL && p->element.first != thePair.first)
	{
		tp = p;
		p = p->next;
	}

	if (p != NULL && p->element.first == thePair.first)
	{// replace old value
		p->element.second = thePair.second;
		return;
	}

	pairNode<K, E>* newNode = new pairNode<K, E>(thePair, p);
	if (tp==NULL) {
		firstNode = newNode;
	}
	else {
		tp->next = newNode;
	}
	dSize++;
	return;
}

template<typename K, typename E>
inline void sortedChain<K, E>::output(ostream& out) const
{
	for (pairNode<K, E>* currentNode = firstNode;
		currentNode != NULL;
		currentNode = currentNode->next)
		out << currentNode->element.first << " "
		<< currentNode->element.second << "  ";
}

template <class K, class E>
ostream& operator<<(ostream& out, const sortedChain<K, E>& x)
{
	x.output(out); return out;
}