#include <iostream>
#include "Graph.h"

void test1();

void test2();

void test3();

int main() {
    test3();

    return 0;
}

void test2()
{
    Graph<std::string> graph;
    graph.addNode("A");
    graph.addNode("B");
    graph.addNode("C");
    graph.addNode("D");
    graph.addNode("E");

    graph.addEdge("A", "B", 1);
    graph.addEdge("A", "C", 1);
    graph.addEdge("A", "D", 1);
    graph.addEdge("A", "E", 1);
    std::cout << std::endl;
    graph.dijkstra("A");
}

void test1()
{
    Graph<int, int> graph;

    graph.addNode(1);
    graph.addNode(2);
    graph.addNode(3);
    graph.addNode(4);
    graph.addNode(7);
    graph.addNode(9);
    graph.addNode(11);

    graph.addEdge(1, 2, 1);
    graph.addEdge(1, 3, 1);
    graph.addEdge(2, 3, 1);
    graph.addEdge(2, 11, 1);
    graph.addEdge(3, 4, 1);
    graph.addEdge(4, 7, 1);
    graph.addEdge(7, 9, 1);
    graph.addEdge(9, 11, 1);
    graph.addEdge(11, 1, 1);

    std::cout << "Graph:" << std::endl;
    for (const auto& node : graph.getAllNodes())
    {
        std::cout << "\t" << node << " -> ";
        for (const auto& next : graph.getNextNodes(node))
        {
            std::cout << next << ", ";
        }
        std::cout << "/" << std::endl;
    }
}

void test3() {
    Graph<std::string, int> graph;

    graph.addNode("A");
    graph.addNode("B");
    graph.addNode("C");
    graph.addNode("D");
    graph.addNode("E");
    graph.addNode("F");

    graph.addEdge("A", "B", 9);
    graph.addEdge("A", "E", 1);
    graph.addEdge("A", "D", 8);
    graph.addEdge("B", "C", 4);
    graph.addEdge("D", "C", 3);
    graph.addEdge("E", "F", 2);
    graph.addEdge("E", "D", 2);
    graph.addEdge("F", "B", 3);

    std::cout << "Graph:" << std::endl;
    graph.dijkstra("A");
    graph.printAllDijkstraNodes();

    for (const auto& path: graph.getShortestPaths("A")) {
        for (const auto& node: path) {
            std::cout << node << " -> ";
        }
        std::cout << "/" << std::endl;
    }
}
