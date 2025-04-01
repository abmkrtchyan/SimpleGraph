#ifndef SIMPLE_GRAPH_GRAPH_H
#define SIMPLE_GRAPH_GRAPH_H

#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <algorithm>
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

    std::vector<Node<T>*> topologicalSortNodes()
    {
        dfs();
        std::vector<Node<T>*> sortedNodes;
        sortedNodes.reserve(allNodes.size());

        for (auto& [_, node] : allNodes)
        {
            sortedNodes.push_back(&node);
        }

        std::sort(sortedNodes.begin(), sortedNodes.end(),
                  [](Node<T>* a, Node<T>* b) { return a->getFinish() > b->getFinish(); });

        return sortedNodes;
    }

public:
    bool addNode(const T& v)
    {
        if (getNode(v) == nullptr)
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

    std::unordered_set<T> getNeighborNodes(const T& nodeValue) const
    {
        std::unordered_set<T> neighbors;
        if (getNode(nodeValue) != nullptr)
        {
            auto it = outEdges.find(nodeValue);
            if (it != outEdges.end())
            {
                for (const auto& edge : it->second)
                {
                    neighbors.insert(edge.getDestination()->getValue());
                }
            }
        }
        return neighbors;
    }

    void dfs()
    {
        for (auto& [_, node] : allNodes)
        {
            node.reset();
        }
        std::size_t time = 0;
        for (auto& [_, node] : allNodes)
        {
            if (node.getColor() == WHITE)
            {
                dfsVisit(node, time);
            }
        }
    }

    void dfsVisit(Node<T>& node, std::size_t& time)
    {
        node.setStart(time++);
        node.setColor(GREY);
        for (const auto& edge : outEdges[node.getValue()])
        {
            auto nextNode = edge.getDestination();
            if (nextNode->getColor() == WHITE)
            {
                dfsVisit(*nextNode, time);
            }
        }
        node.setColor(BLACK);
        node.setFinish(time++);
    }

    std::vector<T> topologicalSort()
    {
        std::vector<T> sortedValues;
        sortedValues.reserve(allNodes.size());
        for (auto* node : topologicalSortNodes())
        {
            sortedValues.push_back(node->getValue());
        }
        return sortedValues;
    }
};

#endif // SIMPLE_GRAPH_GRAPH_H
