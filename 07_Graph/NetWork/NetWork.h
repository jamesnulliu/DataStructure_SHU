#pragma once

#include "../Graph_AM/Graph_AM.h"

template<class VertTy = char, class WeightTy = int, WeightTy UNLINK = INT_MAX>
class NetWork : public class Graph_AM<VertTy, WeightTy, UNLINK> {};