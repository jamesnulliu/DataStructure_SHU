#pragma once

template<class VertDataTy, class WeightTy = int>
class Graph
{
public:
    using sizet = long long;
    using index = long long;
public:
    virtual ~Graph() {}
    constexpr virtual index get_vertIndex(const VertDataTy& v) const = 0;
    constexpr virtual sizet get_edgeNum(const VertDataTy& v) const = 0;
    virtual void insertVertex(const VertDataTy& v) = 0;
    virtual void insertArc(const VertDataTy& v1, const VertDataTy& v2, const WeightTy& weight) = 0;
    virtual void insertEdge(const VertDataTy& v1, const VertDataTy& v2, const WeightTy& weight) = 0;
    virtual void eraseVertex(const VertDataTy& v) = 0;
    virtual void eraseArc(const VertDataTy& v1, const VertDataTy& v2) = 0;
    virtual void eraseEdge(const VertDataTy& v1, const VertDataTy& v2) = 0;
    virtual WeightTy& get_weight(const VertDataTy& v1, const VertDataTy& v2) = 0;
    virtual const WeightTy& get_weight(const VertDataTy& v1, const VertDataTy& v2) const = 0;
    virtual VertDataTy& get_firstAdjVert(const VertDataTy& v) = 0;
    virtual const VertDataTy& get_firstAdjVert(const VertDataTy& v) const = 0;
    virtual VertDataTy& get_nextAdjVert(const VertDataTy& v1, const VertDataTy& v2) = 0;
    virtual const VertDataTy& get_nextAdjVert(const VertDataTy& v1, const VertDataTy& v2) const = 0;
    // virtual void travers() const = 0;
};
