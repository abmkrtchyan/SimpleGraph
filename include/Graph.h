#ifndef SIMPLE_GRAPH_GRAPH_H
#define SIMPLE_GRAPH_GRAPH_H

#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <iostream>
#include <limits>
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

    std::unordered_map<T, std::unordered_map<T, L>> getInitMatrixForFloydWarshall()
    {
        const L INF = std::numeric_limits<L>::max();
        std::unordered_map<T, std::unordered_map<T, L>> dist;
        for (const auto& [u, _] : allNodes)
        {
            for (const auto& [v, _] : allNodes)
            {
                if (u == v)
                {
                    dist[u][v] = 0;
                }
                else
                {
                    dist[u][v] = INF;
                }
            }

            for (const auto& edge : outEdges[u])
            {
                dist[u][edge.getDestination()->getValue()] = edge.getLabel();
            }
        }
        return dist;
    }

    std::unordered_map<T, std::unordered_map<T, L>> floydWarshall()
    {
        std::unordered_map<T, std::unordered_map<T, L>> dist = getInitMatrixForFloydWarshall();

        const L INF = std::numeric_limits<L>::max(); // or const L INF = INT_MAX
        for (const auto& [k, _] : allNodes)
        {
            for (const auto& [i, _] : allNodes)
            {
                for (const auto& [j, _] : allNodes)
                {
                    if (dist[i][k] != INF && dist[k][j] != INF && dist[i][k] + dist[k][j] < dist[i][j])
                    {
                        dist[i][j] = dist[i][k] + dist[k][j];
                    }
                }
            }
        }

        return dist;
    }

    void printFloydWarshall()
    {
        auto dist = floydWarshall();
        const L INF = std::numeric_limits<L>::max();

        std::cout << "Floyd-Warshall distance matrix:\n";
        for (const auto& [i, row] : dist)
        {
            std::cout << i << ": ";
            for (const auto& [j, d] : row)
            {
                if (d == INF)
                    std::cout << j << "=INF ";
                else
                    std::cout << j << "=" << d << " ";
            }
            std::cout << "\n";
        }
    }
};

#endif // SIMPLE_GRAPH_GRAPH_H
