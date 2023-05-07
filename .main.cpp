#include "06_Tree_Forest/BTree/BTree.hpp"

int main()
{
    BTree<int, 4> tree;
    tree.insert(10);
    tree.insert(20);
    tree.insert(30);
    tree.insert(40);
    tree.insert(50);
    tree.insert(60);
    tree.insert(45);
    tree.insert(46);
    tree.insert(44);
    tree.insert(43);
    tree.insert(42);
    tree.printTree();
    tree.erase(40);
    tree.printTree();
    tree.erase(44);
    tree.printTree();
    tree.erase(43);
    tree.printTree();
}