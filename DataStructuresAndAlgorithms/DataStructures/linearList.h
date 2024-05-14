#pragma once

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
	virtual void erase (int theIndex) const = 0;
	virtual void insert(int theIndex,const T&theElement) const = 0;
	virtual void output(ostream& out) const = 0;
};

