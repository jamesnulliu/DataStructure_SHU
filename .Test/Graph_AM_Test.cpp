#include "../07_Graph/Graph_AM/Graph_AM.h"
#include "Test.h"
#include <conio.h>

void Graph_AM_test() {
    puts("[TEST FOR UNDIRECTED GRAPH] ============= Part 1");
    Graph_AM<> graph;
    puts("Add 4 points: ");
    graph.insertVertex('a');
    graph.insertVertex('b');
    graph.insertVertex('c');
    graph.insertVertex('d');
    puts("Result: ");
    graph.print_adjacencyMatrix();
    puts("#");
    puts("Link a and d");
    graph.insertEdge('a', 'd');
    puts("Link b and c");
    graph.insertEdge('b', 'c');
    puts("Link d and c");
    graph.insertEdge('d', 'c');
    puts("Link a and b");
    graph.insertEdge('a', 'b');
    puts("Result: ");
    graph.print_adjacencyMatrix();
    puts("================================================");
    puts("Press Enter to continue");
    while (_getch() != 13);
    system("cls");

    puts("[TEST FOR UNDIRECTED GRAPH] ============= Part 2");
    puts("Erase edge of b and c");
    graph.eraseEdge('b', 'c');
    puts("Result: ");
    graph.print_adjacencyMatrix();
    puts("#");
    puts("Erase vertex a");
    graph.eraseVertex('a');
    puts("Result: ");
    graph.print_adjacencyMatrix();
    puts("================================================");
    puts("Press Enter to continue");
    while (_getch() != 13);
    system("cls");

    puts("[TEST FOR DIRECTED GRAPH] =============== Part 1");
    Graph_AM<> dgraph;
    puts("Add 4 points: ");
    dgraph.insertVertex('a');
    dgraph.insertVertex('b');
    dgraph.insertVertex('c');
    dgraph.insertVertex('d');
    puts("Result: ");
    dgraph.print_adjacencyMatrix();
    puts("#");
    puts("Link a and d");
    dgraph.insertArc('a', 'd');
    puts("Link b and c");
    dgraph.insertArc('b', 'c');
    puts("Link d and c");
    dgraph.insertArc('d', 'c');
    puts("Link a and b");
    dgraph.insertArc('a', 'b');
    puts("Result: ");
    dgraph.print_adjacencyMatrix();
    puts("================================================");
    puts("Press Enter to continue");
    while (_getch() != 13);
    system("cls");

    puts("[TEST FOR UNDIRECTED GRAPH] ============= Part 2");
    puts("Erase arc of b and c");
    dgraph.eraseArc('b', 'c');
    puts("Result: ");
    dgraph.print_adjacencyMatrix();
    puts("#");
    puts("Erase vertex a");
    dgraph.eraseVertex('a');
    puts("Result: ");
    dgraph.print_adjacencyMatrix();
    puts("================================================");
    puts("Press Enter to continue");
    while (_getch() != 13);
    system("cls");

}