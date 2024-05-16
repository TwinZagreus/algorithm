#pragma once
#include <algorithm> // ���� std::copy
#include <stdexcept> // ���� std::invalid_argument
#include <climits>   // ���� #include <limits.h>������ std::min
#include <iostream>
#include <ostream>
#include <sstream> 

/*һ�����Ա�ĳ�����*/
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

/* �ı�һ��һά����ĳ���*/
template<class T>
void changeLength1D(T*& a, int oldLength, int newLength)
{
	if (newLength < 0) {
		throw std::invalid_argument("newLength cannot be negative");
	}
	T* temp = new T(newLength);
	//��ȡҪ���Ƶ�Ԫ�ظ���
	int number = std::min(oldLength, newLength);
	//a��ǰnumber���Ƹ�temp
	std::copy(a,a+number,temp);
	delete[] a;
	a = temp;
};

