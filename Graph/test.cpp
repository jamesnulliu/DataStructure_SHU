#include "Graph_AdjacencyMatrix/Graph_AM.h"
#include "Graph_Link/Graph_Link.h"
#include <iostream>
using namespace std;

int main1() {
    Graph_AM<> graph_AM({ 'a','b','c' });
    graph_AM.insertVertex('d');
    graph_AM.print_adjacencyMatrix();
    cout << graph_AM.edgeNum << endl;
    graph_AM.insertEdge('b', 'd');
    graph_AM.print_adjacencyMatrix();
    cout << graph_AM.edgeNum << endl;
    graph_AM.erase_edge('d', 'b');
    graph_AM.print_adjacencyMatrix();
    cout << graph_AM.edgeNum << endl;

    Graph_Link<> graph_link({ 'a','b','c' });
    graph_link.insertVertex('d');
    graph_link.print_vertTable();
    cout << "Vert num: " << graph_link.vertNum() << endl;
    cout << "Edge num: " << graph_link.edgeNum() << endl;
    graph_link.insertEdge('b', 'd');
    graph_link.insertEdge('a', 'd');
    graph_link.print_vertTable();
    cout << "Vert num: " << graph_link.vertNum() << endl;
    cout << "Edge num: " << graph_link.edgeNum() << endl;
    graph_link.erase_edge('b', 'd');
    graph_link.print_vertTable();
    cout << "Vert num: " << graph_link.vertNum() << endl;
    cout << "Edge num: " << graph_link.edgeNum() << endl;
    graph_link.insertEdge('a', 'c');
    graph_link.insertEdge('d', 'c');
    graph_link.print_vertTable();
    cout << "Vert num: " << graph_link.vertNum() << endl;
    cout << "Edge num: " << graph_link.edgeNum() << endl;
    graph_link.eraseVertex('a');
    graph_link.print_vertTable();
    cout << "Vert num: " << graph_link.vertNum() << endl;
    cout << "Edge num: " << graph_link.edgeNum() << endl;

    return 0;
}