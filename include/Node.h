#ifndef SIMPLE_GRAPH_NODE_H
#define SIMPLE_GRAPH_NODE_H

#include <iostream>

template <class T>
class Node
{
    T value;

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

    bool operator==(const Node& other) const
    {
        return value == other.value;
    }

    void print() const
    {
        std::cout << "Node: " << getValue()
                  << std::endl;
    }
};

#endif //SIMPLE_GRAPH_NODE_H
