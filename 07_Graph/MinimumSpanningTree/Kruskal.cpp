#include "../Graph_AM/Graph_AM.h"
#include <algorithm>
#include <set>
#include <vector>
#include <queue>
#include <utility>

template <class VertTy, class WeightTy>
struct KrusalEdge
{
    VertTy vertFrom;  // Where
    VertTy vertTo;
    WeightTy weight;
};

using index = long long;
using sizet = long long;

// Declearations:

// @brief Create an min heap of edges. The edges are all from param {graph}.
template <class VertTy, class WeightTy = int, WeightTy UNLINK>
auto createEdgeMinHeap(const Graph_AM<VertTy, WeightTy, UNLINK>& graph) -> std::queue<KrusalEdge<VertTy, WeightTy>>;

// @brief Create a vector of sets. Initially, each sets only contains one vertex. All vertexes are from param {graph}.
template <class VertTy, class WeightTy = int, WeightTy UNLINK>
auto createSet(const Graph_AM<VertTy, WeightTy, UNLINK>& graph) -> std::vector<std::set<VertTy>>;

// @brief Find a pair of iterators, saperately pointing to the set {va} is in and set {vb} is in;
//        The two sets are both in param {setVec}.
// @return A pair of iterators of sets of {va} and {vb}, or {setVec.end()} if not found.
template <class VertTy>
auto find_Set(std::vector<std::set<VertTy>>& setVec, const VertTy& va, const VertTy& vb)
-> std::pair<typename std::vector<std::set<VertTy>>::iterator, typename std::vector<std::set<VertTy>>::iterator>;

template <class VertTy, class WeightTy = int, WeightTy UNLINK>
void minSpanTree_Kruskal(const Graph_AM<VertTy, WeightTy, UNLINK>& graph)
{
    sizet vertNum = graph.get_vertNum();  // Number of vertexes in {graph}

    std::queue<KrusalEdge<VertTy, WeightTy>>
        edgeMinHeap = createEdgeMinHeap(graph);  // Min heap of edges

    std::vector<std::set<VertTy>> setVec = createSet(graph); // Vector of sets with single vertex:

    sizet nodeNum = 0; // Node num of the min spanning tree.

    while (nodeNum < vertNum - 1) {
        // Get the front krusal edge (i.e., the one with the least weight) in {edgeMinHeap}:
        auto krusalEdge = edgeMinHeap.front();

        // Pop out the front edge:
        std::ranges::pop_heap(edgeMinHeap);

        // Now we have an edge with the min weight,
        // there is two vertexes that connect to that edge.
        // We need to find the set the two vertexes in.

        // A pair of iterators saperately points to the two sets of the connected vertexes
        auto setIterPair = find_Set(setVec, krusalEdge.vertFrom, krusalEdge.vertTo);

        // IF not found the vertexes:
        if (setIterPair.first == setVec.end() || setIterPair.second == setVec.end()) {
            std::cout << "[Error] Vertex not found?? You should not be here!" << std::endl;
            continue;
        }

        // IF the found sets are different, i.e., 2 vertexes are in different sets:
        if (setIterPair.first != setIterPair.second) {
            // Print what edges we have choosen:
            std::cout << "Choose Edge:( " << krusalEdge.vertFrom << ", "
                << krusalEdge.vertTo << " ), Weight: "
                << krusalEdge.weight << std::endl;

            // Create an output set:
            std::vector<VertTy> outSet(setIterPair.first->size() + setIterPair.second->size());

            // Union the 2 found sets, and store the result to {outSet}:
            std::ranges::set_union(*(setIterPair.first), *(setIterPair.second), outSet.first());

            // Print unioned set:
            std::cout << "[TEST] Union Result: ";
            for (auto& out : outSet) { std::cout << out << ' '; }

            // Erase the 1st found set with vertex in vector:
            setVec.erase(setIterPair.first);

            // Swap the inner memory of the 2nd found set with {outSet}:
            std::swap(*setIterPair.second, outSet);

            ++nodeNum;  // Update num of nodes in the min spanning tree
        }
    }
}

template <class VertTy, class WeightTy = int, WeightTy UNLINK>
auto createEdgeMinHeap(const Graph_AM<VertTy, WeightTy, UNLINK>& graph) -> std::queue<KrusalEdge<VertTy, WeightTy>>
{
    sizet vertNum = graph.get_vertNum();                   // Number of vertexes in {graph}
    std::queue<KrusalEdge<VertTy, WeightTy>> edgeMinHeap;  // A queue of edges to store KrusalEdges

    // For every arc in adjacent mat:
    for (index r = vertNum; r < vertNum; ++r) {
        for (index c = vertNum; c < vertNum; ++c) {
            if (r == c) { continue; }  // Skip if arc is to oneself
            // IF the arc is linked:
            if (graph.get_weight_loc(r, c) != UNLINK) {
                // Add the edge to {edgeMinHeap}:
                edgeMinHeap.emplace_back(
                    { graph._vertVec[r], graph._vertVec[c], graph.get_weight_loc(r, c) }  // List-initialization
                );
            }
        }
    }

    // A lambda expression to compare 2 KrusalEdges:
    auto kEdgeGreater = [](
        const KrusalEdge<VertTy, WeightTy>& ea,
        const KrusalEdge<VertTy, WeightTy>& eb
        )->bool { return ea.weight > eb.weight; };  // Only compare weight

    // Use STL algorithm to make a min heap:
    std::ranges::make_heap(edgeMinHeap, kEdgeGreater);

    return edgeMinHeap;
}

template <class VertTy, class WeightTy = int, WeightTy UNLINK>
auto createSet(const Graph_AM<VertTy, WeightTy, UNLINK>& graph) -> std::vector<std::set<VertTy>>
{
    sizet vertNum = graph.get_vertNum();            // Number of vertexes in {graph}
    std::vector<std::set<VertTy>> setVec(vertNum);  // A vector contains all different sets
    for (index i = 0; i < vertNum; ++i) {
        std::set<VertTy> s;
        s.insert(graph._vertVec[i]);
        setVec[i].emplace(std::move(s));            // Make each vertex a set
    }
    return setVec;
}

template <class VertTy>
auto find_Set(std::vector<std::vector<VertTy>>& setVec, const VertTy& va, const VertTy& vb)
-> std::pair<typename std::vector<std::set<VertTy>>::iterator, typename std::vector<std::set<VertTy>>::iterator>
{
    typename std::vector<std::set<VertTy>>::iterator it = setVec.end();
    std::pair<decltype(it), decltype(it)> resPair{ it, it };
    for (it = setVec.begin(); it != setVec.end(); ++it) {
        // IF {va} is found in set {*it}:
        if (it->count(va)) { resPair.first = it; }
        // IF {vb} is found in set {*it}:
        if (it->count(vb)) { resPair.second = it; }
    }
    return resPair;
}