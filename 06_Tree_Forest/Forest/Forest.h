#pragma once
#include "Tree.h"
#include "ChildSiblingTree.h"
#include <iostream>
#include <stack>
#include <algorithm>

template<class _ElemTy>
class Forest : public ChildSiblingTree<_ElemTy>
{
public:
    using Base = ChildSiblingTree<_ElemTy>;

private:
    Base::NodePtr* rightestNode{ &(Base::_root) };

public:
    Forest() = default;
    Forest(const Forest&) = delete;
    Forest& operator=(const Forest&) = delete;

public:
    void insert(const Tree<_ElemTy>& tree) {
        typename Base::NodePtr treeRoot{};           // Set up a pointer to tree
        Base::transfer(tree, treeRoot);              // Transfer tree to binary
        *rightestNode = std::move(treeRoot);         // Move tree to {rightrestNode}
        rightestNode = &((*rightestNode)->sibling);  // Move {rightestNode} to right
    }

    void preorder_visit() const { rec_preorder_visit(Base::_root); }
    void inorder_visit() const { rec_inorder_visit(Base::_root); }
    void postorder_visit() const { rec_postorder_visit(Base::_root); }
    int64_t count_binTreeHeight() const { return rec_countBinTreeHeight(Base::_root); }
    int64_t count_binTreeLeaves() const { int64_t sum{ 0 };  rec_countBinTreeLeaves(Base::_root, sum); return sum; }

    int64_t count_treeNum() const {
        int64_t cnt{ 0 };
        for (auto root = Base::_root; root != nullptr; root = root->sibling) {
            ++cnt;
        }
        return cnt;
    }

    int64_t count_forestHeight() const {
        return Base::count_height();
    }

    int64_t count_forestLeaves() const {
        return Base::count_leaves();
    }

private:
    void rec_preorder_visit(typename Base::NodePtr root) const {
        if (root == nullptr) { return; }
        std::cout << root->data;
        rec_preorder_visit(root->child);
        rec_preorder_visit(root->sibling);
    }

    void rec_inorder_visit(typename Base::NodePtr root) const {
        if (root == nullptr) { return; }
        rec_inorder_visit(root->child);
        std::cout << root->data;
        rec_inorder_visit(root->sibling);
    }

    void rec_postorder_visit(typename Base::NodePtr root) const {
        if (root == nullptr) { return; }
        rec_postorder_visit(root->child);
        rec_postorder_visit(root->sibling);
        std::cout << root->data;
    }

    int64_t rec_countBinTreeHeight(typename Base::NodePtr root) const {
        if (root == nullptr) { return 0; }
        auto leftHeight = rec_countBinTreeHeight(root->child);
        auto rightHeight = rec_countBinTreeHeight(root->sibling);
        return std::max(leftHeight, rightHeight) + 1;
    }

    void rec_countBinTreeLeaves(typename Base::NodePtr root, int64_t& leavesNum) const {
        if (root == nullptr) { return; }
        if (root->child == nullptr && root->sibling == nullptr) {
            ++leavesNum;
            return;
        }
        rec_countBinTreeLeaves(root->child, leavesNum);
        rec_countBinTreeLeaves(root->sibling, leavesNum);
    }
};
