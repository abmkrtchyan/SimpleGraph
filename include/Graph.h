#ifndef SIMPLE_GRAPH_GRAPH_H
#define SIMPLE_GRAPH_GRAPH_H

#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <queue>
#include <algorithm>
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


    void dijkstra(const T& nodeValue)
    {
        auto node = getNode(nodeValue);
        if (node != nullptr)
        {
            dijkstra(node);
        }
    }

    void initializeSingleSource(Node<T>* sourceNode)
    {
        for (auto node : allNodes)
        {
            node.second.setParent(nullptr);
            node.second.setDistance(INT_MAX);
        }
        sourceNode->setDistance(0);
    }

    bool relax(Edge<T, L>& edge)
    {
        if (edge.getDestination()->getDistance() > edge.getSource()->getDistance() + edge.getLabel())
        {
            edge.getDestination()->setDistance(edge.getSource()->getDistance() + edge.getLabel());
            edge.getDestination()->setParent(edge.getSource());
            return true;
        }
        return false;
    }

    void dijkstra(Node<T>* sourceNode)
    {
        initializeSingleSource(sourceNode);
        auto cmp = [](Node<T>* a, Node<T>* b) { return a->getDistance() > b->getDistance(); };
        std::priority_queue<Node<T>*, std::vector<Node<T>*>, decltype(cmp)> pq(cmp);
        pq.push(sourceNode);
        std::unordered_set<T> status;
        while (!pq.empty())
        {
            auto node = pq.top();
            pq.pop();
            if (status.find(node->getValue()) == status.end())
            {
                status.insert(node->getValue());
                for (auto edge : outEdges[node->getValue()])
                {
                    if (relax(edge))
                    {
                        pq.push(edge.getDestination());
                    }
                }
            }
        }
    }

    void printAllDijkstraNodes() const
    {
        std::cout << "Node:\t ";
        for (const auto& [_, node] : allNodes)
        {
            std::cout << "\t" << node.getValue();
        }
        std::cout << std::endl;

        std::cout << "Distance: ";
        for (const auto& [_, node] : allNodes)
        {
            std::cout << "\t" << node.getDistance();
        }
        std::cout << std::endl;

        std::cout << "Parent: ";
        for (const auto& [_, node] : allNodes)
        {
            std::cout << "\t" << (node.getParent() != nullptr ? node.getParent()->getValue() : "NULL");
        }
    }


    std::vector<std::vector<T>> getShortestPaths(const T &nodeValue) {
        dijkstra(nodeValue);
        std::vector<std::vector<T>> paths;
        for(auto nodePair : allNodes) {
            auto node = nodePair.second;
            std::vector<T> current;
            while (node != nullptr) {
                current.push_back(node->getValue());
                node = node->getParent();
            }
            std::reverse(current.begin(), current.end());
            paths.push_back(current);
        }
        return paths;
    }
};


#endif // SIMPLE_GRAPH_GRAPH_H
