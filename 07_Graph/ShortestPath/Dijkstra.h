#pragma once
#include "../Graph_AM/Graph_AM.h"
#include <vector>
#include <deque>

using index = long long;
using sizet = long long;

using namespace std;

template<class VertTy, class WeightTy, WeightTy INIF>
void dijkstra(const Graph_AM<VertTy, WeightTy, INIF>& graph, index sourceI);
