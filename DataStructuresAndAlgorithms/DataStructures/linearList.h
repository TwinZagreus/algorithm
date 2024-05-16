#pragma once
#include <algorithm> // 包含 std::copy
#include <stdexcept> // 包含 std::invalid_argument
#include <climits>   // 或者 #include <limits.h>，包含 std::min
#include <iostream>
#include <ostream>
#include <sstream> 

/*一个线性表的抽象类*/
template<class T>
class linearList
{
public:
	virtual ~linearList() {};
	virtual bool empty() const = 0;
	virtual int size() const = 0;
	virtual T& get(int theIndex) const = 0;
	virtual int indexOf(const T& theElement) const = 0;
	virtual void erase (int theIndex)  = 0;
	virtual void insert(int theIndex,const T&theElement)  = 0;
	virtual void output(std::ostream& out) const = 0;
};

/* 改变一个一维数组的长度*/
template<class T>
void changeLength1D(T*& a, int oldLength, int newLength)
{
	if (newLength < 0) {
		throw std::invalid_argument("newLength cannot be negative");
	}
	T* temp = new T(newLength);
	//获取要复制的元素个数
	int number = std::min(oldLength, newLength);
	//a的前number复制给temp
	std::copy(a,a+number,temp);
	delete[] a;
	a = temp;
};

