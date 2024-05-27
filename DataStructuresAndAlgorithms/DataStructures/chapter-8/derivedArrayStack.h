#pragma once

#include "../chapter-5/arrayList.h"
#include "../myExceptions.h"
#include "stack.h"

template <typename T>
class deriveArrayStack : private arrayList<T>,
	public stack<T> {
public:
	deriveArrayStack(int initialCapacity = 10) :arrayList<T>(initialCapacity) {}
	bool empty() const { return arrayList<T>::empty(); }
	int size() const { return arrayList<T>::size(); }
	T& top() {
		if (arrayList<T>::empty()) {
			throw stackEmpty();
		}
		return get(arrayList<T>::size() - 1);
	}
	void pop() {
		if (arrayList<T>::empty()) {
			throw stackEmpty();
		}
		erase(arrayList<T>::size()-1);
	}
	void push(const T& theElement) {
		insert(arrayList<T>::size(),theElement);
	}
};