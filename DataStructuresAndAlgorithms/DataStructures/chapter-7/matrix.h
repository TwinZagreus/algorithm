#pragma once

#include <algorithm> // 包含copy函数的头文件
#include"../myExceptions.h"

using namespace std;

template<typename T>
class matrix
{
friend ostream& operator<<(ostream&,const matrix<T>&);
public:
    matrix(int theRows = 0, int theColumns = 0);
    matrix(const matrix<T>&);
    ~matrix() { delete[] element; }
    int rows() const { return theRows; }
    int columns() const { return theColumns; }
    T& operator()(int i, int j) const;
    matrix<T>& operator=(const matrix<T>&);
    matrix<T> operator+() const; // unary +
    matrix<T> operator+(const matrix<T>&) const;
    matrix<T> operator-() const; // unary minus
    matrix<T> operator-(const matrix<T>&) const;
    matrix<T> operator*(const matrix<T>&) const;
    matrix<T>& operator+=(const T&);
private:
    int theRows,    // number of rows in matrix
        theColumns; // number of columns in matrix
    T* element;     // element array
};

template<typename t>
inline matrix<t>::matrix(int theRows, int theColumns)
{
    if (theRows<0||theColumns<0) {
        throw illegalParameterValue("rows and columns must be >=0");
    }
    if ((theRows == 0 || theColumns == 0) && (theRows != 0 || theColumns != 0)) {
        throw illegalParameterValue("Either both or neither rows and columns should be zero");
    }

    this->theRows = theRows;
    this->theColumns = theColumns;
    element = new T[theRows * theColumns];

}

template<typename T>
inline matrix<T>::matrix(const matrix<T>& m)
{
    theRows = m.theRows;
    theColumns = m.theColumns;
    element = new T[theRows * theColumns];

    copy(m.element, m.element + (theRows * theColumns), element);
}

template<typename T>
inline T& matrix<T>::operator()(int i, int j) const
{
    // TODO: 在此处插入 return 语句
    if (i < 1 || i > theRows
        || j < 1 || j > theColumns)
        throw matrixIndexOutOfBounds();
    return element[(i - 1) * theColumns + j - 1];
}

template<typename T>
inline matrix<T>& matrix<T>::operator=(const matrix<T>& m)
{
    if (this != &m) {
        delete[] element;
        theRows = m.theRows;
        theColumns = m.theColumns;
        element = new T[theRows * theColumns];
        // copy each element
        copy(m.element,
            m.element + theRows * theColumns,
            element);
    }
    return *this;
    // TODO: 在此处插入 return 语句
}

template<typename T>
inline matrix<T> matrix<T>::operator+() const
{
    return matrix<T>();
}

template<typename T>
inline matrix<T> matrix<T>::operator+(const matrix<T>& m) const
{
    w = (*this) + m;
    if (theRows!=m.theRows||theColumns!=m.theColumns) {
        throw matrixSizeMismatch();
    }
    matrix<T> w(theRows,theColumns);
    for (int i = 0; i < theRows * theColumns;i++) {
        w.element[i] = element[i] + m.element[i];
    }
    return w;
}

template<typename T>
inline matrix<T> matrix<T>::operator-() const
{
    return matrix<T>();
}

template<typename T>
inline matrix<T> matrix<T>::operator-(const matrix<T>&) const
{
    return matrix<T>();
}

template<typename T>
inline matrix<T> matrix<T>::operator*(const matrix<T>&) const
{
    return matrix<T>();
}

template<typename T>
inline matrix<T>& matrix<T>::operator+=(const T&)
{
    // TODO: 在此处插入 return 语句
}

