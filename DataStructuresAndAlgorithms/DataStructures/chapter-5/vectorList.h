#pragma once
#include "linearList.h"
template <typename T>
class vectorList :
    public linearList<T>
{
public:
	//构造函数、复制函数、析构函数
	vectorList(int initialCapacity = 10);
	vectorList(const vectorList<T>&);
	~vectorList() { delete _element; }
	//ADT
//	void erase (int theIndex);
	bool empty() const { return _element->empty(); }
	int size() const { return (int)_element->size(); }
	T& get(int theIndex) const;
	int indexOf(const T& theElement) const;
	void erase(int theIndex);
	void insert(int theIndex, const T& theElement);
	void output() const;

	// additional method
	int capacity() const { return (int)_element->capacity(); }

	typedef typename vector<T>::iterator iterator;
	iterator begin() { return _element->begin(); }
	iterator end() { return _element->end(); }

protected:
	void checkIndex(int theIndex) const;
	vector<T>* _element;
};

template<typename T>
inline vectorList<T>::vectorList(int initialCapacity)
{
	if (initialCapacity<1) {
		ostringstream s;
		s << "Initial capacity = " << initialCapacity << "Must be >0";
	}
	//_element = new
}

template<typename T>
inline vectorList<T>::vectorList(const vectorList<T>&)
{
}

template<typename T>
inline T& vectorList<T>::get(int theIndex) const
{
	// TODO: 在此处插入 return 语句
}

template<typename T>
inline int vectorList<T>::indexOf(const T& theElement) const
{
	return 0;
}

template<typename T>
inline void vectorList<T>::erase(int theIndex)
{
}

template<typename T>
inline void vectorList<T>::insert(int theIndex, const T& theElement)
{
}

template<typename T>
inline void vectorList<T>::output() const
{
}

template<typename T>
inline void vectorList<T>::checkIndex(int theIndex) const
{
}
