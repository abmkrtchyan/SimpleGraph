#include <iostream>
#include "Graph.h"

void test1();

void test2();

int main() {

    test1();

    test2();

    return 0;
}

void test2() {
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
}

void test1() {
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
    for (const auto &node: graph.getAllNodes()) {
        std::cout << "Node: " << node << std::endl;
    }
    std::cout << "____________________DFS_______________" << std::endl;
    graph.dfs();
    std::cout << "________________DFS_FINISH____________" << std::endl;

}
