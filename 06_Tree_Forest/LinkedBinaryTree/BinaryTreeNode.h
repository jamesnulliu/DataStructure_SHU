#pragma once
#include <iostream>
template<class T>
struct binaryTreeNode
{
    T element;
    binaryTreeNode<T>* leftChild, * rightChild;
    binaryTreeNode() { leftChild = rightChild = nullptr; }
    binaryTreeNode(const T& theElement)
    {
        element(theElement);
        leftChild = rightChild = nullptr;
    }
    binaryTreeNode(const T& theElement, binaryTreeNode* theLeftChild, binaryTreeNode* theRightChild)
    {
        element(theElement);
        leftChild = theLeftChild;
        rightChild = theRightChild;
    }
};

/**
* @brief	Output fully bracked infix math expression.
* @param	t The tree.
*/
template<class T>
void infix(binaryTreeNode<T>* t)
{
    if (t != nullptr) {
        std::cout << '(';
        infix(t->leftChild);
        std::cout << t->element;
        infix(t->rightChild);
        std::cout << ')';
    }
}
