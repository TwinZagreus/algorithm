#pragma once

#include <iostream>
#include <math.h>
#include <sstream>
#include <string>
#include "dictionary.h"
#include "skipNode.h"
#include "../myExceptions.h"

using namespace std;


template<class K, class E>
class skipList : public dictionary<K, E>
{
public:
    skipList(K, int maxPairs = 10000, float prob = 0.5);
    ~skipList();

    bool empty() const { return dSize == 0; }
    int size() const { return dSize; }
    pair<const K, E>* find(const K&) const;
    void erase(const K&);
    void insert(const pair<const K, E>&);
    void output(ostream& out) const;

protected:
    float cutOff;          // used to decide level number
    int level() const;     // generate a random level number
    int levels;            // max current nonempty chain
    int dSize;             // number of pairs in dictionary
    int maxLevel;          // max permissible chain level
    K tailKey;             // a large key
    skipNode<K, E>* search(const K&) const;
    // search saving last nodes seen
    skipNode<K, E>* headerNode;  // header node pointer
    skipNode<K, E>* tailNode;    // tail node pointer
    skipNode<K, E>** last;       // last[i] = last node seen on level i
};

template<class K, class E>
inline skipList<K, E>::skipList(K, int maxPairs, float prob)
{
}
