// Graph Implementation with Adjacency Matrix

#pragma once

#include <vector>
#include <iostream>
#include <algorithm>
#include <initializer_list>
#include <string>
#include <ranges>

template <class VertTy = char, class WeightTy = int, WeightTy UNLINK = 0>
class Graph_AM
{
public:
    using sizet = long long;
    using index = long long;
    constexpr static sizet MAX_VERTEXNUM = 10;

public:
    sizet _capacity_vert;  // Capacity of vertex; If full, expansion takes place automatically
    std::vector<std::vector<WeightTy>> _arcMat;  // n*n matrix which stores weight of each arc/edge
    std::vector<VertTy> _vertVec;  // Vector that holds all the vertexes' data (or information)
    sizet _vertNum;  // Number of current vertexes

public: // Constructor and Destructor
    Graph_AM(sizet vertNum = MAX_VERTEXNUM) :
        // Set capcity to {vertNum}:
        _capacity_vert(vertNum),
        // Create a [capacity * capacity] matrix to store arcs:
        _arcMat(_capacity_vert, std::vector<WeightTy>(_capacity_vert, UNLINK)),
        // Create a [1 * capcity] vector to store vertexes:
        _vertVec(_capacity_vert, VertTy()),
        // Set {_vertNum} to 0:
        _vertNum(0) {}
    Graph_AM(std::initializer_list<VertTy> vertList) :
        // Set capcity to {vertList.size()}:
        _capacity_vert((sizet)vertList.size()),
        // Create a [capacity * capacity] matrix to store arcs:
        _arcMat(_capacity_vert, std::vector<WeightTy>(_capacity_vert, UNLINK)),
        // Initialize {_vertVec} with {vertList}
        _vertVec(vertList),
        // Set {_vertNum} to 0:
        _vertNum((sizet)vertList.size())
    {
        // Set all self arc to zero:
        for (index i = 0; i < (index)vertList.size(); ++i)
        {
            _arcMat[i][i] = 0;
        }
    }
    ~Graph_AM() = default;

private:
    constexpr bool is_validIndex(index i) const { return i >= 0 && i < _vertNum; }

public:
    constexpr virtual bool is_emptyVert() const { return _vertNum == 0; }
    constexpr virtual bool is_fullVert() const { return _vertNum >= _capacity_vert; }
    constexpr virtual sizet get_vertNum() const { return _vertNum; }

    constexpr index get_vertIndex(const VertTy& v) const;
    constexpr sizet get_edgeNum(const VertTy& v) const;
    constexpr WeightTy& get_weight(const VertTy& v1, const VertTy& v2);
    constexpr const WeightTy& get_weight(const VertTy& v1, const VertTy& v2) const;

    void insertVertex(const VertTy& v);
    void insertArc(const VertTy& va, const VertTy& vb, const WeightTy& weight = 1);
    void insertEdge(const VertTy& va, const VertTy& vb, const WeightTy& weight = 1);
    void eraseVertex(const VertTy& v);
    void eraseArc(const VertTy& va, const VertTy& vb);
    void eraseEdge(const VertTy& va, const VertTy& vb);

    // @brief [Deprecated] Get the first adjacent vertex of {v}.
    VertTy& get_firstAdjVert(const VertTy& v);
    // @brief [Deprecated] Get the first adjacent vertex of {v}.
    const VertTy& get_firstAdjVert(const VertTy& v) const;
    // @brief [Deprecated] Get an adjacent vertex of {va} which is next to {vb}.
    VertTy& get_nextAdjVert(const VertTy& va, const VertTy& vb);
    // @brief [Deprecated] Get an adjacent vertex of {va} which is next to {vb}.
    const VertTy& get_nextAdjVert(const VertTy& va, const VertTy& vb) const;

public:
    const WeightTy& get_weight_loc(index row, index col) const { return _arcMat[row][col]; }

public:
    void print_adjacencyMatrix();
};

template <class VertTy, class WeightTy, WeightTy UNLINK>
constexpr typename Graph_AM<VertTy, WeightTy, UNLINK>::index
Graph_AM<VertTy, WeightTy, UNLINK>::get_vertIndex(const VertTy& v) const
{
    auto firstOccurIter = std::ranges::find(_vertVec, v);
    return index(firstOccurIter - _vertVec.begin());
};

