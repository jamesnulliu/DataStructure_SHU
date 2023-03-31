#include <iostream>
#include <algorithm>
#include <vector>
#include "07_Graph/Graph_AM/Graph_AM.h"
#include <ranges>
#include "06_Tree_Forest/Forest/Tree.h"
#include "06_Tree_Forest/Forest/Tree_binary.h"

using namespace std;

int main()
{
    //istringstream istr("a b");
    //char aa;
    ////cout << istr.good();
    ////istr >> aa;
    ////cout << istr.good();
    ////istr >> aa;
    ////cout << istr.good();
    ////istr >> aa;
    ////cout << istr.good();

    //while (istr.good()) {
    //    cout << istr.good();
    //    istr >> aa;
    //    cout << aa << endl;
    //}
    Tree<int> tree;
    tree.build();

    Tree_binary<int> btree(tree);
}