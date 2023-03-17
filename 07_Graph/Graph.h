#pragma once

template<class VertTy, class WeightTy = int>
class Graph
{
public:
    virtual ~Graph() {}
    virtual void insertVertex(const VertTy& v) = 0;
    virtual void insertEdge(const VertTy& v1, const VertTy& v2) = 0;
    virtual void eraseVertex(const VertTy& v) = 0;
    virtual void eraseEdge(const VertTy& v1, const VertTy& v2) = 0;
    virtual WeightTy& get_weight(const VertTy& v1, const VertTy& v2) = 0;
    virtual const WeightTy& get_weight(const VertTy& v1, const VertTy& v2) const = 0;
    virtual VertTy& get_firstNeighbor(const VertTy& v) = 0;
    virtual const VertTy& get_firstNeighbor(const VertTy& v) const = 0;
    virtual VertTy& get_nextNeighbor(const VertTy& v1, const VertTy& v2) = 0;
    virtual const VertTy& get_nextNeighbor(const VertTy& v1, const VertTy& v2) const = 0;
    virtual void travers() const = 0;
    virtual bool empty() const = 0;
};