template <class VertTy, class WeightTy, WeightTy UNLINK>
constexpr typename Graph_AM<VertTy, WeightTy, UNLINK>::sizet
Graph_AM<VertTy, WeightTy, UNLINK>::get_edgeNum(const VertTy& v) const
{
    index vI = get_vertIndex(v);
    if (vI == -1)
        return 0;
    sizet num = 0;
    for (auto& n : _arcMat[vI])
    {
        if (n != 0 && n != UNLINK)
            ++num;
    }
    return num;
}

template <class VertTy, class WeightTy, WeightTy UNLINK>
inline void Graph_AM<VertTy, WeightTy, UNLINK>::insertVertex(const VertTy& v)
{
    if (is_fullVert())
    {
        _capacity_vert <<= 1;
        _vertVec.resize(_capacity_vert);
        // Resize row:
        _arcMat.resize(_capacity_vert);
        // Then resize col in each row:
        for (auto& row : _arcMat)
        {
            row.resize(_capacity_vert);
        }
    }
    _vertVec[_vertNum++] = v;
}

template <class VertTy, class WeightTy, WeightTy UNLINK>
void Graph_AM<VertTy, WeightTy, UNLINK>::insertArc(const VertTy& va, const VertTy& vb, const WeightTy& weight)
{
    index vaI = get_vertIndex(va);
    index vbI = get_vertIndex(vb);
    if (!is_validIndex(vaI) || !is_validIndex(vbI) || vaI == vbI)
    {
        return;
    }
    // Link an acr from {va} to {vb}:
    _arcMat[vaI][vbI] = weight;
}

template <class VertTy, class WeightTy, WeightTy UNLINK>
void Graph_AM<VertTy, WeightTy, UNLINK>::insertEdge(const VertTy& va, const VertTy& vb, const WeightTy& weight)
{
    index vaI = get_vertIndex(va);
    index vbI = get_vertIndex(vb);
    if (!is_validIndex(vaI) || !is_validIndex(vbI) || vaI == vbI)
    {
        return;
    }
    // Edge has 2 directions:
    _arcMat[vaI][vbI] = _arcMat[vbI][vaI] = weight;
}

template <class VertTy, class WeightTy, WeightTy UNLINK>
void Graph_AM<VertTy, WeightTy, UNLINK>::eraseVertex(const VertTy& v)
{
    index vI = get_vertIndex(v);
    if (!is_validIndex(vI))
        return;
    _vertVec.erase(_vertVec.begin() + vI);
    _arcMat.erase(_arcMat.begin() + vI);
    for (auto& row : _arcMat)
    {
        row.erase(row.begin() + vI);
    }
    --_vertNum;
}

template <class VertTy, class WeightTy, WeightTy UNLINK>
void Graph_AM<VertTy, WeightTy, UNLINK>::eraseArc(const VertTy& va, const VertTy& vb)
{
    index vaI = get_vertIndex(va);
    index vbI = get_vertIndex(vb);
    if (!is_validIndex(vaI) || !is_validIndex(vbI) || vaI == vbI)
        return;
    _arcMat[vaI][vbI] = UNLINK;
}

template <class VertTy, class WeightTy, WeightTy UNLINK>
void Graph_AM<VertTy, WeightTy, UNLINK>::eraseEdge(const VertTy& va, const VertTy& vb)
{
    index vaI = get_vertIndex(va);
    index vbI = get_vertIndex(vb);
    if (!is_validIndex(vaI) || !is_validIndex(vbI) || vaI == vbI)
        return;
    // Erase both arcs:
    _arcMat[vaI][vbI] = _arcMat[vbI][vaI] = UNLINK;
}

template <class VertTy, class WeightTy, WeightTy UNLINK>
constexpr WeightTy& Graph_AM<VertTy, WeightTy, UNLINK>::get_weight(const VertTy& va, const VertTy& vb)
{
    auto cThis = const_cast<Graph_AM<VertTy> const*>(this);
    return const_cast<WeightTy&>(cThis->get_weight(va, vb));
}

