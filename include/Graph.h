#ifndef SIMPLE_GRAPH_GRAPH_H
#define SIMPLE_GRAPH_GRAPH_H

#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <queue>
#include <iostream>
#include "Node.h"
#include "Edge.h"

template <class T = char, class L = int>
class Graph
{
private:
    std::unordered_map<T, Node<T>> allNodes;
    std::unordered_map<T, std::unordered_set<Edge<T, L>>> inEdges;
    std::unordered_map<T, std::unordered_set<Edge<T, L>>> outEdges;

    Node<T>* getNode(const T& data)
    {
        auto it = allNodes.find(data);
        return (it != allNodes.end()) ? &(it->second) : nullptr;
    }

public:
    bool addNode(const T& v)
    {
        if (allNodes.find(v) == allNodes.end())
        {
            auto& node = allNodes.emplace(v, v).first->second;
            outEdges[v] = {};
            inEdges[v] = {};
            return true;
        }
        return false;
    }

    bool addEdge(const T& source, const T& dest, const L& label)
    {
        auto sourceNode = getNode(source);
        auto destNode = getNode(dest);
        if (sourceNode != nullptr && destNode != nullptr)
        {
            Edge<T, L> edge(sourceNode, destNode, label);
            inEdges[dest].insert(edge);
            outEdges[source].insert(edge);
            return true;
        }
        throw std::runtime_error("Node not found!");
    }

    std::unordered_set<T> getAllNodes() const
    {
        std::unordered_set<T> nodes;
        for (const auto& [key, _] : allNodes)
        {
            nodes.insert(key);
        }
        return nodes;
    }

    std::vector<T> getNextNodes(const T& nodeValue) const
    {
        auto it = outEdges.find(nodeValue);
        if (it == outEdges.end()) return {};

        std::vector<T> nextNodes;
        for (const auto& edge : it->second)
        {
            nextNodes.push_back(edge.getDestination()->getValue());
        }
        return nextNodes;
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


#endif // SIMPLE_GRAPH_GRAPH_H
