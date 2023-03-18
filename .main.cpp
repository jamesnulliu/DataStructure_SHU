#include <iostream>
#include <algorithm>
#include <vector>
#include "07_Graph/Graph_AM/Graph_AM.h"

using namespace std;

int main() {
    Graph_AM graph({ 'a','b','c','d' });
    graph.insertVertex('e');
    graph.insertEdge('a', 'b');
    graph.insertArc('b', 'c');
    graph.insertArc('b', 'd');
    graph.insertArc('b', 'e');
    graph.insertArc('d', 'b');
    graph.insertArc('d', 'a');
    graph.print_adjacencyMatrix();
    std::cout << std::endl;
    graph.eraseVertex('d');
    graph.print_adjacencyMatrix();
}