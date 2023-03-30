#include "myExceptions.h"
#include "../../06_Tree_Forest/LinkedBinaryTree/LinkedBinaryTree.h"
#include <utility>

template<class T>
class maxHBLT :
    public linkedBinaryTree<T>
{
public:
    maxHBLT() {}
    void initialize(T* theElements, int theSize);

public:
    /**
     * @brief Meld "theHblt" into "*this", and reallocate nullptr to "theHblt->root".
     * @param theHblt The melded HBLT.
    */
    void meld(maxHBLT<T>& theHblt);
    void push(const T& theElement);
    void pop();
    static void postOrder(void(*theVisit)(binaryTreeNode<std::pair<int, T>>*))
    {
        visit = theVisit; postOrder(_root);
    }
private:
    /**
     * @brief Meld an HBLT "*y" into another HBLT "*x".
     * @param x The root of one HBLT where the result stores in.
     * @param y The root of one HBLT which is melded into "*x".
    */
    void m_meld(binaryTreeNode<std::pair<int, T>>*& x, binaryTreeNode<std::pair<int, T>>*& y);
    void erase() { postOrder(dispose); }
    static void (*visit)(binaryTreeNode<std::pair<int, T>>* t);
    static void dispose(binaryTreeNode<std::pair<int, T>>* t) { delete t; }
private:
    static void postOrder(binaryTreeNode<std::pair<int, T>>* _root);
private:
    int& treeSize = linkedBinaryTree<T>::treeSize;
    binaryTreeNode<std::pair<int, T>>* _root;
};

template<class T>
void maxHBLT<T>::initialize(T* theElement, int theSize)
{
    arrayQueue<binaryTreeNode<std::pair<int, T>>*> q(theSize);
    erase();
    for (int i = 1; i <= theSize; i++) {
        q.push(new binaryTreeNode<std::pair<int, T>>(std::pair<int, T>(1, theElement[i])));
    }
    for (int i = 1; i <= theSize; i++) {
        binaryTreeNode<std::pair<int, T>>* b = q.front();
        q.pop();
        binaryTreeNode<std::pair<int, T>>* c = q.front();
        q.pop();
        m_meld(b, c);
        q.push(b);
    }
    if (theSize > 0) {
        _root = q.front;
    }
    treeSize = theSize;
}

template<class T>
void maxHBLT<T>::meld(maxHBLT<T>& theHblt)
{
    m_meld(_root, theHblt._root);
    treeSize += theHblt.treeSize;
    theHblt._root = nullptr;
    theHblt.size = 0;
}

template<class T>
void maxHBLT<T>::m_meld(binaryTreeNode<std::pair<int, T>>*& x,
    binaryTreeNode<std::pair<int, T>>*& y)
{
    if (y == nullptr) { return; }
    // When {x} is the rightest external node, replace {x=nullptr} with {y}.
    if (x == nullptr) {
        x = y; // meld
        return;
    }

    // Make sure meld tree with smaller root to the one with a larger.
    // Notice that {std::swap(ptr_1,ptr_2)} exchanges the content in two addresses.
    // The result is that PARENT of x points to the same address with different content (of y), same to y.
    if (x->element.second < y->element.second) { std::swap(x, y); }

    // Suppose that "m_meld(x->rightChild, y)" can meld the subtree
    // whose root is"x->rightChild" with whose is "y".
    m_meld(x->rightChild, y);

    // After right subtree of 'x' is melded with tree 'y',
    // following code adjests the tree whose root is "x" to an HBLT.
    if (x->leftChild == nullptr) {
        /*******************
        *   9          9   *
        *    \   ->   /    *
        *     7      7     *
        ********************/
        // "std::swap()" costs 3 steps, but here we only spends 2 steps.
        x->leftChild = x->rightChild;
        x->rightChild = nullptr;

        // Reset the value of "s(x)".
        x->element.first = 1;
    } else {
        /**********************
        *   9             9   *
        *  / \     ->    / \  *
        * 7   8         8   7 *
        *    / \       / \    *
        *   6   4     6   4   *
        ***********************/
        // Make sure the "s(x->leftChild)" is larger than "s(x->rightChild)".
        if (x->leftChild->element.first < x->rightChild->element.first) {
            // If not smaller, exchange "x->leftChild" and "x->rightChild".
            std::swap(x->leftChild, x->rightChild);
            // Reset the value of "s(x)".
            x->element.first = x->rightChild->element.first + 1;
        }
    }
}

template<class T>
void maxHBLT<T>::push(const T& theElement)
{
    binaryTreeNode<std::pair<int, T>>* q =
        new binaryTreeNode<std::pair<int, T>>(std::pair<int, T>(1, theElement));
    meld(_root, q);
    treeSize++;
}

template<class T>
void maxHBLT<T>::pop()
{
    if (_root == nullptr) {
        throw queueEmpty();
    }
    binaryTreeNode<std::pair<int, T>>* left = _root->leftChild;
    binaryTreeNode<std::pair<int, T>>* right = _root->rightChild;
    delete _root;
    _root = left;
    meld(_root, right);
    treeSize--;
}

template<class T>
void maxHBLT<T>::postOrder(binaryTreeNode<std::pair<int, T>>* _root)
{
    if (_root == nullptr) return;
    postOrder(_root->leftChild);
    postOrder(_root->rightChild);
    binaryTreeNode<T>::visit(_root);
}