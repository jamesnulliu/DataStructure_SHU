// Graph Implementation with Adjacency Matrix

#pragma once

#include "../Graph.h"
#include <vector>
#include <iostream>
#include <algorithm>
#include <initializer_list>

template<class VertTy = char>
class Graph_AM : Graph<VertTy, int>
{
public:
    using sizet = long long;
    using index = long long;
    constexpr static sizet MAX_VERTEXNUM = 10;
    enum class ArcStatus : int { Unlinked = 0, Linked = 1 };

public:
    sizet max_vertNum;
    std::vector<std::vector<ArcStatus>> arcMat;
    std::vector<VertTy> vertList;
    sizet vertNum;

public: // Constructor and Destructor
    Graph_AM(sizet vertexNum = MAX_VERTEXNUM) :
        max_vertNum(vertexNum),
        arcMat(max_vertNum, std::vector<ArcStatus>(max_vertNum, ArcStatus::Unlinked)),
        vertList(max_vertNum, VertTy()),
        vertNum(0) {}
    Graph_AM(std::initializer_list<VertTy> vertList) :
        max_vertNum((sizet)vertList.size()),
        arcMat(max_vertNum, std::vector<ArcStatus>(max_vertNum, ArcStatus::Unlinked)),
        vertList(vertList),
        vertNum((sizet)vertList.size()) {}
    ~Graph_AM() = default;

private: // Tool Function
    template<class _Container, class _Value>
    constexpr auto _find(const _Container& container, const _Value& value) const {
        return std::ranges::find(container, value);
    }
public:
    constexpr bool empty() const { return vertNum == 0; }
    constexpr bool full() const { return vertNum >= max_vertNum; }
    constexpr index get_vertIndex(const VertTy& v) const;
    constexpr sizet get_edgeNum(const VertTy& v) const;

    void insertVertex(const VertTy& v);
    void insertArc(const VertTy& va, const VertTy& vb);
    void insertEdge(const VertTy& va, const VertTy& vb);
    void eraseVertex(const VertTy& v);
    void eraseArc(const VertTy& va, const VertTy& vb);
    void eraseEdge(const VertTy& va, const VertTy& vb);

    VertTy& get_firstAdjVert(const VertTy& v);
    const VertTy& get_firstAdjVert(const VertTy& v) const;
    VertTy& get_nextAdjVert(const VertTy& va, const VertTy& vb);
    const VertTy& get_nextAdjVert(const VertTy& va, const VertTy& vb) const;

    void print_adjacencyMatrix();
};

template<class VertTy>
constexpr Graph_AM<VertTy>::index Graph_AM<VertTy>::get_vertIndex(const VertTy& v) const {
    auto firstOccurIter = this->_find(vertList, v);
    index result = index(firstOccurIter - vertList.begin());
    // IF not found, return -1:
    if (result == (index)vertList.size()) { return -1; }
    // IF found, return result:
    return result;
};

template<class VertTy>
constexpr Graph_AM<VertTy>::sizet Graph_AM<VertTy>::get_edgeNum(const VertTy& v) const {
    index vI = get_vertIndex(v);
    if (vI == -1) return 0;
    sizet num = 0;
    for (auto& n : arcMat[vI]) {
        if (n == ArcStatus::Linked) ++num;
    }
    return num;
}

template<class VertTy>
inline void Graph_AM<VertTy>::insertVertex(const VertTy& v) {
    if (full()) {
        max_vertNum <<= 1;
        vertList.resize(max_vertNum);
        // Resize row:
        arcMat.resize(max_vertNum);
        // Then resize col in each row:
        for (std::vector<ArcStatus>& vec : arcMat) { vec.resize(max_vertNum); }
    }
    vertList[vertNum++] = v;
}

template<class VertTy>
void Graph_AM<VertTy>::insertArc(const VertTy& va, const VertTy& vb) {
    index vaI = get_vertIndex(va);
    index vbI = get_vertIndex(vb);
    // IF {va} or {vb} is not found, return:
    if (vaI == -1 || vbI == -1) { return; }
    // Link an acr from {va} to {vb}:
    arcMat[vaI][vbI] = ArcStatus::Linked;
}

