#pragma once
#include <vector>
#include <iostream>
#include <queue>
template<class ElemTy = char>
class Graph_Link
{
public:
    using index = long long;
    using sizet = long long;
    static constexpr sizet DEFAULT_MAX_VERTNUM = 10;
    struct Edge { index destIndex = {}; Edge* next = nullptr; };
    struct Vertex { ElemTy data = {}; Edge* listHead = nullptr; bool is_exist = true; };
public: // Constructor & Destructor -----
    Graph_Link(sizet vertNum_max) :
        m_max_vertNum(vertNum_max),
        m_vertTable(vertNum_max, Vertex()),
        m_vertNum(0),
        m_edgeNum(0) {
    }
    Graph_Link(const std::vector<ElemTy>& vertexList) :
        Graph_Link(vertexList.size()) {
        for(index i = 0; i < (index)vertexList.size(); ++i) {
            m_vertTable[i].data = vertexList[i];
        }
        m_vertNum = vertexList.size();
    }
    ~Graph_Link() = default;
public: // Interface -----
    constexpr void insert_vertex(const ElemTy& v) {
        if(is_full()) { m_vertTable.resize(++m_max_vertNum); }
        ++m_vertNum;
        if(avaLocQue.empty()) {
            m_vertTable[m_vertNum - 1].data = v;
        } else {
            m_vertTable[avaLocQue.front()].data = v;
            m_vertTable[avaLocQue.front()].is_exist = true;
            avaLocQue.pop();
        }
    }
    constexpr void insert_edge(const ElemTy& va, const ElemTy& vb) {
        _create_edge_Left2Right(va, vb);
        _create_edge_Left2Right(vb, va);
        ++m_edgeNum;
    }
    void print_vertTable() {
        puts("_______________________________");
        for(index i = 0; i < m_vertNum; ++i) {
            if(get_vertRef(i).is_exist == false) continue;
            std::cout.width(4); std::cout << i << '|';
            std::cout.width(4); std::cout << get_vertRef(i).data;
            Edge* ptr = get_vertRef(i).listHead;
            while(ptr != nullptr) {
                index nextIndex = ptr->destIndex;
                std::cout << " ->";
                std::cout.width(2); std::cout << m_vertTable[ptr->destIndex].data;
                std::cout << '(' << nextIndex << ')';
                ptr = ptr->next;
            }
            printf(" -> nullptr\n");
        }
    }
    constexpr void erase_edge(const ElemTy& va, const ElemTy& vb) {
        _delete_edge_Left2Right(va, vb);
        _delete_edge_Left2Right(vb, va);
        --m_edgeNum;
    }
    constexpr void erase_vertex(const ElemTy& v) {
        index vI = get_vertIndex(v);
        if(!is_vertIndexValid(vI)) return;
        // Erase every involved edges:
        for(auto vaEd_Iter = get_vertRef(vI).listHead; vaEd_Iter != nullptr; vaEd_Iter = get_vertRef(vI).listHead) {
            ElemTy& destData = get_vertRef(vaEd_Iter->destIndex).data;
            erase_edge(destData, v);
        }
        avaLocQue.push(vI);
        get_vertRef(vI).is_exist = false;
    }
    constexpr sizet vertNum() const { return m_vertNum; }
    constexpr sizet edgeNum() const { return m_edgeNum; }
private: // Helper Func -----
    constexpr bool is_full() const { return m_vertNum == m_max_vertNum; }
    constexpr bool is_vertIndexValid(index i) const { return i >= 0 && i < m_vertNum; }
    constexpr index get_vertIndex(const ElemTy& v) const {
        for(index i = 0; i < m_vertNum; ++i) {
            if(m_vertTable[i].data == v) return i;
        }
        return -1;
    }
    constexpr Vertex& get_vertRef(index i) { return m_vertTable[i]; }
    // @brief Dangrous to call this func along; Dosen't maintain {edgeNum}.
    constexpr void _create_edge_Left2Right(const ElemTy& _Left, const ElemTy& _Right) {
        index sbjI = get_vertIndex(_Left), objI = get_vertIndex(_Right);
        if(sbjI == -1 || objI == -1) return;
        // [Todo] Need to check replucated edge?? But cost efficiency!
        Edge* ed = new Edge {objI,m_vertTable[sbjI].listHead};
        m_vertTable[sbjI].listHead = ed;
    }
    // @brief Dangrous to call this func along; Dosen't maintain {edgeNum}.
    constexpr void _delete_edge_Left2Right(const ElemTy& _Left, const ElemTy& _Right) {
        index leftI = get_vertIndex(_Left), rightI = get_vertIndex(_Right);
        if(!is_vertIndexValid(leftI) || !is_vertIndexValid(rightI)) return;
        Edge* edge = get_vertRef(leftI).listHead, * preEdge = nullptr;
        while(edge != nullptr && edge->destIndex != rightI) {
            preEdge = edge;
            edge = edge->next;
        }
        if(edge == nullptr) return;
        if(preEdge == nullptr) {
            get_vertRef(leftI).listHead = edge->next;
        } else {
            preEdge->next = edge->next;
        }
        delete edge;
    }

private:
    sizet m_max_vertNum;
    std::vector<Vertex> m_vertTable;
    sizet m_vertNum;
    sizet m_edgeNum;
    std::queue<index> avaLocQue;
};
