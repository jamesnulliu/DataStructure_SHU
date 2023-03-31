#include <iostream>
#include "06_Tree_Forest/Forest/Tree.h"
#include "06_Tree_Forest/Forest/Tree_binary.h"
#include "06_Tree_Forest/Forest/Forest.h"

using namespace std;

int main()
{
    Tree<char> tree1;
    tree1.build();
    puts("");
    Tree<char> tree2;
    tree2.build();
    puts("");
    Tree<char> tree3;
    tree3.build();
    puts("");

    Forest<char> forest;
    forest.insert(tree1);
    forest.insert(tree2);
    forest.insert(tree3);
    forest.preorderVisit(forest.get_root());
}