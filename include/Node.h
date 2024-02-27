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
    std::pair<std::size_t, std::size_t> timestamp{0, INT_MAX};

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
        return this->timestamp.first;
    }

    size_t getFinish() const {
        return this->timestamp.second;
    }

    void setStart(std::size_t start) {
        this->timestamp.first = start;
    }

    void setFinish(std::size_t finish) {
        this->timestamp.second = finish;
    }

    bool operator==(const Node &other) const {
        return value == other.value;
    }

    struct HashFunction {
        size_t operator()(const Node<T> &node) const {
            return std::hash<T>()(node.getValue());
        }
    };
};

#endif //SIMPLE_GRAPH_NODE_H
