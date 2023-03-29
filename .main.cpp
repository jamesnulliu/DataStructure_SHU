#include <iostream>
#include <algorithm>
#include <vector>
#include "07_Graph/Graph_AM/Graph_AM.h"
#include <ranges>

using namespace std;

//int main()
//{
//    Graph_AM graph({'a', 'b', 'c', 'd'});
//    graph.insertVertex('e');
//    graph.insertEdge('a', 'b');
//    graph.insertArc('b', 'c');
//    graph.insertArc('b', 'd', 10);
//    graph.insertEdge('b', 'e', 20);
//    graph.insertArc('d', 'b');
//    graph.insertArc('d', 'a');
//    graph.print_adjacencyMatrix();
//    graph.eraseVertex('d');
//    graph.print_adjacencyMatrix();
//    std::cout << graph.get_firstAdjVert('a') << std::endl;
//    std::cout << graph.get_weight('b','e')<<std::endl;
//    std::cout<<__cplusplus;
//}