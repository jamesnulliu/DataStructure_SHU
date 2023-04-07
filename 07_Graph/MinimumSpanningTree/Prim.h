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
std::unordered_map<VertTy, _CloseArc> closeArcs;

// Step 1. Initialize {closeArcs}
