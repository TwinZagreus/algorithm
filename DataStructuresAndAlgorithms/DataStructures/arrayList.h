#pragma once
#include "linearList.h"

template<class T>
class arrayList :
    public linearList<T>
{
public:
    arrayList(int initialCapacity = 10);
    arrayList(const arrayList<T>&);
    ~arrayList() { delete[]element; }

    bool empty() const { return listSize == 0; }
    int size() const { return listSize; }
    T& get(int theIndex) const;
    int indexOf(const T& theElement) const;
    void erase(int theIndex);
    void insert(int theIndex, const T& theELement);
    void output(std::ostream& out)const;


    int capacity()const { return arrayLength; };

protected:
    void checkIndex(int theIndex)const;
    //存储线性表元素的一维数组
    T* element;
    //一维数组的容量
    int arrayLength;
    //线性表的元素个数
    int listSize;     
};

