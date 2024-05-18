#pragma once

#include <iostream>
#include <stddef.h> 

template <typename iterator>
void copy(iterator start, iterator end, iterator to)
{//´Ó[start,end]¸´ÖÆµ½[to,to+end-start]
	while (start != end)
	{
		*to = *start;
		to++;
		start++;
	}
}


template <typename T>
class iterator
{
public:
	typedef std::bidirectional_iterator_tag iterator_category;
	typedef T value_type;
	typedef ptrdiff_t difference_type;
	typedef T* pointer;
	typedef T& reference;

	iterator(T* thePosition = 0) {
		_position = thePosition;
	};
	T& operator* () const { return * _position; }
	T* operator->() const { return &* _position; }

	iterator& operator++() {
		++_position;
		return *this;
	}

	iterator& operator++(int) {
		iterator old = *this;
		++_position;
		return old;
	}

	iterator& operator--() {
		--_position;
		return *this;
	}

	iterator& operator--(int) {
		iterator old = *this;
		--_position;
		return old;
	}

	bool operator !=(const iterator right) const {
		return _position != right._position;
	}

	bool operator ==(const iterator right) const {
		return _position == right._position;
	}

protected:
	T* _position;
};

