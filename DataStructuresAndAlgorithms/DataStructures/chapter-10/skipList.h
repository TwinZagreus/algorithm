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
    void erase(const K&);
    void insert(const pair<const K, E>&);
    void output(ostream& out) const;

protected:
    float cutOff;          // ����ȷ������
    int levels;            // ��ǰ���ķǿ�����
    int dSize;             // �ֵ�����Ը���
    int maxLevel;          // ���������������
    K tailKey;             // ���ؼ���

    skipNode<K, E>* headerNode;  // ͷ�ڵ�ָ��
    skipNode<K, E>* tailNode;    // β���ָ��
    skipNode<K, E>** last;       // last[i]��ʾi������ڵ�

    int level() const;
    skipNode<K, E>* search(const K&) const;
};

template<typename K, typename E>
inline skipList<K, E>::skipList(K largeKey, int maxPairs, float prob)
{//�ؼ���С��largeKey,�ֵ����Ԥ������0<prod<1
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

    // ����Ϊ��ʱ�����������е�ͷ�ڵ㶼ָ��β�ڵ�
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
        return NULL;  // û�п��ܵ�ƥ������

    // λ��before �ǹؼ���ΪtheKey�Ľڵ�֮ǰ���ұߵ�λ��
    skipNode<K, E>* beforeNode = headerNode;
    for (int i = levels; i >= 0; i--)          // ���ϼ������¼�����
        while (beforeNode->next[i]->element.first < theKey)
            beforeNode = beforeNode->next[i];

    // �����һ���ڵ�Ĺؼ����Ƿ���thekey
    if (beforeNode->next[0]->element.first == theKey)
        return &beforeNode->next[0]->element;

    return NULL;  // no matching pair
}

template<typename K, typename E>
inline void skipList<K, E>::erase(const K& theKey)
{
    if (theKey>=tailKey) {
        return;
    }

    skipNode<K, E>* theNode = search(theKey);
    if (theNode->element.first!=theKey) {
        return;
    }

    for (int i = 0; i < levels && last[i]->next[i] == theNode;i++) {
        last[i]->next[i] = theNode->next[i];
    }
    while (levels>0&&headerNode->next[levels]==tailNode) {
        levels--;
        delete theNode;
        dSize--;
    }
}

template<typename K, typename E>
inline void skipList<K, E>::insert(const pair<const K, E>& thePair)
{
    //������thePair ����
    if (thePair.first>=tailKey) {
        ostringstream s;
        s << "Key = " << thePair.first << "Must be <" << tailKey;
        throw illegalParameterValue(s.str());
    }
    //�鿴�ؼ���ΪtheKey�������Ƿ����
    skipNode<K, E>* theNode = search(thePair.first);
    if (theNode->element.first == thePair.first) {
        theNode->element.second = thePair.second;
        return;
    }
    int theLevel = level();
    if (theLevel>levels) {
        theLevel = ++levels;
        last[theLevel] = headerNode;
    }

    skipNode<K, E>* newNode = new skipNode<K, E>(thePair,theLevel+1);
    for (int i = 0; i <= theLevel;i++) {
        newNode->next[i] = last[i]->next[i];
        last[i]->next[i] = newNode;
    }
    dSize++;
    return;
}

template<typename K, typename E>
inline void skipList<K, E>::output(ostream& out) const
{
    for (skipNode<K, E>* currentNode = headerNode->next[0];
        currentNode != tailNode;
        currentNode = currentNode->next[0])
        out << currentNode->element.first << " "
        << currentNode->element.second << "  ";
}

template <class K, class E>
ostream& operator<<(ostream& out, const skipList<K, E>& x)
{
    x.output(out); return out;
}

template<typename K, typename E>
inline int skipList<K, E>::level() const
{
    //����һ����������������������maxLevel
    int lev = 0;
    while (rand()<=cutOff)
    {
        lev++;
    }
    return (lev <= maxLevel) ? lev : maxLevel;
}

template<typename K, typename E>
inline skipNode<K, E>* skipList<K, E>::search(const K& theKey) const
{
    //�����ؼ���theKey����ÿһ��������Ҫ�鿴�����һ�ڴ洢������last��
    //���ذ����ؼ���theKey�Ľڵ�
    skipNode<K, E>* beforeNode = headerNode;
    for (int i = levels; i >= 0;i--) {
        while (beforeNode->next[i]->element.first<theKey)
        {
            beforeNode = beforeNode->next[i];
        }
        last[i] = beforeNode;
    }
    return beforeNode->next[0];
}
