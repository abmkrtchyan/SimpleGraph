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
    std::unordered_map<Node<T> *, std::unordered_set<Edge<T, L>, typename Edge<T, L>::HashFunction>> in_edges;
    std::unordered_map<Node<T> *, std::unordered_set<Edge<T, L>, typename Edge<T, L>::HashFunction>> out_edges;

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
            out_edges[node] = std::unordered_set<Edge<T, L>, typename Edge<T, L>::HashFunction>();
            in_edges[node] = std::unordered_set<Edge<T, L>, typename Edge<T, L>::HashFunction>();
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

    void dijkstra(const T &nodeValue) {
        auto node = getNode(nodeValue);
        if (node != nullptr) {
            dijkstra(node);
        }
    }

    void initializeSingleSource(Node<T> *sourceNode) {
        for (auto node: allNodes) {
            node.second->setParent(nullptr);
            node.second->setDistance(INT_MAX);
        }
        sourceNode->setDistance(0);
    }

    void relax(Edge<T, L> &edge) {
        if (edge.getDestination()->getDistance() > edge.getSource()->getDistance() + edge.getLabel()) {
            edge.getDestination()->setDistance(edge.getSource()->getDistance() + edge.getLabel());
            edge.getDestination()->setParent(edge.getSource());
        }
    }

    void dijkstra(Node<T> *sourceNode) {
        initializeSingleSource(sourceNode);
        std::priority_queue<Node<T> *, std::vector<Node<T> *>, std::greater<Node<T>*>> pq;
        for (auto node: allNodes) {
            pq.push(node.second);
        }

        while (!pq.empty()) {
            auto node = pq.top();
            pq.pop();
            for (auto edge: out_edges[node]) {
                relax(edge);
            }
        }
    }
};


#endif //SIMPLE_GRAPH_GRAPH_H
