#ifndef SIMPLE_GRAPH_NODE_H
#define SIMPLE_GRAPH_NODE_H

#include <climits>

enum Color {
    BLACK, GREY, WHITE
};

template<class T>
class Node {
private:
    T value;
    Color color = WHITE;
    std::size_t startTime = 0;
    std::size_t finishTime = INT_MAX;

public:
    Node(const T &val) : value(val) {}

    Node(const Node &other) : value(other.value) {}

    T getValue() const {
        return value;
    }

    Color getColor() const {
        return this->color;
    }

    void setColor(Color newColor) {
        this->color = newColor;
    }

    size_t getStart() const {
        return this->startTime;
    }

    size_t getFinish() const {
        return this->finishTime;
    }

    void setStart(std::size_t start) {
        this->startTime = start;
    }

    void setFinish(std::size_t finish) {
        this->finishTime = finish;
    }

    bool operator==(const Node &other) const {
        return value == other.value;
    }

    void print() const {
        std::cout << "Node: " << getValue()
                  << ", color: " << (getColor() == BLACK ? "BLACK" : getColor() == GREY ? "GREY" : "WHITE")
                  << ", start: " << getStart()
                  << ", finish: " << getFinish()
                  << std::endl;
    }

    struct HashFunction {
        size_t operator()(const Node<T> &node) const {
            return std::hash<T>()(node.getValue());
        }
    };
};

#endif //SIMPLE_GRAPH_NODE_H
