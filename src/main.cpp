#include <iostream>
#include "Graph.h"

void test1();

void test2();

int main()
{
    test2();

    return 0;
}

void test2()
{
    Graph<std::string> graph;
    const auto A = "A";
    const auto B = "B";
    const auto C = "C";
    const auto D = "D";
    const auto E = "E";
    graph.addNode(A);
    graph.addNode(B);
    graph.addNode(C);
    graph.addNode(D);
    graph.addNode(E);

    graph.addEdge(A, B, 4);
    graph.addEdge(A, D, 5);
    graph.addEdge(B, C, 1);
    graph.addEdge(B, E, 6);
    graph.addEdge(C, A, 2);
    graph.addEdge(C, D, 3);
    graph.addEdge(D, E, 2);
    graph.addEdge(D, C, 1);
    graph.addEdge(E, A, 1);
    graph.addEdge(E, D, 4);

    graph.printFloydWarshall();
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
