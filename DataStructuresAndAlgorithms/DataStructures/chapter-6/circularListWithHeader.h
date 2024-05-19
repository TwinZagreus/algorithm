#pragma once
#include"chain.h"
#include"../myExceptions.h"

template <typename T>
class circularListWithHeader
{
public:
    // constructor
    circularListWithHeader();

    // some methods
    int size() const { return listSize; }
    int indexOf(const T& theElement) const;
    void insert(int theIndex, const T& theElement);
    void output() const;

protected:
    void checkIndex(int theIndex) const;
    // throw illegalIndex if theIndex invalid
    chainNode<T>* headerNode;  // pointer to header node
    int listSize;
};

template<typename T>
inline circularListWithHeader<T>::circularListWithHeader()
{
    headerNode = new chainNode<T>();
    headerNode->next = headerNode;
    listSize = 0;
}

template<typename T>
inline int circularListWithHeader<T>::indexOf(const T& theElement) const
{
    // Put theElement in header node
    headerNode->element = theElement;

    // search the chain for theElement
    chainNode<T>* currentNode = headerNode->next;
    int index = 0;  // index of currentNode
    while (currentNode->element != theElement)
    {
        // move to next node
        currentNode = currentNode->next;
        index++;
    }

    // make sure we found matching element
    if (currentNode == headerNode)
        return -1;
    else
        return index;
}

template<typename T>
inline void circularListWithHeader<T>::insert(int theIndex, const T& theElement)
{
    if (theIndex < 0 || theIndex > listSize)
    {// invalid index
        ostringstream s;
        s << "index = " << theIndex << " size = " << listSize;
        throw illegalIndex(s.str());
    }

    // find predecessor of new element
    chainNode<T>* p = headerNode;
    for (int i = 0; i < theIndex; i++)
        p = p->next;

    // insert after p
    p->next = new chainNode<T>(theElement, p->next);

    listSize++;
}

template<typename T>
inline void circularListWithHeader<T>::output() const
{
    for (chainNode<T>* currentNode = headerNode->next;
        currentNode != headerNode;
        currentNode = currentNode->next) {
        cout << currentNode->element << "  ";
    }
    cout << endl;
}

template <class T>
ostream& operator<<(ostream& out, const circularListWithHeader<T>& x)
{
    x.output(); return out;
}



template<typename T>
inline void circularListWithHeader<T>::checkIndex(int theIndex) const
{
    if (theIndex < 0 || theIndex >= listSize)
    {
        ostringstream s;
        s << "index = " << theIndex << " size = " << listSize;
        throw illegalIndex(s.str());
    }
}
