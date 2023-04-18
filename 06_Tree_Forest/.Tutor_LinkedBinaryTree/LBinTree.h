// Linked Binary Tree
#pragma once
#include <iostream>
#include <vector>
#include <deque>
#include <algorithm>

// Linked Binary Tree Node
template<class VertDataTy>
struct LBTNode
{
    VertDataTy data;
    LBTNode* left_;
    LBTNode* right;
};

// Linked Binary Tree
template<class VertDataTy>
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
    size_t height(LBTNode<VertDataTy>* t);
    LBTNode<VertDataTy>* find_dfs(const VertDataTy& elem);
    LBTNode<VertDataTy>* find_bfs(const VertDataTy& elem);
    LBTNode<VertDataTy>* findParent(LBTNode<VertDataTy>* target);

    void insert_to_left_(const VertDataTy& elem, LBTNode<VertDataTy>* parent);
    void insert_to_right(const VertDataTy& elem, LBTNode<VertDataTy>* parent);

private:
    // PreOrder recursion body:
    template<class _Pred>
    void preOrder___recBody(LBTNode<VertDataTy>* t, const _Pred& pred);
    // InOrder recursion body:
    template<class _Pred>
    void inOrder____recBody(LBTNode<VertDataTy>* t, const _Pred& pred);
    // PostOrder recursion body:
    template<class _Pred>
    void postOrder__recBody(LBTNode<VertDataTy>* t, const _Pred& pred);
    // LevelOrder non-recursion body:
    template<class _Pred>
    void levelOrder_bfsBody(LBTNode<VertDataTy>* t, const _Pred& pred);
    // Recursion body of {find_dfs()}:
    void find_dfs_recBody(LBTNode<VertDataTy>* t, const VertDataTy& target);

private:
    LBTNode<VertDataTy>* _root;
};

template<class VertDataTy>
void LBinTree<VertDataTy>::preOrder___print() {
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
    auto visit = [](LBTNode<VertDataTy>* node) {
        std::cout << node->data;
    };
    // visit(x); // Invoke function {visit} to output.
    this->preOrder___recBody(this->_root, visit);
}

template<class VertDataTy>
void LBinTree<VertDataTy>::inOrder____print() {
    this->inOrder____recBody(this->_root, [](LBTNode<VertDataTy>* node) { std::cout << node->data; });
}

template<class VertDataTy>
void LBinTree<VertDataTy>::postOrder__print() {
    this->postOrder__recBody(this->_root, [](LBTNode<VertDataTy>* node) { std::cout << node->data; });
}

template<class VertDataTy>
void LBinTree<VertDataTy>::levelOrder_print() {
    this->levelOrder_bfsBody(this->_root, [](LBTNode<VertDataTy>* node) { std::cout << node->data; });
}

template<class VertDataTy>
size_t LBinTree<VertDataTy>::size() {
    size_t numOfNode = 0;
    this->preOrder___recBody(this->_root, [&numOfNode](LBTNode<VertDataTy>* t) { ++numOfNode; });
    return numOfNode;
}

template<class VertDataTy>
size_t LBinTree<VertDataTy>::height(LBTNode<VertDataTy>* t) {
    if (t == nullptr) { return 0; }
    size_t leftH = height(t->left_);
    size_t rightH = height(t->right);
    return std::max(leftH, rightH) + 1;
}

template<class VertDataTy>
LBTNode<VertDataTy>* LBinTree<VertDataTy>::find_dfs(const VertDataTy& elem) {
    LBTNode<VertDataTy>* ptr = nullptr;
    try {
        find_dfs_recBody(this->_root, elem);
    } catch (LBTNode<VertDataTy>* result) {
        ptr = result;
    }
    return ptr;
}

template<class VertDataTy>
void LBinTree<VertDataTy>::find_dfs_recBody(LBTNode<VertDataTy>* t, const VertDataTy& elem) {
    if (t == nullptr) { return; }
    // IF {elem} is found, throw the pointer:
    if (t->data == elem) { throw t; }
    find_dfs_recBody(t->left_, elem);
    find_dfs_recBody(t->right, elem);
}

template<class VertDataTy>
LBTNode<VertDataTy>* LBinTree<VertDataTy>::find_bfs(const VertDataTy& elem) {
    if (this->_root == nullptr) { return nullptr; }
    std::deque<LBTNode<VertDataTy>*> que;
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

template<class VertDataTy>
LBTNode<VertDataTy>* LBinTree<VertDataTy>::findParent(LBTNode<VertDataTy>* target) {
    if (this->_root == nullptr) { return nullptr; }
    if (this->_root == target) { return nullptr; }
    std::deque<LBTNode<VertDataTy>*> que;
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

template<class VertDataTy>
void LBinTree<VertDataTy>::insert_to_left_(const VertDataTy& elem, LBTNode<VertDataTy>* parent) {
    auto node = new LBTNode<VertDataTy>{ elem,nullptr,nullptr };
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

template<class VertDataTy>
void LBinTree<VertDataTy>::insert_to_right(const VertDataTy& elem, LBTNode<VertDataTy>* parent) {
    auto node = new LBTNode<VertDataTy>{ elem,nullptr,nullptr };
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

template<class VertDataTy> // In template class {LBinTree},
template<class _Pred>  // there is a template function {re_pre__Order}:
void LBinTree<VertDataTy>::preOrder___recBody(LBTNode<VertDataTy>* t, const _Pred& pred) {
    if (t == nullptr) return;
    pred(t);
    this->preOrder___recBody(t->left_, pred);
    this->preOrder___recBody(t->right, pred);
}

template<class VertDataTy> // In template class {LBinTree},
template<class _Pred>  // there is a template function {re_pre__Order}:
void LBinTree<VertDataTy>::inOrder____recBody(LBTNode<VertDataTy>* t, const _Pred& pred) {
    if (t == nullptr) return;
    this->inOrder____recBody(t->left_, pred);
    pred(t);
    this->inOrder____recBody(t->right, pred);
}

template<class VertDataTy> // In template class {LBinTree},
template<class _Pred>  // there is a template function {re_pre__Order}:
void LBinTree<VertDataTy>::postOrder__recBody(LBTNode<VertDataTy>* t, const _Pred& pred) {
    if (t == nullptr) return;
    this->postOrder__recBody(t->left_, pred);
    this->postOrder__recBody(t->right, pred);
    pred(t);
}

template<class VertDataTy> // In template class {LBinTree},
template<class _Pred>  // there is a template function {re_pre__Order}:
void LBinTree<VertDataTy>::levelOrder_bfsBody(LBTNode<VertDataTy>* t, const _Pred& pred) {
    // IF the tree is empty, return directly:
    if (this->_root == nullptr) return;
    // Create a queue for board-first-serach:
    std::deque< LBTNode<VertDataTy>* > que;
    // Push non-empty root to {queue}:
    // [Note] The {push} operation creates A NEW POINTER, and copy the value from parameter.
    //        So you should never build a queue of reference (e.g., deque<int&> que),
    //        becase when pushing, you cannot create a NEW reference object!
    que.push_back(this->_root);
    // Loop while there is still nodes in queue:
    while (!que.empty()) {
        LBTNode<VertDataTy>* front = que.front(); // Get front node.
        que.pop_front();                      // Pop queue.
        pred(front);
        // Push queue @{
        if (front->left_ != nullptr) { que.push_back(front->left_); }
        if (front->right != nullptr) { que.push_back(front->right); }
        // @}
    }
}
