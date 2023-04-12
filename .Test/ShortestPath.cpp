#include "../07_Graph/Graph_AM/Graph_AM.h"
#include "../07_Graph/ShortestPath/Dijkstra.h"

void test_Dijkstra()
{
    Graph_AM<char, int, INT_MAX > graph({ 'A','B','C','D','E' });
    graph.insertArc('A', 'B', 10);
    graph.insertArc('A', 'D', 30);
    graph.insertArc('A', 'E', 100);
    graph.insertArc('B', 'C', 50);
    graph.insertArc('C', 'E', 10);
    graph.insertArc('D', 'E', 60);
    graph.insertArc('D', 'C', 20);
    graph.print_adjacencyMatrix();

    auto dists = dijkstra(graph, 0);
    for (auto i : dists) {
        std::cout << i << ' ';
    }
}