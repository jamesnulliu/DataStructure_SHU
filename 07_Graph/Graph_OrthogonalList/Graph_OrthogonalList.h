#pragma once
#include <vector>
#include <memory>

namespace GOL {
    using Index = long long;
    using Size = long long;

    template<class WeightTy = int, WeightTy W_DEFAULT = INT_MAX>
    struct Arc
    {
        using ArcTy = Arc<WeightTy, W_DEFAULT>;
        using ArcPtr = std::shared_ptr<ArcTy>;
        using const_ArcPtr = std::shared_ptr<const ArcTy>;
        enum class Tag { UNVISITED, VISITED };

        Index    srcVertIndex = {};
        Index    dstVertIndex = {};
        ArcPtr   forward = {};
        ArcPtr   backward = {};
        WeightTy weight = { W_DEFAULT };
        Tag      tag = { Tag::UNVISITED };
    };

    template<class VertDataTy = char, class WeightTy = int, WeightTy W_DEFAULT = 0>
    class Graph
    {
    public:
        using ArcTy = Arc<WeightTy, W_DEFAULT>::ArcTy;
        using ArcPtr = Arc<WeightTy, W_DEFAULT>::ArcPtr;
        using const_ArcPtr = ArcTy::const_ArcPtr;

        Size vertNum() const { return (Size)_vertice.size(); }

        // @brief Create and insert a vertex to the back of the container (which is a vertex).
        void insertVert(const VertDataTy& vert);

        // @brief Erase a vertex by its index.
        void eraseVertByIndex(Index vertIndex);

        // @brief Insert an arc by given index and weight.
        void insertArcByIndex(Index srcVertIndex, Index dstVertIndex, WeightTy weight);

        // @brief Erase an arc by given indexes.
        void eraseArcByIndex(Index srcVertIndex, Index dstVertIndex);

        // @brief Find the index of vertex with data {vert}; If not found, return the number of current veritce.
        Index findVertIndex(const VertDataTy& vert) const;

        // @brief Check whether there is an arc from src to dst.
        bool isLinked(Index srcVertIndex, Index dstVertIndex) const;

        // @brief Get the const vertex data by it's index.
        const VertDataTy& getVertByIndex(Index vertIndex) const { return _vertice[vertIndex].data; }

        // @brief Get the vertex data by it's index.
        VertDataTy& getVertByIndex(Index vertIndex) { return _vertice[vertIndex].data; }

        // @brief Get the const arc by given indexes; If not found, return nullptr.
        const_ArcPtr getArcByIndex(Index srcVertIndex, Index dstVertIndex) const;

        // @brief Get the arc by given indexes; If not found, return nullptr.
        ArcPtr getArcByIndex(Index srcVertIndex, Index dstVertIndex);

        // @brief Get a vector of indexes that vertex of each has one arc going out from src vertex.
        std::vector<Index> getOutIndexes(Index srcVertIndex) const;

        // @brief Get a vector of indexes that vertex of each has one arc coming into src vertex.
        std::vector<Index> getInIndexes(Index srcVertIndex) const;

        Size outdegree() const { return (Size)getOutIndexes().size(); }
        Size indegree() const { return (Size)getInIndexes().size(); }

    private:
        struct VertTy
        {
            VertDataTy data = {};
            ArcPtr firstIn = {};
            ArcPtr firstOut = {};
        };

        bool isValidVertIndex(Index vertIndex) const { return vertIndex >= 0 && vertIndex < (Size)_vertice.size(); }

        std::vector<VertTy> _vertice;
    };

    template<class VertDataTy, class WeightTy, WeightTy W_DEFAULT>
    void Graph<VertDataTy, WeightTy, W_DEFAULT>::insertVert(const VertDataTy& vertData)
    {
        _vertice.push_back(
            VertTy{
                vertData,
                nullptr,  // firstIn
                nullptr   // firstOut
            }
        );
    }

    template<class VertDataTy, class WeightTy, WeightTy W_DEFAULT>
    void Graph<VertDataTy, WeightTy, W_DEFAULT>::eraseVertByIndex(Index vertIndex) {
    }

    template<class VertDataTy, class WeightTy, WeightTy W_DEFAULT>
    void Graph<VertDataTy, WeightTy, W_DEFAULT>::
        insertArcByIndex(Index srcVertIndex, Index dstVertIndex, WeightTy weight)
    {
        // If either index is invalid, return directly:
        if (!isValidVertIndex(srcVertIndex) || !isValidVertIndex(dstVertIndex)) { return; }

        if (srcVertIndex == dstVertIndex) return;

        // Try to find the existing arc from src to dst:
        ArcPtr arc = getArcByIndex(srcVertIndex, dstVertIndex);
        // If found, change the weight and return:
        if (arc != nullptr) { arc->weight = weight; return; }

        // Get the references of combined vertices of src and dst:
        VertTy& srcVert = _vertice[srcVertIndex];
        VertTy& dstVert = _vertice[dstVertIndex];

        // Create a new arc, allocate pointers:
        ArcPtr arcNew = std::make_shared<ArcTy>(
            ArcTy{
                srcVertIndex,
                dstVertIndex,
                srcVert.firstOut,
                dstVert.firstOut,
                weight
            }
        );

        srcVert.firstOut = arcNew;
        dstVert.firstIn = arcNew;
    }

