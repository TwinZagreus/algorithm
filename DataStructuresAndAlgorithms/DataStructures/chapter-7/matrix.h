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
    //w = (*this) + m;
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
    if (theRows != m.theRows
        || theColumns != m.theColumns)
        throw matrixSizeMismatch();
    // create result matrix w
    matrix<T> w(theRows, theColumns);
    for (int i = 0; i < theRows * theColumns; i++)
    {
        w.element[i] = element[i] - m.element[i];
    }

    return w;
}

template<typename T>
inline matrix<T> matrix<T>::operator-(const matrix<T>&) const
{
    matrix<T> w(theRows, theColumns);
    for (int i = 0; i < theRows * theColumns; i++)
        w.element[i] = -element[i];
    return w;
}

template<typename T>
inline matrix<T> matrix<T>::operator*(const matrix<T>& m) const
{
    if (theColumns!=m.theRows) {
        throw matrixSizeMismatch();
    }
    matrix<T> w(theRows, m.theColumns);
    int ct = 0; 
    int cm = 0; 
    int cw = 0;
    for (int i = 1; i <= theRows;i++) {
        for (int j = 1; j <= m.theColumns; j++) {
            //计算w(i,j)第一项
            T sum = element[ct] * m.element[cm];
            for (int k = 2; k <= theColumns;k++) {
                ct++;
                cm += m.theColumns;
                sum += element[ct] * m.element[cm];
            }
            w.element[cw++] = sum;

            ct = ct - theColumns + 1;
            cm = j;
        }
        ct = ct + theColumns;
        cm = 0;
    }
    return w;
}

template<typename T>
inline matrix<T>& matrix<T>::operator+=(const T&)
{
    // TODO: 在此处插入 return 语句
    for (int i = 0; i < theRows * theColumns; i++)
        element[i] += x;
    return *this;
}

template<class T>
ostream& operator<<(ostream& out, const matrix<T>& m)
{// Put matrix m into the stream out.
 // One row per line.
    int k = 0;  // index into element array
    for (int i = 0; i < m.theRows; i++)
    {// do row i
        for (int j = 0; j < m.theColumns; j++)
            out << m.element[k++] << "  ";

        // row i finished
        out << endl;
    }

    return out;
}

// for some reason compiler can't create this on its own
ostream& operator<<(ostream& out, const matrix<int>& m)
{// Put matrix m into the stream out.
 // One row per line.
    int k = 0;  // index into element array
    for (int i = 0; i < m.theRows; i++)
    {// do row i
        for (int j = 0; j < m.theColumns; j++)
            out << m.element[k++] << "  ";

        // row i finished
        out << endl;
    }

    return out;
}