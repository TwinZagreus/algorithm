#ifndef LINEAR_LIST_H
#define LINEAR_LIST_H
#include <stdexcept> // 包含 std::invalid_argument




template <typename T>
class linearList {
public:
    virtual ~linearList() {}
    virtual bool empty() const = 0;
    virtual int size() const = 0;
    virtual T& get(int theIndex) const = 0;
    virtual int indexOf(const T& theElement) const = 0;
    virtual void erase(int theIndex) = 0;
    virtual void insert(int theIndex, const T& theElement) = 0;
    virtual void output() const = 0;

};

extern template class linearList<int>;
extern template class linearList<double>;

template <typename T>
void changeLength1D(T*& a, int oldLength, int newLength)
{
	if (newLength < 0) {
		throw std::invalid_argument("newLength cannot be negative");
	}
	T* temp = new T(newLength);
	//获取要复制的元素个数
	int number = std::min(oldLength, newLength);
	//a的前number复制给temp
	std::copy(a, a + number, temp);
	delete[] a;
	a = temp;
};

#endif // LINEAR_LIST_H