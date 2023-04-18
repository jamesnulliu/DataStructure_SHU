#pragma once
#include "../Graph_AM/Graph_AM.h"
#include <algorithm>
#include <set>
#include <vector>
#include <deque>
#include <utility>

template <class VertDataTy, class WeightTy>
struct KruskalEdge
{
    VertDataTy vertFrom;
    VertDataTy vertTo;
    WeightTy weight;
};

using index = long long;
using sizet = long long;

// @brief [Tool] Create an min heap of edges. The edges are all from param {graph}.
template <class VertDataTy, class WeightTy, WeightTy UNLINK>
auto createEdgeMinHeap(const Graph_AM<VertDataTy, WeightTy, UNLINK>& graph) -> std::deque<KruskalEdge<VertDataTy, WeightTy>>
{
    sizet vertNum = graph.get_vertNum();                   // Number of vertexes in {graph}
    std::deque<KruskalEdge<VertDataTy, WeightTy>> edgeMinHeap;  // A queue of edges to store KruskalEdges

    // For every arc in adjacent mat:
    for (index r = 0; r < vertNum; ++r) {
        for (index c = 0; c < r; ++c) {
            ////if (r == c) { continue; }  // Skip if arc is to oneself
            // IF the arc is linked:
            if (graph.get_weight_loc(r, c) != UNLINK) {
                // Add the edge to {edgeMinHeap}:
                edgeMinHeap.push_back(
                    KruskalEdge<VertDataTy, WeightTy>{ graph._vertVec[r], graph._vertVec[c], graph.get_weight_loc(r, c) }
                );
            }
        }
    }

    // Use STL algorithm to make a min heap:
    std::ranges::make_heap(edgeMinHeap, std::greater<>{}, & KruskalEdge<VertDataTy, WeightTy>::weight);

    return edgeMinHeap;
}

// @brief [Tool] Create a vector of sets. Initially, each sets only contains one vertex. All vertexes are from param {graph}.
template <class VertDataTy, class WeightTy, WeightTy UNLINK>
auto createSet(const Graph_AM<VertDataTy, WeightTy, UNLINK>& graph) -> std::vector<std::set<VertDataTy>>
{
    std::vector<std::set<VertDataTy>> setVec{};  // A vector contains all different sets
    for (auto& vert : graph._vertVec) {
        setVec.push_back(std::set<VertDataTy>{vert});
        // [Issue] Why can't following code work?
        ////setVec.emplace_back({ vert });
    }
    return setVec;
}

// @brief [Tool] Find a pair of iterators, saperately pointing to the set where {va} is in and the set where {vb} is in;
//        The two sets are both in param {setVec}.
// @return A pair of iterators of sets of {va} and {vb}, or {setVec.end()} if not found.
template <class VertDataTy>
auto find_Set(std::vector<std::set<VertDataTy>>& setVec, const VertDataTy& va, const VertDataTy& vb)
-> std::pair<typename std::vector<std::set<VertDataTy>>::iterator, typename std::vector<std::set<VertDataTy>>::iterator>
{
    std::pair<typename std::vector<std::set<VertDataTy>>::iterator, typename std::vector<std::set<VertDataTy>>::iterator>
        resPair{};
    for (auto it = setVec.begin(); it != setVec.end(); ++it) {
        // IF {va} is found in set {*it}:
        if (it->count(va)) { resPair.first = it; }
        // IF {vb} is found in set {*it}:
        if (it->count(vb)) { resPair.second = it; }
    }
    return resPair;
}

// @brief Create a minimum spanning tree with input graph.
// @param graph A network with weighted edge
template <class VertDataTy, class WeightTy, WeightTy UNLINK>
auto minSpanTree_Kruskal(const Graph_AM<VertDataTy, WeightTy, UNLINK>& graph) -> std::vector<std::set<VertDataTy>>
{
    sizet vertNum = graph.get_vertNum();  // Number of vertexes in {graph}

    std::deque<KruskalEdge<VertDataTy, WeightTy>>
        edgeMinHeap = createEdgeMinHeap(graph);  // Min heap of edges

    std::vector<std::set<VertDataTy>> setVec = createSet(graph); // Vector of sets with single vertex:

    sizet nodeNum = 0; // Node num of the min spanning tree.

    while (nodeNum < vertNum - 1) {
        // Get the front krusal edge (i.e., the one with the least weight) in {edgeMinHeap}:
        KruskalEdge<VertDataTy, WeightTy> krusalEdge = edgeMinHeap.front();

        // Pop out the front edge:
        std::ranges::pop_heap(edgeMinHeap, std::greater<>{}, & KruskalEdge<VertDataTy, WeightTy>::weight);
        edgeMinHeap.pop_back();

        // Now we have an edge with the min weight,
        // there is two vertexes that connect to that edge.
        // We need to find the set the two vertexes in.

        // A pair of iterators saperately points to the two sets of the connected vertexes
        auto setIterPair{ find_Set(setVec, krusalEdge.vertFrom, krusalEdge.vertTo) };

        // IF vertexes not found:
        if (setIterPair.first == setVec.end() || setIterPair.second == setVec.end()) {
            std::cout << "[Error] Vertex not found?? You should not be here!" << std::endl;
            continue;
        }

        // IF the found sets are different, i.e., 2 vertexes are in different sets:
        if (setIterPair.first != setIterPair.second) {
            // Print what edges we have choosen:
            std::cout << "[TEST] Choose Edge:( " << krusalEdge.vertFrom << ", "
                << krusalEdge.vertTo << " ), Weight: "
                << krusalEdge.weight << std::endl;

            // Create an output set:
            std::vector<VertDataTy> outSet{};

            // Union the 2 found sets, and store the result to {outSet}:
            std::ranges::set_union(*(setIterPair.first), *(setIterPair.second), std::back_inserter(outSet));

            // Print unioned set:
            std::cout << "[TEST] Union Result: ";
            for (auto& out : outSet) { std::cout << out << ' '; }
            puts("");

            // Erase the 1st found set with vertex in vector:
            if (setIterPair.first - setIterPair.second > 0) {
                *(setIterPair.second) = std::set<VertDataTy>(outSet.begin(), outSet.end());
                setVec.erase(setIterPair.first);
            } else {
                *(setIterPair.first) = std::set<VertDataTy>(outSet.begin(), outSet.end());
                setVec.erase(setIterPair.second);
            }
            // Memory of {outSet} would be automatically released.

            ++nodeNum;  // Update num of nodes in the min spanning tree
        }
    }
    return setVec;
}
