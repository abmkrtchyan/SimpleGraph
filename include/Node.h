#ifndef SIMPLE_GRAPH_NODE_H
#define SIMPLE_GRAPH_NODE_H

#include <iostream>

template <class T>
class Node
{
    T value;
    std::size_t rank = 0;
    Node<T>* parent = nullptr;

public:
    explicit Node(const T& val) : value(val)
    {
    }

    Node(const Node& other) : value(other.value)
    {
    }

    T getValue() const
    {
        return value;
    }

    Node<T>* getParent() const
    {
        return this->parent;
    }

    void setParent(Node<T>* newParent)
    {
        this->parent = newParent;
    }


    std::size_t getRank() const
    {
        return this->rank;
    }

    void increaseRank()
    {
        ++this->rank;
    }

    bool operator==(const Node& other) const
    {
        return value == other.value;
    }
};

#endif //SIMPLE_GRAPH_NODE_H