template<class VertTy>
void Graph_AM<VertTy>::insertEdge(const VertTy& va, const VertTy& vb) {
    index vaI = get_vertIndex(va);
    index vbI = get_vertIndex(vb);
    // IF {va} or {vb} is not found, return:
    if (vaI == -1 || vbI == -1) { return; }
    // Edge has 2 directions:
    arcMat[vaI][vbI] = arcMat[vbI][vaI] = ArcStatus::Linked;
}

template<class VertTy>
void Graph_AM<VertTy>::eraseVertex(const VertTy& v) {
    index vI = get_vertIndex(v);
    if (vI == -1) return;
    vertList.erase(vertList.begin() + vI);
    arcMat.erase(arcMat.begin() + vI);
    for (std::vector<ArcStatus>& row : arcMat) { row.erase(row.begin() + vI); }
    --vertNum;
}

template<class VertTy>
void Graph_AM<VertTy>::eraseArc(const VertTy& va, const VertTy& vb) {
    index vaI = get_vertIndex(va);
    index vbI = get_vertIndex(vb);
    if (vaI == -1 || vbI == -1) return;
    arcMat[vaI][vbI] = ArcStatus::Unlinked;
}

template<class VertTy>
void Graph_AM<VertTy>::eraseEdge(const VertTy& va, const VertTy& vb) {
    index vaI = get_vertIndex(va);
    index vbI = get_vertIndex(vb);
    if (vaI == -1 || vbI == -1) return;
    // Erase both arcs:
    arcMat[vaI][vbI] = arcMat[vbI][vaI] = ArcStatus::Unlinked;
}

template<class VertTy>
void Graph_AM<VertTy>::print_adjacencyMatrix() {
    for (int i = 0; i <= vertNum; ++i) {
        putchar('_'); putchar('_'); putchar('_'); putchar('_'); putchar('_');
    }
    putchar('\n');
    std::cout.fill('_');
    printf("____|");
    for (index i = 0; i < vertNum; ++i) {
        std::cout.width(4);
        std::cout << vertList[i] << '|';
    }
    printf("\n");
    for (index i = 0; i < vertNum; ++i) {
        std::cout.fill('_');
        std::cout.width(4);
        std::cout << vertList[i] << '|';
        for (index j = 0; j < vertNum; ++j) {
            std::cout.fill(' ');
            std::cout.width(4);
            std::cout << (arcMat[i][j] == ArcStatus::Linked ? 1 : 0) << ' ';
        }
        std::cout << std::endl;
    }
}

template<class VertTy>
VertTy& Graph_AM<VertTy>::get_firstAdjVert(const VertTy& v) {
    const auto cThis = this;
    return const_cast<VertTy&>(cThis->get_firstAdjVert(v));
}

template<class VertTy>
const VertTy& Graph_AM<VertTy>::get_firstAdjVert(const VertTy& v) const {
    index vI = this->get_vertIndex(v);
    if (vI == -1) { throw "[Failed] Vertex Not Found!"; }
    auto resIt = std::ranges::find(arcMat[vI], ArcStatus::Linked);
    if (resIt == arcMat[vI].end()) { throw"[Failed] No Linked Vertex!"; }
    index resVertIndex = resIt - arcMat[vI].begin();
    return this->vertList[resVertIndex];
}

template<class VertTy>
VertTy& Graph_AM<VertTy>::get_nextAdjVert(const VertTy& va, const VertTy& vb) {
    const auto cThis = this;
    return const_cast<VertTy&>(cThis->get_nextAdjVert(va, vb));
}

template<class VertTy>
const VertTy& Graph_AM<VertTy>::get_nextAdjVert(const VertTy& va, const VertTy& vb) const {
    index vaI = this->get_vertIndex(va);
    index vbI = this->get_vertIndex(vb);
    if (vaI == -1 || vbI == -1) { throw"[Failed] Vertex Not Found!"; }
    auto resIt = std::find(arcMat[vaI].begin() + vbI + 1, arcMat[vaI].end(), ArcStatus::Linked);
    if (resIt == arcMat[vaI].end()) { throw"[Failed] No Linked Vertex!"; }
    index resVertIndex = resIt - arcMat[vaI].begin();
    return this->vertList[resVertIndex];
}
