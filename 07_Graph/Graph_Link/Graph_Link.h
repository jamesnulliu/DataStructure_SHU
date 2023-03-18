#pragma once
#include <initializer_list>
#include <vector>
#include <iostream>
#include <queue>

template<class VertTy = char, class WeightTy = int>
class Graph_Link
{
public:
    using index = long long;
    using sizet = long long;
    static constexpr sizet DEFAULT_MAX_VERTNUM = 10;
    /**
    * Graph_Link Visualization
    *   vector
    * <VertNode>
    * |1| [true,vert1,-]->[3,1,-]->nullptr
    * |2|
    * |3|
    * ...
    * ...
    */
    struct Arc { index destVertIndex = {}; Arc* next = nullptr; WeightTy weight = 1; };
    struct VertNode { bool is_exisit = true; VertTy vert = {}; Arc* firstArcPtr = nullptr; };
private:
    sizet _capacity_vert;
    std::vector<VertNode> _vertTable;
    sizet _vertNum;
    std::queue<index> availableLoc;
public: // Constructor & Destructor -----
    Graph_Link(sizet vertNum_max) :
        _capacity_vert(vertNum_max),
        _vertTable(vertNum_max, VertNode()),
        _vertNum(0) {}
    Graph_Link(std::initializer_list<VertTy> initList) :
        Graph_Link(initList.size())
    {
        // Copy each vert from {initList} to {_vertTable}:
        for (index i = 0; i < (index)initList.size(); ++i) {
            _vertTable[i].vert = initList[i];
        }
        _vertNum = initList.size();
    }
    ~Graph_Link() = default;
public:
    void insertVertex(const VertTy& v) {
        if (full_vert()) { _vertTable.resize(_capacity_vert <<= 1); }
        if (availableLoc.empty()) {
            _vertTable[_vertNum].vert = v;
        } else {
            _vertTable[availableLoc.front()].vert = v;
            _vertTable[availableLoc.front()].is_exist = true;
            availableLoc.pop();
        }
        ++_vertNum;
    }

    void insertArc(const VertTy& _Left, const VertTy& _Right, const WeightTy& weight = 1) {
        index leftI = get_vertIndex(_Left), rightI = get_vertIndex(_Right);
        if (leftI == -1 || rightI == -1) {
            throw "[Failed] Vertex Not Found!";
        }
        // Insert the newly created arc to head:
        Arc* ed = new Arc{ rightI, _vertTable[leftI].firstArcPtr, weight };
        _vertTable[leftI].firstArcPtr = ed;
    }

    void insertEdge(const VertTy& va, const VertTy& vb, const WeightTy& weight = 1) {
        insertArc(va, vb, weight);
        insertArc(vb, va, weight);
    }
    void eraseVertex(const VertTy& v) {
        index vI = get_vertIndex(v); // The index of vertex to be erased.
        // If not found the vertex, throw exception:
        if (vI == -1) {
            throw "[Failed] Vertex Not Found!";
        }
        // Erase every involved arcs:
        for (auto vArcPtr = get_vertRef(vI).firstArcPtr; // Get the first arc linking to some vertex.
            vArcPtr != nullptr;                          // End loop when there is no arc.
            vArcPtr = get_vertRef(vI).firstArcPtr        // Get a new first arc linking to some vertex.
            ) {
            // Find the heading vertex linked by {vArcPtr}.
            VertTy linkedV = get_vertRef(vArcPtr->destVertIndex).vert;
            // Erase the arc from {v} to {linkedV}, vice versa.
            eraseArc(v, linkedV);
            eraseArc(linkedV, v);
            // After the arc from {v} to {linkedV} is erased,
            // {v.firstArcPtr} is no longer the arc to {linkedV}, but to the next vertex.
        }
        availableLoc.push(vI);
        get_vertRef(vI).is_exist = false;
    }

    void eraseArc(const VertTy& _Left, const VertTy& _Right) {
        index leftI = get_vertIndex(_Left), rightI = get_vertIndex(_Right);
        if (leftI == -1 || rightI == -1) {
            throw "[Failed] Vertex Not Found!";
        }
        Arc* arc = get_vertRef(leftI).firstArcPtr, * preArc = nullptr;
        while (arc != nullptr && arc->destVertIndex != rightI) {
            preArc = arc;
            arc = arc->next;
        }
        // IF arc linking to {right} is not found, directly return:
        if (arc == nullptr) return;
        // IF the arc is the first:
        if (preArc == nullptr) {
            get_vertRef(leftI).firstArcPtr = arc->next;
        }
        // IF the arc is not the first:
        else {
            preArc->next = arc->next;
        }
        delete arc;
    }

    void eraseEdge(const VertTy& va, const VertTy& vb) {
        eraseArc(va, vb);
        eraseArc(vb, va);
    }

    void print_vertTable() {
        puts("_______________________________");
        for (index i = 0; i < _vertNum; ++i) {
            if (get_vertRef(i).is_exist == false) continue;
            std::cout.width(4); std::cout << i << '|';
            std::cout.width(4); std::cout << get_vertRef(i).vert;
            Arc* ptr = get_vertRef(i).firstArcPtr;
            while (ptr != nullptr) {
                index nextIndex = ptr->destVertIndex;
                std::cout << " ->";
                std::cout.width(2); std::cout << _vertTable[ptr->destVertIndex].vert;
                std::cout << '(' << nextIndex << ')';
                ptr = ptr->next;
            }
            printf(" -> nullptr\n");
        }
    }

private: // Helper Func -----
    constexpr bool full_vert() const { return _vertNum == _capacity_vert; }
    constexpr index get_vertIndex(const VertTy& v) const {
        for (index i = 0; i < _vertNum; ++i) {
            if (_vertTable[i].vert == v) return i;
        }
        return -1;
    }
    constexpr VertNode& get_vertRef(index i) { return _vertTable[i]; }
};
