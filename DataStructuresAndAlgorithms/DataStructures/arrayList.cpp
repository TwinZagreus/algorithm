#include "arrayList.h"
#include <algorithm>
#include <iterator> 

template<class T>
arrayList<T> ::arrayList(int initialCapacity)
{
	if (initialCapacity<1) {
		std::ostringstream  s;
		s << "initialCapacity=" << initialCapacity << "Must be >0";
		throw std::invalid_argument(s.str());
	}
	arrayLength = initialCapacity;
	element = new T(arrayLength);
	listSize = 0;
};

template<class T>
arrayList<T>::arrayList(const arrayList<T>& theList) {
	arrayLength = theList.arrayLength;
	listSize = theList.listSize;
	element = new T[arrayLength];
	std::copy(theList.element, theList.element + listSize, element);
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
	if (theIndex ==listSize) {
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
	std::copy(element+theIndex+1,element+listSize,element+theIndex);
	element[--listSize].~T();
}

template<class T>
void arrayList<T>::insert(int theIndex, const T& theELement)
{//在索引theIndex处插入元素
	//无效索引
	if (theIndex<0||theIndex>listSize) {
		std::ostringstream  s;
		s << "index=" << theIndex << "size=" << listSize;
		throw std::invalid_argument(s.str());
	}

	if (listSize==arrayLength) {
		changeLength1D(element, arrayLength, arrayLength * 2);
		arrayLength *= 2;
	}
	std::copy(element+theIndex,element+listSize,element+theIndex+1);
	element[theIndex] = theELement;
	listSize++;
}

template<class T>
void arrayList<T>::output(std::ostream& out) const
{
	std::copy(element,element+listSize,std::ostream_iterator<T>(std::cout," "));
}

template<class T>
std::ostream& operator<<(std::ostream& out,const arrayList<T>&x) {
	x.output(out);
	return out;
}

template<class T>
void arrayList<T>::checkIndex(int theIndex)const {
	if (theIndex<0||theIndex>=listSize) {
		std::ostringstream  s;
		s << "index=" << theIndex << "size=" << listSize;
		throw std::invalid_argument(s.str());
	}
}