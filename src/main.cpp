#include <iostream>
#include "Graph.h"

void test1();

void test2();

int main()
{
    test1();
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

    graph.addEdge(A, B, 3);
    graph.addEdge(A, C, 8);
    graph.addEdge(A, E, -4);
    graph.addEdge(B, D, 1);
    graph.addEdge(B, E, 7);
    graph.addEdge(C, B, 4);
    graph.addEdge(D, C, -5);
    graph.addEdge(D, A, 2);
    graph.addEdge(E, D, 6);

    graph.printFloydWarshall();
}
