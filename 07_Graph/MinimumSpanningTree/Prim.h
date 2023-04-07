#pragma once
#include "../Graph_AM/Graph_AM.h"
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <unordered_set>

/** Persudocode for prim algorithm (from GeeksforGeeks)
 * Step 1: Determine an arbitrary vertex as the starting vertex of the MST.
 * Step 2: Follow steps 3 to 5 till there are vertices that are not included in the MST (known as fringe vertex).
 * Step 3: Find edges connecting any tree vertex with the fringe vertices.
 * Step 4: Find the minimum among these edges.
 * Step 5: Add the chosen edge to the MST if it does not form any cycle.
 * Step 6: Return the MST and exit
 */

using sizet = long long;
using index = long long;

template<class VertTy, class WeightTy>
struct PrimEdge
{
    WeightTy weight;
    index vertFromI;
    index vertToI;
};

template<class VertTy, class WeightTy, WeightTy UNLINK>
void MinSpanningTree_Prim(const Graph_AM<VertTy, WeightTy, UNLINK>& graph, index startI) {
    sizet vertNum_graph = graph.get_vertNum();
    std::vector<bool> vIndexMap(vertNum_graph, false);  // Map of whether a vert has been added to MST
    sizet vertNum_mst = 0;

    if (vertNum_graph < 0 || startI < 0 || startI >= vertNum_graph) { throw "[ERROR]"; }

    vIndexMap[startI] = true;  // Add vertex at index {startI} to MST
    ++vertNum_mst;

    while (vertNum_mst < vertNum_graph) {
        PrimEdge<VertTy, WeightTy> minEdge{ UNLINK,{},{} };

        // Traverse {vIndexMap} with index iterator {vertFromI};
        // For every index that is marked as 'has been added to MST' (i.e., true in {vIndexMap}),
        // we need to scan through {graph._arcMat[vertFromI]} to check every existing edges
        // linked from vertex at index {vertFromI} to another vertex:
        // @{
        for (index vertFromI = 0; vertFromI < vertNum_graph; ++vertFromI) {
            // If the vertex at index {vertFromI} has not been added to MST, continue to next loop.
            if (vIndexMap[vertFromI] == 0) continue;
            // Use linear search to find the minimum edge:
            for (index vertToI = 0; vertToI < vertNum_graph; ++vertToI) {
                if (vIndexMap[vertToI] == true) continue;  // Continue to next loop if it forms a circle.
                if (minEdge.weight > graph._arcMat[vertFromI][vertToI]) {
                    minEdge.weight = graph._arcMat[vertFromI][vertToI];
                    minEdge.vertFromI = vertFromI;
                    minEdge.vertToI = vertToI;
                }
            }
        }
        // @}

        vIndexMap[minEdge.vertToI] = true;  // Add vertex at index {vertToI} to {vIndexMap}

        std::cout << "Edge: ("
            << graph._vertVec[minEdge.vertFromI] << ", "
            << graph._vertVec[minEdge.vertToI]
            << ") Weight: " << minEdge.weight << std::endl;

        ++vertNum_mst;
    }
}
