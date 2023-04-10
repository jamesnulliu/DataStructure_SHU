#include "../Graph_AM/Graph_AM.h"
#include <vector>
#include <deque>

using index = long long;
using sizet = long long;

using namespace std;

template<class VertTy, class WeightTy, WeightTy INIF>
void dijkstra(const Graph_AM<VertTy, WeightTy, INIF>& graph, index sourceI)
{
    vector<WeightTy> dists(graph._vertVec.size(), INIF);  // Distance from source vertex to other vertices.
    dists[sourceI] = 0;

    vector<bool> visited{};
    vector<pair<index, WeightTy>> que{};
    que.emplace_back({ sourceI, 0 });
    std::ranges::make_heap(que, std::greater<>{}, & pair<index, WeightTy>::WeightTy);
}