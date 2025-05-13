#ifndef SIMPLE_GRAPH_GRAPH_H
#define SIMPLE_GRAPH_GRAPH_H

#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <iostream>
#include <algorithm>
#include "Node.h"
#include "Edge.h"
#include "DisjointSets.h"

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

    std::vector<Edge<T, L>> mstKruskal()
    {
        auto mst = std::vector<Edge<T, L>>();
        for (auto& [_, node] : this->allNodes)
        {
            DisjointSets<T>::makeSet(&node);
        }
        auto edges = this->getAllEdges();
        std::sort(edges.begin(), edges.end(), [](const Edge<T, L>& e1, const Edge<T, L>& e2)
        {
            return e1.getLabel() < e2.getLabel();
        });

        for (const auto& edge : edges)
        {
            if
            (
                DisjointSets<T>::findSet(edge.getSource())->getValue() !=
                DisjointSets<T>::findSet(edge.getDestination())->getValue()
            )
            {
                mst.push_back(edge);
                DisjointSets<T>::unionSet(edge.getSource(), edge.getDestination());
            }
        }
        return mst;
    }

    std::vector<Edge<T, L>> getAllEdges()
    {
        auto allEdges = std::vector<Edge<T, L>>();
        for (const auto& [_, edges] : this->outEdges)
        {
            allEdges.insert(allEdges.end(), edges.begin(), edges.end());
        }
        return allEdges;
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

    std::vector<std::pair<T, T>> getMstKruskal()
    {
        auto edges = mstKruskal();
        std::vector<std::pair<T, T>> mst;
        for (const auto& edge : edges)
        {
            mst.emplace_back(std::make_pair(edge.getSource()->getValue(), edge.getDestination()->getValue()));
        }
        return mst;
    }
};

#endif // SIMPLE_GRAPH_GRAPH_H
