#pragma once
#include <vector>
#include <iostream>

using sizet = long long;
using index = long long;

constexpr sizet MAX_VERTEXNUM = 10;

template<class ElemTy = char>
class Graph_AM
{
public:
    enum class EdgeStatus : int { Unlinked = 0, Linked };
    Graph_AM(sizet vertexNum = MAX_VERTEXNUM) :
        m_max_vertNum(vertexNum),
        m_edgeMat(m_max_vertNum, std::vector<EdgeStatus>(m_max_vertNum, EdgeStatus::Unlinked)),
        m_vertList(m_max_vertNum, ElemTy()), m_edgeNum(0), m_vertNum(0) {
    }
    Graph_AM(std::vector<ElemTy>&& init_vertVec) :
        m_max_vertNum((sizet)init_vertVec.size()),
        m_edgeMat(m_max_vertNum, std::vector<EdgeStatus>(m_max_vertNum, EdgeStatus::Unlinked)),
        m_vertList(init_vertVec), m_edgeNum(0), m_vertNum((sizet)init_vertVec.size()) {
    }
    ~Graph_AM() = default;
    constexpr bool is_full() const { return m_vertNum >= m_max_vertNum; }
    constexpr void insert_vertex(const ElemTy& v) {
        if(is_full()) {
            m_max_vertNum <<= 1;
            m_vertList.resize(m_max_vertNum);
            m_edgeMat.resize(m_max_vertNum);
            for(std::vector<EdgeStatus>& vec : m_edgeMat) { vec.resize(m_max_vertNum); }
        }
        m_vertList[m_vertNum++] = v;
    }
    constexpr index get_vertIndex(const ElemTy& target) {
        for(index it = 0; it < m_vertNum; ++it) {
            if(m_vertList[it] == target) { return it; }
        }
        return -1;
    };
    constexpr void insert_edge(const ElemTy& va, const ElemTy& vb) {
        index vaI = get_vertIndex(va);
        index vbI = get_vertIndex(vb);
        if(vaI == -1 || vbI == -1) { return; }
        if(m_edgeMat[vaI][vbI] == EdgeStatus::Linked) { return; }
        m_edgeMat[vaI][vbI] = m_edgeMat[vbI][vaI] = EdgeStatus::Linked;
        ++m_edgeNum;
    }
    void print_adjacencyMatrix() {
        puts("_______________________________");
        std::cout.fill('_');
        printf("____|");
        for(index i = 0; i < m_vertNum; ++i) {
            std::cout.width(4);
            std::cout << m_vertList[i] << '|';
        }
        printf("\n");
        for(index i = 0; i < m_vertNum; ++i) {
            std::cout.fill('_');
            std::cout.width(4);
            std::cout << m_vertList[i] << '|';
            for(index j = 0; j < m_vertNum; ++j) {
                std::cout.fill(' ');
                std::cout.width(4);
                std::cout << (m_edgeMat[i][j] == EdgeStatus::Linked ? 1 : 0) << ' ';
            }
            std::cout << std::endl;
        }
    }
    constexpr sizet get_edgeNum(const ElemTy& v) {
        index vI = get_vertIndex(v);
        if(vI == -1) return 0;
        sizet num = 0;
        for(auto& n : m_edgeMat[vI]) {
            if(n == EdgeStatus::Linked) ++num;
        }
        return num;
    }
    void erase_vertex(const ElemTy& v) {
        index vI = get_vertIndex(v);
        if(vI == -1) return;
        m_edgeNum -= get_edgeNum(v);
        m_vertList.erase(m_vertList.begin() + vI);
        m_edgeMat.erase(m_edgeMat.begin() + vI);
        for(std::vector<EdgeStatus>& row : m_edgeMat) { row.erase(row.begin() + vI); }
        --m_vertNum;
    }
    void erase_edge(const ElemTy& va, const ElemTy& vb) {
        index vaI = get_vertIndex(va);
        index vbI = get_vertIndex(vb);
        if(vaI == -1 || vbI == -1) return;
        m_edgeMat[vaI][vbI] = m_edgeMat[vbI][vaI] = EdgeStatus::Unlinked;
        --m_edgeNum;
    }

    sizet m_max_vertNum;
    std::vector<std::vector<EdgeStatus>> m_edgeMat;
    std::vector<ElemTy> m_vertList;
    sizet m_edgeNum;
    sizet m_vertNum;
};
