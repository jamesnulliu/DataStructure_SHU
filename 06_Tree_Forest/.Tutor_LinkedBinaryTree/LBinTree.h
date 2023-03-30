// Linked Binary Tree
#pragma once
#include <iostream>
#include <vector>
#include <deque>
#include <algorithm>

// Linked Binary Tree Node
template<class VertTy>
struct LBTNode
{
    VertTy data;
    LBTNode* left_;
    LBTNode* right;
};

// Linked Binary Tree
template<class VertTy>
class LBinTree
{
public:
    LBinTree() {}

public:
    void preOrder___print();
    void inOrder____print();
    void postOrder__print();
    void levelOrder_print();

    size_t size();
    size_t height(LBTNode<VertTy>* t);
    LBTNode<VertTy>* find_dfs(const VertTy& elem);
    LBTNode<VertTy>* find_bfs(const VertTy& elem);
    LBTNode<VertTy>* findParent(LBTNode<VertTy>* target);

    void insert_to_left_(const VertTy& elem, LBTNode<VertTy>* parent);
    void insert_to_right(const VertTy& elem, LBTNode<VertTy>* parent);

private:
    // PreOrder recursion body:
    template<class _Pred>
    void preOrder___recBody(LBTNode<VertTy>* t, const _Pred& pred);
    // InOrder recursion body:
    template<class _Pred>
    void inOrder____recBody(LBTNode<VertTy>* t, const _Pred& pred);
    // PostOrder recursion body:
    template<class _Pred>
    void postOrder__recBody(LBTNode<VertTy>* t, const _Pred& pred);
    // LevelOrder non-recursion body:
    template<class _Pred>
    void levelOrder_bfsBody(LBTNode<VertTy>* t, const _Pred& pred);
    // Recursion body of {find_dfs()}:
    void find_dfs_recBody(LBTNode<VertTy>* t, const VertTy& target);

private:
    LBTNode<VertTy>* _root;
};

template<class VertTy>
void LBinTree<VertTy>::preOrder___print() {
    // Function object:
    //----------------------------------------------------------------------------
    // struct Visit {
    //     void operator()(LBTNode<ElemTy>* node) { std::cout << node->data; }
    // };
    // Visit visit;
    // visit(x); // Invoke operator() to output.
    //----------------------------------------------------------------------------
    // Lambda expression:
    // {visit} is a function.
    auto visit = [](LBTNode<VertTy>* node) {
        std::cout << node->data;
    };
    // visit(x); // Invoke function {visit} to output.
    this->preOrder___recBody(this->_root, visit);
}

template<class VertTy>
void LBinTree<VertTy>::inOrder____print() {
    this->inOrder____recBody(this->_root, [](LBTNode<VertTy>* node) { std::cout << node->data; });
}

template<class VertTy>
void LBinTree<VertTy>::postOrder__print() {
    this->postOrder__recBody(this->_root, [](LBTNode<VertTy>* node) { std::cout << node->data; });
}

template<class VertTy>
void LBinTree<VertTy>::levelOrder_print() {
    this->levelOrder_bfsBody(this->_root, [](LBTNode<VertTy>* node) { std::cout << node->data; });
}

template<class VertTy>
size_t LBinTree<VertTy>::size() {
    size_t numOfNode = 0;
    this->preOrder___recBody(this->_root, [&numOfNode](LBTNode<VertTy>* t) { ++numOfNode; });
    return numOfNode;
}

template<class VertTy>
size_t LBinTree<VertTy>::height(LBTNode<VertTy>* t) {
    if (t == nullptr) { return 0; }
    size_t leftH = height(t->left_);
    size_t rightH = height(t->right);
    return std::max(leftH, rightH) + 1;
}

template<class VertTy>
LBTNode<VertTy>* LBinTree<VertTy>::find_dfs(const VertTy& elem) {
    LBTNode<VertTy>* ptr = nullptr;
    try {
        find_dfs_recBody(this->_root, elem);
    } catch (LBTNode<VertTy>* result) {
        ptr = result;
    }
    return ptr;
}

template<class VertTy>
void LBinTree<VertTy>::find_dfs_recBody(LBTNode<VertTy>* t, const VertTy& elem) {
    if (t == nullptr) { return; }
    // IF {elem} is found, throw the pointer:
    if (t->data == elem) { throw t; }
    find_dfs_recBody(t->left_, elem);
    find_dfs_recBody(t->right, elem);
}

