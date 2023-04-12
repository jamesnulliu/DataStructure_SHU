#pragma once
#include <climits>
#include <memory>

namespace gol {
    using Index = long long;
    using Size = long long;

    template<class WeightTy = int, WeightTy UNLINK = INT_MAX>
    struct GOL_Arc
    {
        using ArcTy = GOL_Arc<WeightTy, UNLINK>;
        using ArcPtr = std::shared_ptr<GOL_Arc<WeightTy, UNLINK>>;
        enum class Tag { UNVISITED, VISITED };

        Tag      tag = { Tag::UNVISITED };
        WeightTy weight = { UNLINK };
        Index    vertFrom = {};
        ArcPtr   arcTo = {};
        Index    vertTo = {};
        ArcPtr   arcFrom = {};
    };
}