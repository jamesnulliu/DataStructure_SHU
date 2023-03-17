#pragma once

#include "../Graph.h"
#include <vector>
#include <iostream>
#include <algorithm>
#include <initializer_list>

// Graph Implementation with Adjacency Matrix
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

public:
    bool empty() const { return vertNum == 0; }

    bool is_full() const { return vertNum >= max_vertNum; }

    index get_vertIndex(const VertTy& target) {
        auto firstOccurIter = std::ranges::find(vertList, target);
        index result = index(firstOccurIter - vertList.begin());
        // IF not found, return -1:
        if (result == (index)vertList.size()) { return -1; }
        // IF found, return result:
        return result;
    };

    sizet get_edgeNum(const VertTy& v) {
        index vI = get_vertIndex(v);
        if (vI == -1) return 0;
        sizet num = 0;
        for (auto& n : arcMat[vI]) {
            if (n == ArcStatus::Linked) ++num;
        }
        return num;
    }

    void insertVertex(const VertTy& v) {
        if (is_full()) {
            max_vertNum <<= 1;
            vertList.resize(max_vertNum);
            // Resize row:
            arcMat.resize(max_vertNum);
            // Then resize col in each row:
            for (std::vector<ArcStatus>& vec : arcMat) { vec.resize(max_vertNum); }
        }
        vertList[vertNum++] = v;
    }

    void insertArc(const VertTy& va, const VertTy& vb) {
        index vaI = get_vertIndex(va);
        index vbI = get_vertIndex(vb);
        // IF {va} or {vb} is not found, return:
        if (vaI == -1 || vbI == -1) { return; }
        // Link an acr from {va} to {vb}:
        arcMat[vaI][vbI] = ArcStatus::Linked;
    }

    void insertEdge(const VertTy& va, const VertTy& vb) {
        index vaI = get_vertIndex(va);
        index vbI = get_vertIndex(vb);
        // IF {va} or {vb} is not found, return:
        if (vaI == -1 || vbI == -1) { return; }
        // Edge has 2 directions:
        arcMat[vaI][vbI] = arcMat[vbI][vaI] = ArcStatus::Linked;
    }

    void eraseVertex(const VertTy& v) {
        index vI = get_vertIndex(v);
        if (vI == -1) return;
        edgeNum -= get_edgeNum(v);
        vertList.erase(vertList.begin() + vI);
        arcMat.erase(arcMat.begin() + vI);
        for (std::vector<ArcStatus>& row : arcMat) { row.erase(row.begin() + vI); }
        --vertNum;
    }

    void erase_arc(const VertTy& va, const VertTy& vb) {
        index vaI = get_vertIndex(va);
        index vbI = get_vertIndex(vb);
        if (vaI == -1 || vbI == -1) return;
        arcMat[vaI][vbI] = ArcStatus::Unlinked;
    }

    void erase_edge(const VertTy& va, const VertTy& vb) {
        index vaI = get_vertIndex(va);
        index vbI = get_vertIndex(vb);
        if (vaI == -1 || vbI == -1) return;
        // Erase both arcs:
        arcMat[vaI][vbI] = arcMat[vbI][vaI] = ArcStatus::Unlinked;
    }

    void print_adjacencyMatrix() {
        puts("_______________________________");
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
};
