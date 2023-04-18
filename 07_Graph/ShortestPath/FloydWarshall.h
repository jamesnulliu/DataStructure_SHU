#pragma once
#include "../Graph_AM/Graph_AM.h"
#include <vector>
#include <deque>
#include <algorithm>
#include <unordered_set>

using Index = long long;
using Size = long long;

template<class VertTy, class WeightTy, WeightTy INF>
void folydwarshall(const Graph_AM<VertTy, WeightTy, INF>& graph) {
    std::vector<std::vector<WeightTy>> shortestPath = graph._arcMat;
    Size vertNum = graph.get_vertNum();

    for (Index k = 0; k < vertNum; ++k) {
        for (Index i = 0; i < vertNum; ++i) {
            for (Index j = 0; j < vertNum; ++j) {
                if (shortestPath[i][k] != INF && shortestPath[k][j] != INF &&
                    shortestPath[i][j] > shortestPath[i][k] + shortestPath[k][j]) {
                    shortestPath[i][j] = shortestPath[i][k] + shortestPath[k][j];
                }
            }
        }
    }
}
