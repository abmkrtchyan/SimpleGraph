#ifndef SIMPLE_GRAPH_NODE_H
#define SIMPLE_GRAPH_NODE_H

#include <climits>

template<class T>
class Node {
private:
    T value;
    int distance = INT_MAX;
    Node<T> *parent = nullptr;

public:
    Node(const T &val) : value(val) {}

    Node(const Node &other) : value(other.value) {}

    T getValue() const {
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

    void print() const {
        std::cout << "Node: " << getValue()
                  << std::endl;
    }

    struct HashFunction {
        size_t operator()(const Node<T> &node) const {
            return std::hash<T>()(node.getValue());
        }
    };
};

#endif //SIMPLE_GRAPH_NODE_H
