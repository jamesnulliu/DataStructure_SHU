#include "Graph.h"
#include "../Graph_OrthogonalList/Graph_OrthogonalList.h"
#include <queue>
#include <stack>

using namespace std;
using Index = long long;
using Sizet = long long;

template<class VertDataTy>
bool topologicalSorting_Kahn(Graph<VertDataTy>& graph, queue<VertDataTy>& result) {
    result = {};
    queue<Index> zeroIndegreeVertI_que = {};
    for (Index i = 0; i < graph._vertNum(); ++i) {
        if (graph.getIndegreeR(i) == 0) { zeroIndegreeVertI_que.push(i); }
    }
    while (!zeroIndegreeVertI_que.empty()) {
        Index curVertI = zeroIndegreeVertI_que.front(); zeroIndegreeVertI_que.pop();
        result.push(graph.getDataR(curVertI));
        for (Index linkedI : graph.getAdjListR(curVertI)) {
            --graph.getIndegreeR(linkedI);
            if (graph.getIndegreeR(linkedI) == 0) {
                zeroIndegreeVertI_que.push(linkedI);
            }
        }
    }
    if (result.size() == graph._vertNum()) return true;
    else return false;
}

template<class VertDataTy>
bool topologicalSorting_DFS(Graph<VertDataTy>& graph, stack<VertDataTy>& result) {
    result = {};
    vector<bool> isAddedToResult(graph._vertNum(), false);
    vector<bool> isUnderRecursion(graph._vertNum(), false);
    try {
        for (Index i = 0; i < graph._vertNum(); ++i) {
            if (isAddedToResult[i] == false) {
                visit_DFS(graph, i, result, isAddedToResult, isUnderRecursion);
            }
        }
    } catch (int status) {
        if (status == 1) { result = {}; return false; }
    }
    return true;
}

template<class VertDataTy>
void visit_DFS(Graph<VertDataTy>& graph, Index vertI, stack<VertDataTy>& result,
    vector<bool>& isAddedToResult, vector<bool>& isUnderRecursion) {
    if (isAddedToResult[vertI] == true) return;
    if (isUnderRecursion[vertI] == true) throw 1;
    isUnderRecursion[vertI] = true;
    for (Index linkedI : graph.getAdjListR(vertI)) {
        visit_DFS(graph, linkedI, result, isAddedToResult, isUnderRecursion);
    }
    isUnderRecursion[vertI] = false;
    result.push(graph.getDataR(vertI));
    isAddedToResult[vertI] = true;
}

// =================== TEST =====================
#include <iostream>

void solve() {
    ////Graph<> g(4);
    ////g.setData(0, 'a'); g.setData(1, 'b'); g.setData(2, 'c'); g.setData(3, 'd');
    ////g.addEdge(0, 1); g.addEdge(2, 1); g.addEdge(3, 2);
    ////queue<char> result_Kahn;
    ////if (topologicalSorting_Kahn(g, result_Kahn) == true) {
    ////    while (!result_Kahn.empty()) {
    ////        printf("%c < ", result_Kahn.front());
    ////        result_Kahn.pop();
    ////    }
    ////    printf("\b\b ");
    ////} else { puts("Impossible."); }
    ////stack<char> result_DFS;
    ////if (topologicalSorting_DFS(g, result_DFS) == true) {
    ////    while (!result_DFS.empty()) {
    ////        printf("%c < ", result_DFS.top());
    ////        result_DFS.pop();
    ////    }
    ////    printf("\b\b ");
    ////} else { puts("Impossible."); }
}

namespace GOL {
    void visit_DFS(GOL::Graph<char, int, 0>& graph, Index vertI, stack<char>& result,
        vector<bool>& isAddedToResult, vector<bool>& isUnderRecursion);

    bool topologicalSorting_DFS(GOL::Graph<char, int, 0>& graph, stack<char>& result) {
        result = {};
        vector<bool> isAddedToResult(graph.vertNum(), false);
        vector<bool> isUnderRecursion(graph.vertNum(), false);
        try {
            for (Index i = 0; i < graph.vertNum(); ++i) {
                if (isAddedToResult[i] == false) {
                    GOL::visit_DFS(graph, i, result, isAddedToResult, isUnderRecursion);
                }
            }
        } catch (int status) {
            if (status == 1) { result = {}; return false; }
        }
        return true;
    }

    void visit_DFS(GOL::Graph<char, int, 0>& graph, Index vertI, stack<char>& result,
        vector<bool>& isAddedToResult, vector<bool>& isUnderRecursion) {
        if (isAddedToResult[vertI] == true) return;
        if (isUnderRecursion[vertI] == true) throw 1;
        isUnderRecursion[vertI] = true;
        for (Index linkedI : graph.getOutIndexes(vertI)) {
            visit_DFS(graph, linkedI, result, isAddedToResult, isUnderRecursion);
        }
        isUnderRecursion[vertI] = false;
        result.push(graph.getVertByIndex(vertI));
        isAddedToResult[vertI] = true;
    }
}
void test_topological() {
    GOL::Graph<char, int, 0> g;
    g.insertVert('a');
    g.insertVert('b');
    g.insertVert('c');
    g.insertVert('d');

    g.insertArcByIndex(0, 1, 1);
    g.insertArcByIndex(2, 1, 1);
    g.insertArcByIndex(3, 2, 1);

    stack<char> result_DFS;
    if (GOL::topologicalSorting_DFS(g, result_DFS) == true) {
        while (!result_DFS.empty()) {
            printf("%c < ", result_DFS.top());
            result_DFS.pop();
        }
        printf("\b\b ");
    } else { puts("Impossible."); }
}

void printDate() {
}