#pragma once
#include <vector>
#include <list>
template<class _Elem = char>
class Graph
{
public: // Interface
    using Index = long long;
    using Sizet = long long;
    struct Vertex { _Elem data; Sizet indegree; std::list<Index> adjList; };
    Graph(Sizet vertNum) : vert_vec(vertNum, Vertex {{},0,{}}) {}
    constexpr Sizet vertNum() const { return (Sizet)vert_vec.size(); }
    constexpr void addEdge(Index sbjVert_I, Index objVert_I) {
        vert_vec[sbjVert_I].adjList.push_back(objVert_I);
        ++(vert_vec[objVert_I].indegree);
    }
    constexpr void setData(Index vertI, const _Elem& data) { vert_vec[vertI].data = data; }
    constexpr Vertex& getVertR(Index vertI) { return vert_vec[vertI]; }
    constexpr _Elem& getDataR(Index vertI) { return vert_vec[vertI].data; }
    constexpr Sizet& getIndegreeR(Index vertI) { return vert_vec[vertI].indegree; }
    constexpr std::list<Index>& getAdjListR(Index vertI) { return vert_vec[vertI].adjList; }
private:
    std::vector<Vertex> vert_vec;
};
