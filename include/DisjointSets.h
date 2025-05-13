#ifndef DISJOINT_SETS_H
#define DISJOINT_SETS_H
#include "Node.h"

template <class T>
class DisjointSets
{
public:
    static void makeSet(Node<T>* node)
    {
        node->setParent(node);
        node->initRank();
    }

    static Node<T>* findSet(Node<T>* node)
    {
        if (node->getParent()->getValue() != node->getValue())
        {
            node->setParent(findSet(node->getParent()));
        }
        return node->getParent();
    }

    static void unionSet(Node<T>* n1, Node<T>* n2)
    {
        auto v1 = findSet(n1);
        auto v2 = findSet(n2);
        if (v1->getValue() != v2->getValue())
        {
            link_by_rank(v1, v2);
        }
    }

    static void link_by_rank(Node<T>* n1, Node<T>* n2)
    {
        if (n1->getRank() == n2->getRank())
        {
            n2->increaseRank();
        }
        if (n1->getRank() > n2->getRank())
        {
            n2->setParent(n1);
        }
        else
        {
            n1->setParent(n2);
        }
    }
};

#endif //DISJOINT_SETS_H
