#pragma once

#include <iostream>
#include <string>

using namespace std;

template <class K> class hash;

template<>
class hash <string> {

public:
	size_t operator()(const string theKey) const{
		unsigned long hashVakue = 0;
		int length = (int)theKey.length();
		for (int i = 0; i < length;i++) {
			hashVakue = 5 * hashVakue + theKey.at(i);
		}
		return size_t(hashVakue);
    }
};
