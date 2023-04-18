#include <iostream>
#include "../07_Graph/Graph_OrthogonalList/Graph_OrthogonalList.h"

void test_gol() {
    GOL::Graph<> graph;
    graph.insertVert('A');
    graph.insertVert('B');
    graph.insertVert('C');
    GOL::Index indexA = graph.findVertIndex('A');
    GOL::Index indexB = graph.findVertIndex('B');
    GOL::Index indexC = graph.findVertIndex('C');
    {
        std::cout << "Check vertices: \n";
        std::cout << graph.getVertByIndex(indexA) << std::endl;
        std::cout << graph.getVertByIndex(indexB) << std::endl;
        std::cout << graph.getVertByIndex(indexC) << std::endl;
        std::cout << std::endl;
    }

    {
        std::cout << "Check arc-insert: \n";
        graph.insertArcByIndex(indexA, indexB, 10);
        graph.insertArcByIndex(indexA, indexC, 20);
        graph.insertArcByIndex(indexB, indexC, 30);
        graph.insertArcByIndex(indexC, indexB, 40);
        auto arcABptr = graph.getArcByIndex(indexA, indexB);
        std::cout << arcABptr->srcVertIndex << " to " << arcABptr->dstVertIndex << ", w: " << arcABptr->weight << std::endl;
        auto arcACptr = graph.getArcByIndex(indexA, indexC);
        std::cout << arcACptr->srcVertIndex << " to " << arcACptr->dstVertIndex << ", w: " << arcACptr->weight << std::endl;
        auto arcBCptr = graph.getArcByIndex(indexB, indexC);
        std::cout << arcBCptr->srcVertIndex << " to " << arcBCptr->dstVertIndex << ", w: " << arcBCptr->weight << std::endl;
        auto arcCBptr = graph.getArcByIndex(indexC, indexB);
        std::cout << arcCBptr->srcVertIndex << " to " << arcCBptr->dstVertIndex << ", w: " << arcCBptr->weight << std::endl;
        std::cout << std::endl;
    }

    {
        std::cout << "Check arc-erase: \n";
        graph.eraseArcByIndex(indexB, indexC);
        auto arcBCptr = graph.getArcByIndex(indexB, indexC);
        if (arcBCptr == nullptr) { std::cout << "B->C erased\n"; }
        auto arcABptr = graph.getArcByIndex(indexA, indexB);
        std::cout << arcABptr->srcVertIndex << " to " << arcABptr->dstVertIndex << ", w: " << arcABptr->weight << std::endl;
        auto arcACptr = graph.getArcByIndex(indexA, indexC);
        std::cout << arcACptr->srcVertIndex << " to " << arcACptr->dstVertIndex << ", w: " << arcACptr->weight << std::endl;
        auto arcCBptr = graph.getArcByIndex(indexC, indexB);
        std::cout << arcCBptr->srcVertIndex << " to " << arcCBptr->dstVertIndex << ", w: " << arcCBptr->weight << std::endl;

        graph.eraseArcByIndex(indexA, indexC);
        arcACptr = graph.getArcByIndex(indexA, indexC);
        if (arcACptr == nullptr) { std::cout << "A->C erased\n"; }
        arcABptr = graph.getArcByIndex(indexA, indexB);
        std::cout << arcABptr->srcVertIndex << " to " << arcABptr->dstVertIndex << ", w: " << arcABptr->weight << std::endl;
        arcCBptr = graph.getArcByIndex(indexC, indexB);
        std::cout << arcCBptr->srcVertIndex << " to " << arcCBptr->dstVertIndex << ", w: " << arcCBptr->weight << std::endl;
    }

    return;
}