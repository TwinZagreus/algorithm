#ifndef ARRAY_LIST_H
#define ARRAY_LIST_H

#include <iostream>
#include <stdlib.h>
#include <sstream>	//包含ostringstream
#include <algorithm>//包含find函数	
#include <iterator>//ostream_iterator
#include <string>

#include "linearList.h"
#include "iterator.h"


//arrayList<int> test(9);
//std::cout << test.capacity() << std::endl;
//if (test.empty()) { std::cout << "is empty" << std::endl; }
//std::cout << "test.size:" << test.size() << std::endl;
//
//test.insert(0, 0);
//test.insert(1, 3);
//test.insert(2, 5);
//test.erase(1);
//std::cout << "test.0:" << test.indexOf(0) << std::endl;
//
//test.output();

template <class T>
class arrayList : public linearList<T> {
public:
    arrayList(int initialCapacity = 10);
    arrayList(const arrayList<T>&);
    ~arrayList() { delete[] element; }
    bool empty() const { return listSize == 0; }
    int size() const { return listSize; }
    T& get(int theIndex) const;
    int indexOf(const T& theElement) const;
    void erase(int theIndex);
    void insert(int theIndex, const T& theElement);
    void output() const;
    template <typename U>
    friend std::ostream& operator<<(std::ostream& out, const arrayList<U> & x);
    int capacity() const { return arrayLength; }

	iterator<T> begin() const { return _begin; }
	iterator<T> end() const { return _end; }

private:
	iterator<T> _begin;
	iterator<T> _end;
	void resetIterator() {
		_begin = iterator<T>(element);
		_end = iterator<T>(element + listSize);
	};
protected:
    void checkIndex(int theIndex) const;
    T* element;        // 存储线性表元素的一维数组
    int arrayLength;   // 一维数组的容量
    int listSize;      // 线性表元素的个数
};


// 这里包含所有的模板函数定义
template<class T>
arrayList<T> ::arrayList(int initialCapacity)
{
	if (initialCapacity < 1) {
		std::ostringstream  s;
		s << "initialCapacity=" << initialCapacity << "Must be >0";
		throw std::invalid_argument(s.str());
	}
	arrayLength = initialCapacity;
	element = new T(arrayLength);
	listSize = 0;
	resetIterator();
};

template<class T>
arrayList<T>::arrayList(const arrayList<T>& theList) {
	arrayLength = theList.arrayLength;
	listSize = theList.listSize;
	element = new T[arrayLength];
	std::copy(theList.element, theList.element + listSize, element);
	resetIterator();
}

template<class T>
T& arrayList<T>::get(int theIndex) const {
	checkIndex(theIndex);
	return element[theIndex];
}

//返回元素theElement第一次出现的索引
//若元素不存在，则返回-1
template<class T>
int arrayList<T>::indexOf(const T& theElement) const
{
	//查找元素theElement
	int theIndex = static_cast<int>(std::find(element, element + listSize, theElement) - element);
	if (theIndex == listSize) {
		return -1;
	}
	else {
		return theIndex;
	}
}

template<class T>
void arrayList<T>::erase(int theIndex)
{
	checkIndex(theIndex);
	std::copy(element + theIndex + 1, element + listSize, element + theIndex);
	element[--listSize].~T();
	resetIterator();
}

template<class T>
void arrayList<T>::insert(int theIndex, const T& theELement)
{//在索引theIndex处插入元素
	//无效索引
	if (theIndex<0 || theIndex>listSize) {
		std::ostringstream  s;
		s << "index=" << theIndex << "size=" << listSize;
		throw std::invalid_argument(s.str());
	}

	if (listSize == arrayLength) {
		changeLength1D(element, arrayLength, arrayLength * 2);
		arrayLength *= 2;
	}
	std::copy(element + theIndex, element + listSize, element + theIndex + 1);
	element[theIndex] = theELement;
	listSize++;
	resetIterator();
}

template<class T>
void arrayList<T>::output() const
{
	for (int i = 0; i < listSize; i++)
	{
		std::cout << *(element + i) << " ";
	}
	std::cout << std::endl;
}

template<class T>
std::ostream& operator<<(std::ostream& out, const arrayList<T>& x) {
	x.output(out);
	return out;
}


template<class T>
void arrayList<T>::checkIndex(int theIndex)const {
	if (theIndex < 0 || theIndex >= listSize) {
		std::ostringstream  s;
		s << "index=" << theIndex << "size=" << listSize;
		throw std::invalid_argument(s.str());
	}
}


#endif // ARRAY_LIST_H