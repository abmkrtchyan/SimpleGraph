#ifndef SIMPLE_GRAPH_GRAPH_H
#define SIMPLE_GRAPH_GRAPH_H

#include <unordered_map>
#include <unordered_set>
#include <queue>
#include "Node.h"
#include "Edge.h"

template<class T=char, class L=int>
class Graph {
private:
    std::unordered_map<T, Node<T> *> allNodes;
    std::unordered_map<Node<T>, std::unordered_set<Edge<T, L>, typename Edge<T, L>::HashFunction>, typename Node<T>::HashFunction> inEdges;
    std::unordered_map<Node<T>, std::unordered_set<Edge<T, L>, typename Edge<T, L>::HashFunction>, typename Node<T>::HashFunction> outEdges;

    Node<T> *getNode(const T &data) const {
        auto nodeIter = allNodes.find(data);
        if (nodeIter != allNodes.end()) {
            return nodeIter->second;
        }
        return nullptr;
    }

public:
    bool addNode(const T &v) {
        if (getNode(v) == nullptr) {
            auto node = new Node<T>(v);
            allNodes[v] = node;
            outEdges[*node] = std::unordered_set<Edge<T, L>, typename Edge<T, L>::HashFunction>();
            inEdges[*node] = std::unordered_set<Edge<T, L>, typename Edge<T, L>::HashFunction>();
            return true;
        }
        return false;
    }

    bool addEdge(const T &source, const T &dest, const L &label) {
        auto sourceNode = getNode(source);
        auto destNode = getNode(dest);
        if (sourceNode != nullptr && destNode != nullptr) {
            Edge<T, L> edge(sourceNode, destNode, label);
            inEdges[*sourceNode].insert(edge);
            outEdges[*sourceNode].insert(edge);
            return true;
        }
        throw std::runtime_error("Node not found!");
    }

    std::unordered_set<T> getAllNodes() const {
        std::unordered_set<T> nodes;
        for (const auto &pair: allNodes) {
            nodes.insert(pair.first);
        }
        return nodes;
    }

    std::unordered_set<T> getNeighborNodes(const T &nodeValue) const {
        std::unordered_set<T> neighbors;
        auto node = getNode(nodeValue);
        if (node != nullptr) {
            for (const auto &edge: outEdges.find(*node)->second) {
                auto neighbor = getNode(edge.getDestination()->getValue());
                neighbors.insert(neighbor->getValue());
            }
        }
        return neighbors;
    }

    void dfs() {
        for (auto &node: this->allNodes) {
            node.second->reset();
        }
        std::size_t time = 0;
        for (auto &node: this->allNodes) {
            if (node.second->getColor() == WHITE) {
                dfsVisit(*node.second, time);
            }
        }
    }

    void dfsVisit(Node<T> &node, std::size_t &time) {
        node.setStart(time++);
        node.setColor(GREY);
        for (const auto &outEdge: outEdges[node]) {
            auto nextNode = outEdge.getDestination();
            if (nextNode->getColor() == WHITE) {
                dfsVisit(*nextNode, time);
            }
        }
        node.setColor(BLACK);
        node.setFinish(time++);
    }
};


#endif //SIMPLE_GRAPH_GRAPH_H
