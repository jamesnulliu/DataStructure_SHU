#pragma once
#include "../Graph_AM/Graph_AM.h"
#include <vector>
#include <deque>
#include <algorithm>
#include <unordered_set>

using index = long long;
using sizet = long long;

namespace sj {
    template<class VertDataTy, class WeightTy, WeightTy INF>
    auto dijkstra(const Graph_AM<VertDataTy, WeightTy, INF>& graph, index srcVertIndex,
        std::vector<index>& prev, std::vector<WeightTy>& dists)
    {
        WeightTy curMinDist{};
        std::vector<bool> visited(graph._vertVec.size(), false);
        sizet vertNum = graph.get_vertNum();
        prev.resize(vertNum, {});
        dists.resize(vertNum, {});
        // Initialize the distance vector and the previous node vector.
        for (index vIndex = 0; vIndex < vertNum; ++vIndex) {
            dists[v] = graph.get_weight_loc(srcVertIndex, vIndex);
            if (dists[v] == INF) {
                prev[v] = -1;
            } else {
                prev[v] = srcVertIndex;
            }
        }
        // Mark the source node as visited.
        visited[srcVertIndex] = true;
        // Loop until all nodes have been visited.
        for (sizet i = 0; i < vertNum - 1; ++i) {
            curMinDist = INF;
            index curMinDistVertIndex = -1;
            // Get the node with current smallest distance by Linear Search.
            for (index vIndex = 0; vIndex < vertNum; ++vIndex) {
                // Only check the nodes that have not been visited.
                if (visited[vIndex] == false && dists[vIndex] < curMinDist) {
                    curMinDist = dists[vIndex];
                    curMinDistVertIndex = vIndex;
                }
            }
            // If no node can be found, break the loop.
            if (curMinDistVertIndex == -1) { continue; }
            // Mark the found node as visited.
            visited[curMinDistVertIndex] = true;
            // Update the distance vector and the previous node vector.
            for (index vIndex = 0; vIndex < vertNum; ++vIndex) {
                // If the node has been visited or there is no edge between the two nodes, skip it.
                if (visited[vIndex] == true || graph.get_weight_loc(curMinDistVertIndex, vIndex) == INF) { continue; }
                WeightTy newDist = curMinDist + graph.get_weight_loc(curMinDistVertIndex, vIndex);
                // If the new distance is smaller than the current distance, update the distance.
                if (newDist < dists[vIndex]) {
                    dists[vIndex] = newDist;
                    prev[vIndex] = curMinDistVertIndex;
                }
            }
        }
    }
}

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
        // Get the current node with the smallest distance from the priority queue.
        std::ranges::pop_heap(que, popMinHeap);
        auto current = que.back();
        que.pop_back();

        // If the node has already been visited, skip it:
        if (visited.count(current.first)) { continue; }
        // Or the node has not been visited, mark it as visited:
        else { visited.insert(current.first); }

        // Check all neighbor nodes to see if their distances need to be updated:
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
                std::ranges::push_heap(que, popMinHeap);
            }
        }
    }
    return dists;
}
