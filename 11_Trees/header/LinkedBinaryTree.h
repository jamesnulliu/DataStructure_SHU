#pragma once
#include <cmath>
#include "BInaryTree.h"
#include "BinaryTreeNode.h"
#include "../../09_Queue/header/arrayQueue.h"
#include "../../08_Stack/class/arrayStack.h"
template<class E>
class linkedBinaryTree :
    public binaryTree<binaryTreeNode<E>>
{
public:
    linkedBinaryTree() { root = nullptr; treeSize = 0; }
    linkedBinaryTree(const linkedBinaryTree<E>& theTree);
    ~linkedBinaryTree() { erase(); }
    bool empty() const { return treeSize == 0; }
    int size() const { return treeSize; }
    void erase() { postOrder(dispose); root = nullptr; treeSize = 0; }
public:
    void preOrder(void(*theVisit)(binaryTreeNode<E>*)) { visit = theVisit; preOrder(root); }
    void preOrder_iterative(void(*theVisit)(binaryTreeNode<E>*)) { visit = theVisit; preOrder_iterative(root); }
    void preOrderOutput() { preOrder(output); std::cout << std::endl; }

    void inOrder(void(*theVisit)(binaryTreeNode<E>*)) { visit = theVisit; inOrder(root); }
    void inOrder_iterative(void(*theVisit)(binaryTreeNode<E>*)) { visit = theVisit; inOrder_iterative(root); }
    void inOrderOutput() { inOrder(output); std::cout << std::endl; }

    void postOrder(void(*theVisit)(binaryTreeNode<E>*)) { visit = theVisit; postOrder(root); }
    void postOrderOutput() { postOrder(output); std::cout << std::endl; }

    void levelOrder(void(*theVisit)(binaryTreeNode<E>*)) { visit = theVisit; levelOrder(root); }
    void levelOrderOutput() { levelOrder(output); std::cout << std::endl; }
public:
    int height() const { return height(root); }
    /**
    * @brief	Compare "*this" and "theTree" in an iterative way.
    * @param	theTree The compared tree.
    * @return	<true>-Two trees are completely the same; <false>-Otherwise.
    */
    bool compare(const linkedBinaryTree<E>& theTree);
    /**
    * @breif	Compare "*this" and "theTree" in a recursive way.
    */
    bool compare_recursive(const linkedBinaryTree<E>& theTree);
    void swapTrees(binaryTreeNode<E>* t);
    int maxHeightDifference(const binaryTreeNode<E>* t);
protected:
    binaryTreeNode<E>* root;	// The pointer points to the root of the tree.
    int treeSize;				// The number of the nodes of the tree.
private:
    /**
    * @brief	Static function; output the nodes.
    * @param	"visit" The function pointer which points to "output()".
    */
    static void (*visit)(binaryTreeNode<E>* t);
    static void output(binaryTreeNode<E>* t) { std::cout << t->element << ' '; }
    static void get(binaryTreeNode<E>* t) {}
    static void dispose(binaryTreeNode<E>* t) { delete t; }
private:
    // The purpose of static function mainly is for get access to a static member/method.
    static void preOrder(binaryTreeNode<E>* t);
    static void preOrder_iterative(binaryTreeNode<E>* t);
    static void inOrder(binaryTreeNode<E>* t);
    static void inOrder_iterative(binaryTreeNode<E>* t);
    static void postOrder(binaryTreeNode<E>* t);
    static void levelOrder(binaryTreeNode<E>* t);
private:
    int* levelCount(binaryTreeNode<E>* t);
    int height(binaryTreeNode<E>* t);
    bool m_compare_recursive(binaryTreeNode<E>* t1, binaryTreeNode<E>* t2);
    // Not finished!
    void m_heightDifference(const binaryTreeNode<E>* t, int* height, int curHeight);
};

