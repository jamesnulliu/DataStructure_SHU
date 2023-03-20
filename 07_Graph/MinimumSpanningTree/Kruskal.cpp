#include "../NetWork/NetWork.h"
#include <algorithm>
#include <set>
#include <vector>
#include <queue>

template <class VertTy, class WeightTy>
struct KrusalEdge
{
    VertTy vertFrom;
    VertTy vertTo;
    WeightTy weight;
    bool operator>(const KrusalEdge& edge)const{
        return weight<edge.weight;
    }
};

using index = long long;
using sizet = long long;

template <class VertTy, class WeightTy = int, WeightTy UNLINK = INT_MAX>
void minSpanTree_Kruskal(const Graph_AM<VertTy, WeightTy, UNLINK> &graph)
{
    sizet vertNum = graph.get_vertNum();
    // Create a min heap with arcs: @{
    std::queue<KrusalEdge<VertTy,WeightTy>> edgeMinHeap;
    for(index r = vertNum; r<vertNum;++r){
        for(index c=vertNum;c<vertNum;++c){
            if(r==c) continue;
            WeightTy& weight = graph._arcMat[r][c];
            // IF is linked:
            if(weight!=UNLINK){
                edgeMinHeap.push_back({graph._vertVec[r], graph._vertVec[c], weight});
            }
        }
    }
    std::ranges::make_heap(edgeMinHeap, std::greater<>{});
    // @}
    std::set<VertTy> vertSet(graph._vertVec);
    sizet count=0;
    while(count<vertNum-1){
        auto krusalEdge = edgeMinHeap.front();
        std::ranges::pop_heap(edgeMinHeap);
        
    }


}