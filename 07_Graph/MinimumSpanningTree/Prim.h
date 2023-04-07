#pragma once
#include "../Graph_AM/Graph_AM.h"
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <unordered_set>

/**
 * Step 1: Determine an arbitrary vertex as the starting vertex of the MST.
 * Step 2: Follow steps 3 to 5 till there are vertices that are not included in the MST (known as fringe vertex).
 * Step 3: Find edges connecting any tree vertex with the fringe vertices.
 * Step 4: Find the minimum among these edges.
 * Step 5: Add the chosen edge to the MST if it does not form any cycle.
 * Step 6: Return the MST and exit
 */

using sizet = long long;
using index = long long;

template<class WeightTy, WeightTy UNLINK = INT_MAX>
struct _CloseArc
{
    WeightTy lowWeight = UNLINK;  // lowWeight = UNLINK: Arc selected.
    index nearVert = 0;
};

/**
 * @brief
 * @tparam VertTy
 * @tparam WeightTy
 * @tparam UNLINK
 * @param graph
*/
template<class VertTy, class WeightTy, WeightTy UNLINK = INT_MAX>
void MinSpanningTree_Prim(const Graph_AM<VertTy, WeightTy, UNLINK>& graph, const VertTy& startVert) {
    index startVertIndex = graph.get_vertIndex(startVert);
    if (startVertIndex >= graph._vertNum) {
        throw "[Failed] Vertex Not Found!";
    }

    // Step 1. Initialize {closeArcs}.
    std::vector<_CloseArc> closeArcs;
    for (int j = 0; j < graph._vertNum; j++) {
        closeArcs[j] = _CloseArc{ graph._arcMat[startVertIndex][j], startVertIndex };
    }

    // Step 2. Select {graph._vertNum - 1} arcs.
    for (int k = 1; k < graph._vertNum; k++) {
        // Step 3. Find the vertex connected to {startVert} that has the lowest weight
        WeightTy minWeight = UNLINK;
        index minAdjVertIndex = startVertIndex;
        for (int i = 0; i < graph._vertNum; i++) {
            if (closeArcs[i].lowWeight != UNLINK && closeArcs[i].lowWeight < ) {
                minWeight = closeArcs[i].lowWeight;
                minAdjVertIndex = i;
            }
        }
        if (minAdjVertIndex != startVertIndex) {
            VertTy vert1 = graph._vertVec[closeArcs[minAdjVertIndex].nearVert];
            VertTy vert2 = graph._vertVec[minAdjVertIndex];
            std::cout << "[TEST] Choose Edge:( " << vert1 << ", "
                << vert2 << " ), Weight: "
                << graph._arcMat[vert1][vert2] << std::endl;
            closeArcs[minAdjVertIndex].lowWeight = 0;
            for (int i = 0; i < graph._vertNum; i++) {
                if (i != startVertIndex && graph._arcMat[startVertIndex][i] != UNLINK) {
                    if (closeArcs[i].lowWeight != 0 && graph._arcMat[minAdjVertIndex][i] < closeArcs[i].lowWeight) {
                        closeArcs[i] = _CloseArc{ graph._arcMat[minAdjVertIndex][i], minAdjVertIndex };
                    }
                }
            }
        }
    }
}