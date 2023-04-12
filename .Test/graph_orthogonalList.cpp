#include "../07_Graph/Graph_OrthogonalList/Graph_OrthogonalList.h"
#include <iostream>

void test_gol() {
    gol::Graph<> graph;
    graph.insertVert('A');
    std::cout << graph.findVertIndex('A');
    std::cout << graph.getVertByIndex(graph.findVertIndex('A'));
    graph.insertVert('B');
    std::cout << graph.findVertIndex('B');
    std::cout << graph.getVertByIndex(graph.findVertIndex('B'));

    return;
}