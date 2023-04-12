#pragma once
#include "GOL_Arc.h"
#include <vector>
#include <utility>

namespace gol {
    template<class VertTy, class WeightTy, WeightTy UNLINK>
    class Graph
    {
    public:
        using ArcTy = GOL_Arc<WeightTy, UNLINK>::ArcTy;
        using ArcPtr = GOL_Arc<WeightTy, UNLINK>::ArcPtr;

        Size vertNum() const { return (Size)_vertice.size(); }

        // @brief Create and insert a vertex to the back of the container (which is a vertex).
        void insertVert(const VertTy& vert);

        // @brief Erase a vertex by its index.
        void eraseVertByIndex(Index vertIndex);

        // @brief Insert an arc by given index and weight.
        void insertArcByIndex(Index srcVertIndex, Index dstVertIndex, WeightTy weight);

        // @brief Erase an arc by given indexes.
        void eraseArcByIndex(Index srcVertIndex, Index dstVertIndex);

        // @brief Find the index of vertex with data {vert}; If not found, return the number of current veritce.
        Index findVertIndex(const VertTy& vert) const;

        // @brief Check whether there is an arc from src to dst.
        bool isLinked(Index srcVertIndex, Index dstVertIndex) const;

        // @brief Get the const vertex data by it's index.
        const VertTy& getVertByIndex(Index vertIndex) const { return _vertice[vertIndex].data; }

        // @brief Get the vertex data by it's index.
        VertTy& getVertByIndex(Index vertIndex) { return _vertice[vertIndex].data; }

    private:
        template<class VertTy = char, class WeightTy = int, WeightTy UNLINK = INT_MAX>
        struct _Vertex
        {
            VertTy data = {};
            ArcPtr firstIn = {};
            ArcPtr firstOut = {};
        };

        bool isValidVertIndex(Index vertIndex) const {
            return vertIndex > 0 && vertIndex < _vertice.size();
        }

        std::vector<_Vertex<VertTy, WeightTy, UNLINK>> _vertice;
    };

    template<class VertTy, class WeightTy, WeightTy UNLINK>
    void Graph<VertTy, WeightTy, UNLINK>::insertVert(const VertTy& vert) {
        _vertice.push_back(_Vertex{ vert, nullptr, nullptr });
    }

    template<class VertTy, class WeightTy, WeightTy UNLINK>
    void Graph<VertTy, WeightTy, UNLINK>::
        insertArcByIndex(Index srcVertIndex, Index dstVertIndex, WeightTy weight) {
        // If either index is invalid, return directly:
        if (!isValidVertIndex(srcVertIndex) || !isValidVertIndex(dstVertIndex)) { return; }

        _Vertex& srcVert = _vertice[srcVertIndex];
        _Vertex& dstVert = _vertice[dstVertIndex];

        ArcPtr arcNew = std::make_shared<ArcTy>({});
        arcNew->arcTo = srcVertIndex.firstOut;
    }

    template<class VertTy, class WeightTy, WeightTy UNLINK>
    Index Graph<VertTy, WeightTy, UNLINK>::findVertIndex(const VertTy& vert) const {
        auto equals = [&vert](const _Vertex<VertTy, WeightTy, UNLINK>& v) {
            return v.data == vert;
        };
        auto resIter = std::find_if(_vertice.begin(), _vertice.end(), equals);
        return resIter - _vertice.begin();
    }
}