template<class VertTy>
LBTNode<VertTy>* LBinTree<VertTy>::find_bfs(const VertTy& elem) {
    if (this->_root == nullptr) { return nullptr; }
    std::deque<LBTNode<VertTy>*> que;
    que.push_back(this->_root);
    while (!que.empty()) {
        auto front = que.front();
        que.pop_front();
        // IF {elem} is found, directly return the result:
        if (front->data == elem) { return front; }
        // Push queue @{
        if (front->left_ != nullptr) { que.push_back(front->left_); }
        if (front->right != nullptr) { que.push_back(front->right); }
        // @}
    }
    return nullptr;
}

template<class VertTy>
LBTNode<VertTy>* LBinTree<VertTy>::findParent(LBTNode<VertTy>* target) {
    if (this->_root == nullptr) { return nullptr; }
    if (this->_root == target) { return nullptr; }
    std::deque<LBTNode<VertTy>*> que;
    que.push_back(this->_root);
    while (!que.empty()) {
        auto front = que.front();
        que.pop_front();
        if (front->left_ == target || front->right == target) { return front; }
        // Push queue @{
        if (front->left_ != nullptr) { que.push_back(front->left_); }
        if (front->right != nullptr) { que.push_back(front->right); }
        // @}
    }
    return nullptr;
}

template<class VertTy>
void LBinTree<VertTy>::insert_to_left_(const VertTy& elem, LBTNode<VertTy>* parent) {
    auto node = new LBTNode<VertTy>{ elem,nullptr,nullptr };
    if (this->_root == nullptr) {
        _root = node;
    } else if (parent == nullptr) {
        node->left_ = this->_root;
        this->_root = node;
    } else {
        node->left_ = parent->left_;
        parent->left_ = node;
    }
}

template<class VertTy>
void LBinTree<VertTy>::insert_to_right(const VertTy& elem, LBTNode<VertTy>* parent) {
    auto node = new LBTNode<VertTy>{ elem,nullptr,nullptr };
    if (this->_root == nullptr) {
        _root = node;
    } else if (parent == nullptr) {
        node->right = this->_root;
        this->_root = node;
    } else {
        node->right = parent->right;
        parent->right = node;
    }
}

template<class VertTy> // In template class {LBinTree},
template<class _Pred>  // there is a template function {re_pre__Order}:
void LBinTree<VertTy>::preOrder___recBody(LBTNode<VertTy>* t, const _Pred& pred) {
    if (t == nullptr) return;
    pred(t);
    this->preOrder___recBody(t->left_, pred);
    this->preOrder___recBody(t->right, pred);
}

template<class VertTy> // In template class {LBinTree},
template<class _Pred>  // there is a template function {re_pre__Order}:
void LBinTree<VertTy>::inOrder____recBody(LBTNode<VertTy>* t, const _Pred& pred) {
    if (t == nullptr) return;
    this->inOrder____recBody(t->left_, pred);
    pred(t);
    this->inOrder____recBody(t->right, pred);
}

template<class VertTy> // In template class {LBinTree},
template<class _Pred>  // there is a template function {re_pre__Order}:
void LBinTree<VertTy>::postOrder__recBody(LBTNode<VertTy>* t, const _Pred& pred) {
    if (t == nullptr) return;
    this->postOrder__recBody(t->left_, pred);
    this->postOrder__recBody(t->right, pred);
    pred(t);
}

template<class VertTy> // In template class {LBinTree},
template<class _Pred>  // there is a template function {re_pre__Order}:
void LBinTree<VertTy>::levelOrder_bfsBody(LBTNode<VertTy>* t, const _Pred& pred) {
    // IF the tree is empty, return directly:
    if (this->_root == nullptr) return;
    // Create a queue for board-first-serach:
    std::deque< LBTNode<VertTy>* > que;
    // Push non-empty root to {queue}:
    // [Note] The {push} operation creates A NEW POINTER, and copy the value from parameter.
    //        So you should never build a queue of reference (e.g., deque<int&> que),
    //        becase when pushing, you cannot create a NEW reference object!
    que.push_back(this->_root);
    // Loop while there is still nodes in queue:
    while (!que.empty()) {
        LBTNode<VertTy>* front = que.front(); // Get front node.
        que.pop_front();                      // Pop queue.
        pred(front);
        // Push queue @{
        if (front->left_ != nullptr) { que.push_back(front->left_); }
        if (front->right != nullptr) { que.push_back(front->right); }
        // @}
    }
}
