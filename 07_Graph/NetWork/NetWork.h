#pragma once
#include <iostream>
#include <vector>

template<class ElemTy = char, class WeightTy = int>
struct Edge
{
    ElemTy vertPrev;
    ElemTy vertNext;
    WeightTy weight;
    Edge<ElemTy, WeightTy>& operator=() = default;
    bool operator<=(const Edge<ElemTy, WeightTy>& edge) { return weight <= edge.weight; }
    bool operator>(const Edge<ElemTy, WeightTy>& edge) { return weight > edge.weight; }
};

class NetWork
{
public:
    using WeightTy = int;
    template<class E> using vector = std::vector<E>;
private:
    vector<vector<WeightTy>> _arcMat;
};
