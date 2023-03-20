#pragma once

template<class VertTy, class WeightTy = int>
class Graph
{
public:
    using sizet = long long;
    using index = long long;
public:
    virtual ~Graph() {}
    constexpr virtual index get_vertIndex(const VertTy& v) const = 0;
    constexpr virtual sizet get_edgeNum(const VertTy& v) const = 0;
    virtual void insertVertex(const VertTy& v) = 0;
    virtual void insertArc(const VertTy& v1, const VertTy& v2, const WeightTy& weight) = 0;
    virtual void insertEdge(const VertTy& v1, const VertTy& v2, const WeightTy& weight) = 0;
    virtual void eraseVertex(const VertTy& v) = 0;
    virtual void eraseArc(const VertTy& v1, const VertTy& v2) = 0;
    virtual void eraseEdge(const VertTy& v1, const VertTy& v2) = 0;
    virtual WeightTy& get_weight(const VertTy& v1, const VertTy& v2) = 0;
    virtual const WeightTy& get_weight(const VertTy& v1, const VertTy& v2) const = 0;
    virtual VertTy& get_firstAdjVert(const VertTy& v) = 0;
    virtual const VertTy& get_firstAdjVert(const VertTy& v) const = 0;
    virtual VertTy& get_nextAdjVert(const VertTy& v1, const VertTy& v2) = 0;
    virtual const VertTy& get_nextAdjVert(const VertTy& v1, const VertTy& v2) const = 0;
    // virtual void travers() const = 0;
};
