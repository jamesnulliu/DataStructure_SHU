#include "../07_Graph/MinimumSpanningTree/Kruskal.h"

/**
 *       B -------+
 *   34 /          \12
 *     /  19    26  \ 
 *    A ---- F ----- E
 *    |  25 / \     /
 *  46|  +-+   |   /38
 *    | /    25|  /
 *    C ------ D +
 *        17
 */

using Network = Graph_AM<char, int, INT_MAX>;

inline Network createNetWork() {
    Network net({ 'A','B','C','D','E','F' });
    net.insertEdge('A', 'B', 34);
    net.insertEdge('A', 'C', 46);
    net.insertEdge('A', 'F', 19);
    net.insertEdge('B', 'E', 12);
    net.insertEdge('C', 'F', 25);
    net.insertEdge('C', 'D', 17);
    net.insertEdge('D', 'E', 38);
    net.insertEdge('F', 'D', 25);
    net.insertEdge('F', 'E', 26);
    net.print_adjacencyMatrix();
    return net;
}

void MinSpanningTree_test() {
    minSpanTree_Kruskal(createNetWork());
}
