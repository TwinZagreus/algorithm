#pragma once

#include "../myExceptions.h"
#include "../chapter-6/extendedChain.h"

using namespace std;

template<class T>
class linkedMatrix {
    friend ostream& operator<<
        (ostream&, linkedMatrix<T>&);
    friend istream& operator>>
        (istream&, linkedMatrix<T>&);
public:
    linkedMatrix() {}
    ~linkedMatrix() {}
    void transpose(linkedMatrix<T>& b);
private:
    int rows,       // number of rows in matrix
        cols;       // number of columns in matrix
    extendedChain<headerElement<T> > headerChain;
};

template<class T>
inline void linkedMatrix<T>::transpose(linkedMatrix<T>& b)
{
}