template<class E>
linkedBinaryTree<E>::linkedBinaryTree(const linkedBinaryTree<E>& theTree)
{
    // If "theTree" has no node, return.
    if (!(treeSize = theTree.treeSize)) return;
    // Initialize "this->root" with "theTree->root".
    root = new binaryTreeNode<E>(theTree.root->element);
    // Create the iterator for two root.
    binaryTreeNode<E>* tA = root;
    const binaryTreeNode<E>* tB = theTree.root;
    // Create the stack for iteration.
    arrayStack<binaryTreeNode<E>*> s;
    bool flag = true;
    // The following iteration is base on fuction "inorder_iterative".
    while (true) {
        if (flag) {
            flag = false;
            s.push(tB);
            while (tB->leftChild != nullptr) {
                s.push(tB = tB->leftChild);
                tA = tA->leftChild = new binaryTreeNode<E>(tB->element);
            }
        }
        s.pop();
        if (tB->rightChild != nullptr) {
            tB = tB->rightChild;
            tA = tA->rightChild = new binaryTreeNode<E>(tB->element);
            flag = true;
            continue;
        }
        try { tB = s.top(); } catch (stackEmpty) { return; }
    }
}

template<class E>
void linkedBinaryTree<E>::preOrder(binaryTreeNode<E>* t)
{
    if (t != nullptr) {
        linkedBinaryTree<E>::visit(t);
        preOrder(t->leftChild);
        preOrder(t->rightChild);
    }
}
template<class E>
void linkedBinaryTree<E>::preOrder_iterative(binaryTreeNode<E>* t)
{
    arrayStack<binaryTreeNode<E>*> s;
    // At first, "flag" is "true", indicating that it is the first iteration.
    // Then, only when we step into a right child, "flag" will turn to "true", otherwise is "false".
    bool flag = true;
    // The following iteration is based on fuction "inorder_iterative".
    while (true) {
        if (flag) {
            flag = false;
            s.push(t);
            linkedBinaryTree::visit(t);
            while (t->leftChild != nullptr) {
                s.push(t = t->leftChild);
                linkedBinaryTree::visit(t);
            }
        }
        s.pop();
        if (t->rightChild != nullptr) {
            t = t->rightChild;
            flag = true;
            continue;
        }
        try { t = s.top(); } catch (stackEmpty) { return; }
    }
}

template<class E>
void linkedBinaryTree<E>::inOrder(binaryTreeNode<E>* t)
{
    if (t != nullptr) {
        inOrder(t->leftChild);
        linkedBinaryTree<E>::visit(t);
        inOrder(t->rightChild);
    }
}
template<class E>
void linkedBinaryTree<E>::inOrder_iterative(binaryTreeNode<E>* t)
{
    arrayStack<binaryTreeNode<E>*> s;
    // At first, "flag" is "true", indicating that it is the first iteration.
    // Then, only when we step into a right child, "flag" will turn to "true", otherwise is "false".
    bool flag = true;
    while (true) {
        // IF: "flag" is "true", which means if it is the first iteration or we stepped into a right child in last iteration.
        if (flag) {
            // Switch "flag" to "false".
            flag = false;
            // Push "t" to the stack;
            // "t" indicates either the root of the tree, or the right child we stepped into in last iteration.
            s.push(t);
            // Push the left children to the stack.
            while (t->leftChild != nullptr) {
                s.push(t = t->leftChild);
            }
        }
        visit(t);
        s.pop();
        // IF: "t" has a right child.
        if (t->rightChild != nullptr) {
            t = t->rightChild;
            flag = true;
            continue;
        }
        // IF: stack is empty, means that the iteration is over.
        try { t = s.top(); } catch (stackEmpty) { return; }
    }
}

template<class E>
void linkedBinaryTree<E>::postOrder(binaryTreeNode<E>* t)
{
    if (t != nullptr) {
        postOrder(t->leftChild);
        postOrder(t->rightChild);
        linkedBinaryTree<E>::visit(t);
    }
}

template<class E>
void linkedBinaryTree<E>::levelOrder(binaryTreeNode<E>* t)
{
    arrayQueue<binaryTreeNode<E>*> q;
    while (t != nullptr) {
        linkedBinaryTree<E>::visit(t);
        // Insert "t"'s children to the queue.
        if (t->leftChild != nullptr) {
            q.push(t->leftChild);
        }
        if (t->rightChild != nullptr) {
            q.push(t->rightChid);
        }
        // Extract next node to visit.
        try { t = q.front(); } catch (queueEmpty) { return; }
        q.pop();
    }
}

template<class E>
int linkedBinaryTree<E>::height(binaryTreeNode<E>* t)
{
    if (t == nullptr) return 0;
    int hL = height(t->leftChild);
    int hR = height(t->rightChild);
    if (hL > hR) return ++hL;
    else return ++hR;
}

