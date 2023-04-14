#pragma once
#include "../Graph_AM/Graph_AM.h"
#include <vector>
#include <deque>
#include <algorithm>
#include <unordered_set>

using index = long long;
using sizet = long long;

template<class VertDataTy, class WeightTy, WeightTy INF>
auto dijkstra(const Graph_AM<VertDataTy, WeightTy, INF>& graph, index sourceI) -> std::vector<WeightTy> {
    // Initialize distances to all nodes as infinity, except for the source node.
    std::vector<WeightTy> dists(graph._vertVec.size(), INF);
    dists[sourceI] = 0;

    // Initialize an empty set of visited nodes and a priority queue to keep track of the nodes to visit.
    std::unordered_set<index> visited{};
    std::vector<std::pair<index, WeightTy>> que{};
    que.push_back(std::make_pair(sourceI, 0));

    auto popMinHeap =
        [](const std::pair<index, WeightTy>& lhs, const std::pair<index, WeightTy>& rhs) -> bool {
        return lhs.second > rhs.second;
    };

    // Loop until all nodes have been visited.
    while (!que.empty()) {
        std::ranges::pop_heap(que, popMinHeap);
        auto current = que.back();
        que.pop_back();

        // If the node has already been visited, skip it:
        // [O(V) for search]
        if (visited.count(current.first)) {
            continue;
        }
        // Else the node has not, mark it as visited:
        // [O(V) for insert]
        else {
            visited.insert(current.first);
        }

        // Check all neighbor nodes to see if their distances need to be updated:
        // [O(V) for iteration]
        for (index neighbor = 0; neighbor < graph._vertVec.size(); ++neighbor) {
            if (neighbor == current.first) continue;
            if (graph._arcMat[current.first][neighbor] == INF) continue;

            // Calculate the tentative distance to the neighbor through the current node.
            WeightTy tempDist = dists[current.first] + graph._arcMat[current.first][neighbor];

            // If the tentative distance is smaller than the current distance to the neighbor, update the distance.
            if (tempDist < dists[neighbor]) {
                dists[neighbor] = tempDist;

                // Push the neighbor to queue with its new distance to be considered for visitation in the future.
                // [Note] A vertex may be pushed to the priority queue multiply times with different distances.
                //        When pop queue, we will get the one with minimum distance, and mark the vertex 'visited';
                //        So when we get the vertex again, it will be skipped.
                que.push_back(std::make_pair(neighbor, dists[neighbor]));
                // [O(logE) for push once]
                std::ranges::push_heap(que, popMinHeap);
            }
        }
    }
    return dists;
}
