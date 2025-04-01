#ifndef SIMPLE_GRAPH_GRAPH_H
#define SIMPLE_GRAPH_GRAPH_H

#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <algorithm>
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

    void bfsPrint(const T& start)
    {
        auto nodeValues = bfs(start);
        std::cout << "BFS: start from " << start << std::endl << "\t";
        for (const auto& value : nodeValues)
        {
            std::cout << value << ", ";
        }
        std::cout << "\nEND BFS" << std::endl;
    }

    std::vector<T> bfs(const T& start)
    {
        auto startNode = getNode(start);
        if (startNode == nullptr)
        {
            return {};
        }
        std::unordered_set<Node<T>*> visited;
        std::queue<Node<T>*> q;

        q.push(startNode);
        visited.insert(startNode);

        std::vector<T> result;
        while (!q.empty())
        {
            auto current = q.front();
            q.pop();

            for (auto neighborValue : getNextNodes(current->getValue()))
            {
                auto neighbor = getNode(neighborValue);
                if (neighbor && visited.find(neighbor) == visited.end())
                {
                    q.push(neighbor);
                    visited.insert(neighbor);
                }
            }
            result.push_back(current->getValue());
        }
        return result;
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
