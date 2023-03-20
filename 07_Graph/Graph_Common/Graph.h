#pragma once
#include <vector>
#include <list>
template <class VertTy = char>
class Graph
{
public:
    using Index = long long;
    using Sizet = long long;
    struct Vertex
    {
        VertTy data;
        Sizet indegree;
        std::list<Index> adjList;
    };

public:
    Graph(Sizet _vertNum) : vert_vec(_vertNum, Vertex{{}, 0, {}}) {}
    constexpr Sizet _vertNum() const { return (Sizet)vert_vec.size(); }
    constexpr void addEdge(Index sbjVert_I, Index objVert_I)
    {
        vert_vec[sbjVert_I].adjList.push_back(objVert_I);
        ++(vert_vec[objVert_I].indegree);
    }
    constexpr void setData(Index vertI, const VertTy &data) { vert_vec[vertI].data = data; }
    constexpr Vertex &getVertR(Index vertI) { return vert_vec[vertI]; }
    constexpr VertTy &getDataR(Index vertI) { return vert_vec[vertI].data; }
    constexpr Sizet &getIndegreeR(Index vertI) { return vert_vec[vertI].indegree; }
    constexpr std::list<Index> &getAdjListR(Index vertI) { return vert_vec[vertI].adjList; }

private:
    std::vector<Vertex> vert_vec;
};
