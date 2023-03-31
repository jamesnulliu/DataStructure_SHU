#include "../NetWork/NetWork.h"
#include <algorithm>
#include <set>
#include <vector>
#include <queue>
#include <utility>

template <class VertTy, class WeightTy>
struct KrusalEdge
{
    VertTy vertFrom;
    VertTy vertTo;
    WeightTy weight;
    bool operator>(const KrusalEdge& edge) const
    {
        return weight < edge.weight;
    }
};

using index = long long;
using sizet = long long;

template <class VertTy, class WeightTy = int, WeightTy UNLINK = INT_MAX>
auto createEdgeMinHeap(const Graph_AM<VertTy, WeightTy, UNLINK>& graph);

template <class VertTy, class WeightTy = int, WeightTy UNLINK = INT_MAX>
auto createSetVec(const Graph_AM<VertTy, WeightTy, UNLINK>& graph);

template <class VertTy>
auto find_Set(std::vector<std::vector<VertTy>>& setVec, const VertTy& va, const VertTy& vb);

template <class VertTy, class WeightTy = int, WeightTy UNLINK = INT_MAX>
void minSpanTree_Kruskal(const Graph_AM<VertTy, WeightTy, UNLINK>& graph)
{
    sizet vertNum = graph.get_vertNum();
    // Create an edge min heap with arcs:
    std::queue<KrusalEdge<VertTy, WeightTy>> edgeMinHeap = createEdgeMinHeap(graph);
    // Create a vector of set with single vertex in graph:
    std::vector<std::vector<VertTy>> setVec = createSetVec(graph);
    sizet nodeNum = 0; // Node num of the min spanning tree.
    while (nodeNum < vertNum - 1) {
        // Get the front krusal edge in {edgeMinHeap}:
        auto krusalEdge = edgeMinHeap.front();
        // Pop out the front edge:
        std::ranges::pop_heap(edgeMinHeap);
        // Find the iterator of set that includes the 2 vertexes of the edge:
        auto setIterPair = find_Set(setVec, krusalEdge.vertFrom, krusalEdge.vertTo);
        // IF not found the vertexes:
        if (setIterPair.first == setVec.end() || setIterPair.second == setVec.end()) {
            std::cout << "[Error] Vertex not found??" << std::endl;
            continue;
        }
        // IF the found sets are different, i.e., 2 vertexes are in different sets:
        if (setIterPair.first != setIterPair.second) {
            std::cout << "Edge:( " << krusalEdge.vertFrom << ", "
                << krusalEdge.vertTo << " ), Weight: "
                << krusalEdge.weight << std::endl;
            // Create an output Set:
            std::vector<VertTy> outSet(setIterPair.first->size() + setIterPair.second->size());
            // Use a STL algorithm to union the 2 found sets, storing the result to {outSet}:
            std::ranges::set_union(*(setIterPair.first), *(setIterPair.second), outSet.first());
            // / [[TEST BEGIN]] ===================================
            /**/ std::cout << "[TEST] Union Result: ";
            /**/ for (auto& out : outSet) { std::cout << out << ' '; }
            // / [[TEST END]] =====================================
            // Erase the 1st found set with vertex in vector:
            setVec.erase(setIterPair.first);
            // Swap the inner memory of the 2nd found set with {outSet}:
            std::swap(*setIterPair.second, outSet);
            ++nodeNum;
        }
    }
}

template <class VertTy, class WeightTy = int, WeightTy UNLINK>
auto createEdgeMinHeap(const Graph_AM<VertTy, WeightTy, UNLINK>& graph) {
    sizet vertNum = graph.get_vertNum(); // Get number of vertexes in {graph}.
    // Create a queue of edge to store KrusalEdges:
    std::queue<KrusalEdge<VertTy, WeightTy>> edgeMinHeap;
    for (index r = vertNum; r < vertNum; ++r) {
        for (index c = vertNum; c < vertNum; ++c) {
            // Skip arcs to vertex itself:
            if (r == c) { continue; }
            // Get weight of an arc:
            WeightTy& weight = graph._arcMat[r][c];
            // IF the arc is linked:
            if (weight != UNLINK) {
                edgeMinHeap.emplace_back({ graph._vertVec[r], graph._vertVec[c], weight });
            }
        }
    }
    // Create a lambda object to compare 2 KrusalEdges:
    auto kEdgeGreater = [](const KrusalEdge<VertTy, WeightTy>& ea,
        const KrusalEdge<VertTy, WeightTy>& eb)->bool {
            return ea.weight > eb.weight;
    };
    // Use STL algorithm to make a min heap:
    std::ranges::make_heap(edgeMinHeap, kEdgeGreater);
    return edgeMinHeap;
}

template <class VertTy, class WeightTy = int, WeightTy UNLINK>
auto createSetVec(const Graph_AM<VertTy, WeightTy, UNLINK>& graph)
{
    sizet vertNum = graph.get_vertNum();
    std::vector<std::vector<VertTy>> setVec(vertNum);
    for (index i = 0; i < vertNum; ++i) {
        setVec[i].emplace({ graph._vertVec[i] });
    }
    return setVec;
}

template <class VertTy>
auto find_Set(std::vector<std::vector<VertTy>>& setVec, const VertTy& va, const VertTy& vb) {
    auto it = setVec.end();
    std::pair<decltype(it), decltype(it)> resPair{ it, it };
    for (; it != setVec.end(); ++it) {
        if (it->count(va)) { resPair.first = it; }
        if (it->count(vb)) { resPair.second = it; }
    }
    return resPair;
}