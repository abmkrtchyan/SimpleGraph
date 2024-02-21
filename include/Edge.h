#include <utility>

#ifndef SIMPLE_GRAPH_EDGE_H
#define SIMPLE_GRAPH_EDGE_H

#ifndef EDGE_H
#define EDGE_H

template<class T, class L>
class Edge {
private:
    Node<T> *source;
    Node<T> *destination;
    L label;

public:
    Edge(Node<T> *src, Node<T> *dest, L lbl) : source(src), destination(dest), label(std::move(lbl)) {}

    Node<T> *getSource() const {
        return source;
    }

    Node<T> *getDestination() const {
        return destination;
    }

    L getLabel() const {
        return label;
    }

    void setLabel(const L &lbl) {
        label = lbl;
    }

    bool operator==(const Edge &other) const {
        return source == other.source && destination == other.destination && label == other.label;
    }
};

namespace std {
    template<class T, class L>
    struct hash<Edge < T, L>> {
    size_t operator()(const Edge <T, L> &edge) const {
        size_t hashValue = 0;
        hashValue ^= std::hash<T>()(edge.getSource()->getValue());
        hashValue ^= std::hash<T>()(edge.getDestination()->getValue()) + 0x9e3779b9 + (hashValue << 6) +
                     (hashValue >> 2);
        hashValue ^= std::hash<L>()(edge.getLabel()) + 0x9e3779b9 + (hashValue << 6) + (hashValue >> 2);
        return hashValue;
    }
};
}

#endif /* EDGE_H */


#endif //SIMPLE_GRAPH_EDGE_H
