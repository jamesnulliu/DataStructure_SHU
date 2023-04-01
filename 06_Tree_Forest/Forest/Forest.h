#pragma once
#include "Tree.h"
#include "Tree_binary.h"
#include <iostream>
#include <stack>

template<class _ElemTy>
class Forest : public Tree_binary<_ElemTy>
{
public:
    using Base = Tree_binary<_ElemTy>;

private:
    Base::NodePtr* rightestNode{&(Base::_root)};

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
};
