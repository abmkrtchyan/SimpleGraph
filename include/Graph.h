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
    std::unordered_map<Node<T> *, std::unordered_set<Edge<T, L>>> in_edges;
    std::unordered_map<Node<T> *, std::unordered_set<Edge<T, L>>> out_edges;

    Node<T> *getNode(const T &data) const {
        auto nodeIter = allNodes.find(data);
        if (nodeIter != allNodes.end()) {
            return nodeIter->second;
        }
        return nullptr;
    }

public:
    bool addVertex(const T &v) {
        if (allNodes.find(v) == allNodes.end()) {
            auto node = new Node<T>(v);
            allNodes[v] = node;
            out_edges[node] = std::unordered_set<Edge<T, L>>();
            in_edges[node] = std::unordered_set<Edge<T, L>>();
            return true;
        }
        return false;
    }

    bool addEdge(const T &source, const T &dest, const L &label) {
        auto sourceNode = getNode(source);
        auto destNode = getNode(dest);
        if (sourceNode != nullptr && destNode != nullptr) {
            Edge<T, L> edge(sourceNode, destNode, label);
            in_edges[sourceNode].insert(edge);
            out_edges[sourceNode].insert(edge);
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
            for (const auto &edge: out_edges.find(node)->second) {
                auto neighbor = getNode(edge.getDestination()->getValue());
                neighbors.insert(neighbor->getValue());
            }
        }
        return neighbors;
    }

    void bfsPrint(const T &start) const {
        auto startNode = getNode(start);
        if (startNode == nullptr)
            return;
        std::unordered_set<Node<T>> visited;
        std::queue<Node<T>> q;

        q.push(*startNode);
        visited.insert(*startNode);

        while (!q.empty()) {
            auto current = q.front();
            q.pop();

            std::cout << current.getValue() << " -> ";

            for (auto neighborValue: getNeighborNodes(current.getValue())) {
                auto neighbor = *getNode(neighborValue);
                if (visited.find(neighbor) == visited.end()) {
                    q.push(neighbor);
                    visited.insert(neighbor);
                }
            }
        }
    }
};


#endif //SIMPLE_GRAPH_GRAPH_H
