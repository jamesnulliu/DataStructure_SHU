#include "Graph_AdjacencyMatrix/Graph_AM.h"
#include "Graph_Link/Graph_Link.h"
#include <iostream>
using namespace std;

int main1() {
    Graph_AM<> graph_AM({'a','b','c'});
    graph_AM.insert_vertex('d');
    graph_AM.print_adjacencyMatrix();
    cout << graph_AM.m_edgeNum << endl;
    graph_AM.insert_edge('b', 'd');
    graph_AM.print_adjacencyMatrix();
    cout << graph_AM.m_edgeNum << endl;
    graph_AM.erase_edge('d', 'b');
    graph_AM.print_adjacencyMatrix();
    cout << graph_AM.m_edgeNum << endl;

    Graph_Link<> graph_link({'a','b','c'});
    graph_link.insert_vertex('d');
    graph_link.print_vertTable();
    cout << "Vert num: " << graph_link.vertNum() << endl;
    cout << "Edge num: " << graph_link.edgeNum() << endl;
    graph_link.insert_edge('b', 'd');
    graph_link.insert_edge('a', 'd');
    graph_link.print_vertTable();
    cout << "Vert num: " << graph_link.vertNum() << endl;
    cout << "Edge num: " << graph_link.edgeNum() << endl;
    graph_link.erase_edge('b', 'd');
    graph_link.print_vertTable();
    cout << "Vert num: " << graph_link.vertNum() << endl;
    cout << "Edge num: " << graph_link.edgeNum() << endl;
    graph_link.insert_edge('a', 'c');
    graph_link.insert_edge('d', 'c');
    graph_link.print_vertTable();
    cout << "Vert num: " << graph_link.vertNum() << endl;
    cout << "Edge num: " << graph_link.edgeNum() << endl;
    graph_link.erase_vertex('a');
    graph_link.print_vertTable();
    cout << "Vert num: " << graph_link.vertNum() << endl;
    cout << "Edge num: " << graph_link.edgeNum() << endl;

    return 0;
}