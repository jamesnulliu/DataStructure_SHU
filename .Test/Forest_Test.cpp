#include "Test.h"

#include <iostream>
#include "../06_Tree_Forest/Forest/Tree.h"
#include "../06_Tree_Forest/Forest/Tree_binary.h"
#include "../06_Tree_Forest/Forest/Forest.h"

using namespace std;


void Forest_test()
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
    puts("Preorder: ");
    forest.preorder_visit();
    puts("\nInorder: ");
    forest.inorder_visit();
    puts("\nPostorder: ");
    forest.postorder_visit();

    puts("\n\nLeaves:");
    std::cout << forest.count_leaves();
    puts("\nHeight:");
    std::cout << forest.count_height();
}