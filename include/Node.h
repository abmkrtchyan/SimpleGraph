#ifndef SIMPLE_GRAPH_NODE_H
#define SIMPLE_GRAPH_NODE_H

#include <functional>

template<class T>
class Node {
private:
    T value;

public:
    Node(const T &val) : value(val) {}

    Node(const Node &other) : value(other.value) {}

    T getValue() const {
        return value;
    }

    bool operator==(const Node &other) const {
        return value == other.value;
    }
};

#endif //SIMPLE_GRAPH_NODE_H
