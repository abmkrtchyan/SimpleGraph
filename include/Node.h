#ifndef SIMPLE_GRAPH_NODE_H
#define SIMPLE_GRAPH_NODE_H

#include <iostream>
#include <climits>

template <class T>
class Node
{
    T value;
    int distance = INT_MAX;
    Node<T> *parent = nullptr;

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

    int getDistance() const {
        return this->distance;
    }

    void setDistance(int newDistance) {
        this->distance = newDistance;
    }

    Node<T> *getParent() const {
        return this->parent;
    }

    void setParent(Node<T> *newParent) {
        this->parent = newParent;
    }

    bool operator==(const Node &other) const {
        return value == other.value;
    }

    void print() const
    {
        std::cout << "Node: " << getValue()
                  << std::endl;
    }
};

#endif //SIMPLE_GRAPH_NODE_H
