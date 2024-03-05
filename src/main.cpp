#include <iostream>
#include "Graph.h"

void test1();

void test2();

void test3();

int main() {
    test3();

    return 0;
}

void test2() {
    Graph<std::string> graph;
    graph.addVertex("A");
    graph.addVertex("B");
    graph.addVertex("C");
    graph.addVertex("D");
    graph.addVertex("E");

    graph.addEdge("A", "B", 1);
    graph.addEdge("A", "C", 1);
    graph.addEdge("A", "D", 1);
    graph.addEdge("A", "E", 1);
    std::cout << std::endl;
    graph.dijkstra("A");
}

void test1() {
    Graph<int, int> graph;

    graph.addVertex(1);
    graph.addVertex(2);
    graph.addVertex(3);
    graph.addVertex(4);
    graph.addVertex(7);
    graph.addVertex(9);
    graph.addVertex(11);

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
    for (const auto &node: graph.getAllNodes()) {
        std::cout << "Node: " << node << std::endl;
    }
}

void test3() {
    Graph<std::string, int> graph;

    graph.addVertex("A");
    graph.addVertex("B");
    graph.addVertex("C");
    graph.addVertex("D");
    graph.addVertex("E");
    graph.addVertex("F");

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
}