template <class VertTy, class WeightTy, WeightTy UNLINK>
constexpr const WeightTy& Graph_AM<VertTy, WeightTy, UNLINK>::get_weight(const VertTy& va, const VertTy& vb) const
{
    index vaI = get_vertIndex(va);
    index vbI = get_vertIndex(vb);
    if (!is_validIndex(vaI) || !is_validIndex(vbI))
    {
        throw "[Failed] Vertex Not Found!";
    }
    return _arcMat[vaI][vbI];
}

template <class VertTy, class WeightTy, WeightTy UNLINK>
VertTy& Graph_AM<VertTy, WeightTy, UNLINK>::get_firstAdjVert(const VertTy& v)
{
    auto cThis = const_cast<Graph_AM<VertTy> const*>(this);
    return const_cast<VertTy&>(cThis->get_firstAdjVert(v));
}

template <class VertTy, class WeightTy, WeightTy UNLINK>
const VertTy& Graph_AM<VertTy, WeightTy, UNLINK>::get_firstAdjVert(const VertTy& v) const
{
    index vI = this->get_vertIndex(v);
    if (!is_validIndex(vI))
    {
        throw "[Failed] Vertex Not Found!";
    }
    auto lambda = [](const WeightTy& x)
    { return x != 0 && x != UNLINK; };
    auto resIt = std::ranges::find_if(_arcMat[vI], lambda);
    if (resIt == _arcMat[vI].end())
    {
        throw "[Failed] No Linked Vertex!";
    }
    index resVertIndex = resIt - _arcMat[vI].begin();
    return this->_vertVec[resVertIndex];
}

template <class VertTy, class WeightTy, WeightTy UNLINK>
VertTy& Graph_AM<VertTy, WeightTy, UNLINK>::get_nextAdjVert(const VertTy& va, const VertTy& vb)
{
    auto cThis = const_cast<Graph_AM<VertTy> const*>(this);
    return const_cast<VertTy&>(cThis->get_nextAdjVert(va, vb));
}

template <class VertTy, class WeightTy, WeightTy UNLINK>
const VertTy&
Graph_AM<VertTy, WeightTy, UNLINK>::get_nextAdjVert(const VertTy& va, const VertTy& vb) const
{
    index vaI = this->get_vertIndex(va);
    index vbI = this->get_vertIndex(vb);
    if (!is_validIndex(vaI) || !is_validIndex(vbI))
    {
        throw "[Failed] Vertex Not Found!";
    }
    auto lambda = [](const WeightTy& x) { return x != 0 && x != UNLINK; };
    auto resIt = std::find(_arcMat[vaI].begin() + vbI + 1, _arcMat[vaI].end(), lambda);
    if (resIt == _arcMat[vaI].end())
    {
        throw "[Failed] No Linked Vertex!";
    }
    index resVertIndex = resIt - _arcMat[vaI].begin();
    return this->_vertVec[resVertIndex];
}

template <class VertTy, class WeightTy, WeightTy UNLINK>
void Graph_AM<VertTy, WeightTy, UNLINK>::print_adjacencyMatrix()
{
    for (int i = 0; i <= _vertNum; ++i)
    {
        putchar('_');
        putchar('_');
        putchar('_');
        putchar('_');
        putchar('_');
    }
    putchar('\n');
    std::cout.fill('_');
    printf("____|");
    for (index i = 0; i < _vertNum; ++i)
    {
        std::cout.width(4);
        std::cout << _vertVec[i] << '|';
    }
    printf("\n");
    for (index i = 0; i < _vertNum; ++i)
    {
        std::cout.fill('_');
        std::cout.width(4);
        std::cout << _vertVec[i] << '|';
        for (index j = 0; j < _vertNum; ++j)
        {
            std::cout.fill(' ');
            std::cout.width(5);
            if (i == j)
            {
                std::cout << "0 ";
            }
            else if (_arcMat[i][j] == UNLINK)
            {
                std::cout << "x ";
            }
            else
            {
                std::cout << (std::to_string(_arcMat[i][j]) + " ");
            }
        }
        std::cout << std::endl;
    }
}