    template<class VertDataTy, class WeightTy, WeightTy W_DEFAULT>
    void Graph<VertDataTy, WeightTy, W_DEFAULT>::eraseArcByIndex(Index srcVertIndex, Index dstVertIndex)
    {
        // If either index is invalid, return directly:
        if (!isValidVertIndex(srcVertIndex) || !isValidVertIndex(dstVertIndex)) { return; }

        // Get the references of combined vertices of src and dst:
        VertTy& srcVert = _vertice[srcVertIndex];
        VertTy& dstVert = _vertice[dstVertIndex];

        // Assume that source vert is "src" and destination vert is "dst";
        // Assume that "target arc" is the arc from src to dst;

        // If src has no outgoing arc, target arc would not exist:
        if (srcVert.firstOut == nullptr) { return; }

        // If: the very first outgoing arc of src is the target:
        if (srcVert.firstOut->dstVertIndex == dstVertIndex) {
            // Remove the pointer to target arc:
            srcVert.firstOut = srcVert.firstOut->forward;
        }
        // Else: the first outgoing arc is not the target:
        else {
            // The previous arc of target arc
            ArcPtr prevForwardArc = srcVert.firstOut;

            // Loop to find the previous arc of target arc:
            while (prevForwardArc->forward != nullptr) {
                // If target is found, break from loop;
                if (prevForwardArc->forward->dstVertIndex == dstVertIndex) { break; }
                // Iterate to next forward arc:
                prevForwardArc = prevForwardArc->forward;
            }

            // Return if target arc isn't found:
            if (prevForwardArc->forward == nullptr) { return; }

            // Remove the pointer to target arc:
            prevForwardArc->forward = prevForwardArc->forward->forward;
        }

        // Repeate the steps above to remove the pointer to target arc in backward direction:
        if (dstVert.firstIn == nullptr) { return; }
        if (dstVert.firstIn->srcVertIndex == dstVertIndex) {
            dstVert.firstIn = dstVert.firstIn->backward;
        } else {
            ArcPtr prevBackwardArc = dstVert.firstIn;
            while (prevBackwardArc->backward != nullptr) {
                if (prevBackwardArc->backward->dstVertIndex == dstVertIndex) { break; }
                prevBackwardArc = prevBackwardArc->backward;
            }
            if (prevBackwardArc->backward == nullptr) { return; }
            prevBackwardArc->backward = prevBackwardArc->backward->backward;
        }
    }

    template<class VertDataTy, class WeightTy, WeightTy W_DEFAULT>
    bool Graph<VertDataTy, WeightTy, W_DEFAULT>::isLinked(Index srcVertIndex, Index dstVertIndex) const
    {
        // If either index is invalid, return false directly:
        if (!isValidVertIndex(srcVertIndex) || !isValidVertIndex(dstVertIndex)) { return false; }
        return getArcByIndex(srcVertIndex, dstVertIndex) != nullptr;
    }

    template<class VertDataTy, class WeightTy, WeightTy W_DEFAULT>
    Index Graph<VertDataTy, WeightTy, W_DEFAULT>::findVertIndex(const VertDataTy& vert) const
    {
        auto equals = [&vert](const VertTy& v) {
            return v.data == vert;
        };
        auto resIter = std::find_if(_vertice.begin(), _vertice.end(), equals);
        return resIter - _vertice.begin();
    }

    template<class VertDataTy, class WeightTy, WeightTy W_DEFAULT>
    Graph<VertDataTy, WeightTy, W_DEFAULT>::const_ArcPtr
        Graph<VertDataTy, WeightTy, W_DEFAULT>::getArcByIndex(Index srcVertIndex, Index dstVertIndex) const
    {
        // If either index is invalid, return nullptr:
        if (!isValidVertIndex(srcVertIndex) || !isValidVertIndex(dstVertIndex)) { return nullptr; }

        if (srcVertIndex == dstVertIndex) return nullptr;

        // Get the references of combined vertices of src and dst:
        const VertTy& srcVert = _vertice[srcVertIndex];
        const VertTy& dstVert = _vertice[dstVertIndex];

        ArcPtr arcIterator = srcVert.firstOut;
        // Loop in forward direction to find if there is a arc:
        while (arcIterator != nullptr) {
            // Current pointint vert:
            const VertTy& tempDst = _vertice[arcIterator->dstVertIndex];
            // If found, return the pointer to current arc:
            if (tempDst.data == dstVert.data) {
                return arcIterator;
            }
            // Iterator to next arc:
            arcIterator = arcIterator->forward;
        }

        // Not found, return nullptr:
        return nullptr;
    }

    template<class VertDataTy, class WeightTy, WeightTy W_DEFAULT>
    Graph<VertDataTy, WeightTy, W_DEFAULT>::ArcPtr
        Graph<VertDataTy, WeightTy, W_DEFAULT>::getArcByIndex(Index srcVertIndex, Index dstVertIndex)
    {
        return std::const_pointer_cast<ArcTy>(
            static_cast<const Graph<VertDataTy, WeightTy, W_DEFAULT>&>(*this).getArcByIndex(srcVertIndex, dstVertIndex)
        );
    }

    template<class VertDataTy, class WeightTy, WeightTy W_DEFAULT>
    std::vector<Index> Graph<VertDataTy, WeightTy, W_DEFAULT>::getOutIndexes(Index srcVertIndex) const {
        const VertTy& srcVert = _vertice[srcVertIndex];
        std::vector<Index> outIndexes;
        for (ArcPtr iter = srcVert.firstOut; iter != nullptr; iter = iter->forward) {
            outIndexes.push_back(iter->dstVertIndex);
        }
        return outIndexes;
    }

    template<class VertDataTy, class WeightTy, WeightTy W_DEFAULT>
    std::vector<Index> Graph<VertDataTy, WeightTy, W_DEFAULT>::getInIndexes(Index dstVertIndex) const {
        const VertTy& dstVert = _vertice[dstVertIndex];
        std::vector<Index> inIndexes;
        for (ArcPtr iter = dstVert.firstIn; iter != nullptr; iter = iter->backward) {
            inIndexes.push_back(iter->srcVertIndex);
        }
        return inIndexes;
    }
}
