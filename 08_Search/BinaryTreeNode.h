#pragma once
#include <iostream>

template<class T>
struct BinaryTreeNode
{
    T element;
    BinaryTreeNode<T>* leftChild{ nullptr };
    BinaryTreeNode<T>* rightChild{ nullptr };
};

/**
* @brief	Output fully bracked infix math expression.
* @param	t The tree.
*/
template<class T>
void infix(BinaryTreeNode<T>* t)
{
    if (t != nullptr) {
        std::cout << '(';
        infix(t->leftChild);
        std::cout << t->element;
        infix(t->rightChild);
        std::cout << ')';
    }
}
