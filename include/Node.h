#ifndef SIMPLE_GRAPH_NODE_H
#define SIMPLE_GRAPH_NODE_H

#include <climits>

enum Color
{
    BLACK, GREY, WHITE
};

template <class T>
class Node
{
    T value;
    Color color = WHITE;
    std::size_t startTime = 0;
    std::size_t finishTime = INT_MAX;

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

    Color getColor() const
    {
        return this->color;
    }

    void setColor(Color newColor)
    {
        this->color = newColor;
    }

    size_t getStart() const
    {
        return this->startTime;
    }

    size_t getFinish() const
    {
        return this->finishTime;
    }

    void setStart(std::size_t start)
    {
        this->startTime = start;
    }

    void setFinish(std::size_t finish)
    {
        this->finishTime = finish;
    }

    void reset()
    {
        this->color = WHITE;
        this->startTime = 0;
        this->finishTime = INT_MAX;
    }

    bool operator==(const Node& other) const
    {
        return value == other.value;
    }

    void print() const
    {
        std::cout << "Node: " << getValue()
            << ", color: " << (getColor() == BLACK ? "BLACK" : getColor() == GREY ? "GREY" : "WHITE")
            << ", start: " << getStart()
            << ", finish: " << getFinish()
            << std::endl;
    }
};

#endif //SIMPLE_GRAPH_NODE_H
