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
    using NodePtr = Base::NodePtr;

private:
    NodePtr* rightestNode{&(Base::_root)};

public:
    Forest() = default;
    Forest(const Forest&) = delete;
    Forest& operator=(const Forest&) = delete;

public:
    void insert(const Tree<_ElemTy>& tree) {
        NodePtr treeRoot{};
        Base::transfer(tree, treeRoot);
        *rightestNode = std::move(treeRoot);
        rightestNode = &((*rightestNode)->sibling);
    }

    void preorder_visit() const { rec_preorder_visit(Base::_root); }
    void inorder_visit() const { rec_inorder_visit(Base::_root); }
    void postorder_visit() const {
        std::stack<NodePtr> s;
        for(NodePtr* it = &(Base::_root); it!=nullptr; ++it){
            s.push(*it);
        }
        for(auto ptr: s) {
            
        }
    }

private:
    void rec_preorder_Visit(NodePtr root) const {
        if (root == nullptr) { return; }
        std::cout << root->data;
        rec_preorder_Visit(root->child);
        rec_preorder_Visit(root->sibling);
    }

    void rec_inorder_visit(NodePtr root) const {
        if (root == nullptr) { return; }
        rec_inorder_visit(root->child);
        std::cout << root->data;
        rec_inorder_visit(root->sibling);
    }

    void rec_postorder_visit(NodePtr root) const {
        if (root == nullptr) { return; }
        rec_postorder_visit(root->child);
        std::cout << root->data;
        rec_postorder_visit(root->sibling);
    }
};