template<class E>
int* linkedBinaryTree<E>::levelCount(binaryTreeNode<E>* t)
{
    arrayQueue<binaryTreeNode<E>*> q;
    // Save space but waste time:
    // int* counter = new int[ceil(log(treeSize + 1) / log(2))];
    int* counter = new int[treeSize];
    int theLevel = 1;
    int buffer[2] = { 1, 0 };
    while (t != nullptr) {
        visit(t);
        if (t->leftChild != nullptr) {
            q.push(t->leftChild);
            buffer[(theLevel + 1) % 2]++;
            counter[theLevel + 1]++;
        }
        if (t->rightChild != nullptr) {
            q.push(t->rightChild);
            buffer[(theLevel + 1) % 2]++;
            counter[theLevel + 1]++;
        }
        try { t = q.front(); } catch (queueEmpty) { return counter; }
        q.pop();
        if (--buffer[theLevel % 2] == 0) {
            std::cout << std::endl;
            theLevel++;
        }
    }
}

template<class E>
bool linkedBinaryTree<E>::compare(const linkedBinaryTree<E>& theTree)
{
    if (treeSize != theTree.size) return false;
    const binaryTreeNode<E>* tA = root, * tB = theTree.root;
    // Create the stack for iteration.
    arrayStack<binaryTreeNode<E>*> sA, sB;
    bool flag = true;
    // The following iteration is base on fuction "inorder_iterative".
    while (true) {
        // Return ocassion 1: The element is different, return false.
        if (tA->element != tB->element) return false;
        if (flag) {
            flag = false;
            sA.push(tA);
            sB.push(tB);
            while (tA->leftChild != nullptr) {
                // Return ocassion 2: While "tA" is going left but "tB" has no left child, return false.
                // But perhaps tB has more left child, so see Return ocassion 3.
                if (tB->leftChild == nullptr) return false;
                sA.push(tA = tA->leftChild);
                sB.push(tB = tB->leftChild);
            }
            // Return ocassion 3: "tA" has no left child but "tB" has, return false.
            if (tB->leftChild != nullptr) return false;
        }
        sA.pop();
        sB.pop();
        if (tA->rightChild != nullptr) {
            // Return ocassion 3: "tA" has right child but "tB" does not, return false.
            if (tB->rightChild == nullptr) return false;
            tA = tA->rightChild;
            tB = tB->rightChild;
            flag = true;
            continue;
        }
        try { tB = sA.top(); } catch (stackEmpty) { return true; }
    }
}
template<class E>
bool linkedBinaryTree<E>::compare_recursive(const linkedBinaryTree<E>& theTree)
{
    if (treeSize != theTree.size) return false;
    return m_compare_recursive(root, theTree.root);
}
template<class E>
bool linkedBinaryTree<E>::m_compare_recursive(binaryTreeNode<E>* t1, binaryTreeNode<E>* t2)
{
    if (t1 && t2 && t1->element == t2->element) {
        if (m_compare_recursive(t1->leftChild, t2->leftChild) && m_compare_recursive(t1->rightChild, t2->rightChild)) {
            return true;
        } else {
            return false;
        }
    } else if (t1 == nullptr && t2 == nullptr) {
        return true;
    } else {
        return false;
    }
}

template<class E>
void linkedBinaryTree<E>::swapTrees(binaryTreeNode<E>* t)
{
    if (t == nullptr) return;
    swapTrees(t->leftChild);
    swapTrees(t->rightChild);
    std::swap(t->leftChild, t->rightChild);
}

template<class E>
int linkedBinaryTree<E>::maxHeightDifference(const binaryTreeNode<E>* t)
{
    int height[2] = { 0 };
    m_heightDifference(t, height, 0);
    return height[1] - height[0];
}
template<class E>
void linkedBinaryTree<E>::m_heightDifference(const binaryTreeNode<E>* t, int* height, int curHeight)
{
    if (t == nullptr) {
        --curHeight < height[0] ? (height[0] = curHeight) : (curHeight > height[1]) ? (height[1] = curHeight) : 1;
        return;
    }
    maxHeightDifference(t->leftChild, height, curHeight + 1);
    maxHeightDifference(t->rightChild, height, curHeight + 1);
}
