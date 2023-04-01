#pragma once
#include "Tree.h"
#include <memory>

template<class _ElemTy>
struct bNode
{
    using NodePtr = std::shared_ptr<bNode>;
    _ElemTy data;
    NodePtr child;
    NodePtr sibling;
};

template<class _ElemTy>
class Tree_binary
{
public:
    using Node = bNode<_ElemTy>;
    using NodePtr = std::shared_ptr<Node>;
    using const_NodePtr = std::shared_ptr<const Node>;

protected:
    NodePtr _root{nullptr};

public:
    Tree_binary() = default;
    Tree_binary(const Tree<_ElemTy>& tree) { transfer(tree, _root); }
    
    void transfer(const Tree<_ElemTy>& sourceTree, NodePtr& destRoot) {
        auto sourceRoot = sourceTree.get_root();
        if(sourceRoot == nullptr) { return; }  // Return if {tree} is empty
        destRoot = std::make_shared<Node>(sourceRoot->data);    // Create root
        destRoot->child = std::move(rec_build(sourceRoot->children.cbegin(), sourceRoot->children.cend()));
    }

public:
    NodePtr get_root() { 
        return _root; 
    }
    const_NodePtr get_root() const { 
        return _root; 
    }

    int64_t count_leaves() const { 
        int64_t cnt = 0;
        rec_count_leaves(get_root(), cnt); 
        return cnt;
    }

    int64_t count_height() const { 
        return rec_count_height(get_root()); 
    }
    
protected:
    NodePtr rec_build(std::vector<std::shared_ptr<TreeNode<_ElemTy>>>::const_iterator tnode,
                      std::vector<std::shared_ptr<TreeNode<_ElemTy>>>::const_iterator end);
    
    void rec_count_leaves(const_NodePtr root, int64_t& cnt) const;

    int64_t rec_count_height(const_NodePtr root) const;

};

template<class _ElemTy>
Tree_binary<_ElemTy>::NodePtr Tree_binary<_ElemTy>::rec_build(
    std::vector<std::shared_ptr<TreeNode<_ElemTy>>>::const_iterator tnode,
    std::vector<std::shared_ptr<TreeNode<_ElemTy>>>::const_iterator end
    ){
    if(tnode == end) { return nullptr; }
    NodePtr btnode = std::make_shared<Node>((*tnode)->data);
    btnode->child = std::move(rec_build((*tnode)->children.cbegin(), (*tnode)->children.cend()));
    btnode->sibling = std::move(rec_build(++tnode, end));
    return btnode;
}

template<class _ElemTy>
void Tree_binary<_ElemTy>::rec_count_leaves(const_NodePtr root, int64_t& cnt) const {
    if(root == nullptr) { return; }
    if(root->child == nullptr) { ++cnt; }
    rec_count_leaves(root->child, cnt);
    rec_count_leaves(root->sibling, cnt);
}

template<class _ElemTy>
int64_t Tree_binary<_ElemTy>::rec_count_height(const_NodePtr root) const {
    if(root == nullptr) { return 0; }
    if(root->child == nullptr) { return 1; }  // Leaves
    return std::max(rec_count_height(root->child) + 1, rec_count_height(root->sibling));
}

