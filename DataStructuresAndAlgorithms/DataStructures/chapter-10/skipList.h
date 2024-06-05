#pragma once

#include <iostream>
#include <math.h>
#include <sstream>
#include <string>
#include "dictionary.h"
#include "skipNode.h"
#include "../myExceptions.h"

using namespace std;

template<typename K, typename E>
class skipList : public dictionary<K, E>
{
public:
    skipList(K, int maxPairs = 10000, float prob = 0.5);
    ~skipList();

    bool empty() const { return dSize == 0; }
    int size() const { return dSize; }
    pair<const K, E>* find(const K&) const;
    //void erase(const K&);
    void insert(const pair<const K, E>&);
    void output(ostream& out) const;

protected:
    float cutOff;          // 用来确定层数
    int levels;            // 当前最大的非空链表
    int dSize;             // 字典的数对个数
    int maxLevel;          // 允许的最大链表层数
    K tailKey;             // 最大关键字

    skipNode<K, E>* headerNode;  // 头节点指针
    skipNode<K, E>* tailNode;    // 尾结点指针
    skipNode<K, E>** last;       // last[i]表示i层的最后节点

    int level() const;
    skipNode<K, E>* search(const K&) const;
};

template<typename K, typename E>
inline skipList<K, E>::skipList(K largeKey, int maxPairs, float prob)
{
    cutOff = prob * RAND_MAX;
    maxLevel = (int)ceil(logf((float)maxPairs) / logf(1 / prob)) - 1;
    levels = 0;  // initial number of levels
    dSize = 0;
    tailKey = largeKey;

    // create header & tail nodes and last array
    pair<K, E> tailPair;
    tailPair.first = tailKey;
    headerNode = new skipNode<K, E>(tailPair, maxLevel + 1);
    tailNode = new skipNode<K, E>(tailPair, 0);
    last = new skipNode<K, E>* [maxLevel + 1];

    // header points to tail at all levels as lists are empty
    for (int i = 0; i <= maxLevel; i++)
        headerNode->next[i] = tailNode;
}

template<typename K, typename E>
inline skipList<K, E>::~skipList()
{
    skipNode<K, E>* nextNode;

    // delete all nodes by following level 0 chain
    while (headerNode != tailNode)
    {
        nextNode = headerNode->next[0];
        delete headerNode;
        headerNode = nextNode;
    }
    delete tailNode;

    delete[] last;
}

template<typename K, typename E>
inline pair<const K, E>* skipList<K, E>::find(const K& theKey) const
{
    if (theKey >= tailKey)
        return NULL;  // no matching pair possible

    // position beforeNode just before possible node with theKey
    skipNode<K, E>* beforeNode = headerNode;
    for (int i = levels; i >= 0; i--)          // go down levels
        // follow level i pointers
        while (beforeNode->next[i]->element.first < theKey)
            beforeNode = beforeNode->next[i];

    // check if next node has theKey
    if (beforeNode->next[0]->element.first == theKey)
        return &beforeNode->next[0]->element;

    return NULL;  // no matching pair
}

//template<typename K, typename E>
//inline void skipList<K, E>::erase(const K&)
//{
//}

template<typename K, typename E>
inline void skipList<K, E>::insert(const pair<const K, E>&)
{
}

template<typename K, typename E>
inline void skipList<K, E>::output(ostream& out) const
{
}

template<typename K, typename E>
inline int skipList<K, E>::level() const
{
    return 0;
}

template<typename K, typename E>
inline skipNode<K, E>* skipList<K, E>::search(const K&) const
{
    return nullptr;
}
