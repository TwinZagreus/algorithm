#pragma once

template <typename K, typename E>
struct skipNode
{
    typedef pair<const K, E> pairType;
    pairType element;
    skipNode<K, E>** next;   // Êý×éÖ¸Õë

    skipNode(const pairType& thePair, int size)
        :element(thePair) {
        next = new skipNode<K, E>* [size];
    }
};